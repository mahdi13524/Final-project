#include "customerwindow.h"
#include "transferwindow.h"
#include "transferwindow.h"
#include "changepinwindow.h"

#include <QMessageBox>
#include <QInputDialog>

CustomerWindow::CustomerWindow(Customer* customer, QWidget* parent)
    : QWidget(parent), currentCustomer(customer) {
    setWindowTitle("منوی مشتری - " + QString::fromStdString(customer->getFullName()));
    resize(300, 200);

    QPushButton* showAccBtn = new QPushButton("مشاهده حساب‌ها");
    QPushButton* transferBtn = new QPushButton("کارت به کارت");
    QPushButton* changePinBtn = new QPushButton("🔐 تغییر رمز کارت");

    QPushButton* exitBtn = new QPushButton("خروج");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(showAccBtn);
    layout->addWidget(transferBtn);
    layout->addWidget(changePinBtn);

    layout->addWidget(exitBtn);

    setLayout(layout);

    connect(showAccBtn, &QPushButton::clicked, this, &CustomerWindow::onShowAccounts);
    connect(transferBtn, &QPushButton::clicked, this, &CustomerWindow::onTransferMoney);
    connect(exitBtn, &QPushButton::clicked, this, &QWidget::close);
    connect(changePinBtn, &QPushButton::clicked, this, &CustomerWindow::onChangePinClicked);

    connect(transferBtn, &QPushButton::clicked, this, &CustomerWindow::onTransferClicked);

}

void CustomerWindow::onShowAccounts() {
    QString result;
    vector<BankAccount*> accs = currentCustomer->getAccounts();
    if (accs.empty()) {
        result = "هیچ حسابی ندارید.";
    } else {
        for (auto* acc : accs) {
            result += "نوع: " + QString::fromStdString(acc->getType()) + "\n";
            result += "کارت: " + QString::fromStdString(acc->getCardNumber()) + "\n";
            result += "موجودی: " + QString::number(acc->getBalance()) + " تومان\n\n";
            result += "ویژگی: " + QString::fromStdString(acc->getSpecialFeature()) + "\n";

        }
    }
    QMessageBox::information(this, "حساب‌ها", result);
}
void CustomerWindow::onTransferClicked() {
    TransferWindow* win = new TransferWindow(currentCustomer);
    win->show();
}

void CustomerWindow::onTransferMoney() {
        TransferWindow* win = new TransferWindow(currentCustomer);
        win->show();
    }
void CustomerWindow::onChangePinClicked() {
    ChangePinWindow* win = new ChangePinWindow(currentCustomer);
    win->show();
}

