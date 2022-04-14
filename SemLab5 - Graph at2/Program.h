#pragma once
#include "Header.h"
#include "Node.h"
#include "Edge.h"

class Program
{
private:
	sf::RenderWindow* window;
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
	void input();
	bool mouse_on_screen();
	std::vector<Node*> nodes;
	sf::Vector2i last_position;
	void add_edge(Node* beginning);
	void update_edges();
	void pop_edge(Edge* edge);
	void clear_list();
	void establish_edge();
	Edge* is_over_edge();
	Node* is_over_node();
	Node* is_over_node(Node* exception);

public:
	Program(bool graph_mode, short input_mode);
	~Program();
	const bool get_window_opened() const;
	void update();
	void render();
};
