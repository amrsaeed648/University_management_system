#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define WHITE   "\033[37m"
#define BG_BLACK "\033[40m"



using namespace std;


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void sleepMs(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void animatedPrint(const string& text) {
    for (char c : text) {
        cout << c << flush;
        sleepMs(1);
    }
}

void printBanner() {
    cout << BG_BLACK << WHITE << BOLD << R"(
═══════════════════════════════════════════════════════════════════════════════════════════

                            ███████╗███████╗██╗  ██╗██╗   ██╗
                            ██╔════╝██╔════╝██║  ██║██║   ██║
                            █████╗  █████╗  ███████║██║   ██║
                            ██╔══╝  ██╔══╝  ██╔══██║██║   ██║
                            ██║     ███████╗██║  ██║╚██████╔╝
                            ╚═╝     ╚══════╝╚═╝  ╚═╝ ╚═════╝

                                   MANAGEMENT SYSTEM
═══════════════════════════════════════════════════════════════════════════════════════════

)" << RESET;
}