#include "createaccountwindow.h"
#include <QMessageBox>

CreateAccountWindow::CreateAccountWindow(Customer* customer, QWidget* parent)
    : QWidget(parent), currentCustomer(customer) {

    setWindowTitle("ایجاد حساب بانکی برای: " + QString::fromStdString(customer->getFullName()));
    resize(400, 400);

    cardEdit = new QLineEdit();
    shebaEdit = new QLineEdit();
    accNumEdit = new QLineEdit();
    cvv2Edit = new QLineEdit();
    expireEdit = new QLineEdit();
    pass1Edit = new QLineEdit();
    pass2Edit = new QLineEdit();
    balanceEdit = new QLineEdit();

    typeBox = new QComboBox();
    typeBox->addItem("قرض‌الحسنه");
    typeBox->addItem("سپرده");
    typeBox->addItem("جاری");

    QPushButton* createBtn = new QPushButton("ایجاد حساب");

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("شماره کارت:", cardEdit);
    formLayout->addRow("شماره شبا:", shebaEdit);
    formLayout->addRow("شماره حساب:", accNumEdit);
    formLayout->addRow("CVV2:", cvv2Edit);
    formLayout->addRow("تاریخ انقضا:", expireEdit);
    formLayout->addRow("رمز اول:", pass1Edit);
    formLayout->addRow("رمز دوم ثابت:", pass2Edit);
    formLayout->addRow("موجودی اولیه:", balanceEdit);
    formLayout->addRow("نوع حساب:", typeBox);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(formLayout);
    layout->addWidget(createBtn);
    setLayout(layout);

    connect(createBtn, &QPushButton::clicked, this, &CreateAccountWindow::onCreateClicked);
}

void CreateAccountWindow::onCreateClicked() {
    string card = cardEdit->text().toStdString();
    string sheba = shebaEdit->text().toStdString();
    string accNum = accNumEdit->text().toStdString();
    string cvv2 = cvv2Edit->text().toStdString();
    string expire = expireEdit->text().toStdString();
    string pass1 = pass1Edit->text().toStdString();
    string pass2 = pass2Edit->text().toStdString();
    double balance = balanceEdit->text().toDouble();

    int type = typeBox->currentIndex();

    BankAccount* acc = nullptr;
    if (type == 0)
        acc = new GharzAccount(card, sheba, accNum, cvv2, balance, expire, pass1, pass2);
    else if (type == 1)
        acc = new SepordeAccount(card, sheba, accNum, cvv2, balance, expire, pass1, pass2);
    else
        acc = new JariAccount(card, sheba, accNum, cvv2, balance, expire, pass1, pass2);

    if (!currentCustomer->addAccount(acc)) {
        QMessageBox::warning(this, "خطا", "این مشتری قبلاً ۵ حساب دارد و نمی‌توان حساب جدیدی ایجاد کرد.");
        delete acc;
        return;
    }

    QMessageBox::information(this, "موفق", "✅ حساب با موفقیت ایجاد شد!");
    close();

}
