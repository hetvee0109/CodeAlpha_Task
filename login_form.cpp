#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function declarations
void registerUser();
void loginUser();
bool credentialsMatch(const string& user, const string& pass);

int main() {
    int choice;

    do {
        cout << "\n===========================================\n";
        cout << "         LOGIN & REGISTRATION SYSTEM       \n";
        cout << "===========================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "-------------------------------------------\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            cout << "\nThank you for using the system. Goodbye!\n";
            break;
        default:
            cout << "\nInvalid choice! Please enter 1, 2, or 3.\n";
        }
    } while (choice != 3);

    return 0;
}

void registerUser() {
    string username, password;
    cout << "\n========== USER REGISTRATION ==========\n";
    cout << "Please enter a username: ";
    cin >> username;
    cout << "Please enter a password: ";
    cin >> password;

    ofstream file("database.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << password << endl;
        file.close();
        cout << "\n User '" << username << "' registered successfully!\n";
    } else {
        cout << "\n Error: Unable to open file for writing.\n";
    }
}

void loginUser() {
    string username, password;
    cout << "\n============= USER LOGIN =============\n";
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    if (credentialsMatch(username, password)) {
        cout << "\n Login successful! Welcome, " << username << ".\n";
    } else {
        cout << "\ns Login failed! Invalid username or password.\n";
    }
}

bool credentialsMatch(const string& user, const string& pass) {
    ifstream file("database.txt");
    string u, p;

    if (file.is_open()) {
        while (file >> u >> p) {
            if (u == user && p == pass) {
                return true;
            }
        }
        file.close();
    }
    return false;
}
