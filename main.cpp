#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string BLUE = "\033[34m";
const string BRIGHT_BLUE = "\033[94m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RESET = "\033[0m";

class BankAccount {
private:
    int accountNo;
    string name;
    double balance;

public:
    static int nextAccountNo;

    BankAccount(const string& name, double balance = 0.0)
        : accountNo(nextAccountNo++), name(name), balance(balance) {}

    int getAccountNo() const {
        return accountNo;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << RED << "Invalid deposit amount." << RESET << endl;
            return;
        }

        balance += amount;
        cout << GREEN << "Amount deposited successfully." << RESET << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << RED << "Invalid withdrawal amount." << RESET << endl;
            return;
        }

        if (amount > balance) {
            cout << RED << "Insufficient balance." << RESET << endl;
            return;
        }

        balance -= amount;
        cout << GREEN << "Amount withdrawn successfully." << RESET << endl;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Account No.: " << accountNo << endl;
        cout << "Balance: Rs. " << fixed << setprecision(2) << balance << endl;
        cout << endl;
    }
};

int BankAccount::nextAccountNo = 10001;

class Bank {
private:
    vector<BankAccount> accounts;

    BankAccount* findAccount(int accountNo) {
        for (auto& account : accounts) {
            if (account.getAccountNo() == accountNo) {
                return &account;
            }
        }
        return nullptr;
    }

public:
    void createAccount() {
        string name;
        double initialBalance;

        cout << "\nCreating a new account\n";
        cout << "Enter user name: ";
        cin >> name;

        cout << "Enter initial balance: ";
        cin >> initialBalance;

        if (initialBalance < 0) {
            cout << RED << "Initial balance cannot be negative." << RESET << endl;
            return;
        }

        accounts.emplace_back(name, initialBalance);

        cout << GREEN << "Account created successfully." << RESET << endl;
        cout << "Account No.: "
             << accounts.back().getAccountNo() << endl << endl;
    }

    void userOptions() {
        int accountNo;

        cout << GREEN << "\nEnter your Account No.: " << RESET;
        cin >> accountNo;

        BankAccount* account = findAccount(accountNo);

        if (account == nullptr) {
            cout << RED << "Account does not exist." << RESET << endl;
            return;
        }

        bool running = true;

        while (running) {
            cout << BLUE << "\nAccount Details\n" << RESET;
            account->display();

            cout << GREEN;
            cout << "1. Withdraw" << endl;
            cout << "2. Deposit" << endl;
            cout << "3. Exit User Options" << RESET << endl;

            int action;
            cin >> action;

            switch (action) {
                case 1: {
                    double amount;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    account->withdraw(amount);
                    break;
                }

                case 2: {
                    double amount;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    account->deposit(amount);
                    break;
                }

                case 3:
                    cout << RED << "Exiting user options." << RESET << endl;
                    running = false;
                    break;

                default:
                    cout << RED << "Invalid input. Try again." << RESET << endl;
            }
        }
    }

    void displayAllAccounts() const {
        if (accounts.empty()) {
            cout << RED << "No accounts available." << RESET << endl;
            return;
        }

        cout << BRIGHT_BLUE
             << "\nDisplaying details of all accounts:\n"
             << RESET << endl;

        for (const auto& account : accounts) {
            account.display();
        }
    }

    void run() {
        bool running = true;

        while (running) {
            cout << YELLOW;
            cout << "\n1. Create New Account" << endl;
            cout << "2. User Options" << endl;
            cout << "3. Display All Accounts" << endl;
            cout << "4. Exit" << RESET << endl;

            cout << "\nEnter your choice: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    createAccount();
                    break;

                case 2:
                    userOptions();
                    break;

                case 3:
                    displayAllAccounts();
                    break;

                case 4:
                    cout << RED << "Exiting from program." << RESET << endl;
                    running = false;
                    break;

                default:
                    cout << RED << "Invalid input. Try again." << RESET << endl;
            }
        }
    }
};

int main() {
    Bank bank;
    bank.run();
    return 0;
}
