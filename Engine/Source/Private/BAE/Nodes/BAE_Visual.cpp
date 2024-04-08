#include "Nodes/BAE_Visual.h"
#include "BAE_Image.h"
#include "BAE_Graphics.h"

namespace bae
{
	Visual::Visual(in<std::string> name, in<bool> enabled) noexcept : 
		Behaviour::Behaviour(name, enabled),
		_zIndex(0) { }
	Visual::Visual(in<bool> enabled) noexcept : 
		Visual::Visual("", enabled) { }

	void Visual::OnEnabled()
	{
		Behaviour::OnEnabled();

		Game::GetGraphics()->_MarkVisualHasBeenModified(this);
	}

	void Visual::OnDisabled()
	{
		Behaviour::OnDisabled();
	
		Game::GetGraphics()->_MarkVisualHasBeenDeleted(this);
	}

	Visual::~Visual() noexcept
	{
		Behaviour::~Behaviour();
	}

	int Visual::GetZIndex() const noexcept
	{ return _zIndex; }

	void Visual::SetZIndex(in<int> index) noexcept
	{
		_zIndex = index;

		Game::GetGraphics()->_MarkVisualHasBeenModified(this);
	}
}