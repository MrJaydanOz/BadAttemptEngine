#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Engine.h"))
#endif
#include "BAE.h"

int BAE_Initialize();

extern void BAE_Start();

extern void BAE_Update();

extern void BAE_LateUpdate();

extern void BAE_PhysicsUpdate();

extern void BAE_End();