#pragma once
#include "Nodes/Node.h"
#include "Game.h"

class Behaviour : public Node
{
	friend Game;

private:
	bool enabled;
	bool isFirstFrame;

public:
	void SetEnabled(const bool& enabled);
	bool IsEnabled(const bool& includeHerarchy = true) const;

	virtual void OnEnable() { };

	virtual void OnDisable() { };

protected:
	Behaviour(const std::string& name = "") noexcept;
};