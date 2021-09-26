#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include <iomanip>
#include <sstream>


namespace fs = std::experimental::filesystem;


int main()
{
    fs::path path = "root";
    path /= "\\dir";
    std::cout << path << std::endl;  // root\dir

    fs::path pathChild = path;
    pathChild /= "child";
    std::cout << pathChild.u8string() << std::endl;  // root\dir\child

    path.append("child2");
    std::cout << path << std::endl;  // root\dir\child\child2

    path.append("\\child3");
    std::cout << path << std::endl;  // root\dir\child\child2\child3

    fs::path filename = path;
    filename.append( "FileName.ext" );
    std::cout << "filename: " << filename << std::endl;
    std::cout << "filename.filename(): " << filename.filename() << std::endl;
    std::cout << "filename.extension(): " << filename.extension() << std::endl;
    std::cout << "filename.stem(): " << filename.stem() << std::endl;

    fs::path filenameNoExt = path;
    filenameNoExt.append("FileName");
    std::cout << "filenameNoExt.filename(): " << filenameNoExt.filename() << std::endl;
    std::cout << "filenameNoExt.extension(): " << filenameNoExt.extension() << std::endl;
    std::cout << "filenameNoExt.stem(): " << filenameNoExt.stem() << std::endl;


    fs::file_time_type filetime = fs::last_write_time("test.txt");
    std::time_t cftime = decltype(filetime)::clock::to_time_t(filetime);
    std::tm tm;
    localtime_s(&tm, &cftime);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%y%m%d_%H%M%S");
    std::cout << "filetime: " << oss.str() << std::endl;

    std::cout << fs::exists("") << std::endl;

    return 0;
}
