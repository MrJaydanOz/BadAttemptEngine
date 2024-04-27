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

#define NODE_BEGIN friend class bae::Node /* This allows for Node::AddChild() to access the node's constructor. */

namespace bae
{
	class Scene;

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Node))
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
		bae::uintx_t<2> _statusFlags;
		_Node_Location_Type _location_type;

	public:
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
		_NODISCARD T* FindChildThat(in_delegate<TNodePredicate> predicate) const noexcept requires std::is_base_of_v<Node, T>
		{
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
		_NODISCARD T* FindChildThatRecursive(in_delegate<TNodePredicate> predicate) const noexcept requires std::is_base_of_v<Node, T>
		{
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
		bool TryFindChildThat(in_delegate<TNodePredicate> predicate, out<T*> result) const noexcept requires std::is_base_of_v<Node, T>
		{ return (result = FindChildThat<T, TNodePredicate>(predicate)) != nullptr; }

		template<typename T, typename TNodePredicate = bool(T*)>
		bool TryFindChildThatRecursive(in_delegate<TNodePredicate> predicate, out<T*> result) const noexcept requires std::is_base_of_v<Node, T>
		{ return (result = FindChildThatRecursive<T, TNodePredicate>(predicate)) != nullptr; }

		template<typename T, typename TNodePredicate = bool(T*), typename TResultCollection = bae::List<T*>>
		size_t FindChildrenThat(in_delegate<TNodePredicate> predicate, ref<TResultCollection> results) const noexcept requires std::is_base_of_v<Node, T>
		{
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
		size_t FindChildrenThatRecursive(in_delegate<TNodePredicate> predicate, ref<TResultCollection> results) const noexcept requires std::is_base_of_v<Node, T>
		{
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
		_NODISCARD T* FindParentThatRecursive(in_delegate<TNodePredicate> predicate) const noexcept requires std::is_base_of_v<Node, T>
		{
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
		bool TryFindParentThatRecursive(in_delegate<TNodePredicate> predicate, out<T*> result) const noexcept requires std::is_base_of_v<Node, T>
		{ return (result = FindParentThatRecursive<T, TNodePredicate>(predicate)) != nullptr; }

		template<typename T>
		_NODISCARD T* FindChildOfType() const noexcept requires std::is_base_of_v<Node, T>
		{ return FindChildThat<T>([](T*) -> bool { return true; }); }
		
		template<typename T>
		_NODISCARD T* FindChildOfTypeRecursive() const noexcept requires std::is_base_of_v<Node, T>
		{ return FindChildThatRecursive<T>([](T*) -> bool { return true; }); }
		
		template<typename T>
		bool TryFindChildOfType(out<T*> result) const noexcept requires std::is_base_of_v<Node, T>
		{ return TryFindChildThat<T>([](T*) -> bool { return true; }, result); }

		template<typename T>
		bool TryFindChildOfTypeRecursive(out<T*> result) const noexcept requires std::is_base_of_v<Node, T>
		{ return TryFindChildThatRecursive<T>([](T*) -> bool { return true; }, result); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindChildrenOfType(ref<TResultCollection> results) const noexcept requires std::is_base_of_v<Node, T>
		{ return FindChildrenThat<T>([](T*) -> bool { return true; }, results); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindChildrenOfTypeRecursive(ref<TResultCollection> results) const noexcept requires std::is_base_of_v<Node, T>
		{ return FindChildrenThatRecursive<T>([](T*) -> bool { return true; }, results); }
		
		template<typename T>
		_NODISCARD T* FindParentOfTypeRecursive() const noexcept requires std::is_base_of_v<Node, T>
		{ return FindParentThatRecursive<T>([](T*) -> bool { return true; }); }
		
		template<typename T>
		bool TryFindParentOfTypeRecursive(out<T*> result) const noexcept requires std::is_base_of_v<Node, T>
		{ return TryFindParentThatRecursive<T>([](T*) -> bool { return true; }, result); }

		template<typename T>
		_NODISCARD T* FindChildWithName(in<std::string> name) const noexcept requires std::is_base_of_v<Node, T>
		{ return FindChildThat<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }

		template<typename T>
		_NODISCARD T* FindChildWithNameRecursive(in<std::string> name) const noexcept requires std::is_base_of_v<Node, T>
		{ return FindChildThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }
		
		template<typename T>
		bool TryFindChildWithName(in<std::string> name, out<T*> result) const noexcept requires std::is_base_of_v<Node, T>
		{ return TryFindChildThat<T>([&](T* node) -> bool { return node->NameIs(name); }, result); }

		template<typename T>
		bool TryFindChildWithNameRecursive(in<std::string> name, out<T*> result) const noexcept requires std::is_base_of_v<Node, T>
		{ return TryFindChildThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }, result); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindChildrenWithName(in<std::string> name, ref<TResultCollection> results) const noexcept requires std::is_base_of_v<Node, T>
		{ return FindChildrenThat<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }

		template<typename T, typename TResultCollection = bae::List<T*>>
		size_t FindChildrenWithNameRecursive(in<std::string> name, ref<TResultCollection> results) const noexcept requires std::is_base_of_v<Node, T>
		{ return FindChildrenThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }
		
		template<typename T>
		_NODISCARD T* FindParentWithNameRecursive(in<std::string> name) const noexcept requires std::is_base_of_v<Node, T>
		{ return FindParentThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }); }
		
		template<typename T>
		bool TryFindParentWithNameRecursive(in<std::string> name, out<T*> result) const noexcept requires std::is_base_of_v<Node, T>
		{ return TryFindParentThatRecursive<T>([&](in<T*> node) -> bool { return node->NameIs(name); }, result); }

		template<typename T>
		T* AddChild(in<const char*> name) requires std::is_base_of_v<Node, T>
		{ return AddChildIn<T>(this, name); }

		template<typename T>
		static T* AddChildIn(in<Node*> parent, in<const char*> name) requires std::is_base_of_v<Node, T>
		{
			T* newNode = _ConstructNode<T>(parent);
			newNode->_CallCreate(name);
			return newNode;
		}

		template<typename T>
		static void Destroy(ref<T*> node) requires std::is_base_of_v<Node, T>
		{
			if (node != nullptr)
			{
				node->_statusFlags |= (1 << 1);
				node->_CallDestroy();
				delete node;
				node = nullptr;
			}
		}

	protected:
		Node(in<Node*> parent) noexcept;
		virtual ~Node() noexcept;
		virtual void Create(in<const char*> name = "");
		virtual void Destroy();

		virtual void OnParentChanged() { };

	private:
		void _RemoveThisFromParent() noexcept;

		void _SetAsParent(in<Node*> parentNode) noexcept;
		
		template<typename T>
		static T* _ConstructNode(in<Node*> parent) requires std::is_base_of_v<Node, T>
		{ return new T(parent); }

		void _CallCreate(in<const char*> name);

		void _CallDestroy();

		bool constexpr _IsActive() const;

		bool constexpr _AllowDelete() const;
	};

	template<typename T, typename... TConstructorArguments>
	static T* AddChildIn(in<Node*> parent, in<const char*> name, TConstructorArguments... constructorArguments) requires std::is_base_of_v<Node, T>
	{ return Node::AddChildIn<T, TConstructorArguments...>(parent, name, constructorArguments...); }

	template<typename T>
	static void Destroy(ref<T*> node) requires std::is_base_of_v<Node, T>
	{ Node::Destroy<T>(node); }
}