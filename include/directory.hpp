#pragma once

#include <filesystem>
#include <vector>

namespace directory
{
    bool create_directory(std::filesystem::path& p);

    void directory_menu();

    std::vector<std::string> get_directory_list(const std::filesystem::path& path);    
} // namespace directory

