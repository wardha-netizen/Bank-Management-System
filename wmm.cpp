#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <fstream>

using namespace std;

struct account {
    int id;
    string number;
    string name;
    char type;
    int balance;
} accounts[3];

void intro() {
    cout << "\n\n MADE BY : WARDHA KHALID";
    cout << "\n UNIVERSITY : BAHRIA UNIVERSITY KARACHI";
    cin.get();
}

void openAccount() {
    
    for (int i = 0; i < 3; i++) {
        cout << "\nPlease! Enter The account No. : ";
        cin >> accounts[i].number;

        cout << "\nPlease! Enter The Name of The account Holder: ";
        cin.ignore();
        getline(cin, accounts[i].name);

        cout << "\nPlease! Enter Type of The account (C/S): ";
        char accountTypeInput;
        cin >> accountTypeInput;

        while (accountTypeInput != 'C' && accountTypeInput != 'S') {
            cout << "Invalid account type! Please enter C for Current or S for Saving: ";
            cin >> accounts[i].type;
            accounts[i].type = toupper(accounts[i].type);
        }

        bool isValidInput;
        do {
            cout << "Please Enter Account Type. Please enter C for Current or S for Saving: ";
            cin >> accounts[i].type;
            accounts[i].type = toupper(accounts[i].type);
            isValidInput = accounts[i].type == 'C' || accounts[i].type == 'S';
            if (!isValidInput) {
                cout << "Invalid Input!. Please try again.";
            }
        } while (!isValidInput);

        cout << "\nPlease! Enter The Initial amount (>=440 for Saving and >=1000 for Current): ";
        cin >> accounts[i].balance;

        while ((accounts[i].type == 'S' && accounts[i].balance < 440) ||
            (accounts[i].type == 'C' && accounts[i].balance < 1000)) {
            cout << "Invalid initial deposit. Please re-enter: ";
            cin >> accounts[i].balance;
        }

        cout << "\n\nAccount Created Successfully.\n";
    }
}

void display() {
    cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "Displaying information of all account holders in Fast Bank!\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    cout << left << setw(15) << "Account No."
        << setw(25) << "Name"
        << setw(15) << "Account Type"
        << setw(15) << "Deposit Amount" << endl;

    for (int i = 0; i < 3; i++) {
        if (accounts[i].number != -1) {
            cout << left << setw(15) << accounts[i].number
                << setw(25) << accounts[i].name
                << setw(15) << accounts[i].type
                << setw(15) << accounts[i].balance << endl;
        }
    }
}

void sortaccounts() {
    
    for (int i = 0; i < 3 - 1; i++) {
        for (int j = 0; j < 3 - i - 1; j++) {
            if (accounts[j].number > accounts[j + 1].number) {
                swap(accounts[j], accounts[j + 1]);
            }
        }
    }

    cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "Displaying sorted accounts in Fast Bank!\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    display();
}

void search() {
    
    int key;
    cout << "Enter account number you want to search: ";
    cin >> key;

    bool found = false;
    for (int i = 0; i < 3; i++) {
        if (accounts[i].number == key) {
            cout << "\nAccount found:\n";
            cout << left << setw(15) << "Account No."
                << setw(25) << "Name"
                << setw(15) << "Account Type"
                << setw(15) << "Deposit Amount" << endl;
            cout << left << setw(15) << accounts[i].number
                << setw(25) << accounts[i].name
                << setw(15) << accounts[i].type
                << setw(15) << accounts[i].balance << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nAccount number " << key << " not found!\n";
    }
}

void updateDeposit() {
    
    int accountNumber, amount;
    cout << "\nEnter the account number you want to deposit into: ";
    cin >> accountNumber;

    bool found = false;
    for (int i = 0; i < 3; i++) {
        if (accounts[i].number == accountNumber) {
            cout << "Enter the amount you want to deposit: ";
            cin >> amount;

            if (amount > 0) {
                accounts[i].balance += amount;
                cout << "\nDeposit successful! Updated account details:\n";
                display();
            }
            else {
                cout << "Invalid deposit amount. Please enter a positive value.\n";
            }

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account number " << accountNumber << " not found. Please try again.\n";
    }
}

void withdraw() {
    
    int accountNumber, amount;
    cout << "\nEnter the account number you want to withdraw from: ";
    cin >> accountNumber;

    bool found = false;
    for (int i = 0; i < 3; i++) {
        if (accounts[i].number == accountNumber) {
            account account = accounts[i];
            cout << "Enter the amount you want to withdraw: ";
            cin >> amount;

            if (amount > 0 && amount <= account.balance) {
                account.balance -= amount;
                cout << "\nWithdrawal successful! Updated account details:\n";
                display();
            }
            else {
                cout << "Invalid withdrawal amount. Please ensure it's positive and doesn't exceed your deposit.\n";
            }

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Account number " << accountNumber << " not found. Please try again.\n";
    }
}

void deleteAccount() {
    int accountNumber;
    cout << "\nEnter the account number you want to delete: ";
    cin >> accountNumber;

    bool found = false;
    for (int i = 0; i < 3; i++) {
        if (accounts[i].number == accountNumber) {
            accounts[i].number = -1;
            accounts[i].name = "";
            accounts[i].type = '\0';
            accounts[i].balance = 0;

            cout << "Account number " << accountNumber << " deleted successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Error! Account number " << accountNumber << " not found. Please enter the correct account number.\n";
    }
}

void addToFile(account* account) {
    ofstream outfile;
    outfile.open("accounts.txt", ios::app);

    outfile << account->id << endl;
    outfile << account->name << endl;
    outfile << account->type << endl;
    outfile << account->number << endl;
    outfile << account->balance << endl;

    outfile.close();
}

void readAll(account[3] accounts) {
    ifstream infile;
    infile.open("accounts.txt");

    string id;
    string type;
    string balance;
    account account;
    getline(infile, id);
    getline(infile, account.name);
    getline(infile, type);
    getline(infile, account.number);
    getline(infile, balance);

    account.id = stoi(id);
    account.type = type[0];
    account.balance = stoi(balance);
}



int main() {
    cout << "\n*************************************************************************************\n";
    cout << "\"Welcome To Fast Bank Management System!\"\n";
    cout << "****************************************************************************************\n";
    intro();

    int choice;
    do {
        cout << "\n\n\t\tMAIN MENU";
        cout << "\n\t\t01. INPUT USER DETAILS TO CREATE NEW ACCOUNT";
        cout << "\n\t\t02. SORT ACCOUNTS";
        cout << "\n\t\t03. SEARCH FOR AN ACCOUNT";
        cout << "\n\t\t04. DISPLAY ACCOUNTS";
        cout << "\n\t\t05. DEPOSIT MORE AMOUNT";
        cout << "\n\t\t06. WITHDRAW FROM DEPOSIT AMOUNT";
        cout << "\n\t\t07. DELETE AN ACCOUNT";
        cout << "\n\t\t08. EXIT";
        cout << "\n\t\tSelect Your Option (1-8): ";
        cin >> choice;

        switch (choice) {
        case 1:
            openAccount();
            break;
        case 2:
            sortaccounts();
            break;
        case 3:
            search();
            break;
        case 4:
            display();
            break;
        case 5:
            updateDeposit();
            break;
        case 6:
            withdraw();
            break;
        case 7:
            deleteAccount();
            break;
        case 8:
            cout << "\nThank you for using FAST BANK!\n";
            break;
        default:
            cout << "\nInvalid choice. Please enter a valid option (1-8).\n";
            break;
        }
    } while (choice != 8);

    return 0;
}
