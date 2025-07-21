#include "bank_system.h"
#include <algorithm>

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>


using namespace std;

vector<User*> users;


BankAccount::BankAccount(string cNum, string sh, string accNum, string cv, double bal, string exp, string pw1, string pw2)
    : cardNumber(cNum), sheba(sh), accountNumber(accNum), cvv2(cv), balance(bal),
    expireDate(exp), password1(pw1), staticPassword2(pw2) {}

void BankAccount::showInfo() {
    cout << "نوع حساب: " << getType() << endl;
    cout << "شماره کارت: " << cardNumber << endl;
    cout << "موجودی: " << balance << " تومان" << endl;
    cout << "تاریخ انقضا: " << expireDate << endl;
}

string BankAccount::getCardNumber() { return cardNumber; }
string BankAccount::getExpireDate() { return expireDate; }
double BankAccount::getBalance() { return balance; }

bool BankAccount::validatePassword2(string pw) {
    return pw == staticPassword2 || pw == dynamicPassword2;
}

void BankAccount::setDynamicPassword2(string dynPw) {
    dynamicPassword2 = dynPw;
}

void BankAccount::deposit(double amount) {
    balance += amount;
}

bool BankAccount::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}


User::User(string fn, string ln, string nc, int ag, string un, string pw)
    : firstName(fn), lastName(ln), nationalCode(nc), age(ag), username(un), password(pw) {}

string User::getUsername() { return username; }
string User::getPassword() { return password; }
string User::getFullName() { return firstName + " " + lastName; }
void User::setFirstName(const string& fname) {
    firstName = fname;
}

void User::setLastName(const string& lname) {
    lastName = lname;
}

void User::setNationalCode(const string& nc) {
    nationalCode = nc;
}

void User::setAge(int a) {
    age = a;
}

void User::setPassword(const string& pw) {
    password = pw;
}
int User::getAge() {
    return age;
}

std::string User::getNationalCode() {
    return nationalCode;
}



GharzAccount::GharzAccount(string c, string s, string a, string cv, double b, string ex, string p1, string p2)
    : BankAccount(c, s, a, cv, b, ex, p1, p2) {}

string GharzAccount::getType() { return "قرض الحسنه"; }
string GharzAccount::getSpecialFeature() {
    return "بدون سود. مناسب وام‌های بدون بهره.";
}



SepordeAccount::SepordeAccount(string c, string s, string a, string cv, double b, string ex, string p1, string p2)
    : BankAccount(c, s, a, cv, b, ex, p1, p2) {}

string SepordeAccount::getType() { return "سپرده"; }
string SepordeAccount::getSpecialFeature() {
    return "دارای سود ماهانه.";
}



JariAccount::JariAccount(string c, string s, string a, string cv, double b, string ex, string p1, string p2)
    : BankAccount(c, s, a, cv, b, ex, p1, p2) {}

string JariAccount::getType() { return "جاری"; }
string JariAccount::getSpecialFeature() {
    return "دارای دسته‌چک و بدون سود.";
}



Customer::Customer(string fn, string ln, string nc, int ag, string un, string pw)
    : User(fn, ln, nc, ag, un, pw) {}

bool Customer::addAccount(BankAccount* acc) {
    if (accounts.size() >= 5) {
        return false;
    }
    accounts.push_back(acc);
    return true;
}


void Customer::removeAccount(BankAccount* acc) {
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i] == acc) {
            delete accounts[i];
            accounts.erase(accounts.begin() + i);
            break;
        }
    }
}


void Customer::showAccounts() {
    if (accounts.empty()) {
        cout << "هیچ حسابی برای شما ثبت نشده.\n";
        return;
    }
    for (auto* acc : accounts) {
        cout << "----------------------\n";
        acc->showInfo();
    }
}
BankAccount* Customer::findAccountByCard(const string& inputCard) {
    string card = inputCard;
    card.erase(remove_if(card.begin(), card.end(), ::isspace), card.end());

    for (BankAccount* acc : accounts) {
        string accCard = acc->getCardNumber();
        accCard.erase(remove_if(accCard.begin(), accCard.end(), ::isspace), accCard.end());

        if (accCard == card)
            return acc;
    }
    return nullptr;
}


