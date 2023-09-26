#include "stdafx.h"
#include "MainFrame.h"

#include <vector>
#include <algorithm>
#include <cassert>

#include "Body.h"
#include "Ball.h"
#include "Wall.h"
#include "Capsule.h"
#include "Box.h"

#include "Shape.h"
#include "Circle.h"
#include "Line.h"
#include "Rect.h"
#include "RegularPolygon.h"
#include "Star.h"

#include "Math.h"

std::vector<Body*> bodies;

void MainFrame::OnStart()
{
	Capsule* capsule = new Capsule({ 500,100 }, { 700,100 }, 50);
	//capsule->player = true;
	bodies.push_back(capsule);
	bodies.push_back(new Capsule({ 800,100 }, { 1000,200 }, 50));

	Box* box1 = new Box(500, 300, 600, 200);
	//box1->player = true;
	bodies.push_back(box1);
	Box* box2 = new Box(700, 300, 800, 200);
	bodies.push_back(box2);

	Ball* ball = new Ball(500, 400, 50);
	ball->player = true;
	bodies.push_back(ball);
	bodies.push_back(new Ball(700, 400, 50));

	Wall* wall1 = new Wall(500, 500, 700, 500);
	wall1->setMass(0);
	//wall1->player = true;
	bodies.push_back(wall1);
	Wall* wall2 = new Wall(800, 200, 1200, 200);
	wall2->setMass(0);
	//wall2->player = true;
	bodies.push_back(wall2);

	RegularPolygon* polygon3 = new RegularPolygon(500, 500, 50, 90 * DEG2RAD, 3);
	//polygon3->player = true;
	bodies.push_back(polygon3);

	RegularPolygon* polygon5 = new RegularPolygon(600, 500, 50, 0, 5);
	//polygon5->player = true;
	bodies.push_back(polygon5);

	Star* star = new Star(800, 600, 100);
	//star->player = true;
	bodies.push_back(star);
}

Vector2 ClosetPointBetweenPointAndLine(Vector2 point, Vector2 p1, Vector2 p2)
{
	Vector2 lineDir = (p2 - p1).normalized();
	if (lineDir.sqrMagnitude() == 0) return p1;
	Vector2 p1ToP = point - p1;
	if (Vector2::Dot(lineDir, p1ToP) < 0) return p1;
	Vector2 p2ToP = point - p2;
	if (Vector2::Dot(lineDir, p2ToP) > 0) return p2;
	Vector2 movedPoint = point - p1;
	Vector2 projOnOrigin = Vector2::Project(movedPoint, lineDir);
	projOnOrigin += p1;
	return projOnOrigin;
}

// Line1 = { p1, p2 }, Line2 = { q1, q2 } 일때
// out_closePoint1: Line1에서 Line2까지 가장 가까운 두 점의 시작점
// out_closePoint2: Line1에서 Line2까지 가장 가까운 두 점의 끝점
// return: out_closetPoint1, out_closetPoint2 사이의 거리
float ClosetPointBetweenTwoLines(Vector2 p1, Vector2 p2, Vector2 q1, Vector2 q2, Vector2* out_closetPoint1, Vector2* out_closetPoint2)
{
	float shortestDistance = (p1 - ClosetPointBetweenPointAndLine(p1, q1, q2)).magnitude();
	Vector2 closetPoints[2] = { p1, ClosetPointBetweenPointAndLine(p1,q1,q2) };
	if (shortestDistance > (p2 - ClosetPointBetweenPointAndLine(p2, q2, q2)).magnitude())
	{
		shortestDistance = (p2 - ClosetPointBetweenPointAndLine(p2, q2, q2)).magnitude();
		closetPoints[0] = p2;
		closetPoints[1] = ClosetPointBetweenPointAndLine(p2, q2, q2);
	}
	if (shortestDistance > (q1 - ClosetPointBetweenPointAndLine(q1, p1, p2)).magnitude())
	{
		shortestDistance = (q1 - ClosetPointBetweenPointAndLine(q1, p1, p2)).magnitude();
		closetPoints[0] = ClosetPointBetweenPointAndLine(q1, p1, p2);
		closetPoints[1] = q1;
	}
	if (shortestDistance > (q2 - ClosetPointBetweenPointAndLine(q2, p1, p2)).magnitude())
	{
		shortestDistance = (q2 - ClosetPointBetweenPointAndLine(q2, p1, p2)).magnitude();
		closetPoints[0] = ClosetPointBetweenPointAndLine(q2, p1, p2);
		closetPoints[1] = q2;
	}
	if (out_closetPoint1) *out_closetPoint1 = closetPoints[0];
	if (out_closetPoint2) *out_closetPoint2 = closetPoints[1];
	return shortestDistance;
}

