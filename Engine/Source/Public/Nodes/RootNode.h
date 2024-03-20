#pragma once
#include "Nodes/Node.h"
#include "Game.h"

class RootNode : public Node
{
	friend class Game;

private:
	RootNode() noexcept;
	~RootNode() noexcept;
};