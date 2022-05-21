#include <menu.h>
#include <curses.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <utility>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctime>
#include <chrono>
#include <clocale>

#include "../include/directory.hpp"
#include "../include/app.hpp"

static void init_ncurse(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	app::init_logs_1_stage();
}

static app::Options menu(void)
{
	enum app::Options opt = app::Options::EXIT;
	ITEM **my_items;
	MENU *my_menu;
	std::vector<std::pair<std::string, std::string>> choices = {
			{"1. C++", "Creating C++ enviroment"},
			{"2. C", "Creating C enviroment"},
			{"3. Python", "Crearing Python script"},
			{"4. Shell Script", "Creating Shell script"},
			{"5. Exit", ""},
	};
	int num_of_choices = choices.size();
	my_items = (ITEM **)calloc(num_of_choices + 1, sizeof(ITEM *));
	for (size_t i = 0; i < choices.size(); i++)
	{
		my_items[i] = new_item(choices[i].first.c_str(),
													 choices[i].second.c_str());
	}
	my_items[num_of_choices] = (ITEM *)NULL;

	my_menu = new_menu((ITEM **)my_items);
	post_menu(my_menu);
	refresh();

	int key;
	unsigned int current_options;
	while ((key = getch()))
	{
		switch (key)
		{
		case KEY_DOWN:
		{
			menu_driver(my_menu, REQ_DOWN_ITEM);
			break;
		}
		case KEY_UP:
		{
			menu_driver(my_menu, REQ_UP_ITEM);
			break;
		}
		case 10: /* ENTER KEY */
		{
			move(20, 0);
			char selected_item = item_name(current_item(my_menu))[0];
			current_options = static_cast<unsigned int>(selected_item - '0');
			opt = static_cast<app::Options>(current_options);
			return opt;
			break;
		}
		}
	}
	free(my_items);
	return opt;
}
void c_menu()
{
	// TODO
}
void sh_menu()
{
	// TODO
}
void pyhon_menu()
{
	// TODO
}

int main(void)
{
	init_ncurse();
	app::Options choice = menu();
	switch (choice)
	{
	case app::Options::OPTIONS_1:
	{
		app::cpp_menu();
		break;
	}
	case app::Options::OPTIONS_2:
	{
		c_menu();
		break;
	}
	case app::Options::OPTIONS_3:
	{
		pyhon_menu();
		break;
	}
	case app::Options::OPTIONS_4:
	{
		sh_menu();
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
