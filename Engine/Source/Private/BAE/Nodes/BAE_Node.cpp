#include "Nodes/BAE_Node.h"
#include <algorithm>
#include "BAE_Scene.h"
#include "BAE_Game.h"
#include "BAE_Debug.h"

namespace bae
{
	Node::Node(in<Node*> parent) noexcept :
		_parent(parent),
		_name(""),
		_children(),
		_statusFlags(0b01),
		_location_type(_Node_Location_Type::_NODE_LOCATION_INVALID) { }

	Node::~Node() noexcept { }

	void Node::Create(in<const char*> name)
	{
		_name = std::string(name);
		_SetAsParent(_parent);

		_statusFlags |= (1 << 0);
	}

	void Node::Destroy()
	{
		if (!_AllowDelete())
			throw new std::exception("Nodes cannot be deleted via the delete operator. Use bae::Destroy(Node*&) instead.");

		_statusFlags &= ~(1 << 0);

		Scene* scene = Game::GetScene();

		for (auto& child : _children)
			Destroy(child);

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
			if (_parent->_IsActive())
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
					Game::GetScene()->_prefabs.Remove(this);

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

	void Node::_CallDestroy()
	{
		NODE_TRIGGER_EVENT_WITH_TRY_CATCH(this, Destroy);

		if (_IsActive())
			DEBUG_LOG_ERROR_CONTEXTED(BAE_LOG_CONTEXT,
				"A node has been destroyed with Destroy() has not also called its base::Destroy(). "
				"All nodes have to call their base::Destroy().");
	}

	constexpr bool Node::_IsActive() const
	{ return (_statusFlags & (1 << 0)) != 0; }
	constexpr bool Node::_AllowDelete() const
	{ return (_statusFlags & (1 << 1)) != 0; }
}