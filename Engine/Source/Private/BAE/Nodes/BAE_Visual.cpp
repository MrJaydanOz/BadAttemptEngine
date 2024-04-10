#include "Nodes/BAE_Visual.h"
#include "BAE_Image.h"
#include "BAE_Graphics.h"

namespace bae
{
	Visual::Visual(in<Node*> parent) noexcept :
		Behaviour::Behaviour(parent),
		_zIndex(0) { }

	Visual::~Visual() noexcept { }

	void Visual::Create(in<const char*> name)
	{
		Behaviour::Create(name);
		SetZIndex(0);
	}

	void Visual::Destroy()
	{
		Behaviour::Destroy();
	}

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

	int Visual::GetZIndex() const noexcept
	{ return _zIndex; }

	void Visual::SetZIndex(in<int> index) noexcept
	{
		_zIndex = index;

		Game::GetGraphics()->_MarkVisualHasBeenModified(this);
	}
}