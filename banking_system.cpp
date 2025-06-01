#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Transaction {
    string type;
    float amount;
    string note;
};

class Account {
private:
    string accNumber;
    string accHolder;
    float balance;
    vector<Transaction> transactions;

public:
    Account(string number, string holder) {
        accNumber = number;
        accHolder = holder;
        balance = 0;
    }

    string getAccNumber() { return accNumber; }
    string getHolderName() { return accHolder; }
    float getBalance() { return balance; }

    void deposit(float amount, string note = "Deposit") {
        balance += amount;
        transactions.push_back({ "Deposit", amount, note });
    }

    bool withdraw(float amount, string note = "Withdraw") {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        transactions.push_back({ "Withdraw", amount, note });
        return true;
    }

    bool transfer(Account &toAccount, float amount) {
        if (withdraw(amount, "Transfer to " + toAccount.getAccNumber())) {
            toAccount.deposit(amount, "Transfer from " + accNumber);
            return true;
        }
        return false;
    }

    void showDetails() {
        cout << "Account Number: " << accNumber << endl;
        cout << "Account Holder: " << accHolder << endl;
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void showTransactions() {
        cout << "Transactions for " << accNumber << ":\n";
        for (auto &t : transactions) {
            cout << t.type << ": $" << fixed << setprecision(2) << t.amount;
            if (!t.note.empty()) cout << " (" << t.note << ")";
            cout << endl;
        }
    }
};

class Bank {
private:
    vector<Account> accounts;

public:
    Account* findAccount(string accNumber) {
        for (auto &acc : accounts) {
            if (acc.getAccNumber() == accNumber) {
                return &acc;
            }
        }
        return nullptr;
    }

    void createAccount() {
        string name, accNo;
        cout << "Enter account holder name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter new account number: ";
        cin >> accNo;

        if (findAccount(accNo)) {
            cout << "Account number already exists!\n";
            return;
        }

        accounts.emplace_back(accNo, name);
        cout << "Account created successfully!\n";
    }

    void depositMoney() {
        string accNo;
        float amount;
        cout << "Enter account number: ";
        cin >> accNo;
        Account* acc = findAccount(accNo);
        if (acc) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            acc->deposit(amount);
            cout << "Deposit successful.\n";
        } else {
            cout << "Account not found.\n";
        }
    }

    void withdrawMoney() {
        string accNo;
        float amount;
        cout << "Enter account number: ";
        cin >> accNo;
        Account* acc = findAccount(accNo);
        if (acc) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            if (acc->withdraw(amount)) {
                cout << "Withdrawal successful.\n";
            }
        } else {
            cout << "Account not found.\n";
        }
    }

    void transferMoney() {
        string fromAccNo, toAccNo;
        float amount;
        cout << "Enter sender account number: ";
        cin >> fromAccNo;
        cout << "Enter receiver account number: ";
        cin >> toAccNo;
        cout << "Enter amount to transfer: ";
        cin >> amount;

        Account* from = findAccount(fromAccNo);
        Account* to = findAccount(toAccNo);

        if (from && to) {
            if (from->transfer(*to, amount)) {
                cout << "Transfer successful.\n";
            }
        } else {
            cout << "One or both accounts not found.\n";
        }
    }

    void viewAccountDetails() {
        string accNo;
        cout << "Enter account number: ";
        cin >> accNo;
        Account* acc = findAccount(accNo);
        if (acc) {
            acc->showDetails();
        } else {
            cout << "Account not found.\n";
        }
    }

    void viewTransactions() {
        string accNo;
        cout << "Enter account number: ";
        cin >> accNo;
        Account* acc = findAccount(accNo);
        if (acc) {
            acc->showTransactions();
        } else {
            cout << "Account not found.\n";
        }
    }
};

int main() {
    Bank bank;
    int choice;

    do {
        cout << "\n======== BANKING SYSTEM MENU ========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. View Account Details\n";
        cout << "6. View Transaction History\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.depositMoney(); break;
            case 3: bank.withdrawMoney(); break;
            case 4: bank.transferMoney(); break;
            case 5: bank.viewAccountDetails(); break;
            case 6: bank.viewTransactions(); break;
            case 7: cout << "Thank you for using our Banking System!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
