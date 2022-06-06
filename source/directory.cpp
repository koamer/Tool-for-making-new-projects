#include <filesystem>
#include <cstdlib>
#include <iostream>
#include <curses.h>

#include "../include/directory.hpp"
#include "../include/app.hpp"

bool create_directory(std::filesystem::path& p)
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
    for(const auto &dir_entry : std::filesystem::directory_iterator(home_directory)) 
    {   
        if(dir_entry.is_directory() == true) {
            const auto directory_name = dir_entry.path().filename().string();
            if(directory_name[0] != '.') {
                printw("%s\n", directory_name.c_str());
            }
        }   
        else { continue; }
    }
    char key = getch();
}