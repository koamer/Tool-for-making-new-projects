#pragma once

#include <string>
#include <vector>
#include <menu.h>
#include <curses.h>

namespace app
{
	using Menu_options = std::vector<std::pair<std::string, std::string>>; 
	using Options_index = uint16_t;

	const std::string get_current_time(void);

	void logs_err(std::string logs);
	void init_logs_1_stage(void);

	Options_index basic_menu(app::Menu_options& m_options);

	void c_menu();
	void cpp_menu();
	void python_menu();
	void sh_menu();

} // namespace app
