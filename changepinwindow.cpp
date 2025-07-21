#include "changepinwindow.h"

ChangePinWindow::ChangePinWindow(Customer* customer, QWidget* parent)
    : QWidget(parent), currentCustomer(customer) {

    setWindowTitle("🔐 تغییر رمز کارت");
    resize(300, 200);

    cardBox = new QComboBox();
    newPin1Edit = new QLineEdit();
    newPin2Edit = new QLineEdit();
    newPin1Edit->setEchoMode(QLineEdit::Password);
    newPin2Edit->setEchoMode(QLineEdit::Password);

    for (BankAccount* acc : currentCustomer->getAccounts()) {
        cardBox->addItem(QString::fromStdString(acc->getCardNumber()));
    }

    changeBtn = new QPushButton("✅ تغییر رمزها");

    QFormLayout* form = new QFormLayout;
    form->addRow("شماره کارت:", cardBox);
    form->addRow("رمز اول جدید:", newPin1Edit);
    form->addRow("رمز دوم ثابت جدید:", newPin2Edit);
    form->addWidget(changeBtn);

    setLayout(form);

    connect(changeBtn, &QPushButton::clicked, this, &ChangePinWindow::onChangeClicked);
}

void ChangePinWindow::onChangeClicked() {
    QString cardText = cardBox->currentText();
    QString pin1 = newPin1Edit->text();
    QString pin2 = newPin2Edit->text();

    if (pin1.length() != 4 || pin2.length() != 4 || !pin1.toUInt() || !pin2.toUInt()) {
        QMessageBox::warning(this, "خطا", "رمزها باید عددی و ۴ رقمی باشند.");
        return;
    }

    std::string card = cardText.toStdString();
    BankAccount* acc = currentCustomer->findAccountByCard(card);
    if (!acc) {
        QMessageBox::warning(this, "خطا", "کارت انتخاب‌شده یافت نشد.");
        return;
    }

    acc->setPassword1(pin1.toStdString());
    acc->setStaticPassword2(pin2.toStdString());

    QMessageBox::information(this, "✅ موفق", "رمزها با موفقیت تغییر یافتند.");
    close();
}
