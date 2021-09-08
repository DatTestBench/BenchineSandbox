#include "SandboxPCH.h"
#undef main

#if _DEBUG
#include "vld.h"
#endif
#include "Sandbox.h"
#include "Core/Benchine.h"

int main()
{
	Benchine engine;
	engine.Run<Sandbox>("Sandbox");
	return 0;
}
