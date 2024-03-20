#pragma once
#include "Nodes/Node.h"

class Behaviour : public Node
{
private:
	bool _enabled;

public:
	virtual ~Behaviour() noexcept override;

	void SetEnabled(const bool& enabled) noexcept;
	bool IsEnabled(const bool& includeHerarchy = true) const noexcept;

	virtual void OnEnable() noexcept { };

	virtual void OnDisable() noexcept { };

	virtual void OnParentChanged() noexcept;;

protected:
	Behaviour(const std::string& name = "", bool enabled = true) noexcept;
};