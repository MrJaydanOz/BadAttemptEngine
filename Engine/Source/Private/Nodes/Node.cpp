#include "Nodes/Node.h"
#include <algorithm>

namespace bae
{
	Node::Node(const std::string& name) noexcept :
		_name(name),
		_children(),
		_parent(nullptr),
		_active(true) { }

	Node::~Node() noexcept
	{
		_active = false;

		for (auto i = _children.rbegin(); i != _children.rend(); ++i)
			delete* i;

		RemoveThisFromParent();
	}

	_NODISCARD bool Node::HasName() const noexcept { return _name.length() > 0u; }

	_NODISCARD const std::string& Node::GetName() const noexcept { return _name; }

	void Node::SetName(const std::string& name) noexcept { _name = name; }

	_NODISCARD bool Node::HasParent() const noexcept { return GetParent() != nullptr; }

	Node* Node::GetParent() const noexcept { return _parent; }
	void Node::SetParent(Node* node) noexcept
	{
		if (_parent == node)
			return;

		RemoveThisFromParent();

		if (node == nullptr)
			_parent = nullptr;
		else
			node->AddAsChild(this);

		OnParentChanged();
	}

	const std::vector<Node*>& Node::GetChildren() const noexcept { return _children; }

	void Node::RemoveThisFromParent() noexcept
	{
		if (!HasParent())
			return;

		std::vector<Node*>& siblings = _parent->_children;

		auto removeIndex = std::find(siblings.begin(), siblings.end(), this);

		if (removeIndex != siblings.end())
			siblings.erase(removeIndex);

		_parent = nullptr;
	}

	void Node::AddAsChild(Node* childNode) noexcept
	{
		_children.push_back(childNode);
		childNode->_parent = this;
		OnParentChanged();
	}
}