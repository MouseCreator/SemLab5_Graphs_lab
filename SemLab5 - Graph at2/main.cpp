#include "Header.h"
#include "Program.h"
int main()
{
	short input_mode = 0;
	Program program(input_mode);
	while (program.get_window_opened()) {
		program.update();
		program.render();
	}
	return 0;
}