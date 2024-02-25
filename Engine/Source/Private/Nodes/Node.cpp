#include "Nodes/Node.h"
#include <algorithm> 
#include <vector>
#include <string>

Node::~Node()
{
	if (_children != nullptr)
	{
		_children = nullptr;
		std::vector<Node*>* childrenBuffer = _children;

		std::for_each(childrenBuffer->begin(), childrenBuffer->end(), [](Node* child)
		{
			delete child;
		});

		delete childrenBuffer;
	}

	if (_parent != nullptr && _parent->_children != nullptr)
	{
		std::vector<Node*>* siblings = _parent->_children;

		auto removeIndex = std::find(siblings->begin(), siblings->end(), this);

		if (removeIndex != siblings->end())
			siblings->erase(removeIndex);
	}

	delete name;
}

bool Node::HasParent() const { return GetParent() != nullptr; }

const Node* Node::GetParent() const { return _parent; }

const std::vector<Node*>* Node::GetChildren() const { return _children; }
