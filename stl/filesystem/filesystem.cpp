#include <iostream>
#include <filesystem>


namespace fs = std::experimental::filesystem;

int main()
{
    fs::path path = "root";
    path /= "\\dir";
    std::cout << path << std::endl;  // root\dir

    path /= "child";
    std::cout << path << std::endl;  // root\dir\child

    path.append("child2");
    std::cout << path << std::endl;  // root\dir\child\child2

    path.append("\\child3");
    std::cout << path << std::endl;  // root\dir\child\child2\child3
    return 0;
}
