#include <iostream>
#include "graph_D.h"

int main() 
{
	graph g(4);
	g.print_adj();
	std::cout << "*************************\n";
//	g.dijkstra('A');
//	g.add_vertex();
//	g.add_vertex();
//	g.print_adj();
//	g.add_edge('A', 'B', 3);
//	g.add_edge('A', 'C', 5);
//	g.print_adj();
//	graph h;
//	std::cout << h.is_empty();
	g.remove_edge('A', 'B');
	g.print_adj();
	return 0;
}
