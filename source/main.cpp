#include <curses.h>

#include "../include/app.hpp"
#include "../include/directory.hpp"

static void init_ncurse(void)
{
	initscr();
	cbreak();
	noecho();
	start_color();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	app::init_logs_1_stage();
}

int main(void)
{
	app::Menu_options base_menu = {
			{"1. C++", "Creating C++ enviroment"},
			{"2. C", "Creating C enviroment"},
			{"3. Python", "Crearing Python script"},
			{"4. Shell Script", "Creating Shell script"},
			{"5. Exit", ""},
	};
	init_ncurse();
	app::Options_index choice = app::basic_menu(base_menu);
	switch (choice)
	{
		case 1:
		{
			app::cpp_menu();
			break;
		}
		case 2:
		{
			app::c_menu();
			break;
		}
		case 3:
		{
			app::python_menu();
			break;
		}
		case 4:
		{
			app::sh_menu();
			break;
		}
		case 5:
		{
			endwin();
			exit(EXIT_SUCCESS);
			break;
		}
		default:
		{
			endwin();
			exit(EXIT_FAILURE);
			app::logs_err("Something went wrong");
		}
	}
	endwin();
	return 0;
}
