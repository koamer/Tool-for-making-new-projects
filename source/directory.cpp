#include "../include/directory.hpp"
#include <dirent.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <curses.h>

bool create_directory(void)
{
    // directory::directory_menu();

    return true;
}

void directory::directory_menu()
{
    DIR *current_directory = opendir("~");
    if (current_directory == NULL)
    {
        fprintf(stderr,
                "Cannot open home directory. Check perrmisions");
        endwin();
        exit(EXIT_FAILURE);
    }
}