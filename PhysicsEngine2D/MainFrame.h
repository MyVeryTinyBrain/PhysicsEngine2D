#pragma once
#ifndef __MainFrame_h__
#define __MainFrame_h__

#include <iostream>
using std::cout;
using std::endl;

#include "MemoryDC.h"
#include "Input.h"

class MainFrame
{
public:
	void OnStart();
	void OnPaint(MemoryDC& hdc, int width, int height);
	void OnUpdate(float deltaTime, MemoryDC& hdc);
	void OnDestroy();
};

#endif
