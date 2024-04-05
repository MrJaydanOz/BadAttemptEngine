#pragma once
#include <string>
#include <vector>
#include "BAE_Debug.h"
#include "BAE_Def.h"

#define NODE_TRIGGER_EVENT_WITH_TRY_CATCH(nodePointer, functionName, ...) \
try { nodePointer->functionName(__VA_ARGS__); } \
catch (in<std::exception> exception) \
{ DEBUG_LOG_EXCEPTION_CONTEXTED(DEBUG_NODE_NAME(nodePointer) << '.' << #functionName << "()", exception); }

namespace bae
{
	class Node
	{
	private:
		std::string _name;
		std::vector<Node*> _children;
		Node* _parent;
		bool _active;

	public:
		virtual ~Node() noexcept;

		_NODISCARD bool HasName() const noexcept;
		_NODISCARD const std::string& GetName() const noexcept;
		void SetName(in<std::string> name) noexcept;

		_NODISCARD bool HasParent() const noexcept;
		_NODISCARD Node* GetParent() const noexcept;
		void SetParent(Node* parent) noexcept;

		_NODISCARD const std::vector<Node*>& GetChildren() const noexcept;

		template<typename T, typename TNodePredicate>
		_NODISCARD T* FindChildThat(delegate<TNodePredicate> predicate) const noexcept
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

		template<typename T, typename TNodePredicate>
		_NODISCARD T* FindChildThatRecursive(delegate<TNodePredicate> predicate) const noexcept
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

		template<typename T, typename TNodePredicate>
		bool TryFindChildThat(delegate<TNodePredicate> predicate, out<T*> result) const noexcept
		{ return (result = FindChildThat<T, TNodePredicate>(predicate)) != nullptr; }

		template<typename T, typename TNodePredicate>
		bool TryFindChildThatRecursive(delegate<TNodePredicate> predicate, out<T*> result) const noexcept
		{ return (result = FindChildThatRecursive<T, TNodePredicate>(predicate)) != nullptr; }

		template<typename T, typename TNodePredicate, typename TResultCollection>
		size_t FindChildrenThat(delegate<TNodePredicate> predicate, ref_nullable<TResultCollection> results) const noexcept
		{
			static_assert(std::is_base_of<Node, T>::value);
			size_t foundCount = 0;

			if (results == nullptr)
			{
				DEBUG_LOG_ERROR_CONTEXTED(BAE_LOG_CONTEXT, "Result collection in '" << DEBUG_NODE_NAME(this) << "'.FindChildrenThatRecursive() is null.");
				return;
			}

			for (Node* child : GetChildren())
				if (child != nullptr)
				{
					T* castedChild = dynamic_cast<T*>(child);
					if (castedChild != nullptr && predicate(castedChild))
					{
						results->push_back(castedChild);
						foundCount++;
					}
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");

			return foundCount;
		}

		template<typename T, typename TNodePredicate, typename TResultCollection>
		size_t FindChildrenThatRecursive(delegate<TNodePredicate> predicate, ref_nullable<TResultCollection> results) const noexcept
		{
			static_assert(std::is_base_of<Node, T>::value);
			size_t foundCount = 0;

			if (results == nullptr)
			{
				DEBUG_LOG_ERROR_CONTEXTED(BAE_LOG_CONTEXT, "Result collection in '" << DEBUG_NODE_NAME(this) << "'.FindChildrenThatRecursive() is null.");
				return;
			}

			for (Node* child : GetChildren())
				if (child != nullptr)
				{
					T* castedChild = dynamic_cast<T*>(child);
					if (castedChild != nullptr && predicate(castedChild))
					{
						results->push_back(castedChild);
						foundCount++;
					}
					else
					{
						foundCount += child->FindChildrenThatRecursive<T, TNodePredicate>(results, predicate);
					}
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");

			return foundCount;
		}

		template<typename T, typename TNodePredicate>
		_NODISCARD T* FindParentThatRecursive(delegate<TNodePredicate> predicate) const noexcept
		{
			static_assert(std::is_base_of<Node, T>::value);

			Node* parent = GetParent();

			while (parent != nullptr)
			{
				T* castedParent = dynamic_cast<T*>(parent);
				if (castedParent != nullptr && predicate(castedParent))
					return castedParent;

				parent = parent->GetParent();
			}

			return nullptr;
		}
		
		template<typename T, typename TNodePredicate>
		bool TryFindParentThatRecursive(delegate<TNodePredicate> predicate, out<T*> result) const noexcept
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

		template<typename T, typename TResultCollection>
		size_t FindChildrenOfType(ref_nullable<TResultCollection> results) const noexcept
		{ return FindChildrenThat<T>([](T*) -> bool { return true; }, results); }

		template<typename T, typename TResultCollection>
		size_t FindChildrenOfTypeRecursive(ref_nullable<TResultCollection> results) const noexcept
		{ return FindChildrenThatRecursive<T>([](T*) -> bool { return true; }, results); }
		
		template<typename T>
		_NODISCARD T* FindParentOfTypeRecursive() const noexcept
		{ return FindParentThatRecursive<T>([](T*) -> bool { return true; }); }
		
		template<typename T>
		bool TryFindParentOfTypeRecursive(out<T*> result) const noexcept
		{ return TryFindParentThatRecursive<T>([](T*) -> bool { return true; }, result); }

		template<typename T>
		_NODISCARD T* FindChildWithName(in<std::string> name) const noexcept
		{ return FindChildThat<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T>
		_NODISCARD T* FindChildWithNameRecursive(in<std::string> name) const noexcept
		{ return FindChildThatRecursive<T>([&](T* node) -> bool { return node->GetName() == name; }); }
		
		template<typename T>
		bool TryFindChildWithName(in<std::string> name, out<T*> result) const noexcept
		{ return TryFindChildThat<T>([&](T* node) -> bool { return node->GetName() == name; }, result); }

		template<typename T>
		bool TryFindChildWithNameRecursive(in<std::string> name, out<T*> result) const noexcept
		{ return TryFindChildThatRecursive<T>([&](T* node) -> bool { return node->GetName() == name; }, result); }

		template<typename T, typename TResultCollection>
		size_t FindChildrenWithName(in<std::string> name, ref_nullable<TResultCollection> results) const noexcept
		{ return FindChildrenThat<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T, typename TResultCollection>
		size_t FindChildrenWithNameRecursive(in<std::string> name, ref_nullable<TResultCollection> results) const noexcept
		{ return FindChildrenThatRecursive<T>([&](T* node) -> bool { return node->GetName() == name; }); }
		
		template<typename T>
		_NODISCARD T* FindParentWithNameRecursive(in<std::string> name) const noexcept
		{ return FindParentThatRecursive<T>([&](T* node) -> bool { return node->GetName() == name; }); }
		
		template<typename T>
		bool TryFindParentWithNameRecursive(in<std::string> name, out<T*> result) const noexcept
		{ return TryFindParentThatRecursive<T>([&](T* node) -> bool { return node->GetName() == name; }, result); }

		template<typename T, typename... TConstructorArguments>
		T* AddChild(TConstructorArguments... arguments)
		{
			static_assert(std::is_base_of<Node, T>::value);
			T* newNode = new T(arguments...);
			_AddAsChild(newNode);
			return nullptr;
		}

	protected:
		Node(in<std::string> name = "") noexcept;

		virtual void OnLoad() { };

		virtual void OnParentChanged() { };

		virtual void OnDestroy() { };

	private:
		void _RemoveThisFromParent() noexcept;

		void _AddAsChild(Node* childNode) noexcept;
	};	
}