double Customer::getDailyTransferAmount() const {
    return dailyTransferAmount;
}

void Customer::setDailyTransferAmount(double amount) {
    dailyTransferAmount = amount;
}

time_t Customer::getLastTransferTime() const {
    return lastTransferTime;
}

void Customer::setLastTransferTime(time_t t) {
    lastTransferTime = t;
}

vector<BankAccount*> Customer::getAccounts() {
    return accounts;
}

void Customer::transferMoney() {
    string fromCard, toCard;
    double amount;

    cout << "شماره کارت مبدا: ";
    cin >> fromCard;

    BankAccount* from = findAccountByCard(fromCard);
    if (!from) {
        cout << "❌ کارت مبدا یافت نشد!\n";
        return;
    }

    string exp = from->getExpireDate();
    int currentDate = 202507;
    string mm = exp.substr(0, 2);
    string yy = exp.substr(3, 2);
    int expInt = stoi("20" + yy + mm);
    if (expInt < currentDate) {
        cout << "❌ کارت منقضی شده است!\n";
        return;
    }

    cout << "شماره کارت مقصد: ";
    cin >> toCard;

    BankAccount* to = nullptr;
    string recipientName = "";

    for (auto* u : users) {
        Customer* cust = dynamic_cast<Customer*>(u);
        if (cust) {
            to = cust->findAccountByCard(toCard);
            if (to) {
                recipientName = cust->getFullName();
                break;
            }
        }
    }

    if (!to) {
        cout << "❌ شماره کارت مقصد معتبر نیست.\n";
        return;
    }

    cout << "گیرنده: " << recipientName << endl;
    cout << "مبلغ انتقال (تومان): ";
    cin >> amount;

    if (amount > 3000000) {
        cout << "❌ سقف هر تراکنش ۳ میلیون تومان است!\n";
        return;
    }

    time_t now = time(0);
    if (difftime(now, lastTransferTime) > 86400) {
        dailyTransferAmount = 0;
        lastTransferTime = now;
    }

    if (dailyTransferAmount + amount > 6000000) {
        cout << "❌ سقف انتقال روزانه ۶ میلیون تومان است!\n";
        return;
    }

    double fee = 0.01 * amount;
    double total = amount + fee;

    string pass2;
    if (amount <= 100000) {
        cout << "رمز دوم ثابت: ";
        cin >> pass2;
    } else {
        string randPass = to_string(rand() % 900000 + 100000);
        from->setDynamicPassword2(randPass);
        cout << "رمز دوم پویا برای این تراکنش: " << randPass << endl;
        cout << "رمز دوم پویا: ";
        cin >> pass2;

        if (pass2 == from->getStaticPassword2()) {
            cout << "❌ نمی‌توان با رمز دوم ثابت مبلغ بالای ۱۰۰ هزار تومان کارت به کارت کرد.\n";
            return;
        }
    }

    if (!from->validatePassword2(pass2)) {
        cout << "❌ رمز دوم نادرست است!\n";
        return;
    }

    from->setDynamicPassword2("");

    if (!from->withdraw(total)) {
        cout << "❌ موجودی کافی نیست!\n";
        return;
    }

    to->deposit(amount);
    dailyTransferAmount += amount;

    cout << "✅ انتقال با موفقیت انجام شد.\n";
    cout << "مبلغ واریزی: " << amount << " تومان\n";
    cout << "کارمزد: " << fee << " تومان\n";
}

void Customer::changeCardPasswords() {
    string cardNum;
    cout << "شماره کارت برای تغییر رمز: ";
    cin >> cardNum;

    BankAccount* acc = findAccountByCard(cardNum);
    if (!acc) {
        cout << "❌ کارت پیدا نشد!\n";
        return;
    }

    string oldPass1, oldPass2;
    cout << "رمز اول فعلی: ";
    cin >> oldPass1;
    cout << "رمز دوم ثابت فعلی: ";
    cin >> oldPass2;

    if (acc->validatePassword2(oldPass2) == false || oldPass1 != acc->getPassword1()) {
        cout << "❌ رمز فعلی اشتباه است!\n";
        return;
    }

    string newPass1, newPass2;
    cout << "رمز اول جدید: ";
    cin >> newPass1;
    cout << "رمز دوم ثابت جدید: ";
    cin >> newPass2;

    acc->setPassword1(newPass1);
    acc->setStaticPassword2(newPass2);

    cout << "✅ رمزها با موفقیت تغییر یافتند.\n";
}