// out_minLength: axis(normalized)에 object의 점들을 사영했을때 가장 길이가 짧은 것
// out_maxLength: ... 가장 길이가 긴 것
void ProjectShapeOntoAxis(Vector2 axis, Shape* object, float* out_minLength, float* out_maxLength, Vector2* out_colVertex)
{
	size_t vertexCount = object->vertexCount() == 0 ? 2 : object->vertexCount();
	auto vertex = [&](size_t index) -> Vector2
	{
		if (object->vertexCount() == 0)
		{
			if (index == 0) return object->position() + axis.normalized() * object->radius() * (-1);
			if (index == 1) return object->position() + axis.normalized() * object->radius() * (+1);
			bool wtf_error = false;
			assert(wtf_error);
		}
		else return object->vertex(index);
		return {};
	};
	float minLength = Vector2::Dot(axis, vertex(0));
	float maxLength = minLength;
	if (out_colVertex) *out_colVertex = vertex(0);
	for (size_t i = 0; i < vertexCount; ++i)
	{
		float p = Vector2::Dot(axis, vertex(i)); // 한 점을 축에 사영한 길이
		if (p < minLength)
		{
			minLength = p;
			if (out_colVertex) *out_colVertex = vertex(i);
		}
		if (p > maxLength)
		{
			maxLength = p;
		}
	}
	if (out_minLength) *out_minLength = minLength;
	if (out_maxLength) *out_maxLength = maxLength;
}

// object의 점들 중에서 p에 가장 가까운 점을 반환한다
Vector2 ClosetVertexToPoint(Shape* object, Vector2 p)
{
	float minSqrDist = FLT_MAX;
	Vector2 closetVertex;
	for (size_t i = 0; i < object->vertexCount(); ++i)
	{
		float dist = (p - object->vertex(i)).sqrMagnitude();
		if (dist < minSqrDist)
		{
			minSqrDist = dist;
			closetVertex = object->vertex(i);
		}
	}
	return closetVertex;
}

typedef struct tagSATData
{
	Vector2 CollidedVertex;
	Vector2 PenetrationDirection;
	float Penetration;
}SATData;

