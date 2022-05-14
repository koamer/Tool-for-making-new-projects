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

enum class Options
{
	OPTIONS_1 = 1,
	OPTIONS_2 = 2,
	OPTIONS_3 = 3,
	OPTIONS_4 = 4,
	EXIT = 5,
};

const std::string get_current_time(void)
{
	char time_string[64];
	auto time = std::chrono::system_clock::now();
	auto time_c = std::chrono::system_clock::to_time_t(time);
	std::tm now_tm = *std::localtime(&time_c);
	strftime(time_string, sizeof(time_string), "%A %c", &now_tm);
	return (std::string(time_string));
}

static void init_logs_1_stage(void)
{
	int fd_error_logs = open("err_logs.txt", O_CREAT | O_WRONLY, S_IRWXU);
	if (fd_error_logs < 0)
	{
		endwin();
		printf("Cannot create error logs file\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_error_logs, STDERR_FILENO) < 0)
	{
		endwin();
		printf("Cannot attach to error logs file\n");
		exit(EXIT_FAILURE);
	}
}

inline void logs_err(std::string logs)
{
	std::string time = get_current_time();
	fprintf(stderr, "Logs %s: ERROR: %s\n", time.c_str(), logs.c_str());
}

inline void logs_debug(std::string logs)
{
	std::string time = get_current_time();
	fprintf(stdout, "Logs %s: DEBUG: %s\n", time.c_str(), logs.c_str());
}

inline void init_ncurse(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	init_logs_1_stage();
}

static Options menu(void)
{
	enum Options opt = Options::EXIT;
	ITEM **my_items;
	MENU *my_menu;
	std::vector<std::pair<std::string, std::string>> choices = {
			{"1. C++", "Creating C++ enviroment"},
			{"2. C", "Creating C enviroment"},
			{"3. Python", "Crearing Python source file"},
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

	int c;
	unsigned int current_options;
	while ((c = getch()))
	{
		switch (c)
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
			opt = static_cast<Options>(current_options);
			return opt;
			break;
		}
		}
	}
	return opt;
}
void cpp_menu()
{
	// TODO
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
	Options choice = menu();
	switch (choice)
	{
	case Options::OPTIONS_1:
	{
		cpp_menu();
		break;
	}
	case Options::OPTIONS_2:
	{
		c_menu();
		break;
	}
	case Options::OPTIONS_3:
	{
		pyhon_menu();
		break;
	}
	case Options::OPTIONS_4:
	{
		sh_menu();
		break;
	}
	case Options::EXIT:
	{
		endwin();
		exit(EXIT_SUCCESS);
		break;
	}
	default:
	{
		endwin();
		exit(EXIT_FAILURE);
		logs_err("Something went wrong");
	}
	}
	endwin();
	return 0;
}