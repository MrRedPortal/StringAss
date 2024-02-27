#include <iostream>
#include "String.h"


int main() {
    // Create a String object
    String myString;

    // Read input from the console
    myString.ReadFromConsole();

    // Print the string
    std::cout << "String read from console: ";
    myString.WriteToConsole();
    std::cout << std::endl;

    // Display the original input
    std::cout << "Original string: ";
    myString.WriteToConsole();
    std::cout << std::endl;

    // Convert the string to uppercase
    myString.ToUpper();
    std::cout << "String in uppercase: ";
    myString.WriteToConsole();
    std::cout << std::endl;

    // Convert the string to lowercase
    myString.ToLower();
    std::cout << "String in lowercase: ";
    myString.WriteToConsole();
    std::cout << std::endl;

    // Find a substring
    String findString("world");
    size_t index = myString.Find(findString);
    if (index != static_cast<size_t>(-1)) {
        std::cout << "Substring '" << findString.CStr() << "' found at index: " << index << std::endl;
    }
    else {
        std::cout << "Substring '" << findString.CStr() << "' not found." << std::endl;
    }

    // Append a string
    String appendString(" from Nic's computer");
    myString.Append(appendString);
    std::cout << "String after appending: ";
    myString.WriteToConsole();
    std::cout << std::endl;

    // Prepend a string
    String prependString("Good evening ");
    myString.Prepend(prependString);
    std::cout << "String after prepending: ";
    myString.WriteToConsole();
    std::cout << std::endl;

    // Replace a substring
    String replaceString("hello world");
    String replaceWithString("everyone");
    myString.Replace(replaceString, replaceWithString);
    std::cout << "String after replacing: ";
    myString.WriteToConsole();
    std::cout << std::endl;

    return 0;
}
