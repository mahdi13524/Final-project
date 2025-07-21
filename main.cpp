#include <QApplication>
#include "loginwindow.h"
#include "bank_system.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setStyleSheet("QPushButton { background-color: #2980b9; color: white; border-radius: 5px; padding: 5px; }"
                      "QPushButton:hover { background-color: #3498db; }"
                      "QLabel { font-size: 14px; }"
                      "QLineEdit { padding: 4px; border: 1px solid #ccc; border-radius: 3px; }");

    loadUsers();

    if (users.empty()) {
        users.push_back(new Admin("احسان", "مهدوی", "1234567890", 40, "admin", "admin"));

        Customer* c1 = new Customer("علی", "رضایی", "1111111111", 25, "ali", "1234");

        BankAccount* aliAcc1 = new SepordeAccount("1234123412341234", "IR123", "AC123", "123", 100000000, "07/27", "1111", "2222");
        BankAccount* aliAcc2 = new GharzAccount("1212121212121212", "IR456", "AC456", "321", 500000, "07/28", "3333", "4444");
        BankAccount* aliAcc3 = new GharzAccount("4321432155555321", "IR496", "AC486", "321", 500000, "07/20", "3333", "4444");

        c1->addAccount(aliAcc1);
        c1->addAccount(aliAcc2);
        c1->addAccount(aliAcc3);
        users.push_back(c1);

        Customer* c2 = new Customer("مینا", "محمدی", "2222222222", 30, "mina", "1234");

        BankAccount* minaAcc1 = new SepordeAccount("5555444433332222", "IR567", "AC567", "456", 1200000, "08/27", "9999", "8888");
        BankAccount* minaAcc2 = new JariAccount("1234567891011121", "IR890", "AC890", "789", 750000, "09/28", "7777", "6666");

        c2->addAccount(minaAcc1);
        c2->addAccount(minaAcc2);
        users.push_back(c2);
    }

    LoginWindow w;
    w.show();

    int result = app.exec();

    saveUsers();

    return result;
}
// این یه جمله‌ی آزمایشی برای نمایش در Pull Request است.

