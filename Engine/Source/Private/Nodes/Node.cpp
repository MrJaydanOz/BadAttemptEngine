#include "Nodes/Node.h"
#include <algorithm> 

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

const std::vector<Node*>* Node::GetChildren() const { return _children; }
