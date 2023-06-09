#pragma once

struct node
{
	int value;
	char name;
	node* next;
};

class graph
{
	public:
		graph();
		graph(int n);
		int get_v_count() const;
		bool ver_exists(char key);
		void add_vertex();//add the next by alphabet
		void add_edge(char from, char to, int val);
		void remove_vertex();//remove the last added
		void remove_edge(char from, char to);
		void print_adj();
		void dijkstra(char start);
		bool is_empty();
		~graph();
	private:
		node** head_list;
		int v_count;
		node* create_node(int val, char ver_name);
		void insert_node(int degree, int index, char ver_name);
		void remove_node(node*& list, char removable);
		bool is_adj(char from, char to);
		void update_edge_value(char from, char to, int new_val);
		int select_vertex_D(int*& dist, bool*& visit);
		void print_D(char start, int*& dist);

};
