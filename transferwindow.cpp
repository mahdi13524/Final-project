#include "transferwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>

TransferWindow::TransferWindow(Customer* customer, QWidget* parent)
    : QWidget(parent), currentCustomer(customer) {

    setWindowTitle("💳 کارت به کارت");
    resize(400, 300);

    fromCardEdit = new QLineEdit();
    toCardEdit = new QLineEdit();
    amountEdit = new QLineEdit();
    password2Edit = new QLineEdit();
    password2Edit->setEchoMode(QLineEdit::Password);
    resultLabel = new QLabel();

    QPushButton* transferBtn = new QPushButton("✅ انجام انتقال");

    QFormLayout* form = new QFormLayout;
    form->addRow("شماره کارت مبدا:", fromCardEdit);
    form->addRow("شماره کارت مقصد:", toCardEdit);
    form->addRow("مبلغ (تومان):", amountEdit);
    form->addRow("رمز دوم:", password2Edit);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(form);
    layout->addWidget(transferBtn);
    layout->addWidget(resultLabel);
    setLayout(layout);

    connect(transferBtn, &QPushButton::clicked, this, &TransferWindow::onTransferClicked);
}

void TransferWindow::onTransferClicked() {
    string fromCard = fromCardEdit->text().toStdString();
    string toCard = toCardEdit->text().toStdString();
    double amount = amountEdit->text().toDouble();
    string pass2 = password2Edit->text().toStdString();

    BankAccount* from = currentCustomer->findAccountByCard(fromCard);
    if (!from) {
        QMessageBox::warning(this, "خطا", "❌ کارت مبدا یافت نشد.");
        return;
    }

    string exp = from->getExpireDate();
    int expInt = stoi("20" + exp.substr(3, 2) + exp.substr(0, 2));
    int nowInt = 202507; 
    if (expInt < nowInt) {
        QMessageBox::warning(this, "خطا", "❌ کارت منقضی شده است.");
        return;
    }

    BankAccount* to = nullptr;
    Customer* receiver = nullptr;

    for (auto* u : users) {
        Customer* c = dynamic_cast<Customer*>(u);
        if (c) {
            to = c->findAccountByCard(toCard);
            if (to) {
                receiver = c;
                break;
            }
        }
    }

    if (!to) {
        QMessageBox::warning(this, "خطا", "❌ شماره کارت مقصد معتبر نیست.");
        return;
    }
    QString name = QString::fromStdString(receiver->getFullName());
    QMessageBox::information(this, "گیرنده", "👤 صاحب کارت مقصد: " + name);


    if (amount > 3000000) {
        QMessageBox::warning(this, "خطا", "❌ سقف هر تراکنش ۳ میلیون تومان است.");
        return;
    }

    time_t now = time(0);
    if (difftime(now, currentCustomer->getLastTransferTime()) > 86400) {
        currentCustomer->setDailyTransferAmount(0);
        currentCustomer->setLastTransferTime(now);
    }

    if (currentCustomer->getDailyTransferAmount() + amount > 6000000) {
        QMessageBox::warning(this, "خطا", "❌ سقف روزانه ۶ میلیون تومان است.");
        return;
    }

    double fee = amount * 0.01;
    double total = amount + fee;

    if (amount <= 100000) {
        if (pass2 != from->getStaticPassword2()) {
            QMessageBox::warning(this, "خطا", "❌ رمز دوم ثابت نادرست است.");
            return;
        }
    } else {
        if (amount > 100000) {
            if (from->getDynamicPassword2().empty()) {
                string dynamic = to_string(rand() % 900000 + 100000);
                from->setDynamicPassword2(dynamic);
                QMessageBox::information(this, "رمز پویا", QString("رمز دوم پویا شما: %1").arg(QString::fromStdString(dynamic)));
                return;
            }

            if (pass2 != from->getDynamicPassword2()) {
                QMessageBox::warning(this, "خطا", "❌ رمز دوم پویا نادرست است.");
                return;
            }

            from->setDynamicPassword2("");
        }

    }

    if (!from->withdraw(total)) {
        QMessageBox::warning(this, "خطا", "❌ موجودی کافی نیست.");
        return;
    }

    to->deposit(amount);
    currentCustomer->setDailyTransferAmount(currentCustomer->getDailyTransferAmount() + amount);

    resultLabel->setText(QString("✅ انتقال با موفقیت انجام شد.\nمبلغ: %1 تومان\nکارمزد: %2 تومان")
                             .arg(amount).arg(fee));
}

