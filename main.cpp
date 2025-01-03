#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;

// Struct for Transaction
struct Transaction {
    string type;           
    double amount;          
    string timestamp;  
};

// Struct for account
struct Account {
    string name;
    double balance;
    string accountType;  // Account type: "Savings" or "Checking"
    string password;     // Password for the account
    vector<Transaction> transactions;
};

// Function prototypes
void displayMenu();
double getValidBalance();
void addAccount();
void viewAccounts();
void depositMoney();
void withdrawMoney();
void saveAccountsToFile();
void loadAccountsFromFile();
void updateAccount();
void deleteAccount();
void searchAccount();
void sortAccounts();
bool validatePassword(const string& accountName, const string& enteredPassword);
void viewTransactions();
void processMenuChoice();
string trim(const string& str);

// Function to store all accounts in a vector
vector<Account> accounts;

int main() {
    loadAccountsFromFile(); // Load accounts from file at the start
        cout << "===== Accounts Loaded =====" << endl;
    for (const auto& account : accounts) {
        // Print account details
        cout << "Account Holder: " << account.name << endl;
        cout << "Account Type: " << account.accountType << endl;
        cout << "Balance: " << account.balance << endl;

        // Print transactions associated with this account
        cout << "Transactions: " << endl;
        if (account.transactions.empty()) {
            cout << "No transactions available." << endl;
        } else {
            for (const auto& transaction : account.transactions) {
                cout << "  Type: " << transaction.type << ", Amount: " << transaction.amount 
                     << ", Date: " << transaction.timestamp << endl;
            }
        }
        cout << "---------------------------" << endl;
    }
    while(true) {
       processMenuChoice();  // Process the user's menu choice
    }
    return 0;
}
// Utility function to trim leading and trailing spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";  // No content
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}



