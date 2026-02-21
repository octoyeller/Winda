// Stolen from https://github.com/octoyeller/Pacman-Library

#ifndef _WIN32

#include <unistd.h>

std::string get_binary_directory () {
    char buffer[1024];
    ssize_t len = readlink ("/proc/self/exe", buffer, sizeof (buffer) -1);
    
    if (len == -1) {
        return "";
    }

    buffer[len] = '\0';
    std::string path(buffer);
	std::string fullPath="/";
	fullPath += path.substr(1, path.find_last_of("/"));
	return fullPath;
}

#endif
