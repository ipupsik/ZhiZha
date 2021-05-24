#pragma once
#include <functional>
#include <stack>
#include <vector>

enum NodeVisit { NotVisited = 0, Visited = 1, Fixed = 2 };

template <typename T>
class Node {
	NodeVisit _visited;
	T _data;
	std::vector<Node<T>*> _children;
	int _id;
	static int ID;

public:
	explicit Node(const T& data) : _data(data) {
		_id = ID++;
		_visited = NotVisited;
	}

	[[nodiscard]] NodeVisit GetVisited() const { return _visited; }

	[[nodiscard]] const T& GetData() const { return _data; }

	[[nodiscard]] const std::vector<Node<T>*>& GetChildren() const { return _children; }

	[[nodiscard]] int GetId() const { return _id; }

	void AddChild(Node<T>* child) {
		_children.emplace_back(child);
	}

	void SetVisited(const NodeVisit visited) { _visited = visited; }

	static int Count() { return ID + 1; }
};

template <typename T>
int Node<T>::ID = 0;

/**
 *
 */
template <typename T>
class Graph {
	std::vector<Node<T>*> _nodes;

	bool dfs(Node<T>* startPosition, std::function<void(Node<T>*)> onEach) {
		startPosition->SetVisited(Visited);

		for (const auto& child : startPosition->GetChildren()) {
			if (child == nullptr) continue;
			if (child->GetVisited() == NotVisited)
				dfs(child, onEach);
			else if (child->GetVisited() == Visited)
				return false;
		}
		onEach(startPosition);
		return true;
	}

	void clearState() {
		for (auto node : _nodes)
			if (node != nullptr)
				node->SetVisited(NotVisited);
	}

public:
	Graph() : _nodes() {}

	/**
	 * Метод Depends создает связь между родительским элементом primary и дочерним элементом
	 * dependent
	 * @param primary Родительский элемент, к которому присоединяется дочерний элемент dependent
	 * @param dependent Дочерний элемент, который присоединяется к родительскому
	 * @return ссылка на тот же граф
	 */
	Graph& Depends(Node<T>& primary, Node<T>& dependent) {
		if (primary.GetId() >= _nodes.size() || dependent.GetId() >= _nodes.size())
			_nodes.resize(Node<T>::Count());
		_nodes[primary.GetId()] = &primary;
		_nodes[dependent.GetId()] = &dependent;
		primary.AddChild(&dependent);
		return *this;
	}

	/**
	 * Метод Just используется для добавления отдельного элемента, независящего от других.
	 * @param node Ссылка на добавляемый элемент
	 * @return Ссылка на этот же граф.
	 */
	Graph& Just(Node<T>& node) {
		if (node.GetId() >= _nodes.size())
			_nodes.resize(Node<T>::Count());
		_nodes[node.GetId()] = &node;
		return *this;
	}

	bool HasCycles() {
		for (const auto& node : _nodes)
			if (node != nullptr && node->GetVisited() == NotVisited && !dfs(node, [](const auto&) {})) {
				clearState();
				return true;
			}
		clearState();
		return false;
	}

	std::stack<T> TopSort() {
		std::stack<T> result;
		for (const auto& node : _nodes)
			if (node != nullptr && node->GetVisited() == NotVisited && !dfs(node, [&result](auto processed) {
				processed->SetVisited(Fixed);
				result.push(processed->GetData());
			})) {
				clearState();
				throw std::runtime_error("Graph should not have cycles");
			}
		clearState();
		return result;
	}
};
