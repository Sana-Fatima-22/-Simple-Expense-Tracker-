#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <limits> // For numeric_limits

using namespace std;

const string expenseFile = "expenses.txt";

// Function to record a new expense
void recordExpense() {
    ofstream file(expenseFile, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    string description;
    double amount;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any remaining newline characters

    cout << "Enter expense description: ";
    getline(cin, description);

    cout << "Enter expense amount: $";
    while (!(cin >> amount) || amount <= 0) {
        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "Invalid amount. Please enter a valid positive number: $";
    }

    // Get current time
    time_t now = time(0);
    tm* localTime = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localTime);

    // Write expense details to file
    file << buffer << " | " << description << " | $" << fixed << setprecision(2) << amount << endl;
    file.close();

    cout << "Expense recorded successfully!" << endl;
}

// Function to display all recorded expenses
void displayExpenses() {
    ifstream file(expenseFile);
    if (!file.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    cout << "--- All Recorded Expenses ---" << endl;
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

// Function to summarize total expenses
void summarizeExpenses() {
    ifstream file(expenseFile);
    if (!file.is_open()) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    double total = 0.0;
    string line;
    while (getline(file, line)) {
        size_t pos = line.find_last_of("$");
        string amountStr = line.substr(pos + 1);
        double amount = stod(amountStr);
        total += amount;
    }

    file.close();

    cout << "Total expenses: $" << fixed << setprecision(2) << total << endl;
}

// Main function to drive the application
int main() {
    int choice;

    cout << "Welcome to ExpenseTracker!" << endl;

    // Ensure expenses.txt file exists or create it if not
    ofstream checkFile(expenseFile, ios::app);
    if (!checkFile.is_open()) {
        cerr << "Error creating/opening file: " << expenseFile << endl;
        return 1;
    }
    checkFile.close();

    do {
        cout << "\n1. Record a new expense" << endl;
        cout << "2. Display all recorded expenses" << endl;
        cout << "3. Summarize total expenses" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                recordExpense();
                break;
            case 2:
                displayExpenses();
                break;
            case 3:
                summarizeExpenses();
                break;
            case 4:
                cout << "Exiting ExpenseTracker. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                break;
        }
    } while (choice != 4);

    return 0;
}
