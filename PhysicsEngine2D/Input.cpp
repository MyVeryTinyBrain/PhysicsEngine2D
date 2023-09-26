#include "stdafx.h"
#include "Input.h"

_Input _Input::g_instance;

_Input& _Input::Instance()
{
	return g_instance;
}

void _Input::UpdateKeyDown(int keyCode)
{
	m_keyPressing[keyCode] = true;
}

void _Input::UpdateKeyUp(int keyCode)
{
	m_keyPressing[keyCode] = false;
}

bool _Input::GetKey(int keyCode)
{
	return g_instance.m_keyPressing[keyCode];
}

bool _Input::GetKey(KeyCode keyCode)
{
	return g_instance.m_keyPressing[(size_t)keyCode];
}
