#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Scene.h"))
#endif
#include "Nodes/BAE_Node.h"
#include <vector>

namespace bae
{
	class Game;

	#if defined(MESSAGE_WHEN_CLASS_DEFINED)
	#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Scene))
	#endif
	class Scene
	{
		friend class Game;
		friend class Node;

	private:
		std::vector<Node*> _rootNodes;
		std::vector<Node*> _prefabs;
		bool _isWorking;

	public:
		_NODISCARD const std::vector<Node*>& GetRootNodes() const noexcept;

		template<typename T, typename TNodePredicate = bool(T*)>
		_NODISCARD T* FindRootNodeThat(in<TNodePredicate> predicate)
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
		_NODISCARD T* FindNodeThat(in<TNodePredicate> predicate)
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

		template<typename T, typename TNodePredicate = bool(T*), typename TResultCollection = std::vector<T*>>
		size_t FindRootNodesThat(in<TNodePredicate> predicate, ref<TResultCollection> results)
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

		template<typename T, typename TNodePredicate = bool(T*), typename TResultCollection = std::vector<T*>>
		size_t FindNodesThat(in<TNodePredicate> predicate, ref<TResultCollection> results)
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
						foundCount += child->FindChildrenThatRecursive<T, TNodePredicate>(results, predicate);
					}
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

			return foundCount;
		}

		template<typename T>
		_NODISCARD T* FindRootNodeOfType()
		{ return FindRootNodeThat<T, auto>([](T*) -> bool { return true; }); }

		template<typename T>
		_NODISCARD T* FindNodeOfType()
		{ return FindNodeThat<T, auto>([](T*) -> bool { return true; }); }

		template<typename T, typename TResultCollection = std::vector<T*>>
		size_t FindCRootNodesOfType(ref<TResultCollection> results)
		{ return FindRootNodesThat<T, auto, TResultCollection>([](T*) -> bool { return true; }, results); }

		template<typename T, typename TResultCollection = std::vector<T*>>
		size_t FindNodesOfType(ref<TResultCollection> results)
		{ return FindNodesThat<T, auto>([](T*) -> bool { return true; }, results); }

		template<typename T>
		_NODISCARD T* FindRootNodeWithName(in<std::string> name)
		{ return FindRootNodeThat<T>([&](T* node) -> bool { return node->GetName().compare(name) == 0; }); }

		template<typename T>
		_NODISCARD T* FindNodeWithName(in<std::string> name)
		{ return FindNodeThat<T>([&](T* node) -> bool { return node->GetName().compare(name) == 0; }); }

		template<typename T, typename TResultCollection = std::vector<T*>>
		size_t FindRootNodesWithName(in<std::string> name, ref<TResultCollection> results)
		{ return FindRootNodesThat<T>([&](T* node) -> bool { return node->GetName().compare(name) == 0; }); }

		template<typename T, typename TResultCollection = std::vector<T*>>
		size_t FindNodesWithName(in<std::string> name, ref<TResultCollection> results)
		{ return FindNodesThat<T>([&](T* node) -> bool { return node->GetName().compare(name) == 0; }); }

		template<typename T, typename... TConstructorArguments>
		T* AddNode(TConstructorArguments... arguments)
		{
			static_assert(std::is_base_of<Node, T>::value);
			T* newNode = new T(arguments...);
			newNode->_location_type = Node::_Node_Location_Type::_NODE_LOCATION_SCENE_ROOT;
			newNode->_SetAsParent(nullptr);
			NODE_TRIGGER_EVENT_WITH_TRY_CATCH(newNode, OnLoad);
			return newNode;
		}

		template<typename T>
		_NODISCARD T* GetPrefabWithName(in<std::string> name)
		{
			static_assert(std::is_base_of<Node, T>::value);

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

		template<typename T, typename... TConstructorArguments>
		T* AddPrefab(TConstructorArguments... arguments)
		{
			static_assert(std::is_base_of<Node, T>::value);
			T* newNode = new T(arguments...);
			newNode->_location_type = Node::_Node_Location_Type::_NODE_LOCATION_SCENE_PREFAB;
			newNode->_SetAsParent(nullptr);
			NODE_TRIGGER_EVENT_WITH_TRY_CATCH(newNode, OnLoad);
			return newNode;
		}

	private:
		Scene();
		~Scene();

		void ClearWorldPositionCaches() const noexcept;
	};
}