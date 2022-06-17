#pragma once

#include <string>
#include <vector>
#include <menu.h>
#include <curses.h>

namespace app
{
	using Menu_options = std::vector<std::pair<std::string, std::string>>; 
	
	enum class Options
	{
		OPTIONS_1 = 1,
		OPTIONS_2 = 2,
		OPTIONS_3 = 3,
		OPTIONS_4 = 4,
		EXIT = 5,
	};

	const std::string get_current_time(void);

	void logs_err(std::string logs);
	void init_logs_1_stage(void);

	Options menu(app::Menu_options& m_options);

	void c_menu();
	void cpp_menu();
	void python_menu();
	void sh_menu();

} // namespace app
