#include <string>
#include <chrono>
#include <cstdio>

#include "../include/app.hpp"

const std::string app::get_current_time(void)
{
	char time_string[64];
	auto time = std::chrono::system_clock::now();
	auto time_c = std::chrono::system_clock::to_time_t(time);
	std::tm now_tm = *std::localtime(&time_c);
	strftime(time_string, sizeof(time_string), "%A %c", &now_tm);
	return (std::string(time_string));
}
inline void app::logs_err(std::string logs)
{
	std::string time = app::get_current_time();
	fprintf(stderr, "Logs %s: ERROR: %s\n", time.c_str(), logs.c_str());
}
void cpp_menu()
{
}