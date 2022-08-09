#pragma once

#include <filesystem>
#include <vector>

namespace directory
{
    bool create_directory(std::filesystem::path& p);

    void directory_menu();

    std::vector<std::string> get_directory_list(const std::filesystem::path& path);
    //const std::filesystem::path directory_menu(app::Menu_options& m_options);    
} // namespace directory

