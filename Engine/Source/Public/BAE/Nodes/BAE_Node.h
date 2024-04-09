#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Node.h"))
#endif
#include <string>
#include "BAE_Collections.h"
#include "BAE_Debug.h"

#define NODE_TRIGGER_EVENT_WITH_TRY_CATCH(nodePointer, functionName, ...) \
try { nodePointer->functionName(__VA_ARGS__); } \
catch (in<std::exception> exception) \
{ DEBUG_LOG_EXCEPTION_CONTEXTED(DEBUG_NODE_NAME(nodePointer) << '.' << #functionName << "()", exception); }

#define NODE_BEGIN \
friend class Node;  /* This allows for Node::AddChild() and Scene::AddNode() to access the node's */\
friend class Scene  /* constructor which should be protected. */

namespace bae
{
	class Scene;

#if defined(MESSAGE_WHEN_CLASS_DEFINED)
#pragma message(MESSAGE_WHEN_CLASS_DEFINED(class Node))
#endif
	class Node
	{
		friend class Scene;

	private:
		enum class _Node_Location_Type : bae::int_fit_t<4>
		{
			_NODE_LOCATION_INVALID,
			_NODE_LOCATION_SCENE_ROOT,
			_NODE_LOCATION_SCENE_PREFAB,
			_NODE_LOCATION_CHILD_IN_ROOT,
			_NODE_LOCATION_CHILD_IN_PREFAB
		};

	private:
		std::string _name;
		bae::List<Node*> _children;
		Node* _parent;
		bool _active;
		_Node_Location_Type _location_type;

	public:
		virtual ~Node() noexcept;

		_NODISCARD bool HasName() const noexcept;
		_NODISCARD const std::string& GetName() const noexcept;
		void SetName(in<std::string> name) noexcept;
		_NODISCARD bool NameIs(in<std::string> name) const noexcept;

		_NODISCARD bool HasParentNode() const noexcept;
		_NODISCARD Node* GetParentNode() const noexcept;
		bool SetParentNode(in<Node*> parent) noexcept;

		_NODISCARD bool IsPrefab() const noexcept;
		_NODISCARD bool IsUpMostNode() const noexcept;

		_NODISCARD const bae::List<Node*>& GetChildren() const noexcept;

		template<typename T, typename TNodePredicate = bool(T*)>
		_NODISCARD T* FindChildThat(in_delegate<TNodePredicate> predicate) const noexcept
		{
			static_assert(std::is_base_of<Node, T>::value);

			for (Node* child : GetChildren())
				if (child != nullptr)
				{
					T* castedChild = dynamic_cast<T*>(child);
					if (castedChild != nullptr && predicate(castedChild))
						return castedChild;
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");

			return nullptr;
		}

		template<typename T, typename TNodePredicate = bool(T*)>
		_NODISCARD T* FindChildThatRecursive(in_delegate<TNodePredicate> predicate) const noexcept
		{
			static_assert(std::is_base_of<Node, T>::value);

			for (Node* child : GetChildren())
				if (child != nullptr)
				{
					T* castedChild = dynamic_cast<T*>(child);
					if (castedChild != nullptr && predicate(castedChild))
						return castedChild;
					else
					{
						castedChild = child->FindChildThatRecursive<T, TNodePredicate>(predicate);
						if (castedChild != nullptr)
							return castedChild;
					}
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");

			return nullptr;
		}

		template<typename T, typename TNodePredicate = bool(T*)>
		bool TryFindChildThat(in_delegate<TNodePredicate> predicate, out<T*> result) const noexcept
		{ return (result = FindChildThat<T, TNodePredicate>(predicate)) != nullptr; }

		template<typename T, typename TNodePredicate = bool(T*)>
		bool TryFindChildThatRecursive(in_delegate<TNodePredicate> predicate, out<T*> result) const noexcept
		{ return (result = FindChildThatRecursive<T, TNodePredicate>(predicate)) != nullptr; }

		template<typename T, typename TNodePredicate = bool(T*), typename TResultCollection = bae::List<T*>>
		size_t FindChildrenThat(in_delegate<TNodePredicate> predicate, ref<TResultCollection> results) const noexcept
		{
			static_assert(std::is_base_of<Node, T>::value);
			size_t foundCount = 0;

			for (Node* child : GetChildren())
				if (child != nullptr)
				{
					T* castedChild = dynamic_cast<T*>(child);
					if (castedChild != nullptr && predicate(castedChild))
					{
						results.push_back(castedChild);
						foundCount++;
					}
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");

			return foundCount;
		}

		template<typename T, typename TNodePredicate = bool(T*), typename TResultCollection = bae::List<T*>>
		size_t FindChildrenThatRecursive(in_delegate<TNodePredicate> predicate, ref<TResultCollection> results) const noexcept
		{
			static_assert(std::is_base_of<Node, T>::value);
			size_t foundCount = 0;

			for (Node* child : GetChildren())
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
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");

			return foundCount;
		}

		template<typename T, typename TNodePredicate = bool(T*)>
		_NODISCARD T* FindParentThatRecursive(in_delegate<TNodePredicate> predicate) const noexcept
		{
			static_assert(std::is_base_of<Node, T>::value);

			Node* parent = GetParentNode();

			while (parent != nullptr)
			{
				T* castedParent = dynamic_cast<T*>(parent);
				if (castedParent != nullptr && predicate(castedParent))
					return castedParent;

				parent = parent->GetParentNode();
			}

			return nullptr;
		}
		
		template<typename T, typename TNodePredicate = bool(T*)>
		bool TryFindParentThatRecursive(in_delegate<TNodePredicate> predicate, out<T*> result) const noexcept
		{ return (result = FindParentThatRecursive<T, TNodePredicate>(predicate)) != nullptr; }

		template<typename T>
		_NODISCARD T* FindChildOfType() const noexcept
		{ return FindChildThat<T>([](T*) -> bool { return true; }); }
		
		template<typename T>
		_NODISCARD T* FindChildOfTypeRecursive() const noexcept
		{ return FindChildThatRecursive<T>([](T*) -> bool { return true; }); }
		
		template<typename T>
		bool TryFindChildOfType(out<T*> result) const noexcept
		{ return TryFindChildThat<T>([](T*) -> bool { return true; }, result); }

		template<typename T>
		bool TryFindChildOfTypeRecursive(out<T*> result) const noexcept
		{ return TryFindChildThatRecursive<T>([](T*) -> bool { return true; }, result); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindChildrenOfType(ref<TResultCollection> results) const noexcept
		{ return FindChildrenThat<T>([](T*) -> bool { return true; }, results); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindChildrenOfTypeRecursive(ref<TResultCollection> results) const noexcept
		{ return FindChildrenThatRecursive<T>([](T*) -> bool { return true; }, results); }
		
		template<typename T>
		_NODISCARD T* FindParentOfTypeRecursive() const noexcept
		{ return FindParentThatRecursive<T>([](T*) -> bool { return true; }); }
		
		template<typename T>
		bool TryFindParentOfTypeRecursive(out<T*> result) const noexcept
		{ return TryFindParentThatRecursive<T>([](T*) -> bool { return true; }, result); }

		template<typename T>
		_NODISCARD T* FindChildWithName(in<std::string> name) const noexcept
		{ return FindChildThat<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }

		template<typename T>
		_NODISCARD T* FindChildWithNameRecursive(in<std::string> name) const noexcept
		{ return FindChildThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }
		
		template<typename T>
		bool TryFindChildWithName(in<std::string> name, out<T*> result) const noexcept
		{ return TryFindChildThat<T>([&](T* node) -> bool { return node->NameIs(name); }, result); }

		template<typename T>
		bool TryFindChildWithNameRecursive(in<std::string> name, out<T*> result) const noexcept
		{ return TryFindChildThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }, result); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindChildrenWithName(in<std::string> name, ref<TResultCollection> results) const noexcept
		{ return FindChildrenThat<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindChildrenWithNameRecursive(in<std::string> name, ref<TResultCollection> results) const noexcept
		{ return FindChildrenThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }
		
		template<typename T>
		_NODISCARD T* FindParentWithNameRecursive(in<std::string> name) const noexcept
		{ return FindParentThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }
		
		template<typename T>
		bool TryFindParentWithNameRecursive(in<std::string> name, out<T*> result) const noexcept
		{ return TryFindParentThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }, result); }

		template<typename T, typename... TConstructorArguments>
		T* AddChild(TConstructorArguments... constructorArguments)
		{ return AddChildIn<T, TConstructorArguments...>(this, constructorArguments...); }

		template<typename T, typename... TConstructorArguments>
		static T* AddChildIn(in<Node*> parent, TConstructorArguments... constructorArguments)
		{
			static_assert(std::is_base_of<Node, T>::value);
			T* newNode = new T(constructorArguments...);
			newNode->_SetAsParent(parent);
			NODE_TRIGGER_EVENT_WITH_TRY_CATCH(newNode, OnLoad);
			return newNode;
		}

	protected:
		Node(in<std::string> name = "") noexcept;

		virtual void OnLoad() { };

		virtual void OnParentChanged() { };

		virtual void OnDestroy() { };

	private:
		void _RemoveThisFromParent() noexcept;

		void _SetAsParent(in<Node*> parentNode) noexcept;
	};	
}