#include <curses.h>
#include <chrono>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#include "../include/app.hpp"
#include "../include/directory.hpp"


const std::string app::get_current_time(void)
{
	char time_string[64];
	auto time_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm now_tm = *std::localtime(&time_c);
	strftime(time_string, sizeof(time_string), "%A %c", &now_tm);
	return std::string(time_string);
}

void app::logs_err(std::string logs)
{
	std::string time = app::get_current_time();
	std::cerr << "Logs " << time.c_str() << " ERROR: " << logs.c_str() << std::endl;
}

void app::init_logs_1_stage(void) {
	int fd_error_logs = open("err_logs.txt",
				O_CREAT | O_WRONLY,
				S_IRWXU);
	if(fd_error_logs < 0)
	{
		endwin();
		printf("Cannot create error logs file\n");
		exit(EXIT_FAILURE);
	}
	if(dup2(fd_error_logs, STDERR_FILENO) < 0)
	{
		endwin();
		printf("Cannot attach to error logs file\n");
		exit(EXIT_FAILURE);
	}
}

app::Options_index app::basic_menu(app::Menu_options& m_options)
{
	Options_index opt = 0;
	ITEM **my_items;
	MENU *my_menu;
	WINDOW *menu_window;
	std::size_t num_of_choices = m_options.size();
	my_items = (ITEM **)calloc(num_of_choices + 1, sizeof(ITEM *));
	for (size_t i = 0; i < num_of_choices; i++)
	{
		my_items[i] = new_item(m_options[i].first.c_str(),
													 m_options[i].second.c_str());
	}
	my_items[num_of_choices] = (ITEM *)NULL;

	my_menu = new_menu((ITEM**)my_items);

	menu_opts_off(my_menu, O_SHOWDESC);
	menu_window = newwin(10, 70, 4, 4);
	keypad(menu_window, TRUE);
	
	set_menu_win(my_menu, menu_window);
	set_menu_sub(my_menu, derwin(menu_window, 6, 68, 3, 1));
	set_menu_format(my_menu, static_cast<int>(num_of_choices), 1);
	set_menu_mark(my_menu, "  -> ");

	
    box(menu_window, 0, 0);
	
	attron(COLOR_PAIR(2));
	mvprintw(LINES - 2, 0, "Use Arrow Keys to navigate");
	attroff(COLOR_PAIR(2));
	refresh();

	post_menu(my_menu);
	wrefresh(menu_window);

	int key;

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
			char selected_item = item_name(current_item(my_menu))[0];
			opt = static_cast<Options_index>(selected_item - '0');
			return opt;
		}
		}
		wrefresh(menu_window);
	}
	
	unpost_menu(my_menu);
    free_menu(my_menu);
	for(size_t i = 0; i < num_of_choices; ++i) {
		free_item(my_items[i]);
	}
	return opt;
}

void app::c_menu()
{
	clear();
	directory::directory_menu();
	// TODOOO
}
void app::cpp_menu()
{
	// TODOOO
}
void app::python_menu()
{
	// TODOOO
}
void app::sh_menu() {
	// TODOOO
}
