#include <iostream>
#include "String.h" // Assuming your String class is declared in String.h

int main() {
    // Test Length(), CharacterAt(), EqualTo(), Append(), Prepend(), CStr(), ToLower(), ToUpper()
    String str("Hello");
    std::cout << "Length: " << str.Length() << std::endl;
    std::cout << "Character at index 2: " << str.CharacterAt(2) << std::endl;
    std::cout << "EqualTo(\"Hello\"): " << (str.EqualTo("Hello") ? "true" : "false") << std::endl;

    String appendStr(" world!");
    str.Append("appendStr");
    std::cout << "Appended string: " << str.CStr() << std::endl;

    String prependStr("Hi, ");
    str.Prepend(prependStr);
    std::cout << "Prepended string: " << str.CStr() << std::endl;

    std::cout << "Lowercase string: ";
    str.ToLower();
    std::cout << str.CStr() << std::endl;

    std::cout << "Uppercase string: ";
    str.ToUpper();
    std::cout << str.CStr() << std::endl;

    // Test Find(), Replace()
    String testString("hello world, hello!hello");
    String findString("hello");
    String replaceString("hi");
    std::cout << "Find(\"hello\"): " << testString.Find(findString) << std::endl;
    std::cout << "Replace(\"hello\", \"hi\"): ";
    testString.Replace(findString, replaceString);
    std::cout << testString.CStr() << std::endl;

    // Test ReadFromConsole(), WriteToConsole()
    std::cout << "Enter a string: ";
    String userInput;
    userInput.ReadFromConsole();
    std::cout << "User input: ";
    userInput.WriteToConsole();
    std::cout << std::endl;

    // Test Equality Operator ( == )
    String str1("hello");
    String str2("world");
    std::cout << "str1: " << str1.CStr() << std::endl;
    std::cout << "str2: " << str2.CStr() << std::endl;
    std::cout << "str1 == str2: " << (str1 == str2 ? "true" : "false") << std::endl;

    // Test Subscript Operator ( [] )
    std::cout << "Character at index 2: " << str[2] << std::endl;

    // Test Assignment Operator ( = )
    String assignedString;
    assignedString = str;
    std::cout << "Assigned string: " << assignedString.CStr() << std::endl;

    // Test LessThan Operator ( < )
    String lessThanStr("apple");
    String greaterThanStr("banana");
    std::cout << "lessThanStr < greaterThanStr: " << (lessThanStr < greaterThanStr ? "true" : "false") << std::endl;

    // Test Plus Operator ( + )
    String plusStr = str1 + str2;
    std::cout << "Concatenated string: " << plusStr.CStr() << std::endl;

    // Test Plus Equals Operator ( += )
    String plusEqualsStr("Hello");
    plusEqualsStr += " world!";
    std::cout << "+= result: " << plusEqualsStr.CStr() << std::endl;

    return 0;
}
