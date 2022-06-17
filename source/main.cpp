#include <curses.h>

#include "../include/app.hpp"
#include "../include/directory.hpp"

static void init_ncurse(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
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
	app::Options choice = app::menu(base_menu);
	switch (choice)
	{
		case app::Options::OPTIONS_1:
		{
			app::cpp_menu();
			break;
		}
		case app::Options::OPTIONS_2:
		{
			app::c_menu();
			break;
		}
		case app::Options::OPTIONS_3:
		{
			app::python_menu();
			break;
		}
		case app::Options::OPTIONS_4:
		{
			app::sh_menu();
			break;
		}
		case app::Options::EXIT:
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
