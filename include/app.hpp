#pragma once
#include <string>
namespace app
{
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
	void cpp_menu();
	void init_logs_1_stage(void);
} // namespace app
