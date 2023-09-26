#pragma once
#ifndef __Input_h__
#define __Input_h__
#define Input _Input::Instance()

#include <conio.h>

enum class KeyCode
{
	Left = 37,
	Up, Right, Down, 
	Zero = 48,
	One, Two, Tree, Four, Five, Six, Seven, Eight, Nine,
	A = 65,
	B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, T, U, V, W, X, Y, Z,
};

class _Input
{
	static _Input g_instance;
	bool m_keyPressing[0xFF];
public:
	static _Input& Instance();
	void UpdateKeyDown(int keyCode);
	void UpdateKeyUp(int keyCode);
	static bool GetKey(int keyCode);
	static bool GetKey(KeyCode keyCode);
};

#endif
