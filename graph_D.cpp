#include <iostream>
#include <limits.h>
#include "graph_D.h"

graph::graph()
:head_list(nullptr)
,v_count(0)
{}

graph::graph(int n)
:v_count(n)
{
	head_list = new node*[n]{};
	std::cout << "Your vertices are from A to " << static_cast<char>(n + 'A' - 1) << std::endl;
	for(int i = 0; i < n; i++){
		char tmp_name = static_cast<char>(i + 'A');
		std::cout << "********************************\n";
		std::cout << "Enter the adjacent vertices of " << tmp_name  << "\n";
		char adj;
		std::cout << "Press 0 if you are done.\n";
		while(true){
			std::cout << "\nVertex: ";
			std::cin >> adj;
			if(adj == '0'){
				break;
			}
			else if(adj < 'A' || adj >= (n + 'A') || adj == static_cast<char>(tmp_name)){
				std::cout << "\nInvalid name\n";
			}
			else {
				std::cout << "Degree(positive): ";
				int deg;
				do{
					std::cin >> deg;
				}while(deg <= 0);
				insert_node(deg, i, adj);
			}
		}
			
	}
}

int graph::get_v_count() const
{
	return v_count;
}

bool graph::ver_exists(char key)
{
	if(this->is_empty()){
		return false;
	}		
	if(key >= 'A' && key < (v_count + 'A')){
		return true;
	}
	return false;
}

void graph::add_vertex()
{	
	node** new_head = new node*[v_count + 1];
	for(int i = 0; i < v_count; i++){
		new_head[i] = head_list[i];
	}
	new_head[v_count] = nullptr;
	v_count++;
	delete[] head_list;
	head_list = new_head;
	std::cout << "Vertex added\n";
}

void graph::add_edge(char from, char to, int val)
{
	if(ver_exists(from) && ver_exists(to)){
		if(is_adj(from, to)){
			update_edge_value(from, to, val);
			return;
		}
		int index = static_cast<int>(from - 'A');
		insert_node(val, index, to);
	}	
}

void graph::remove_vertex()
{
	if(!(this->is_empty())){
		char name_r = static_cast<char>(v_count + 'A' - 1);
		//delete adjecents
		for(int i = 0; i < v_count - 1; i++){
			remove_node(head_list[i], name_r);
		}	
		//finally deleting the vertex
		node* tmp = nullptr;
		node* cur_h = nullptr;
		cur_h = head_list[v_count - 1];
		while(cur_h != nullptr){
			tmp = cur_h;
			cur_h = cur_h->next;
			delete tmp;
		}
		node** new_head = new node*[v_count - 1];
		for(int i = 0; i < v_count - 1; i++){
			new_head[i] = head_list[i];
		}
		delete[] head_list;
		head_list = new_head;
		v_count--;
	}
}

void graph::remove_edge(char from, char to)
{
	if(is_adj(from, to)){
		int source = static_cast<int>(from - 'A');
		remove_node(head_list[source], to);
	}else{
		std::cout << "There is no such edge\n";
	}
}

void graph::print_adj()
{
	for(int i = 0; i < v_count; i++){
		if(head_list[i] == nullptr){
			std::cout << static_cast<char>('A' + i)  << " has no adjecents\n";
			continue;
		}
		node* ptr = head_list[i];
		if(ptr->next == nullptr){
			std::cout << "Adjecent of " << static_cast<char>('A' + i) << " is " << ptr->name;
			std::cout << std::endl;
			continue;
		}
		std::cout << "Adjecents of " << static_cast<char>('A' + i) << " are ";
		while(ptr != nullptr){
			std::cout << ptr->name;
			if(ptr->next != nullptr){       
				std::cout << ", ";
			}
			ptr = ptr->next;
		}
		std::cout << std::endl;
	}

}

void graph::dijkstra(char start)
{
	bool* visited = new bool[v_count]{};
	int* distances = new int[v_count];
	for(int i = 1; i < v_count; i++){
		distances[i] = INT_MAX;
	}
	int st = static_cast<int>(start - 'A');
	distances[st] = 0;

	for(int i = 0; i < v_count; i++){
		int tmp_index = select_vertex_D(distances, visited);
		visited[tmp_index] = true;
		node* ptr = head_list[tmp_index];
		while(ptr != nullptr){
			int cur_node = static_cast<int>(ptr->name - 'A');
			if(visited[cur_node] == false && distances[tmp_index] != INT_MAX
				       	&& distances[tmp_index] + (ptr->value) < distances[cur_node]){
						distances[cur_node] = distances[tmp_index] + (ptr->value);
			}
			ptr = ptr->next;	
		}
	}
	print_D(start, distances);
	delete[] visited;
	delete[] distances;
}

bool graph::is_empty()
{
	return !(get_v_count());
}

node* graph::create_node(int val, char ver_name)
{
	node* myNode = new node;
	myNode->value = val;
	myNode->name = ver_name;
       	myNode->next = nullptr;
	return myNode;
}

void graph::insert_node(int degree, int index, char ver_name)
{
	node* myNode = create_node(degree, ver_name);

	if(head_list[index] == nullptr){
		head_list[index] = myNode;
	}else{
		myNode->next = head_list[index];
		head_list[index] = myNode;
	}
}

void graph::remove_node(node*& list, char removable)
{
	if(list == nullptr){
		return;
	}
	node* tmp = nullptr;
	if(list->name == removable){
		tmp = list;
		list = list->next;
		delete tmp;
		return;
	}
	node* prev = list;
	tmp = list->next;
	while(tmp != nullptr && tmp->name != removable){
		prev = tmp;
		tmp = tmp->next;
	}
	if(tmp != nullptr){
		prev->next = tmp->next;
		delete tmp;
	}

}

bool graph::is_adj(char from, char to)
{
	if(!(this->is_empty())){
		int index = static_cast<int>(from - 'A');
		node* tmp = head_list[index];
		while(tmp != nullptr){
			if(tmp->name == to){
				return true;
			}
			tmp = tmp->next;
		}
		return false;
	}
	return false;
}

void graph::update_edge_value(char from, char to, int new_val)
{
	if(ver_exists(from) && ver_exists(to) && is_adj(from, to)){
		int index = static_cast<int>(from - 'A');
		node* tmp = head_list[index];
		while(tmp != nullptr){
			if(tmp->name == to){
				head_list[index]->value = new_val;
				std::cout << "Value updated\n";
				return;
			}
			tmp = tmp->next;
		}
	}
	std::cout << "Invalid parameters for update_edge_value()\n";
}

int graph::select_vertex_D(int*& dist, bool*& visit)
{
	int min = INT_MAX;
	int index = 0;
	for(int i = 0; i < v_count; i++){
		if(visit[i] == false && dist[i] < min) {
			min = dist[i];
			index = i;
		}
	}
	return index;
}

void graph::print_D(char start, int*& dist)
{
	if(v_count == 1){
		std::cout << "A is the only node\n";
		return;
	}
	std::cout << "\nThe minimal distances from " << start << " are\n";
	for(int i = 0; i < v_count; i++){
		if(i + 'A' != start){
			std::cout << static_cast<char>(i + 'A') << ": ";
			std::cout << dist[i] << std::endl;
		}
	}
}

graph::~graph()
{
	if(this->is_empty()){
		return;
	}	
	for(int i = 0; i < v_count; i++){
		while(head_list[i] != nullptr){
			node* tmp = head_list[i];
			head_list[i] = head_list[i]->next;
			delete tmp;
		}	
	}
	delete[] head_list;
}
