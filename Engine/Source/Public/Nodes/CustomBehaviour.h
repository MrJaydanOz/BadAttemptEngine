﻿#pragma once
#include "Game.h"
#include "Nodes/Behaviour.h"

class CustomBehaviour : public Behaviour
{
	friend class Game;

private:
	bool _isFirstFrame;

protected:
	virtual int UpdateOrder() { return 0; }

public:
	CustomBehaviour

/*
┏[Activation]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃  Triggers when is first created.                      ┃
┃  - [Constructor]*/(const std::string& name = "")/*; - ┃                      */noexcept; public:/*
┃                                                       ┃
┃  Triggers when is enabled in the hierarchy.           ┃
┃  - virtual void OnEnable() { } -                      ┃
┃                                                       ┃
┃  Triggers once after the constructor and before the   ┃
┃  first frame this is enabled for.                     ┃
┃  */virtual void OnFirst() { }/*                       ┃
┃                                                       ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
							 ↓
┏[Loop]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃  Triggers after every physics update.                 ┃ <─┐
┃  */virtual void OnPhysicsUpdate() { }/*               ┃   │
┃                                                       ┃   │
┃  Triggers every frame.                                ┃   │
┃  */virtual void OnUpdate() { }/*                      ┃ ──┘
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
							 ↓
┏[Deactivation]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃  Triggers when is disabled in the hierarchy.          ┃
┃  - virtual void OnDisable() { } -                     ┃
┃                                                       ┃
┃  Triggers when is deleted directly or by a parent.    ┃
┃  - ~[Destructor]() -                                  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/
};