// Function to display the menu
void displayMenu() {
    cout << "\n===== Bank Management System =====" << endl;
    cout << "1. Add Account" << endl;
    cout << "2. View Accounts" << endl;
    cout << "3. Deposit Money" << endl;
    cout << "4. Withdraw Money" << endl;
    cout << "5. Update Account" << endl;
    cout << "6. Delete Account" << endl;
    cout << "7. Search Account" << endl;
    cout << "8. Sort Accounts" << endl;
    cout << "9. View Transactions" << endl;
    cout << "10. Exit" << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

// Function to validate balance input
double getValidBalance() {
    double balance;
    while (true) {
        cout << "Enter initial balance: ";
        cin >> balance;
        if (cin.fail() || balance < 0) {
            cout << "Invalid balance. Please enter a positive number" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return balance;
        }
    }
}

// Function to validate account password
bool validatePassword(const string& accountName, const string& enteredPassword) {
    for (const auto& account : accounts) {
        if (account.name == accountName && account.password == enteredPassword) {
            return true;
        }
    }
    return false;
}

// Function to process menu choice
void processMenuChoice() {
    displayMenu();

    int choice;
    cin >> choice;
    if(cin.fail()){
        cout << "Invalid input! Please enter a number between 1 and 9." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    switch (choice) {
        case 1: addAccount(); break;
        case 2: viewAccounts(); break;
        case 3: depositMoney(); break;
        case 4: withdrawMoney(); break;
        case 5: updateAccount(); break;
        case 6: deleteAccount(); break;
        case 7: searchAccount(); break;
        case 8: sortAccounts(); break;
        case 9: viewTransactions(); break;
        case 10: exit(0); break;
        default:
            cout << "Invalid choice! Please try again." << endl;
            break;
    }
}

// Function to add an account
void addAccount() {
    string name, accountType, password;
    cout << "Enter account holder's name: ";
    cin >> ws;  // To consume leading whitespace
    getline(cin, name);

    if (name.empty()) {
        cout << "Account holder's name cannot be empty!" << endl;
        return;
    }

    cout << "Enter account type (Savings/Checking): ";
    cin >> accountType;

    if (accountType != "Savings" && accountType != "Checking") {
        cout << "Invalid account type. Must be 'Savings' or 'Checking'." << endl;
        return;
    }

    cout << "Enter a password for the account: ";
    cin >> password;

    double balance = getValidBalance();
    Account newAccount = {name, balance, accountType, password};
    accounts.push_back(newAccount);
    cout << "Account for " << name << " with balance " << balance << " added!" << endl;
    saveAccountsToFile();  // Save accounts to file after adding
}

// Function to display all accounts
void viewAccounts() {
    if(accounts.empty()){
        cout << "No accounts to display." << endl;
        return;
    }
    for(const auto& account : accounts){
        cout << account.name << ", " << account.accountType << ", " << account.balance << endl; 
    }
}

// Function to deposit money into an account
void depositMoney() {
    if(accounts.empty()){
        cout << "No accounts to display." << endl;
        return;
    }
    string name, enteredPassword;
    cout << "Enter account holder's name to deposit money: ";
    cin >> ws;  // To consume leading whitespace
    getline(cin, name);

    bool found = false;
    for (auto& account : accounts) {
        if (account.name == name) {
            cout << "Enter password for account: ";
            cin >> enteredPassword;

            if (validatePassword(name, enteredPassword)) {
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                if (amount <= 0) {
                    cout << "Deposit amount must be positive!" << endl;
                } else {
                    account.balance += amount;
                    time_t now = time(0);
                    string timestamp = ctime(&now);
                    timestamp.pop_back();  // Remove the newline character from timestamp
                    Transaction newTransaction = {"Deposit", amount, timestamp};
                    account.transactions.push_back(newTransaction);
                    saveAccountsToFile();  // Save the account data after the transaction
                    cout << "Deposited " << amount << " to " << name << "'s account. New balance: " << account.balance << endl;
                }
            } else {
                cout << "Invalid password!" << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found!" << endl;
    }
}

// Function to withdraw money from an account
void withdrawMoney() {
    if(accounts.empty()){
        cout << "No accounts to display." << endl;
        return;
    }
    string name, enteredPassword;
    cout << "Enter account holder's name to withdraw money: ";
    cin >> ws;  // To consume leading whitespace
    getline(cin, name);

    bool found = false;
    for (auto& account : accounts) {
        if (account.name == name) {
            cout << "Enter password for account: ";
            cin >> enteredPassword;

            if (validatePassword(name, enteredPassword)) {
                double amount;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                if (amount <= 0) {
                    cout << "Withdrawal amount must be positive!" << endl;
                } else if (amount > account.balance) {
                    cout << "Insufficient funds!" << endl;
                } else {
                    account.balance -= amount;
                    time_t now = time(0);
                    string timestamp = ctime(&now);
                    timestamp.pop_back();  // Remove the newline character from timestamp
                    Transaction newTransaction = {"Withdrawal", amount, timestamp};
                    account.transactions.push_back(newTransaction);
                    saveAccountsToFile();  // Save the account data after the transaction

                    cout << "Withdrew " << amount << " from " << name << "'s account. New balance: " << account.balance << endl;

                }
            } else {
                cout << "Invalid password!" << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found!" << endl;
    }
   

}

// Function to view transaction history for an account

// Function to view transactions
void viewTransactions() {
    string name;
    cout << "Enter account holder's name to view transactions: ";
    cin >> ws;  // To consume leading whitespace
    getline(cin, name);

    bool found = false;
    for (const auto& account : accounts) {
        if (account.name == name) {
            cout << "Transaction history for " << name << ":\n";
            if (account.transactions.empty()) {
                cout << "No transactions available." << endl;
            } else {
                for (const auto& transaction : account.transactions) {
                    cout << "Type: " << transaction.type << ", Amount: " << transaction.amount 
                         << ", Date: " << transaction.timestamp << endl;
                }
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found!" << endl;
    }
}
// Function to save accounts to a file
void saveAccountsToFile() {
    ofstream file("accounts.txt");
    for (const auto& account : accounts) {
        file << account.name << endl;
        file << account.accountType << endl;
        file << account.balance << endl;
        file << account.password << endl;
        for (const auto& transaction : account.transactions) {
            file << transaction.type << " " << transaction.amount << " " << transaction.timestamp << endl;
        }
        file << "----" << endl; 
    }
    file.close();
}

// Function to load accounts from a file
// Function to load accounts from a file
void loadAccountsFromFile() {
    ifstream file("accounts.txt");
    if (file.is_open()) {
        string name, accountType, password;
        double balance;
        while (getline(file, name)) {
            // Read account details
            getline(file, accountType);
            file >> balance;
            file.ignore();  // Ignore newline after balance
            getline(file, password);

            Account account = {name, balance, accountType, password};

            string line;
            double amount;
            string timestamp;
            
            // Check for transactions until we encounter a non-transaction line or the separator '----'
            while (getline(file, line)) {
                cout << "Transaction line found: " << line << endl;  // Debugging output
                
                // Check if the line starts with "Deposit" or "Withdrawal"
                if (line.find("Deposit") == 0 || line.find("Withdrawal") == 0) {
                    stringstream ss(line);
                    string type;
                    ss >> type;  // Extract the transaction type (Deposit/Withdrawal)
                    ss >> amount;  // Extract the amount
                    getline(ss, timestamp);  // Extract the timestamp (remainder of the line)
                    
                    Transaction transaction = {type, amount, timestamp};
                    account.transactions.push_back(transaction);
                    
                    cout << "Added transaction: " << transaction.type << " " << transaction.amount 
                         << " " << transaction.timestamp << endl;  // Debugging output
                } else if (line == "----") {
                    // If we encounter a separator, break out and start loading the next account
                    break;
                } else {
                    // If it's not a transaction type or separator, it's potentially invalid data
                    continue;
                }
            }
            
            // Add the current account to the list
            accounts.push_back(account);
        }
        file.close();
    } else {
        cerr << "Unable to open file for loading accounts." << endl;
    }
}

// Function to update an account's details (e.g., name, password, account type)
void updateAccount() {
    if(accounts.empty()){
        cout << "No accounts to display." << endl;
        return;
    }
    string name, enteredPassword ,newName, newAccountType, newPassword;
    cout << "Enter account holder's name to update: ";
    cin >> ws;  // To consume leading whitespace
    getline(cin, name);

    bool found = false;
    for (auto& account : accounts) {
        if (account.name == name) {
            cout << "Enter password: "; 
            cin >> enteredPassword;
           if(validatePassword(name, enteredPassword)){
                cout << "Account found! What would you like to update?" << endl;
                cout << "1. Update account holder's name" << endl;
                cout << "2. Update account type (Savings/Checking)" << endl;
                cout << "3. Update password" << endl;
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "Enter new account holder's name: ";
                        cin >> ws;  // To consume leading whitespace
                        getline(cin, newName);
                        account.name = newName;
                        cout << "Account holder's name updated successfully!" << endl;
                        break;
                    case 2:
                        cout << "Enter new account type (Savings/Checking): ";
                        cin >> newAccountType;
                        if (newAccountType == "Savings" || newAccountType == "Checking") {
                            account.accountType = newAccountType;
                            cout << "Account type updated successfully!" << endl;
                        } else {
                            cout << "Invalid account type. Please enter 'Savings' or 'Checking'." << endl;
                        }
                        break;
                    case 3:
                        cout << "Enter new password: ";
                        cin >> newPassword;
                        account.password = newPassword;
                        cout << "Password updated successfully!" << endl;
                        break;
                    default:
                        cout << "Invalid choice!" << endl;
                        break;
                }
                
                break;
            }else{
                  cout << "Invalid password!" << endl;
             }
            
            found = true;
          }
    }

    if (!found) {
        cout << "Account not found!" << endl;
    }
}

// Function to delete an account by name
void deleteAccount() {
    if(accounts.empty()){
        cout << "No accounts to display." << endl;
        return;
    }
    string name;
    cout << "Enter account holder's name to delete: ";
    cin >> ws;  // To consume leading whitespace
    getline(cin, name);

    auto it = remove_if(accounts.begin(), accounts.end(), [&name](const Account& account) {
        return account.name == name;
    });

    if (it != accounts.end()) {
        accounts.erase(it, accounts.end());
        cout << "Account for " << name << " deleted successfully!" << endl;
        saveAccountsToFile();  // Save updated accounts to file
    } else {
        cout << "Account not found!" << endl;
    }
}

// Function to search for an account by name and display details
void searchAccount() {
    if(accounts.empty()){
        cout << "No accounts to display." << endl;
        return;
    }
    string name;
    cout << "Enter account holder's name to search: ";
    cin >> ws;  // To consume leading whitespace
    getline(cin, name);

    bool found = false;
    for (const auto& account : accounts) {
        if (account.name == name) {
            cout << "Account found!" << endl;
            cout << "Name: " << account.name << endl;
            cout << "Account Type: " << account.accountType << endl;
            cout << "Balance: " << account.balance << endl;
            cout << "Transactions: " << endl;
            for (const auto& transaction : account.transactions) {
                cout << "Type: " << transaction.type << ", Amount: " << transaction.amount
                     << ", Date: " << transaction.timestamp << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account not found!" << endl;
    }
}

// Function to sort accounts by balance (ascending order)
void sortAccounts() {
    if(accounts.empty()){
        cout << "No accounts to display." << endl;
        return;
    }
    cout << "Sorting accounts by balance..." << endl;

    sort(accounts.begin(), accounts.end(), [](const Account& a, const Account& b) {
        return a.balance < b.balance;
    });

    cout << "Accounts sorted by balance." << endl;
    cout << "Here is the sorted list of accounts:" << endl;
    for (const auto& account : accounts) {
        cout << account.name << ", " << account.accountType << ", " << account.balance << endl;
    }
}

