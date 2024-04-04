#include "Def.h"
#include "Nodes/Node.h"

namespace bae
{
	class Scene
	{
	private:
		std::vector<Node*> _rootNodes;

	public:
		_NODISCARD const std::vector<Node*>& GetRootNodes() const noexcept;

		template<typename T, typename TNodePredicate>
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

		template<typename T, typename TNodePredicate>
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

		template<typename T, typename TNodePredicate, typename TResultCollection>
		in<size_t> FindRootNodesThat(in<TNodePredicate> predicate, ref_nullable<TResultCollection> results)
		{
			static_assert(std::is_base_of<Node, T>::value);
			size_t foundCount = 0;

			if (results == nullptr)
			{
				DEBUG_LOG_ERROR_CONTEXTED(BAE_LOG_CONTEXT, "Result collection in Scene.FindRootNodesThat() is null.");
				return 0;
			}

			for (Node* node : GetRootNodes())
				if (node != nullptr)
				{
					T* castedNode = dynamic_cast<T*>(node);
					if (castedNode != nullptr && predicate(castedNode))
					{
						results->push_back(castedNode);
						foundCount++;
					}
				}
				else
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

			return foundCount;
		}

		template<typename T, typename TNodePredicate, typename TResultCollection>
		in<size_t> FindNodesThat(in<TNodePredicate> predicate, ref_nullable<TResultCollection> results)
		{
			static_assert(std::is_base_of<Node, T>::value);
			size_t foundCount = 0;

			if (results == nullptr)
			{
				DEBUG_LOG_ERROR_CONTEXTED(BAE_LOG_CONTEXT, "Result collection in Scene.FindNodesThat() is null.");
				return 0;
			}

			for (Node* child : GetRootNodes())
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
					DEBUG_LOG_WARNING_CONTEXTED(BAE_LOG_CONTEXT, "The scene has a null root node.");

			return foundCount;
		}

		template<typename T>
		_NODISCARD T* FindRootNodeOfType()
		{ return FindRootNodeThat<T, auto>([](T*) -> bool { return true; }); }

		template<typename T>
		_NODISCARD T* FindNodeOfType()
		{ return FindNodeThat<T, auto>([](T*) -> bool { return true; }); }

		template<typename T, typename TResultCollection>
		in<size_t> FindCRootNodesOfType(ref_nullable<TResultCollection> results)
		{ return FindRootNodesThat<T, auto, TResultCollection>([](T*) -> bool { return true; }, results); }

		template<typename T, typename TResultCollection>
		in<size_t> FindNodesOfType(ref_nullable<TResultCollection> results)
		{ return FindNodesThat<T, auto>([](T*) -> bool { return true; }, results); }

		template<typename T>
		_NODISCARD T* FindRootNodeWithName(in<std::string> name)
		{ return FindRootNodeThat<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T>
		_NODISCARD T* FindNodeWithName(in<std::string> name)
		{ return FindNodeThat<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T, typename TResultCollection>
		in<size_t> FindRootNodesWithName(in<std::string> name, ref_nullable<TResultCollection> results)
		{ return FindRootNodesThat<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T, typename TResultCollection>
		in<size_t> FindNodesWithName(in<std::string> name, ref_nullable<TResultCollection> results)
		{ return FindNodesThat<T>([&](T* node) -> bool { return node->GetName() == name; }); }

		template<typename T, typename... TConstructorArguments>
		in<T*> AddChild(TConstructorArguments... arguments)
		{
			static_assert(std::is_base_of<Node, T>::value);
			T* newNode = new T(arguments...);
			AddAsChild(newNode);
			return newNode;
		}
	};
}