bool SAT(Shape* object1, Shape* object2, SATData* out_SATData)
{
	// Find axes ===================================================================================
	std::vector<Vector2> axis;
	auto addNormals = [&](Shape* obj) -> void
	{
		size_t vertexCount = obj->vertexCount();
		if (obj->vertexCount() == 0) return;
		if (obj->vertexCount() % 2 == 0) vertexCount /= 2;
		for (size_t i = 0; i < vertexCount; ++i)
		{
			size_t next = i + 1;
			if (next == obj->vertexCount()) next = 0;
			Vector2 dir = (obj->vertex(next) - obj->vertex(i)).normalized();
			axis.push_back(dir.normal());
		}
	};
	auto findAxis = [&](Shape* obj1, Shape* obj2) -> void
	{
		if (obj1->vertexCount() == 0)
		{
			Vector2 oneAxis = (ClosetVertexToPoint(obj2, obj1->position()) - obj1->position()).normalized();
			if (oneAxis.sqrMagnitude() == 0) oneAxis = Vector2(1, 0);
			axis.push_back(oneAxis);
		}
		else addNormals(obj1);
	};
	if (object1->vertexCount() == 0 && object2->vertexCount() == 0)
	{
		Vector2 oneAxis = (object2->position() - object1->position()).normalized();
		if (oneAxis.sqrMagnitude() == 0) oneAxis = Vector2(1, 0);
		axis.push_back(oneAxis);
	}
	else
	{
		findAxis(object1, object2);
		findAxis(object2, object1);
	}
	// Find axes ===================================================================================

	// SAT =========================================================================================
	float	shortOverlap =		FLT_MAX;
	Vector2 shortOverlapAxis;
	Shape*	colObj =			nullptr;
	float	proj1min, proj1max, proj2min, proj2max, overlap;
	for (size_t i = 0; i < axis.size(); ++i)
	{
		ProjectShapeOntoAxis(axis[i], object1, &proj1min, &proj1max, nullptr);
		ProjectShapeOntoAxis(axis[i], object2, &proj2min, &proj2max, nullptr);
		overlap = min(proj1max, proj2max) - max(proj1min, proj2min);
		if (overlap < 0) return false;	
		if ((proj1max > proj2max && proj1min < proj2min) || (proj1max < proj2max && proj1min > proj2min))
		{
			float mins = fabsf(proj1min - proj2min);
			float maxs = fabsf(proj1max - proj2max);
			if (mins < maxs)
			{
				overlap += mins;
			}
			else
			{
				overlap += maxs;
				axis[i] *= -1;
			}
		}	
		if (overlap < shortOverlap)
		{
			shortOverlap = overlap;
			shortOverlapAxis = axis[i];
			if (i < object1->vertexCount())
			{
				colObj = object2;
				if (proj1max > proj2max)
					shortOverlapAxis = axis[i] * -1;
			}
			else
			{
				colObj = object1;
				if (proj1max < proj2max)
					shortOverlapAxis = axis[i] * -1;
			}
		}
	}
	// SAT =========================================================================================

	if(out_SATData)
	{
		ProjectShapeOntoAxis(shortOverlapAxis, colObj, nullptr, nullptr, &out_SATData->CollidedVertex);
		if (colObj == object2)
			shortOverlapAxis *= -1;
		out_SATData->PenetrationDirection = shortOverlapAxis;
		out_SATData->Penetration = shortOverlap;
	}

	return true;
}

void MainFrame::OnPaint(MemoryDC& hdc, int width, int height)
{
	for (auto& body : bodies)
		body->Draw(hdc);
}

void KeyControlVel(Body& body)
{
	const static float speed = 2.5f;
	const Vector2& velocity = body.velocity();
	Vector2 acceleration = {};
	if (Input.GetKey(KeyCode::Up)) acceleration.y = +1;
	if (Input.GetKey(KeyCode::Down)) acceleration.y = -1;
	if (Input.GetKey(KeyCode::Left)) acceleration.x = -1;
	if (Input.GetKey(KeyCode::Right)) acceleration.x = +1;
	acceleration.Normalize();
	body.setVelocity(velocity + acceleration * speed);
}

void KeyControlAng(Body& body)
{
	const static float speed = 2.5f;
	const float& angularVelocity = body.angularVelcoity();
	float acceleration = 0;
	if (Input.GetKey(KeyCode::A)) acceleration = speed * DEG2RAD;
	if (Input.GetKey(KeyCode::D)) acceleration = -speed * DEG2RAD;
	body.setAngularVelocity(angularVelocity + acceleration);
}

