#pragma once
#include <string>
#include <vector>

class Node
{
public:
	std::string* name = nullptr;

public:
	virtual ~Node();

	/*
	bool HasName() const;
	std::string GetName() const;
	void SetName(const std::string& name);

	*/
	bool HasParent() const;
	const Node* GetParent() const;
	/*
	void SetParent(const Node* node);

	*/
	const std::vector<Node*>* GetChildren() const;

	/*
	template<typename T>
	T* FindChildOfType() const;
	template<typename T>
	bool FindChildrenOfType(const std::vector<T*>& results) const;

	template<typename T = Node>
	T* FindChildByName(const std::string& name) const;
	template<typename T = Node>
	bool FindChildrenByName(const std::string& name, const std::vector<T*>& results) const;

	template<typename T>
	T* CreateNode();
	template<typename T>
	T* CreateNode(const std::string& name);
	*/

private:
	std::vector<Node*>* _children;
	Node* _parent;
};