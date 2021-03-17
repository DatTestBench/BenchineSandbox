#include "SandboxPCH.h"
#undef main
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