void Customer::showMenu() {
    int choice;
    do {
        cout << "\n-- منوی مشتری: " << getFullName() << " --\n";
        cout << "1. مشاهده حساب‌ها\n2. کارت به کارت\n3. تغییر رمز کارت\n4. خروج\n";
        cin >> choice;
        switch (choice) {
        case 1: showAccounts(); break;
        case 2: transferMoney(); break;
        case 3: changeCardPasswords(); break;
        }
    } while (choice != 3);
}


Admin::Admin(string fn, string ln, string nc, int ag, string un, string pw)
    : User(fn, ln, nc, ag, un, pw) {}

void Admin::showAllCustomers() {
    for (auto* u : users) {
        Customer* c = dynamic_cast<Customer*>(u);
        if (c)
            cout << "- " << c->getFullName() << " (" << c->getUsername() << ")\n";
    }
}

void Admin::showAllAccounts() {
    for (auto* u : users) {
        Customer* c = dynamic_cast<Customer*>(u);
        if (c) {
            cout << "\n" << c->getFullName() << ":\n";
            c->showAccounts();
        }
    }
}

void Admin::createCustomer() {
    string fn, ln, nc, un, pw;
    int age;
    cout << "نام: "; cin >> fn;
    cout << "نام خانوادگی: "; cin >> ln;
    cout << "کد ملی: "; cin >> nc;
    cout << "سن: "; cin >> age;
    cout << "نام کاربری: "; cin >> un;
    cout << "رمز عبور: "; cin >> pw;
    users.push_back(new Customer(fn, ln, nc, age, un, pw));
    cout << "✅ مشتری با موفقیت اضافه شد.\n";
}

void Admin::deleteCustomer() {
    string un;
    cout << "نام کاربری مشتری: ";
    cin >> un;
    for (int i = 0; i < users.size(); ++i) {
        Customer* c = dynamic_cast<Customer*>(users[i]);
        if (c && c->getUsername() == un) {
            delete users[i];
            users.erase(users.begin() + i);
            cout << "✅ مشتری حذف شد.\n";
            return;
        }
    }
    cout << "مشتری پیدا نشد.\n";
}

void Admin::createAccount() {
    string un;
    cout << "نام کاربری مشتری: ";
    cin >> un;
    for (auto* u : users) {
        Customer* c = dynamic_cast<Customer*>(u);
        if (c && c->getUsername() == un) {
            int type;
            cout << "نوع حساب (1. قرض‌الحسنه 2. سپرده 3. جاری): ";
            cin >> type;
            string cnum, sh, anum, cvv, ex, p1, p2;
            double bal;
            cout << "شماره کارت: "; cin >> cnum;
            cout << "شبا: "; cin >> sh;
            cout << "شماره حساب: "; cin >> anum;
            cout << "CVV2: "; cin >> cvv;
            cout << "موجودی اولیه: "; cin >> bal;
            cout << "تاریخ انقضا: "; cin >> ex;
            cout << "رمز اول: "; cin >> p1;
            cout << "رمز دوم ثابت: "; cin >> p2;

            BankAccount* acc = nullptr;
            if (type == 1)
                acc = new GharzAccount(cnum, sh, anum, cvv, bal, ex, p1, p2);
            else if (type == 2)
                acc = new SepordeAccount(cnum, sh, anum, cvv, bal, ex, p1, p2);
            else
                acc = new JariAccount(cnum, sh, anum, cvv, bal, ex, p1, p2);

            c->addAccount(acc);
            cout << "✅ حساب بانکی ایجاد شد.\n";
            return;
        }
    }
    cout << "مشتری پیدا نشد.\n";
}

void Admin::showOtherAdmins() {
    for (auto* u : users) {
        Admin* a = dynamic_cast<Admin*>(u);
        if (a && a != this)
            cout << "- " << a->getFullName() << endl;
    }
}

