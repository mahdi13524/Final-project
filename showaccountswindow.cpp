#include "showaccountswindow.h"
#include <QVBoxLayout>
#include <QString>

ShowAccountsWindow::ShowAccountsWindow(Customer* customer, QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("📋 حساب‌های مشتری: " + QString::fromStdString(customer->getFullName()));
    resize(400, 300);

    QTextEdit* display = new QTextEdit(this);
    display->setReadOnly(true);

    QString content;
    for (BankAccount* acc : customer->getAccounts()) {
        content += "🔸 نوع حساب: " + QString::fromStdString(acc->getType()) + "\n";
        content += "شماره کارت: " + QString::fromStdString(acc->getCardNumber()) + "\n";
        content += "موجودی: " + QString::number(acc->getBalance()) + " تومان\n";
        content += "تاریخ انقضا: " + QString::fromStdString(acc->getExpireDate()) + "\n";
        content += "-----------------------------\n";
    }

    if (content.isEmpty()) {
        content = "این مشتری هیچ حساب فعالی ندارد.";
    }

    display->setText(content);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(display);
    setLayout(layout);
}
