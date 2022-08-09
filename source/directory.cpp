#include <cstdlib>
#include <iostream>
#include <curses.h>

#include "../include/directory.hpp"
#include "../include/app.hpp"

std::vector<std::string> directory::get_directory_list(const std::filesystem::path& current_path) {
    
    std::vector<std::string> options; 

    for(const auto &dir_entry : std::filesystem::directory_iterator(current_path)) 
    {   
        if(dir_entry.is_directory() == true) {
            const auto directory_name = dir_entry.path().filename().string();
            if(directory_name[0] != '.') {
                options.push_back(directory_name);
            }
        }   
        else { continue; }
    }

    return options;
}

//const std::filesystem::path directory::directory_menu(app::Menu_options& m_options) {
	// std::filesystem::path path_to_chosen_driectory;
    // ITEM **my_items;
	// MENU *my_menu;
	// std::size_t num_of_choices = m_options.size();
	// my_items = (ITEM **)calloc(num_of_choices + 1, sizeof(ITEM *));
	// for (size_t i = 0; i < num_of_choices; i++)
	// {
	// 	my_items[i] = new_item(m_options[i].first.c_str(),
	// 												 m_options[i].second.c_str());
	// }
	// my_items[num_of_choices] = (ITEM *)NULL;

	// my_menu = new_menu((ITEM**)my_items);
	// post_menu(my_menu);
	// refresh();

	// int key;

	// while ((key = getch()))
	// {
	// 	switch (key)
	// 	{
	// 	case KEY_DOWN:
	// 	{
	// 		menu_driver(my_menu, REQ_DOWN_ITEM);
	// 		break;
	// 	}
	// 	case KEY_UP:
	// 	{
	// 		menu_driver(my_menu, REQ_UP_ITEM);
	// 		break;
	// 	}
    //     case KEY_RIGHT: {
    //         //menu_format()
    //         menu_driver(my_menu, REQ_RIGHT_ITEM);
    //     }
    //     case KEY_LEFT: {
    //         menu_driver(my_menu, REQ_RIGHT_ITEM);
    //     }
	// 	case 10: /* ENTER KEY */
	// 	{
	// 		char selected_item = item_name(current_item(my_menu))[0];
	// 		break;
	// 	} 
    //     }
    // }
    // free(my_items);
    // free(my_menu);
    // return path_to_chosen_driectory;
//}


bool directory::create_directory(std::filesystem::path& p)
{
    (void)p;
    // TODOOO

    return true;
}

void directory::directory_menu()
{
    const char *home_path = secure_getenv("HOME");
    if (home_path == NULL) {
        app::logs_err("Cannot get $HOME variable");
        exit(EXIT_FAILURE);
    } 
    const std::filesystem::path home_directory{home_path};
    
    auto option_vector = directory::get_directory_list(home_path);
    
    printw("%s", "Choose Directory");

    app::Menu_options directory_options; 
    
    for(size_t i = 0; i < option_vector.size(); i++) {
        directory_options.push_back(std::make_pair(option_vector.at(i), "Director"));
    }
    directory_options.push_back(std::make_pair("Exit", ""));



    char key = getch();
}
