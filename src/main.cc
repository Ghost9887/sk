#include <common.h>
#include <sk.h>
#include <fstream>
#include <sstream>
#include <string>

void read_file(const char *file_path) {
    std::string source {};
    std::fstream file { file_path };

    std::stringstream buffer {};
    buffer << file.rdbuf();
    source = buffer.str();
    SK::run(source);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Pouzitie: ./sk <nazov suboru>" << std::endl;
        return 127;
    }
    read_file(argv[1]);
    return 0;
}
