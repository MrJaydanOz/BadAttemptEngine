#include "Nodes/Node.h"
#include <algorithm> 
#include <vector>
#include <string>
#include <type_traits>

Node::Node(const std::string& name) noexcept : _name(name), _children(nullptr), _parent(nullptr) { }

Node::~Node() noexcept
{
	if (_children != nullptr)
	{
		std::for_each(_children->begin(), _children->end(), [](Node* child)
		{
			delete child;
		});

		delete _children;
		_children = nullptr;
	}

	RemoveThisFromParent();
}

bool Node::HasName() const noexcept { return _name.length() > 0u; }

const std::string& Node::GetName() const noexcept { return _name; }

void Node::SetName(const std::string& name) noexcept { _name = name; }

bool Node::HasParent() const noexcept { return GetParent() != nullptr; }

Node* Node::GetParent() const noexcept { return _parent; }

void Node::SetParent(Node* node) noexcept
{
	if (_parent == node)
		return;

	RemoveThisFromParent();

	_parent = node;
	if (_parent != nullptr)
		_parent->AddAsChild(this);
}

const std::vector<Node*>* Node::GetChildren() const noexcept { return _children; }

template<typename T>
T* Node::FindChildOfType() const noexcept
{
	auto removeIndex = std::find(GetChildren()->begin(), GetChildren()->end(), this);

	return nullptr;
	//if (removeIndex != siblings->end())
}

template<typename T>
bool Node::FindChildrenOfType(const std::vector<T*>& results) const noexcept
{
	return false;
}

template<typename T>
T* Node::FindChildByName(const std::string& name) const noexcept
{
	return nullptr;
}

template<typename T>
bool Node::FindChildrenByName(const std::string& name, const std::vector<T*>& results) const noexcept
{
	return false;
}

template<typename T, class ...ConstructorArgs>
T* Node::CreateNode(ConstructorArgs... args) noexcept
{
	static_assert(std::is_base_of<Node, T>::value);
	T* newNode = new T(args...);
	AddAsChild(newNode);
	return nullptr;
}

void Node::RemoveThisFromParent() noexcept
{
	if (!HasParent())
		return;

	std::vector<Node*>* siblings = _parent->_children;

	if (siblings == nullptr)
		return;

	auto removeIndex = std::find(siblings->begin(), siblings->end(), this);

	if (removeIndex != siblings->end())
		siblings->erase(removeIndex);
}

void Node::AddAsChild(Node* node) noexcept
{
	_children->push_back(node);
}