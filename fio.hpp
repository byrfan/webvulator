#include <fstream>
#include <iterator>
#include <streambuf>
#include <string>

std::string readFile(std::string name)
{
    std::ifstream ifs("assets/"+name);

    std::string content((std::istreambuf_iterator<char>(ifs)), 
                        (std::istreambuf_iterator<char>()));

    return content;
}



