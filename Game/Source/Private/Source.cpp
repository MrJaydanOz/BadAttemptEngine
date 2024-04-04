#include "BAE/Engine.h"

int main(int argc, char* argv[])
{ return BAE_Initialize(); }

void BAE_Start()
{
	DEBUG_LOG_SUCCESS("GAME BAE_Start!");
}

void BAE_Update()
{
	DEBUG_LOG_SUCCESS("GAME BAE_Update!");
}

void BAE_LateUpdate()
{
	DEBUG_LOG_SUCCESS("GAME BAE_LateUpdate!");
}

void BAE_FixedUpdate()
{
	DEBUG_LOG_SUCCESS("GAME BAE_FixedUpdate!");
}

void BAE_End()
{
	DEBUG_LOG_SUCCESS("GAME BAE_End!");
}