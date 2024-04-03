#pragma once
#include <string>
#include <vector>
#include "Debug.h"
#include "Def.h"

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

		virtual void OnParentChanged() noexcept { };

		_NODISCARD bool HasName() const noexcept;
		_NODISCARD const std::string& GetName() const noexcept;
		void SetName(IN(std::string) name) noexcept;

		_NODISCARD bool HasParent() const noexcept;
		_NODISCARD Node* GetParent() const noexcept;
		void SetParent(Node* node) noexcept;

		_NODISCARD const std::vector<Node*>& GetChildren() const noexcept;

		template<typename T, typename TNodePredicate>
		_NODISCARD T* FindChildThat(IN(TNodePredicate) predicate)
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
		_NODISCARD T* FindChildThatRecursive(IN(TNodePredicate) predicate)
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

		template<typename T, typename TNodePredicate, typename TResultCollection>
		size_t FindChildrenThat(IN(TNodePredicate) predicate, REF_NULLABLE(TResultCollection) results)
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
		size_t FindChildrenThatRecursive(IN(TNodePredicate) predicate, REF_NULLABLE(TResultCollection) results)
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

		template<typename T>
		_NODISCARD T* FindChildOfType()
		{ return FindChildThat<T, auto>([](T*) -> bool { return true; }); }

		template<typename T>
		_NODISCARD T* FindChildOfTypeRecursive()
		{ return FindChildThatRecursive<T, auto>([](T*) -> bool { return true; }); }

		template<typename T, typename TResultCollection>
		size_t FindChildrenOfType(REF_NULLABLE(TResultCollection) results)
		{ return FindChildrenThat<T, auto, TResultCollection>([](T*) -> bool { return true; }, results); }

		template<typename T, typename TResultCollection>
		size_t FindChildrenOfTypeRecursive(REF_NULLABLE(TResultCollection) results)
		{ return FindChildrenThatRecursive<T, auto>([](T*) -> bool { return true; }, results); }

		template<typename T>
		_NODISCARD T* FindChildWithName(IN(std::string) name)
		{ return FindChildThat<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T>
		_NODISCARD T* FindChildWithNameRecursive(IN(std::string) name)
		{ return FindChildThatRecursive<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T, typename TResultCollection>
		size_t FindChildrenWithName(IN(std::string) name, REF_NULLABLE(TResultCollection) results)
		{ return FindChildrenThat<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T, typename TResultCollection>
		size_t FindChildrenWithNameRecursive(IN(std::string) name, REF_NULLABLE(TResultCollection) results)
		{ return FindChildrenThatRecursive<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T, typename... TConstructorArguments>
		T* AddChild(TConstructorArguments... arguments)
		{
			static_assert(std::is_base_of<Node, T>::value);
			T* newNode = new T(args...);
			AddAsChild(newNode);
			return nullptr;
		}

	protected:
		Node(IN(std::string) name = "") noexcept;

	private:
		void RemoveThisFromParent() noexcept;

		void AddAsChild(Node* childNode) noexcept;
	};
}

/*template<typename T>
	T* FindChildOfType() const noexcept
	{
		static_assert(std::is_base_of<Node, T>::value);

		for (Node* child : GetChildren())
			if (child != nullptr)
			{
				const T* castedChild = dynamic_cast<const T*>(child);
				if (castedChild)
					return castedChild;
			}
			else
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");

		return nullptr;
	}

	template<typename T>
	bool TryFindChildOfType(T*& result) const noexcept
	{
		static_assert(std::is_base_of<Node, T>::value);

		result = FindChildOfType<T>();
		return result != nullptr;
	}

	template<typename T>
	bool FindChildrenOfType(std::vector<T*>& results) const noexcept
	{
		static_assert(std::is_base_of<Node, T>::value);

		bool found = false;

		for (Node* child : GetChildren())
			if (child != nullptr)
			{
				const T* castedChild = dynamic_cast<const T*>(child);
				if (castedChild)
				{
					found = true;
					results.push_back(castedChild);
				}
			}
			else
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");
	}

	template<typename T = Node>
	T* FindChildByName(const std::string& name) const noexcept
	{
		static_assert(std::is_base_of<Node, T>::value);

		for (Node* child : GetChildren())
			if (child != nullptr)
			{
				const T* castedChild = dynamic_cast<const T*>(child);
				if (castedChild && castedChild->_name == name)
					return castedChild;
			}
			else
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");

		return nullptr;
	}

	template<typename T = Node>
	bool TryFindChildByName(T*& result) const noexcept
	{
		static_assert(std::is_base_of<Node, T>::value);

		result = FindChildByName<T>();
		return result != nullptr;
	}

	template<typename T = Node>
	bool FindChildrenByName(const std::string& name, std::vector<T*>& results) const noexcept
	{
		static_assert(std::is_base_of<Node, T>::value);

		bool found = false;

		for (Node* child : GetChildren())
			if (child != nullptr)
			{
				const T* castedChild = dynamic_cast<const T*>(child);
				if (castedChild && castedChild->_name == name)
				{
					found = true;
					results.push_back(castedChild);
				}
			}
			else
				DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, DEBUG_NODE_NAME(this) << " has a null child.");
	}

	template<typename T, typename... ConstructorArgs>
	T* Add(ConstructorArgs... args) noexcept
	{
		static_assert(std::is_base_of<Node, T>::value);
		T* newNode = new T(args...);
		AddAsChild(newNode);
		return nullptr;
	}*/