void Admin::editUserInfo() {
    string un, newpw;
    cout << "نام کاربری کاربر: ";
    cin >> un;
    for (auto* u : users) {
        if (u->getUsername() == un) {
            cout << "رمز جدید: ";
            cin >> newpw;
            u->setPassword(newpw);
            cout << "✅ رمز تغییر یافت.\n";
            return;
        }
    }
    cout << "کاربر پیدا نشد.\n";
}

void Admin::showMenu() {
    int choice;
    do {
        cout << "\n-- منوی ادمین: " << getFullName() << " --\n";
        cout << "1. نمایش مشتریان\n2. نمایش حساب‌ها\n3. ایجاد مشتری\n4. حذف مشتری\n5. ایجاد حساب\n";
        cout << "6. نمایش ادمین‌های دیگر\n7. تغییر رمز کاربران\n8. خروج\n";
        cin >> choice;
        switch (choice) {
        case 1: showAllCustomers(); break;
        case 2: showAllAccounts(); break;
        case 3: createCustomer(); break;
        case 4: deleteCustomer(); break;
        case 5: createAccount(); break;
        case 6: showOtherAdmins(); break;
        case 7: editUserInfo(); break;
        }
    } while (choice != 8);
}


User* login(string username, string password) {
    for (auto u : users)
        if (u->getUsername() == username && u->getPassword() == password)
            return u;
    return nullptr;
}

void saveUsers() {
    ofstream fout("users.txt");

    for (User* u : users) {
        if (Customer* c = dynamic_cast<Customer*>(u)) {
            fout << "Customer "
                 << c->getFirstName() << " "
                 << c->getLastName() << " "
                 << c->getNationalCode() << " "
                 << c->getAge() << " "
                 << c->getUsername() << " "
                 << c->getPassword() << "\n";

            for (BankAccount* acc : c->getAccounts()) {
                fout << "Account "
                     << acc->getType() << " "
                     << acc->getCardNumber() << " "
                     << acc->getShebaNumber() << " "
                     << acc->getAccountNumber() << " "
                     << acc->getCVV2() << " "
                     << acc->getBalance() << " "
                     << acc->getExpireDate() << " "
                     << acc->getPassword1() << " "
                     << acc->getStaticPassword2() << "\n";
            }
        } else if (Admin* a = dynamic_cast<Admin*>(u)) {
            fout << "Admin "
                 << a->getFirstName() << " "
                 << a->getLastName() << " "
                 << a->getNationalCode() << " "
                 << a->getAge() << " "
                 << a->getUsername() << " "
                 << a->getPassword() << "\n";
        }
    }

    fout.close();
}


void loadUsers() {
    ifstream fin("users.txt");
    if (!fin.is_open()) return;

    string type;
    Customer* currentCustomer = nullptr;

    while (fin >> type) {
        if (type == "Customer") {
            string fname, lname, nc, username, password;
            int age;
            fin >> fname >> lname >> nc >> age >> username >> password;

            currentCustomer = new Customer(fname, lname, nc, age, username, password);
            users.push_back(currentCustomer);

        } else if (type == "Admin") {
            string fname, lname, nc, username, password;
            int age;
            fin >> fname >> lname >> nc >> age >> username >> password;

            users.push_back(new Admin(fname, lname, nc, age, username, password));

        } else if (type == "Account" && currentCustomer != nullptr) {
            string accType, card, sheba, accNum, cvv2, expire, pass1, pass2;
            double balance;
            fin >> accType >> card >> sheba >> accNum >> cvv2 >> balance >> expire >> pass1 >> pass2;

            // حذف فاصله‌های شماره کارت
            card.erase(remove_if(card.begin(), card.end(), ::isspace), card.end());

            BankAccount* acc = nullptr;
            if (accType == "سپرده")
                acc = new SepordeAccount(card, sheba, accNum, cvv2, balance, expire, pass1, pass2);
            else if (accType == "جاری")
                acc = new JariAccount(card, sheba, accNum, cvv2, balance, expire, pass1, pass2);
            else if (accType == "قرض‌الحسنه")
                acc = new GharzAccount(card, sheba, accNum, cvv2, balance, expire, pass1, pass2);

            if (acc && currentCustomer)
                currentCustomer->addAccount(acc);
        }
    }

    fin.close();
}
