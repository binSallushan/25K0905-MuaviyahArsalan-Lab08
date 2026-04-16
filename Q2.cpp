#include <iostream>
#include <string>
using namespace std;

class Account {
private:
    string accountNumber;
    string accountHolder;
    double balance;

public:
    Account(string accNo, string holder, double bal) {
        accountNumber = accNo;
        accountHolder = holder;
        balance = bal;
    }

    double getBalance() const {
        return balance;
    }

    string getName() const {
        return accountHolder;
    }

    Account operator+(const Account &other) {
        return Account("000", "Combined Account", this->balance + other.balance);
    }

    Account &operator-=(double amount) {
        if (amount <= balance) {
            balance -= amount;
        }
        return *this;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool operator>(const Account &other) {
        return this->balance > other.balance;
    }

    friend ostream &operator<<(ostream &out, const Account &acc);
};

ostream &operator<<(ostream &out, const Account &acc) {
    out << "Account Number: " << acc.accountNumber
        << " | Holder: " << acc.accountHolder
        << " | Balance: $" << acc.balance;
    return out;
}

int main() {
    Account acc1("101", "John Doe", 5000);
    Account acc2("102", "Alice Smith", 3000);

    Account total = acc1 + acc2;
    cout << "Total Balance (After Addition): " << total.getBalance() << endl;

    acc1 -= 2000;
    acc2.deposit(2000);

    cout << "\nAfter Transfer:\n";
    cout << acc1.getName() << "'s New Balance: " << acc1.getBalance() << endl;
    cout << acc2.getName() << "'s New Balance: " << acc2.getBalance() << endl;

    cout << "\nComparison:\n";
    if (acc1 > acc2)
        cout << "John Doe has higher balance than Alice Smith.\n";
    else
        cout << "John Doe has less balance than Alice Smith.\n";

    cout << "\nFinal Account Details:\n";
    cout << acc1 << endl;
    cout << acc2 << endl;

    return 0;
}
