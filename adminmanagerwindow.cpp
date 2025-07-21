#include "adminmanagerwindow.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

AdminManagerWindow::AdminManagerWindow(QWidget* parent)
    : QWidget(parent) {
    setWindowTitle("مدیریت ادمین‌ها");
    resize(400, 300);

    adminList = new QListWidget(this);
    QPushButton* addBtn = new QPushButton("➕ افزودن ادمین");
    QPushButton* delBtn = new QPushButton("❌ حذف ادمین انتخاب‌شده");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(adminList);
    layout->addWidget(addBtn);
    layout->addWidget(delBtn);
    setLayout(layout);

    connect(addBtn, &QPushButton::clicked, this, &AdminManagerWindow::onAddAdminClicked);
    connect(delBtn, &QPushButton::clicked, this, &AdminManagerWindow::onDeleteAdminClicked);

    refreshAdminList();
}

void AdminManagerWindow::refreshAdminList() {
    adminList->clear();
    for (User* u : users) {
        Admin* a = dynamic_cast<Admin*>(u);
        if (a) {
            QString entry = QString::fromStdString(a->getUsername()) + " - " +
                            QString::fromStdString(a->getFullName());
            QListWidgetItem* item = new QListWidgetItem(entry);
            item->setData(Qt::UserRole, QVariant::fromValue<void*>(a));
            adminList->addItem(item);
        }
    }
}

void AdminManagerWindow::onAddAdminClicked() {
    bool ok;
    QString username = QInputDialog::getText(this, "نام کاربری", "نام کاربری ادمین جدید:", QLineEdit::Normal, "", &ok);
    if (!ok || username.isEmpty()) return;

    QString password = QInputDialog::getText(this, "رمز عبور", "رمز عبور ادمین جدید:", QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty()) return;

    for (User* u : users)
        if (u->getUsername() == username.toStdString()) {
            QMessageBox::warning(this, "خطا", "نام کاربری قبلاً وجود دارد.");
            return;
        }

    users.push_back(new Admin("ادمین", "جدید", "0000000000", 30, username.toStdString(), password.toStdString()));
    QMessageBox::information(this, "✅ موفق", "ادمین با موفقیت اضافه شد.");
    refreshAdminList();
}

void AdminManagerWindow::onDeleteAdminClicked() {
    QListWidgetItem* item = adminList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "خطا", "لطفاً یک ادمین انتخاب کنید.");
        return;
    }

    QString text = item->text();
    for (int i = 0; i < users.size(); ++i) {
        Admin* a = dynamic_cast<Admin*>(users[i]);
        if (a) {
            QString entry = QString::fromStdString(a->getUsername()) + " - " +
                            QString::fromStdString(a->getFullName());
            if (entry == text) {
                if (a->getUsername() == "admin") {
                    QMessageBox::warning(this, "مجاز نیست", "ادمین اصلی را نمی‌توان حذف کرد!");
                    return;
                }

                delete users[i];
                users.erase(users.begin() + i);
                QMessageBox::information(this, "حذف شد", "ادمین حذف شد.");
                refreshAdminList();
                return;
            }
        }
    }
}
