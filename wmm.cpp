#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <fstream>

using namespace std;

struct account {
    string number;
    string name;
    char type;
    int balance;
} accounts[3];

void saveAccountsToFile();

void loadAccountsFromFile();

void intro() {
    cout << "\n\n MADE BY : WARDHA KHALID, MAHEEN FATIMA AND MUSAVIR WASEEM";
    cout << "\n UNIVERSITY : BAHRIA UNIVERSITY KARACHI";
    cin.get();
}

void openAccount() {
	loadAccountsFromFile();

    account account;
    cout << "\nPlease! Enter The account No. : ";
	cin.ignore();
    getline(cin, account.number);

    cout << "\nPlease! Enter The Name of The account Holder: ";
    cin.ignore();
    getline(cin, account.name);

    bool isValidInput = true;
    do {
        cout << "Please Enter Account Type. Please enter C for Current or S for Saving: ";
        cin >> account.type;
        account.type = toupper(account.type);
        isValidInput = account.type == 'C' || account.type == 'S'; 

        if (!isValidInput)
            cout << "Invalid Input!. Please try again.";

    } while (!isValidInput);

    cout << "\nPlease! Enter The Initial amount (>=440 for Saving and >=1000 for Current): ";
    cin >> account.balance;

    while ((account.type == 'S' && account.balance < 440) || (account.type == 'C' && account.balance < 1000)) {
        cout << "Invalid initial deposit. Please re-enter: ";
        cin >> account.balance;
    }

	for (int i = 0; i < 3; i++) {
		if (accounts[i].number == "") {
			accounts[i] = account;
			break;
		}
	}

    cout << "\n\nAccount Created Successfully.\n";
	saveAccountsToFile();
}

void display() {
	loadAccountsFromFile();
    cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "Displaying information of all account holders in Fast Bank!\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    cout << left << setw(15) << "Account No."
        << setw(25) << "Name"
        << setw(15) << "Account Type"
        << setw(15) << "Deposit Amount" << endl;

    for (int i = 0; i < 3; i++) {
        if (accounts[i].number != "") {
            cout << left << setw(15) << accounts[i].number
                << setw(25) << accounts[i].name
                << setw(15) << accounts[i].type
                << setw(15) << accounts[i].balance << endl;
        }
    }
}

void sortaccounts() {
	loadAccountsFromFile();
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
	loadAccountsFromFile();
    string key;
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
	loadAccountsFromFile();
    string accountNumber;
    int amount;
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
                saveAccountsToFile();
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
	saveAccountsToFile();
}

void withdraw() {
	loadAccountsFromFile();
    string accountNumber;
    int amount;
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
				saveAccountsToFile();
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
    string accountNumber;
    cout << "\nEnter the account number you want to delete: ";
    cin >> accountNumber;
    loadAccountsFromFile();

    bool found = false;
    for (int i = 0; i < 3; i++) {
        if (accounts[i].number == accountNumber) {
			account* foundAccount = &accounts[i];
            
            foundAccount->number = "";
            foundAccount->name = "";
            foundAccount->type = '\0';
            foundAccount->balance = 0;

            cout << "Account number " << accountNumber << " deleted successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)   
        cout << "Error! Account number " << accountNumber << " not found. Please enter the correct account number.\n";
	
    saveAccountsToFile();
}

void addToFile(account* account) {
    ofstream outfile;
    outfile.open("accounts.txt", ios::app);

    outfile << account->name << endl;
    outfile << account->type << endl;
    outfile << account->number << endl;
    outfile << account->balance << endl;

    outfile.close();
}

void readAll(account accounts[3]) {
	loadAccountsFromFile();
	display();
}

void loadAccountsFromFile() {
	ifstream infile;
	infile.open("accounts.txt");

	if (!infile) {
		cout << "Error! File not found.\n";
		return;
	}

	int i = 0;
	while (!infile.eof()) {
		string type;
		string balance;
		account account;
		getline(infile, account.name);
		getline(infile, type);
		getline(infile, account.number);
		getline(infile, balance);
		account.type = type[0];

		if (balance != "")
		    account.balance = stoi(balance);

		accounts[i] = account;
		i++;
	}

	infile.close();

}

void saveAccountsToFile() {
	ofstream outfile;
	outfile.open("accounts.txt");

	for (int i = 0; i < 3; i++) {

        if (accounts[i].number == "")
			continue;

		outfile << accounts[i].name << endl;
		outfile << accounts[i].type << endl;
		outfile << accounts[i].number << endl;
		outfile << accounts[i].balance << endl;
	}

	outfile.close();
}

void createFile() {
	ofstream outfile;
	outfile.open("accounts.txt");
	outfile.close();
}

int main() {
    createFile();

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
