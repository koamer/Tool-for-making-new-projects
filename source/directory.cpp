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
    
    std::size_t menu_size = option_vector.size();

    for(size_t i = 0; i < menu_size; i++) {
        directory_options.push_back(std::make_pair(option_vector.at(i), "Director"));
    }
    directory_options.push_back(std::make_pair("Exit", ""));

    auto result = app::menu(directory_options);


    char key = getch();
}
