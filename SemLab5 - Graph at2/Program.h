#pragma once
#include "Header.h"
#include "Node.h"
#include "Edge.h"
#include "Tab.h"
#include "Graph_structure.h"
#include "Graphs.h"
class Program
{
private:
	unsigned graph_vector[NODE_LIMIT];
	int weights[NODE_LIMIT][NODE_LIMIT];
	StructGraph structed_graph;
	void convert_to_vector();
	void convert_to_structure();
	void clear_structure();
	void clear_structure(Graph_structure** to_clear);
	void add_to_structure(int id_1, int id_2, int weight);

	sf::RenderWindow* window;
	sf::Clock clock;
	const float min_delay = 0.25f;
	float delta_time;
	bool oriented_graph;
	bool weight_mode;
	int current_weight;
	struct List_edges {
		List_edges* next = nullptr;
		Edge *edge = nullptr;
		Node* node1 = nullptr;
		Node* node2 = nullptr;
	};
	List_edges* all_edges = nullptr;
	sf::Event ev;
	
	sf::VideoMode video_mode;
	sf::Mouse mouse;
	sf::Font font;
	sf::Font button_font;
	sf::Texture arrow_texture;
	sf::Texture check_box_texture;
	Tab tab;
	sf::Keyboard keyboard;
	Node* active_node;
	Edge* active_edge;
	void poll_events();
	bool graph_mode;
	bool is_iterational;
	bool is_demonstration;
	bool is_benchmark;
	void init_window();
	void init_font();
	void init_texture();
	void input();
	bool text_bar_input();
	void delete_edge();
	bool mouse_on_screen();
	void clear_canvas();
	std::vector<Node*> nodes;
	sf::Vector2f last_position;
	void add_edge(Node* beginning);
	void update_edges();
	void pop_edge(Edge* edge);
	void clear_list();
	void update_current_weight();
	void establish_edge();
	Node* is_over_node();
	Node* is_over_node(Node* exception);
	sf::Vector2f mouse_position();
	bool using_ui();
	Node* selected;
	void add_mode();
	void move_mode();
	void delete_mode();
	void put_new_edge();

	//Put them in structure class???? :
	void bfs_structure();
	void bfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool *visited);
	void dfs_structure();
	void dfs_structure_recursive(int current, std::string& to_show, bool weight_mode, bool* visited);
	Graph_structure* sort_by_weight(Graph_structure* beginning);
	bool edge_exists(Node* from, Node* to);
	Graph_structure* gen_queue(Graph_structure* beginning, bool* visited);
	void pop_from_queue(Graph_structure** from);

public:
	Program(bool graph_mode, short input_mode);
	~Program();
	const bool get_window_opened() const;
	void update();
	void render();
};

