#pragma once
#include "Nodes/Node.h"

class Behaviour : public Node
{
private:
	bool _enabled;
	bool _isFirstFrame;

public:
	virtual ~Behaviour() noexcept override;

	void SetEnabled(const bool& enabled);
	bool IsEnabled(const bool& includeHerarchy = true) const;

	virtual void OnEnable() { };

	virtual void OnDisable() { };

protected:
	Behaviour(const std::string& name = "") noexcept;
};