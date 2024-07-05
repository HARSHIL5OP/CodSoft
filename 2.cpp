#include <iostream>
#include <iomanip> // For setw
#include <cstdlib> // For system
#include <string>  // For to_string

#define width 50

using namespace std;

void printDecor() {
    cout << string(width, '-') << "\n";
}

void printCentered(string message) {
    int messageLength = message.length();
    int padding = (width - messageLength) / 2;

    cout << setfill('-') << setw(padding) << "" << message << setw(padding + messageLength % 2) << "" << "\n";
}

int main() {
    char op;
    double num1, num2, result;

    system("cls");

    printDecor();
    printCentered("Simple Calculator Program");
    printDecor();

    cout << "Enter first number: ";
    cin >> num1;

    cout << "Enter second number: ";
    cin >> num2;

    cout << "Enter the operation (+, -, *, /): ";
    cin >> op;

    switch(op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if(num2 != 0)
                result = num1 / num2;
            else {
                printDecor();
                printCentered("Error! Division by zero is not allowed.");
                printDecor();
                return 1;
            }
            break;
        default:
            printDecor();
            printCentered("Error! Invalid operation.");
            printDecor();
            return 1;
    }

    printDecor();
    cout << setprecision(2) << fixed; 
    cout << "Result = " << result << "\n";
    printDecor();

    return 0;
}

