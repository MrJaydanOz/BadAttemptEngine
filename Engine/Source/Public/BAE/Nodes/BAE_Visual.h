#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Visual.h"))
#endif
#include "Nodes/BAE_Behaviour.h"
#include "Math/BAE_VectorT.h"
#include "Math/BAE_RectT.h"
#include "Math/BAE_PoseT.h"

namespace bae
{
	class Graphics;

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Visual))
#endif
	class Visual : public Behaviour
	{
		NODE_BEGIN;
		friend class Graphics;

	private:
		int _zIndex;

	public:
		_NODISCARD int GetZIndex() const noexcept;
		void SetZIndex(in<int> index) noexcept;

	protected:
		Visual(in<Node*> parent) noexcept;
		virtual ~Visual() noexcept override;
		virtual void Create(in<const char*> name = "") override;
		virtual void Destroy() override;

		virtual void OnEnabled() override;

		virtual void OnDisabled() override;

		virtual void Render() = 0;
	};
}