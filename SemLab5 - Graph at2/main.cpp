#include "Header.h"
#include "Program.h"
int main()
{
	bool graph_mode = 0;
	short input_mode = 0;
	Program program(graph_mode, input_mode);
	while (program.get_window_opened()) {
		program.update();
		program.render();
	}
	return 0;
}