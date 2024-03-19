#include "Nodes/RootNode.h"
#include "Nodes/Node.h"
#include <string>

RootNode::RootNode() noexcept : Node() { }

RootNode::~RootNode() noexcept 
{ 
	Node::~Node();
}