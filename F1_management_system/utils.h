// Utils.h
#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <iostream>
#include <limits>

using namespace std;

// ************ Display Banner & Utility ************
inline void displayBanner(){
    cout << R"(
        _________   __  ___                                             __
       / ____<  /  /  |/  /___ _____  ____ _____ _____ ___  ___  ____  / /_
      / /_   / /  / /|_/ / __ `/ __ \/ __ `/ __ `/ __ `__ \/ _ \/ __ \/ __/
     / __/  / /  / /  / / /_/ / / / / /_/ / /_/ / / / / / /  __/ / / / /_  
    /_/____/_/  /_/  /_/\__,_/_/ /_/\__,_/\__, /_/ /_/ /_/\___/_/ /_/\__/  
      / ___/__  _______/ /____  ____ ___ /____/
      \__ \/ / / / ___/ __/ _ \/ __ `__ \
     ___/ / /_/ (__  ) /_/  __/ / / / / /
    /____/\__, /____/\__/\___/_/ /_/ /_/
         /____/
    )" << '\n';
}

inline void clearScreenDisplayBanner(){
    system("CLS"); // Clear screen (Windows)
    displayBanner();
}

inline void pauseScreen(){
    cout << "\nPress Enter to continue...";
    // cin.ignore();
    cin.get();
}

inline void handleInvalidInputChar() {
    // Handle invalid input using a character
        cin.clear();  // Clear the error state
        cin.ignore(100, '\n');  // Discard invalid input up to the next newline
        cout << "\nInvalid input. Please enter a number." << endl;
        cout << "Press Enter to continue...";
        cin.get();  // Wait for user to press Enter
}

#endif // INPUT_UTILS_H
