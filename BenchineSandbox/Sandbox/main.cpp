// BubbleBobble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SandboxPCH.h"
#if _DEBUG
#include "vld.h"
#endif
#include "Sandbox.h"
#include "Core/Benchine.h"

int main(int, char* [])
{
	Benchine engine;
	engine.Run<Sandbox>();
	return 0;
}
