#include "Nodes/BAE_Node.h"
#include <algorithm>
#include "BAE_Scene.h"
#include "BAE_Game.h"

namespace bae
{
	Node::Node(in<std::string> name) noexcept :
		_name(name),
		_children(),
		_parent(nullptr),
		_active(true),
		_location_type(_Node_Location_Type::_NODE_LOCATION_INVALID) { }

	Node::~Node() noexcept
	{
		NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnDestroy);

		_active = false;

		for (auto i = _children.begin(); i != _children.end(); i++)
			delete *i;

		_RemoveThisFromParent();
	}

	bool Node::HasName() const noexcept 
	{ return _name.length() > 0u; }
	const std::string& Node::GetName() const noexcept 
	{ return _name; }
	void Node::SetName(in<std::string> name) noexcept
	{ _name = name; }
	bool Node::NameIs(in<std::string> name) const noexcept
	{
		// Jesus christ, C++. Why can't I just safely equate empty strings?
		return _name.size() == 0
			? name.size() == 0
			: name.size() != 0 && _name.compare(name) == 0;
	}

	bool Node::HasParentNode() const noexcept 
	{ return GetParentNode() != nullptr; }
	Node* Node::GetParentNode() const noexcept
	{ return _parent; }
	bool Node::SetParentNode(in<Node*> parent) noexcept
	{
		if (_parent == parent)
			return false;

		_RemoveThisFromParent();
		_SetAsParent(_parent);

		NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnParentChanged);

		return true;
	}

	bool Node::IsPrefab() const noexcept 
	{ return _location_type == _Node_Location_Type::_NODE_LOCATION_CHILD_IN_PREFAB || _location_type == _Node_Location_Type::_NODE_LOCATION_SCENE_PREFAB; }

	bool Node::IsUpMostNode() const noexcept
	{ return _location_type == _Node_Location_Type::_NODE_LOCATION_SCENE_ROOT || _location_type == _Node_Location_Type::_NODE_LOCATION_SCENE_PREFAB; }

	const bae::List<Node*>& Node::GetChildren() const noexcept 
	{ return _children; }

	void Node::_RemoveThisFromParent() noexcept
	{
		if (_parent != nullptr)
		{
			if (_parent->_active)
				_parent->_children.Remove(this);
			_parent = nullptr;
		}
		else
		{
			if (Game::GetScene()->_isWorking)
			{
				switch (_location_type)
				{
				case _Node_Location_Type::_NODE_LOCATION_SCENE_ROOT:
				{
					Game::GetScene()->_rootNodes.Remove(this);

					break;
				}
				case _Node_Location_Type::_NODE_LOCATION_SCENE_PREFAB:
				{
					Game::GetScene()->_rootNodes.Remove(this);

					break;
				}
				}
			}
		}
	}

	void Node::_SetAsParent(in<Node*> parentNode) noexcept
	{
		if (parentNode != nullptr)
		{
			parentNode->_children.Append(this);
			this->_parent = parentNode;
			switch (_location_type)
			{
			case _Node_Location_Type::_NODE_LOCATION_INVALID:
			case _Node_Location_Type::_NODE_LOCATION_SCENE_ROOT: 
			case _Node_Location_Type::_NODE_LOCATION_CHILD_IN_ROOT:
				_location_type = _Node_Location_Type::_NODE_LOCATION_CHILD_IN_ROOT;
				break;
			case _Node_Location_Type::_NODE_LOCATION_SCENE_PREFAB: 
			case _Node_Location_Type::_NODE_LOCATION_CHILD_IN_PREFAB:
				_location_type = _Node_Location_Type::_NODE_LOCATION_CHILD_IN_PREFAB;
				break;
			}
		}
		else
		{
			this->_parent = nullptr;
			switch (_location_type)
			{
			case _Node_Location_Type::_NODE_LOCATION_INVALID:
			case _Node_Location_Type::_NODE_LOCATION_SCENE_ROOT: 
			case _Node_Location_Type::_NODE_LOCATION_CHILD_IN_ROOT:
				_location_type = _Node_Location_Type::_NODE_LOCATION_SCENE_ROOT;
				Game::GetScene()->_rootNodes.Append(this);
				break;
			case _Node_Location_Type::_NODE_LOCATION_SCENE_PREFAB: 
			case _Node_Location_Type::_NODE_LOCATION_CHILD_IN_PREFAB:
				_location_type = _Node_Location_Type::_NODE_LOCATION_SCENE_PREFAB;
				Game::GetScene()->_prefabs.Append(this);
				break;
			}
		}

		NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, OnParentChanged);
	}
}