#include <iostream>
#include <iomanip> // For setw
#include <cstdlib> // For rand
#include <ctime>   // For time
#include <stdlib.h> // For system

using namespace std;

const int width = 80;
int randomNumber, ll, ul;

void printDecor() {
    for (int i = 0; i < width; i++) {
        cout << "-";
    }
    cout << "\n";
}

void printCentered(string message) {
    int messageLength = message.length();
    int padding = (width - messageLength) / 2;
    cout << setfill('-') << setw(padding) << "" << message << setw(padding + messageLength % 2) << "" << "\n";
}

int generateRandomNumber(int ll, int ul) {
    return (rand() % (ul - ll + 1) + ll);
}

void checkFarness(int guess, bool badaGuess) {
    int tooHigh, high, close, tooClose;
    int diff = ul - ll;
    tooHigh = diff / 2;
    high = diff / 5;
    close = diff / 10;
    int diff2;
    if (badaGuess) {
        diff2 = guess - randomNumber;
    } else {
        diff2 = randomNumber - guess;
    }
    if (diff2 >= tooHigh) {
        cout << "Too Far\n";
    } else if (diff2 > high && diff2 <= tooHigh) {
        cout << "Far\n";
    } else if (diff2 > close && diff2 <= high) {
        cout << "Close\n";
    } else if (diff2 <= close) {
        cout << "Very Close\n";
    }
    cout << "\n";
}

void NumberGuess() {
    int guess;
    for (int i = 0; i < 6; i++) {
        cout << "Guess The Number: ";
        cin >> guess;
        if (guess == randomNumber) {
            cout << "Correct Guess! Congratulations :) You Won The Game\n\n";
            break;
        } else if (i == 5) {
            cout << "Better Luck Next Time! You lost the Game :(\n";
            printDecor();
            cout << "The Correct Number was => " << randomNumber << "\n\n";
        } else {
            cout << "Oops!! Try Again\n";
            if (guess > randomNumber) {
                cout << "Your Guess is Greater than The Actual Number!\n";
                checkFarness(guess, true);
            } else if (guess < randomNumber) {
                cout << "Your Guess is Smaller than The Actual Number!\n";
                checkFarness(guess, false);
            }
            cout << "Number of Attempts Left = " << 6 - (i + 1) << "\n";
        }
    }
}

int main() {
    srand(time(0)); // Seed the random number generator with the current time
    system("cls");
    printDecor();
    printCentered("Welcome To Number Guessing Game!!");
    printDecor();
    printCentered("Specify Range for Random Number");
    printDecor();
    cout << "Enter Lower Limit: ";
    cin >> ll;
    cout << endl;
    cout << "Enter Upper Limit: ";
    cin >> ul;
    cout << endl;
    if (ul == ll) {
        cout << "Lower Limit and Upper Limit can't be Equal!\n\n";
        printDecor();
    } else if (ll > ul) {
        cout << "Lower Limit can't be Greater than Upper Limit!\n\n";
        printDecor();
    } else {
        randomNumber = generateRandomNumber(ll, ul);
      //
	  //  cout << randomNumber << "\n";
        printDecor();
        printCentered("A Random Number is Generated within your Specified Range");
        printDecor();
        printCentered("Now you have 6 Chances to Guess the Number");
        NumberGuess();
        printDecor();
    }
    return 0;
}

