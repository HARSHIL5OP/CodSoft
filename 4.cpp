#include <iostream>
#include <iomanip> // For setw
#include <cstdlib> // For system

#define MAX_TASKS 10
#define width 50

using namespace std;

struct Task {
    string description;
    bool completed;
};

Task taskList[MAX_TASKS];
int numTasks = 0;

void clearScreen() {
    system("cls");
}

void printDecor() {
    cout << string(width, '-') << "\n";
}

void printCentered(string message) {
    int messageLength = message.length();
    int padding = (width - messageLength) / 2;
    cout << setfill('-') << setw(padding) << "" << message << setw(padding + messageLength % 2) << "" << "\n";
}

void addTask(string description) {
    if (numTasks < MAX_TASKS) {
        taskList[numTasks].description = description;
        taskList[numTasks].completed = false;
        numTasks++;
        cout << "Task added successfully!\n";
    } else {
        cout << "Cannot add more tasks. Task list is full!\n";
    }
}

void viewTasks() {
    clearScreen();
    printDecor();
    printCentered("To-Do List");
    printDecor();
    if (numTasks == 0) {
        cout << "No tasks available.\n";
    } else {
        for (int i = 0; i < numTasks; ++i) {
            cout << i + 1 << ". " << taskList[i].description << " - " << (taskList[i].completed ? "Completed" : "Pending") << "\n";
        }
    }
    printDecor();
}

void markCompleted(int index) {
    if (index >= 1 && index <= numTasks) {
        taskList[index - 1].completed = true;
        cout << "Task marked as completed.\n";
    } else {
        cout << "Invalid task number!\n";
    }
}

void removeTask(int index) {
    if (index >= 1 && index <= numTasks) {
        for (int i = index - 1; i < numTasks - 1; ++i) {
            taskList[i] = taskList[i + 1];
        }
        numTasks--;
        cout << "Task removed successfully.\n";
    } else {
        cout << "Invalid task number!\n";
    }
}

int main() {
    char choice;
    string taskDescription;
    int taskNumber;

    do {
        clearScreen();
        printDecor();
        printCentered("To-Do List Manager");
        printDecor();
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        printDecor();
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1':
                clearScreen();
                printDecor();
                printCentered("Add Task");
                printDecor();
                cout << "Enter task description: ";
                getline(cin, taskDescription);
                addTask(taskDescription);
                break;
            case '2':
                viewTasks();
                break;
            case '3':
                clearScreen();
                printDecor();
                printCentered("Mark Task as Completed");
                printDecor();
                viewTasks();
                cout << "Enter task number to mark as completed: ";
                cin >> taskNumber;
                markCompleted(taskNumber);
                break;
            case '4':
                clearScreen();
                printDecor();
                printCentered("Remove Task");
                printDecor();
                viewTasks();
                cout << "Enter task number to remove: ";
                cin >> taskNumber;
                removeTask(taskNumber);
                break;
            case '5':
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please enter a number from 1 to 5.\n";
                break;
        }

        system("pause");

    } while (choice != '5');

    return 0;
}

