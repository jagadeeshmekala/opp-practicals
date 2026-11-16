// Experiment 9: Custom exception hierarchy for a banking transaction scenario
//
//                std::exception
//                      |
//                BankException
//        _____________|_____________________
//       |                |                  |
// InsufficientFunds  InvalidAmount   AccountNotFound
#include <iostream>
#include <string>
#include <map>
#include <exception>
using namespace std;

// ---------- Exception hierarchy ----------
class BankException : public exception {
protected:
    string message;

public:
    BankException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InsufficientFundsException : public BankException {
public:
    InsufficientFundsException(int balance, int amount)
        : BankException("Insufficient funds: balance is " + to_string(balance) +
                        ", requested " + to_string(amount)) {}
};

class InvalidAmountException : public BankException {
public:
    InvalidAmountException(int amount)
        : BankException("Invalid amount: " + to_string(amount) +
                        " (amount must be greater than 0)") {}
};

class AccountNotFoundException : public BankException {
public:
    AccountNotFoundException(int accNo)
        : BankException("Account not found: " + to_string(accNo)) {}
};

// ---------- Bank classes ----------
class BankAccount {
private:
    int accNo;
    int balance;

public:
    BankAccount(int no = 0, int bal = 0) : accNo(no), balance(bal) {}

    int getBalance() const { return balance; }

    void deposit(int amount) {
        if (amount <= 0) throw InvalidAmountException(amount);
        balance += amount;
    }

    void withdraw(int amount) {
        if (amount <= 0) throw InvalidAmountException(amount);
        if (amount > balance) throw InsufficientFundsException(balance, amount);
        balance -= amount;
    }
};

class Bank {
private:
    map<int, BankAccount> accounts;

    BankAccount& find(int accNo) {
        auto it = accounts.find(accNo);
        if (it == accounts.end()) throw AccountNotFoundException(accNo);
        return it->second;
    }

public:
    void addAccount(int accNo, int balance) {
        accounts[accNo] = BankAccount(accNo, balance);
    }

    void deposit(int accNo, int amount)  { find(accNo).deposit(amount); }
    void withdraw(int accNo, int amount) { find(accNo).withdraw(amount); }

    void transfer(int from, int to, int amount) {
        BankAccount& src = find(from);
        BankAccount& dst = find(to);       // throws if destination is missing
        src.withdraw(amount);
        dst.deposit(amount);
    }

    int balance(int accNo) { return find(accNo).getBalance(); }
};

int main() {
    Bank bank;
    bank.addAccount(101, 5000);
    bank.addAccount(102, 2000);

    // Test 1: successful transfer
    try {
        bank.transfer(101, 102, 1500);
        cout << "Test 1: Transfer successful. Balances: "
             << bank.balance(101) << " and " << bank.balance(102) << endl;
    } catch (const BankException& e) {
        cout << "Test 1 failed: " << e.what() << endl;
    }

    // Test 2: not enough money
    try {
        bank.withdraw(102, 99999);
    } catch (const InsufficientFundsException& e) {
        cout << "Test 2 caught InsufficientFundsException -> " << e.what() << endl;
    }

    // Test 3: negative amount
    try {
        bank.deposit(101, -500);
    } catch (const InvalidAmountException& e) {
        cout << "Test 3 caught InvalidAmountException -> " << e.what() << endl;
    }

    // Test 4: account that does not exist
    try {
        bank.transfer(101, 999, 100);
    } catch (const AccountNotFoundException& e) {
        cout << "Test 4 caught AccountNotFoundException -> " << e.what() << endl;
    }

    // Test 5: catching through the BASE class (shows the hierarchy)
    try {
        bank.withdraw(101, 0);
    } catch (const BankException& e) {
        cout << "Test 5 caught via base BankException -> " << e.what() << endl;
    }

    cout << "Program finished normally." << endl;
    return 0;
}
