#include <iostream>
#include <fstream> // For file operations
#include <vector> // For vector
#include "String.h" // Assuming your String class is declared in String.h

void writeTestResults(std::ofstream& logfile, double successRate, const std::vector<std::pair<std::string, bool>>& testResults) {
    // Get current date and time
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    char timeBuffer[80];
    std::strftime(timeBuffer, 80, "%c", localTime);

    // Write date/time and success rate to log file and console
    std::cout << "Date: " << timeBuffer << " Successful: " << successRate << "%" << std::endl;
    logfile << "Date: " << timeBuffer << " Successful: " << successRate << "%" << std::endl;

    // Write individual test results to log file and console
    for (const auto& test : testResults) {
        std::cout << test.first << (test.second ? " Passed" : " Failed") << std::endl;
        logfile << test.first << (test.second ? " Passed" : " Failed") << std::endl;
    }
    std::cout << std::endl;
    logfile << std::endl;
}


int main() {
    // Open or create log file in append mode
    std::ofstream logfile("test_log.txt", std::ios_base::app);
    if (!logfile.is_open()) {
        std::cerr << "Failed to open log file!" << std::endl;
        return 1;
    }

    // Test Length(), CharacterAt(), EqualTo(), Append(), Prepend(), CStr(), ToLower(), ToUpper()
    String str("Hello");
    std::vector<std::pair<std::string, bool>> testResults;

    // Run tests and store results
    testResults.emplace_back("Length Test", str.Length() == 5);
    testResults.emplace_back("CharacterAt Test", str.CharacterAt(2) == 'l');
    testResults.emplace_back("EqualTo Test", str.EqualTo("Hello"));

    String appendStr(" world!");
    str.Append(appendStr);
    testResults.emplace_back("Append Test", str.EqualTo("Hello world!"));

    String prependStr("Hi, ");
    str.Prepend(prependStr);
    testResults.emplace_back("Prepend Test", str.EqualTo("Hi, Hello world!"));

    str.ToLower();
    testResults.emplace_back("ToLower Test", str.EqualTo("hi, hello world!"));

    str.ToUpper();
    testResults.emplace_back("ToUpper Test", str.EqualTo("HI, HELLO WORLD!"));

    // Test Find(), Replace()
    String testString("hello world, hello!hello");
    String findString("hello");
    String replaceString("hi");
    testResults.emplace_back("Find Test", testString.Find(findString) == 0);
    testString.Replace(findString, replaceString);
    testResults.emplace_back("Replace Test", testString.EqualTo("hi world, hi!hi"));

    // Test ReadFromConsole(), WriteToConsole()
    String userInput;
    userInput.ReadFromConsole();
    std::cout << "User input: ";
    userInput.WriteToConsole();
    std::cout << std::endl;
    testResults.emplace_back("ReadFromConsole & WriteToConsole Test", userInput.EqualTo(userInput));

    // Test Equality Operator ( == )
    String str1("hello");
    String str2("world");
    testResults.emplace_back("Equality Operator Test", !(str1 == str2));

    // Test Subscript Operator ( [] )
    testResults.emplace_back("Subscript Operator Test", str[1] == 'I');

    // Test Assignment Operator ( = )
    String assignedString;
    assignedString = str;
    testResults.emplace_back("Assignment Operator Test", assignedString.EqualTo(str));

    // Test LessThan Operator ( < )
    String lessThanStr("apple");
    String greaterThanStr("banana");
    testResults.emplace_back("LessThan Operator Test", (lessThanStr < greaterThanStr));

    // Test Plus Operator ( + )
    String plusStr = str1 + str2;
    testResults.emplace_back("Plus Operator Test", plusStr.EqualTo("helloworld"));

    // Test Plus Equals Operator ( += )
    String plusEqualsStr("Hello");
    plusEqualsStr += " world!";
    testResults.emplace_back("Plus Equals Operator Test", plusEqualsStr.EqualTo("Hello world!"));

    // Calculate success rate
    int passedTests = 0;
    for (const auto& test : testResults) {
        if (test.second) passedTests++;
    }
    double successRate = (static_cast<double>(passedTests) / testResults.size()) * 100.0;

    // Write test results to log file
    writeTestResults(logfile, successRate, testResults);

    // Close log file
    logfile.close();

    return 0;
}
