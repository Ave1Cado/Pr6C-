#include <iostream>
#include <locale>
#include <cmath>

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accountNumber, double initialBalance) {
        this->accountNumber = accountNumber;
        this->balance = initialBalance;
        this->interestRate = 0.0;
    }

    void deposit(double amount) {
        if (amount > 0) {
            this->balance += amount;
        }
        else {
            std::cout << "Неверная сумма депозита." << std::endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= this->balance) {
            this->balance -= amount;
        }
        else {
            std::cout << "Неверная сумма вывода." << std::endl;
        }
    }

    double getBalance() const {
        return this->balance;
    }

    double getInterest() const {
        return this->balance * this->interestRate * (1.0 / 12.0);
    }

    void setInterestRate(double interestRate) {
        if (interestRate >= 0.0) {
            this->interestRate = interestRate;
        }
        else {
            std::cout << "Неверная процентная ставка." << std::endl;
        }
    }

    int getAccountNumber() const {
        return this->accountNumber;
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
        os << "Номер аккаунта: " << account.accountNumber << "\n";
        os << "Баланс: " << account.balance << "\n";
        os << "Процентная ставка: " << account.interestRate << "\n";
        return os;
    }
};

bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount) {
    if (amount > 0 && amount <= fromAccount.getBalance()) {
        fromAccount.withdraw(amount);
        toAccount.deposit(amount);
        return true;
    }
    else {
        std::cout << "Неверная сумма перевода." << std::endl;
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "");

    BankAccount account1(12345, 1000.0);
    BankAccount account2(67890, 500.0);

    account1.deposit(200.0);
    account2.withdraw(100.0);

    account1.setInterestRate(0.05);
    account2.setInterestRate(0.03);

    std::cout << "Account 1:\n" << account1 << std::endl;
    std::cout << "Account 2:\n" << account2 << std::endl;

    bool transferSuccess = transfer(account1, account2, 300.0);
    if (transferSuccess) {
        std::cout << "Перевод успешен." << std::endl;
    }
    else {
        std::cout << "Перевод не успешен." << std::endl;
    }

    return 0;
}
