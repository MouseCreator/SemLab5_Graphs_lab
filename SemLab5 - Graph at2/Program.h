#pragma once
#include "Header.h"
#include "Node.h"
#include "Edge.h"
#include "Tab.h"
class Program
{
private:
	sf::RenderWindow* window;
	sf::Clock clock;
	float min_delay = 0.25;
	float delta_time;
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
	void input();
	bool text_bar_input();
	void delete_edge();
	bool mouse_on_screen();
	std::vector<Node*> nodes;
	sf::Vector2i last_position;
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

public:
	Program(bool graph_mode, short input_mode);
	~Program();
	const bool get_window_opened() const;
	void update();
	void render();
};

