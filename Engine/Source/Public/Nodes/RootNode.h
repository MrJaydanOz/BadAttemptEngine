#pragma once
#include "Nodes/Node.h"
#include "Game.h"

class RootNode : public Node
{
	friend Game;

private:
	RootNode() noexcept;
	~RootNode() noexcept;
};