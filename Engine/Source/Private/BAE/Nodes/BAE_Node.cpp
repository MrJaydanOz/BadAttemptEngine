#include "Nodes/BAE_Node.h"
#include <algorithm>

namespace bae
{
	Node::Node(in<std::string> name) noexcept :
		_name(name),
		_children(),
		_parent(nullptr),
		_active(true)
	{
		NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnLoad);
	}

	Node::~Node() noexcept
	{
		NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnDestroy);

		_active = false;

		for (auto i = _children.rbegin(); i != _children.rend(); ++i)
			delete* i;

		_RemoveThisFromParent();
	}

	bool Node::HasName() const noexcept 
	{ return _name.length() > 0u; }
	const std::string& Node::GetName() const noexcept 
	{ return _name; }
	void Node::SetName(in<std::string> name) noexcept
	{ _name = name; }

	bool Node::HasParent() const noexcept 
	{ return GetParent() != nullptr; }
	Node* Node::GetParent() const noexcept
	{ return _parent; }
	void Node::SetParent(Node* parent) noexcept
	{
		if (_parent == parent)
			return;

		_RemoveThisFromParent();

		if (parent == nullptr)
			_parent = nullptr;
		else
			parent->_AddAsChild(this);

		NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnParentChanged)
	}

	const std::vector<Node*>& Node::GetChildren() const noexcept 
	{ return _children; }

	void Node::_RemoveThisFromParent() noexcept
	{
		if (!HasParent())
			return;

		std::vector<Node*>& siblings = _parent->_children;

		auto removeIndex = std::find(siblings.begin(), siblings.end(), this);

		if (removeIndex != siblings.end())
			siblings.erase(removeIndex);

		_parent = nullptr;
	}

	void Node::_AddAsChild(Node* childNode) noexcept
	{
		_children.push_back(childNode);
		childNode->_parent = this;
		NODE_TRIGGER_EVENT_WITH_TRY_CATCH(childNode, OnParentChanged)
	}
}