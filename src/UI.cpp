#include <chrono>
#include <iostream>
#include <string>
#include <thread>
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
