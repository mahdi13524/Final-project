#include "deleteaccountwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

DeleteAccountWindow::DeleteAccountWindow(Customer* customer, QWidget* parent)
    : QWidget(parent), currentCustomer(customer) {
    setWindowTitle("❌ حذف حساب بانکی مشتری");
    resize(400, 300);

    accountList = new QListWidget(this);
    QPushButton* deleteBtn = new QPushButton("حذف حساب انتخاب‌شده");

    for (BankAccount* acc : customer->getAccounts()) {
        QString text = "شماره کارت: " + QString::fromStdString(acc->getCardNumber()) +
                       " | نوع: " + QString::fromStdString(acc->getType());
        QListWidgetItem* item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, QVariant::fromValue<void*>(acc));
        accountList->addItem(item);
    }

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(accountList);
    layout->addWidget(deleteBtn);
    setLayout(layout);

    connect(deleteBtn, &QPushButton::clicked, this, &DeleteAccountWindow::onDeleteClicked);
}

void DeleteAccountWindow::onDeleteClicked() {
    QListWidgetItem* item = accountList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "هشدار", "لطفاً یک حساب انتخاب کنید.");
        return;
    }

    BankAccount* accToDelete = static_cast<BankAccount*>(item->data(Qt::UserRole).value<void*>());
    if (!accToDelete) return;

    currentCustomer->removeAccount(accToDelete);
    QMessageBox::information(this, "موفق", "حساب با موفقیت حذف شد.");
    this->close();
}
