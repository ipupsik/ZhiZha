#include <iostream>

#include "Graph.h"

int main() {
	Graph<int> graph;
	Node a(2);
	Node b(3);
	Node foo(5);
	Node bar(6);
	Node baz(7);

	graph.Just(a)
	     .Just(b)
	     .Depends(foo, bar)
	     .Depends(foo, baz)
	     .Depends(baz, bar)
	     .Depends(a, bar);
	auto stack = graph.TopSort();
	while (!stack.empty()) {
		std::cout << stack.top() << std::endl;
		stack.pop();
	}
}