void PenetrationResolution(Body* body, Body* other, const SATData* sat)
{
	const float& bodyInvMass = body->invMass();
	const float& otherInvMass = other->invMass();
	float invMassSum = bodyInvMass + otherInvMass;
	if (invMassSum == 0) return;
	Vector2 penetrationResolution = sat->PenetrationDirection * (sat->Penetration / invMassSum);
	Vector2 bodyPosition = body->position() + penetrationResolution * bodyInvMass;
	Vector2 otherPosition = other->position() - penetrationResolution * otherInvMass;
	body->setPosition(bodyPosition);
	other->setPosition(otherPosition);
}

void CollisionResolution(Body* body, Body* other, const SATData* sat)
{
	const Vector2& p1 = body->position();
	const Vector2& p2 = other->position();
	const Vector2& v1 = body->velocity();
	const Vector2& v2 = other->velocity();
	const float& av1 = body->angularVelcoity();
	const float& av2 = other->angularVelcoity();
	const float& invInertia1 = body->invInertia();
	const float& invInertia2 = other->invInertia();
	const float& invMass1 = body->invMass();
	const float& invMass2 = other->invMass();
	const float& e1 = body->elastisity();
	const float& e2 = other->elastisity();
	const Vector2& contact = sat->CollidedVertex;
	const Vector2& normal = sat->PenetrationDirection;

	// 1. Closing velocity
	Vector2 collArm1 = contact - p1;
	Vector2 rotVel1 = { -av1 * collArm1.y, av1 * collArm1.x };
	Vector2 closVel1 = v1 + rotVel1;
	Vector2 collArm2 = contact - p2;
	Vector2 rotVel2 = { -av2 * collArm2.y,av2 * collArm2.x };
	Vector2 closVel2 = v2 + rotVel2;

	// 2. Impulse augmentation
	float impAug1 = Vector2::CrossZ(collArm1, normal);
	impAug1 = impAug1 * invInertia1 * impAug1;
	float impAug2 = Vector2::CrossZ(collArm2, normal);
	impAug2 = impAug2 * invInertia2 * impAug2;

	Vector2 relVec = closVel1 - closVel2;
	float sep = Vector2::Dot(relVec, normal);
	float newSep = -sep * min(e1, e2);
	float sepDiff = newSep - sep;

	float impulse = sepDiff / (invMass1 + invMass2 + impAug1 + impAug2);
	Vector2 impulseVec = normal * impulse;

	// 3. Changing the velocities
	body->setVelocity(v1 + impulseVec * invMass1);
	other->setVelocity(v2 - impulseVec * invMass2);
	body->setAngularVelocity(av1 + invInertia1 * Vector2::CrossZ(collArm1, impulseVec));
	other->setAngularVelocity(av2 - invInertia2 * Vector2::CrossZ(collArm2, impulseVec));
}

void MainFrame::OnUpdate(float deltaTime, MemoryDC& hdc)
{
	for (auto& body : bodies)
	{
		if (body->player)
		{
			KeyControlVel(*body);
			KeyControlAng(*body);
		}
		body->Reposition();
		for (size_t i = 0; i < body->shapeCount(); ++i)
		{
			for (auto& other : bodies)
			{
				if (body == other) continue;
				SATData satData = {};
				for (size_t j = 0; j < other->shapeCount(); ++j)
				{
					SATData tempSATData = {};
					if (SAT(body->shape(i), other->shape(j), &tempSATData))
					{
						if (tempSATData.Penetration > satData.Penetration)
							satData = tempSATData;
					}
				}
				if (satData.Penetration > 0.00001f)
				{
					hdc.SetBrush(MemoryBrush::MakeNullBrush());
					hdc.SetPen(255, 0, 0, 1);
					hdc.DrawCircle(satData.CollidedVertex.x, satData.CollidedVertex.y, 5);
					PenetrationResolution(body, other, &satData);
					CollisionResolution(body, other, &satData);
				}
			}
		}
	}
}

void MainFrame::OnDestroy()
{
	std::for_each(bodies.begin(), bodies.end(), [](Body* body) -> void { if (body) delete body; });
}
