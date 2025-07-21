#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H

#include <string>
#include <vector>
using namespace std;

class BankAccount {
protected:
    string cardNumber, sheba, accountNumber, cvv2;
    double balance;
    string expireDate;
    string password1, staticPassword2, dynamicPassword2;

public:
    BankAccount(string, string, string, string, double, string, string, string);
    virtual string getType() = 0;
    virtual string getSpecialFeature() = 0;

    void showInfo();
    string getCardNumber();
    string getExpireDate();
    string getDynamicPassword2() const { return dynamicPassword2; }
    string getPassword1() { return password1; }
    void setPassword1(string pw) { password1 = pw; }

    void setStaticPassword2(string pw) { staticPassword2 = pw; }
    string getShebaNumber() const { return sheba; }
    string getAccountNumber() const { return accountNumber; }
    string getCVV2() const { return cvv2; }


    double getBalance();
    bool validatePassword2(string);
    void setDynamicPassword2(string);
    void deposit(double);
    bool withdraw(double);
    string getStaticPassword2() const {
        return staticPassword2;
    }

};

class User {
protected:
    string firstName, lastName, nationalCode, username, password;
    int age;
public:
    User(string, string, string, int, string, string);

    virtual void showMenu() = 0;
    string getUsername();
    string getPassword();
    string getFullName();
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getNationalCode();
    int getAge();

    void setPassword(const string& pw);
    void setFirstName(const string& fname);
    void setLastName(const string& lname);
    void setNationalCode(const string& nc);
    void setAge(int a);
};

class Customer;
class Admin;

extern vector<User*> users;
User* login(string username, string password);

class GharzAccount : public BankAccount {
public:
    GharzAccount(string, string, string, string, double, string, string, string);
    string getType() override;
    string getSpecialFeature() override;

};

class SepordeAccount : public BankAccount {
public:
    SepordeAccount(string, string, string, string, double, string, string, string);
    string getType() override;
    string getSpecialFeature() override;

};

class JariAccount : public BankAccount {
public:
    JariAccount(string, string, string, string, double, string, string, string);
    string getType() override;
    string getSpecialFeature() override;

};

class Customer : public User {
private:
    vector<BankAccount*> accounts;
    double dailyTransferAmount = 0;
    time_t lastTransferTime = 0;

public:
    Customer(string firstName, string lastName, string nationalCode, int age, string username, string password);

    bool addAccount(BankAccount* acc);
    void removeAccount(BankAccount* acc);
    vector<BankAccount*> getAccounts();
    void showAccounts();
    void changeCardPasswords();


    void transferMoney();

    void showMenu() override;

    BankAccount* findAccountByCard(const string& cardNum);

    double getDailyTransferAmount() const;
    void setDailyTransferAmount(double amount);

    time_t getLastTransferTime() const;
    void setLastTransferTime(time_t time);
};


class Admin : public User {
public:
    Admin(string, string, string, int, string, string);
    void showAllCustomers();
    void showAllAccounts();
    void createCustomer();
    void deleteCustomer();
    void createAccount();
    void showOtherAdmins();
    void editUserInfo();
    void showMenu() override;
};
void loadUsers();
void saveUsers();

#endif
