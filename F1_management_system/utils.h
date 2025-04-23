// Utils.h

// Header guard to revent multiple inclusions of th file.
#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <iostream> // Include input/output stream 

using namespace std; // Use namespace std to avoid using std prefix

// ************ Display Banner & Utility ************
// Displays ASCII "banner"
// Uses "inline" to ensure that the function runs at runtime and prints the banner to the console screen.
inline void displayBanner(){
    // Uses raw string literal for ASCII art banner.
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

// Clears the screen and displays the banner again 
inline void clearScreenDisplayBanner(){
    system("CLS"); // Clear screen (Windows)
    displayBanner(); // Calls displayBanner()
}

// This function pauses the screen and asks the user to press enter to continue.
inline void pauseScreen(){
    cout << "\nPress Enter to continue..."; // Output message to screen.
    // cin.ignore();
    cin.get(); // Waits for the user to press enter.
}

// Handles invalid characters being input. 
inline void handleInvalidInputChar() {
    // Handle invalid input using a character
        cin.clear();  // Clear the error state
        cin.ignore(100, '\n');  // Discard invalid input up to the next newline
        cout << "\nInvalid input. Please enter a number." << endl; // Outputs message to screen
        cout << "Press Enter to continue...";
        cin.get();  // Wait for user to press Enter.
}

#endif // INPUT_UTILS_H
