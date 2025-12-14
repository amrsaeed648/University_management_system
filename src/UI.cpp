#include <chrono>
#include <iostream>
#include <string>
#include <thread>

// ================= COLORS =================
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// ================= BACKGROUND COLORS =================
#define BG_BLACK   "\033[40m"
#define BG_RED     "\033[41m"
#define BG_GREEN   "\033[42m"
#define BG_YELLOW  "\033[43m"
#define BG_BLUE    "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN    "\033[46m"
#define BG_WHITE   "\033[47m"

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
