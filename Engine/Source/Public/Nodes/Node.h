#pragma once
#include <string>
#include <vector>

class Node
{
private:
	std::string _name;
	std::vector<Node*>* _children;
	Node* _parent;

public:
	Node(const std::string& name = "") noexcept;
	virtual ~Node() noexcept;

	bool HasName() const noexcept;
	const std::string& GetName() const noexcept;
	void SetName(const std::string& name) noexcept;

	bool HasParent() const noexcept;
	Node* GetParent() const noexcept;
	void SetParent(Node* node) noexcept;

	const std::vector<Node*>* GetChildren() const noexcept;

	template<typename T>
	T* FindChildOfType() const noexcept;
	template<typename T>
	bool FindChildrenOfType(const std::vector<T*>& results) const noexcept;

	template<typename T = Node>
	T* FindChildByName(const std::string& name) const noexcept;
	template<typename T = Node>
	bool FindChildrenByName(const std::string& name, const std::vector<T*>& results) const noexcept;

	template<typename T, class... ConstructorArgs>
	T* CreateNode(ConstructorArgs... args) noexcept;

private:
	void RemoveThisFromParent() noexcept;

	void AddAsChild(Node* node) noexcept;
};