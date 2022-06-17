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
	auto time = std::chrono::system_clock::now();
	auto time_c = std::chrono::system_clock::to_time_t(time);
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

app::Options app::menu(app::Menu_options& m_options)
{
	enum app::Options opt = app::Options::EXIT;
	ITEM **my_items;
	MENU *my_menu;
	std::size_t num_of_choices = m_options.size();
	my_items = (ITEM **)calloc(num_of_choices + 1, sizeof(ITEM *));
	for (size_t i = 0; i < num_of_choices; i++)
	{
		my_items[i] = new_item(m_options[i].first.c_str(),
													 m_options[i].second.c_str());
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
