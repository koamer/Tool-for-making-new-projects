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

// TODO: Check if it's possible to implement in C++, current implementation in C UNIX API
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
