#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Scene.h"))
#endif
#include "Nodes/BAE_Node.h"
#include "BAE_Collections.h"

namespace bae
{
	class Game;

	#if defined(MESSAGE_WHEN_CLASS_DECLARED)
	#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Scene))
	#endif
	class Scene
	{
		friend class Game;
		friend class Node;

	private:
		bae::List<Node*> _rootNodes;
		bae::List<Node*> _prefabs;
		bae::List<Node*> _nodesToDelete;
		bool _isWorking;

	public:
		_NODISCARD const bae::List<Node*>& GetRootNodes() const noexcept;

		template<typename T, typename TNodePredicate = bool(T*)>
		_NODISCARD T* FindRootNodeThat(in<TNodePredicate> predicate) requires std::is_base_of_v<Node, T>
		{
			static_assert(std::is_base_of<Node, T>::value);

			for (Node* node : GetRootNodes())
				if (node != nullptr)
				{
					T* castedNode = dynamic_cast<T*>(node);
					if (castedNode != nullptr && predicate(castedNode))
						return castedNode;
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

			return nullptr;
		}

		template<typename T, typename TNodePredicate = bool(T*)>
		_NODISCARD T* FindNodeThat(in<TNodePredicate> predicate) requires std::is_base_of_v<Node, T>
		{
			static_assert(std::is_base_of<Node, T>::value);

			for (Node* node : GetRootNodes())
				if (node != nullptr)
				{
					T* castedNode = dynamic_cast<T*>(node);
					if (castedNode != nullptr && predicate(castedNode))
						return castedNode;
					else
					{
						castedNode = node->FindChildThatRecursive<T, TNodePredicate>(predicate);
						if (castedNode != nullptr)
							return castedNode;
					}
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

			return nullptr;
		}

		template<typename T, typename TNodePredicate = bool(T*), typename TResultCollection = bae::List<T*>>
		size_t FindRootNodesThat(in<TNodePredicate> predicate, ref<TResultCollection> results) requires std::is_base_of_v<Node, T>
		{
			static_assert(std::is_base_of<Node, T>::value);
			size_t foundCount = 0;

			for (Node* node : GetRootNodes())
				if (node != nullptr)
				{
					T* castedNode = dynamic_cast<T*>(node);
					if (castedNode != nullptr && predicate(castedNode))
					{
						results.push_back(castedNode);
						foundCount++;
					}
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

			return foundCount;
		}

		template<typename T, typename TNodePredicate = bool(T*), typename TResultCollection = bae::List<T*>>
		size_t FindNodesThat(in<TNodePredicate> predicate, ref<TResultCollection> results) requires std::is_base_of_v<Node, T>
		{
			static_assert(std::is_base_of<Node, T>::value);
			size_t foundCount = 0;

			for (Node* child : GetRootNodes())
				if (child != nullptr)
				{
					T* castedChild = dynamic_cast<T*>(child);
					if (castedChild != nullptr && predicate(castedChild))
					{
						results.push_back(castedChild);
						foundCount++;
					}
					else
					{
						foundCount += child->FindChildrenThatRecursive<T, TNodePredicate, TResultCollection>(predicate, results);
					}
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

			return foundCount;
		}

		template<typename T>
		_NODISCARD T* FindRootNodeOfType() requires std::is_base_of_v<Node, T>
		{ return FindRootNodeThat<T>([](T*) -> bool { return true; }); }

		template<typename T>
		_NODISCARD T* FindNodeOfType() requires std::is_base_of_v<Node, T>
		{ return FindNodeThat<T>([](T*) -> bool { return true; }); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindCRootNodesOfType(ref<TResultCollection> results) requires std::is_base_of_v<Node, T>
		{ return FindRootNodesThat<T, TResultCollection>([](T*) -> bool { return true; }, results); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindNodesOfType(ref<TResultCollection> results) requires std::is_base_of_v<Node, T>
		{ return FindNodesThat<T>([](T*) -> bool { return true; }, results); }

		template<typename T>
		_NODISCARD T* FindRootNodeWithName(in<std::string> name) requires std::is_base_of_v<Node, T>
		{ return FindRootNodeThat<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }

		template<typename T = Node>
		_NODISCARD T* FindNodeWithName(in<std::string> name) requires std::is_base_of_v<Node, T>
		{ return FindNodeThat<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindRootNodesWithName(in<std::string> name, ref<TResultCollection> results) requires std::is_base_of_v<Node, T>
		{ return FindRootNodesThat<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindNodesWithName(in<std::string> name, ref<TResultCollection> results) requires std::is_base_of_v<Node, T>
		{ return FindNodesThat<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }

		template<typename T>
		T* AddNode(in<const char*> name) requires std::is_base_of_v<Node, T>
		{
			T* newNode = Node::_ConstructNode<T>(nullptr);
			newNode->_location_type = Node::_Node_Location_Type::_NODE_LOCATION_SCENE_ROOT;
			newNode->_CallCreate(name);
			return newNode;
		}

		template<typename T>
		_NODISCARD T* GetPrefabWithName(in<std::string> name) requires std::is_base_of_v<Node, T>
		{
			for (Node* node : _prefabs)
				if (node != nullptr)
				{
					T* castedNode = dynamic_cast<T*>(node);
					if (castedNode != nullptr && castedNode->GetName() == name)
						return castedNode;
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

			return nullptr;
		}

		template<typename T>
		T* AddPrefab(in<const char*> name) requires std::is_base_of_v<Node, T>
		{
			T* newNode = Node::_ConstructNode<T>(nullptr);
			newNode->_location_type = Node::_Node_Location_Type::_NODE_LOCATION_SCENE_PREFAB;
			newNode->_CallCreate(name);
			return newNode;
		}

	private:
		Scene();
		~Scene();

		void _ProcessAnimation(in<float> deltaTime) noexcept;

		void _DeleteDestroyed() noexcept;
	};
}