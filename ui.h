
#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>

namespace UI {

    // Console colors
    const std::string RESET  = "\033[0m";
    const std::string BLUE   = "\033[94m";
    const std::string CYAN   = "\033[96m";
    const std::string GREEN  = "\033[92m";
    const std::string YELLOW = "\033[93m";
    const std::string RED    = "\033[91m";
    const std::string WHITE  = "\033[97m";
    const std::string BOLD   = "\033[1m";

    inline void clearScreen() {
        std::cout << "\033[2J\033[H";
    }

    inline void line() {
        std::cout << CYAN
                  << "====================================================\n"
                  << RESET;
    }

    inline void header(const std::string& title) {
        std::cout << "\n" << BLUE << BOLD;
        line();
        std::cout << "   " << title << "\n";
        line();
        std::cout << RESET;
    }

    inline void success(const std::string& message) {
        std::cout << GREEN << "[SUCCESS] "
                  << message << RESET << "\n";
    }

    inline void error(const std::string& message) {
        std::cout << RED << "[ERROR] "
                  << message << RESET << "\n";
    }

    inline void pause() {
        std::cout << "\n" << YELLOW
                  << "  Press any key to continue..."
                  << RESET;
        _getch();
    }

}

#endif
