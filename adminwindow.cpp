#include "adminwindow.h"
#include "createaccountwindow.h"
#include "addcustomerwindow.h"
#include "showaccountswindow.h"
#include "adminmanagerwindow.h"
#include "deleteaccountwindow.h"
#include "edituserwindow.h"
#include <QDateTime>
#include <QLabel>


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QInputDialog>
#include <QLineEdit>

AdminWindow::AdminWindow(Admin* admin, QWidget* parent)
    : QWidget(parent), currentAdmin(admin) {

    setWindowTitle("منوی ادمین - " + QString::fromStdString(admin->getFullName()));
    resize(500, 600);

    customerList = new QListWidget(this);

    QHBoxLayout* searchLayout = new QHBoxLayout;
    QLineEdit* searchInput = new QLineEdit;
    searchInput->setPlaceholderText("🔍 جستجوی نام کاربری...");
    QPushButton* searchBtn = new QPushButton("جستجو");
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchBtn);

    QPushButton* addCustomerBtn     = new QPushButton("➕ افزودن مشتری جدید");
    createAccountBtn                = new QPushButton("💳 ایجاد حساب برای مشتری انتخاب‌شده");
    QPushButton* deleteCustomerBtn  = new QPushButton("❌ حذف مشتری انتخاب‌شده");
    QPushButton* deleteAccountBtn   = new QPushButton("❌ حذف حساب مشتری انتخاب‌شده");
    QPushButton* changePasswordBtn  = new QPushButton("✏️ تغییر رمز عبور مشتری");
    QPushButton* showAccountsBtn    = new QPushButton("📋 نمایش حساب‌های مشتری");
    QPushButton* manageAdminsBtn    = new QPushButton("👥 مدیریت ادمین‌ها");
    QPushButton* editCustomerBtn = new QPushButton("✏️ ویرایش مشتری انتخاب‌شده");
    QPushButton* editSelfBtn = new QPushButton("🧑‍💼 ویرایش اطلاعات خودم");
    showCustomerInfoBtn = new QPushButton("👤 مشاهده اطلاعات مشتری");

    exitBtn                         = new QPushButton("🚪 خروج");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(customerList);
    mainLayout->addWidget(addCustomerBtn);
    mainLayout->addWidget(createAccountBtn);
    mainLayout->addWidget(deleteCustomerBtn);
    mainLayout->addWidget(changePasswordBtn);
    mainLayout->addWidget(showAccountsBtn);
    mainLayout->addWidget(manageAdminsBtn);
    mainLayout->addWidget(deleteAccountBtn);
    mainLayout->addWidget(editCustomerBtn);
    mainLayout->addWidget(editSelfBtn);
    mainLayout->addWidget(showCustomerInfoBtn);

    mainLayout->addWidget(exitBtn);
    setLayout(mainLayout);

    clockLabel = new QLabel(this);
    clockLabel->setAlignment(Qt::AlignRight);
    clockLabel->setStyleSheet("font-size: 14px; color: #555;");

    mainLayout->addWidget(clockLabel);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        QDateTime now = QDateTime::currentDateTime();
        QString timeText = now.toString("⏰ hh:mm:ss     📅 yyyy/MM/dd");
        clockLabel->setText(timeText);
    });
    timer->start(1000);


    loadCustomers();

    connect(addCustomerBtn,     &QPushButton::clicked, this, &AdminWindow::onAddCustomerClicked);
    connect(createAccountBtn,   &QPushButton::clicked, this, &AdminWindow::onCreateAccountClicked);
    connect(deleteCustomerBtn,  &QPushButton::clicked, this, &AdminWindow::onDeleteCustomerClicked);
    connect(changePasswordBtn,  &QPushButton::clicked, this, &AdminWindow::onChangePasswordClicked);
    connect(showAccountsBtn,    &QPushButton::clicked, this, &AdminWindow::onShowAccountsClicked);
    connect(manageAdminsBtn,    &QPushButton::clicked, this, &AdminWindow::onManageAdminsClicked);
    connect(deleteAccountBtn,   &QPushButton::clicked, this, &AdminWindow::onDeleteAccountClicked);
    connect(editCustomerBtn, &QPushButton::clicked, this, &AdminWindow::onEditCustomerClicked);
    connect(editSelfBtn, &QPushButton::clicked, this, &AdminWindow::onEditSelfClicked);
    connect(showCustomerInfoBtn, &QPushButton::clicked, this, &AdminWindow::onShowCustomerInfoClicked);

    connect(exitBtn,            &QPushButton::clicked, this, &AdminWindow::onExitClicked);

    connect(searchBtn, &QPushButton::clicked, this, [=]() {
        QString username = searchInput->text().trimmed();
        if (username.isEmpty()) {
            QMessageBox::warning(this, "خطا", "لطفاً نام کاربری وارد کنید.");
            return;
        }

        bool found = false;
        for (int i = 0; i < customerList->count(); ++i) {
            QListWidgetItem* item = customerList->item(i);
            if (item->text().startsWith(username + " -")) {
                customerList->setCurrentItem(item);
                customerList->scrollToItem(item);
                found = true;
                break;
            }
        }

        if (!found) {
            QMessageBox::information(this, "یافت نشد", "مشتری با این نام کاربری پیدا نشد.");
        }
    });
}

void AdminWindow::loadCustomers() {
    customerList->clear();
    for (User* u : users) {
        if (Customer* c = dynamic_cast<Customer*>(u)) {
            QString entry = QString::fromStdString(c->getUsername()) + " - " +
                            QString::fromStdString(c->getFullName());
            QListWidgetItem* item = new QListWidgetItem(entry);
            item->setData(Qt::UserRole, QVariant::fromValue<void*>(c));
            customerList->addItem(item);
        }
    }
}

Customer* AdminWindow::getSelectedCustomer() {
    QListWidgetItem* selectedItem = customerList->currentItem();
    if (!selectedItem) return nullptr;

    QString selectedText = selectedItem->text();

    for (User* u : users) {
        if (Customer* c = dynamic_cast<Customer*>(u)) {
            QString entry = QString::fromStdString(c->getUsername()) + " - " +
                            QString::fromStdString(c->getFullName());
            if (entry == selectedText)
                return c;
        }
    }
    return nullptr;
}

void AdminWindow::onAddCustomerClicked() {
    AddCustomerWindow* win = new AddCustomerWindow();
    connect(win, &AddCustomerWindow::customerAdded, this, &AdminWindow::loadCustomers);
    win->show();
}

void AdminWindow::onCreateAccountClicked() {
    Customer* selectedCustomer = getSelectedCustomer();
    if (!selectedCustomer) {
        QMessageBox::warning(this, "هشدار", "لطفاً یک مشتری انتخاب کنید.");
        return;
    }
    CreateAccountWindow* win = new CreateAccountWindow(selectedCustomer);
    win->show();
}

void AdminWindow::onDeleteCustomerClicked() {
    Customer* selectedCustomer = getSelectedCustomer();
    if (!selectedCustomer) {
        QMessageBox::warning(this, "هشدار", "لطفاً یک مشتری انتخاب کنید.");
        return;
    }

    QMessageBox::StandardButton confirm = QMessageBox::question(
        this, "تأیید حذف", "آیا از حذف این مشتری مطمئن هستید؟",
        QMessageBox::Yes | QMessageBox::No
        );

    if (confirm == QMessageBox::Yes) {
        for (int i = 0; i < users.size(); ++i) {
            if (users[i] == selectedCustomer) {
                delete users[i];
                users.erase(users.begin() + i);
                break;
            }
        }
        QMessageBox::information(this, "حذف شد", "مشتری با موفقیت حذف شد.");
        loadCustomers();
    }
}

void AdminWindow::onShowCustomerInfoClicked() {
    Customer* selectedCustomer = getSelectedCustomer();
    if (!selectedCustomer) {
        QMessageBox::warning(this, "خطا", "لطفاً یک مشتری انتخاب کنید.");
        return;
    }

    QString info;
    info += "👤 نام: " + QString::fromStdString(selectedCustomer->getFullName()) + "\n";
    info += "🆔 کد ملی: " + QString::fromStdString(selectedCustomer->getNationalCode()) + "\n";
    info += "🎂 سن: " + QString::number(selectedCustomer->getAge()) + "\n";
    info += "👤 نام کاربری: " + QString::fromStdString(selectedCustomer->getUsername());

    QMessageBox::information(this, "اطلاعات مشتری", info);
}


void AdminWindow::onEditCustomerClicked() {
    Customer* selectedCustomer = getSelectedCustomer();
    if (!selectedCustomer) {
        QMessageBox::warning(this, "خطا", "لطفاً یک مشتری انتخاب کنید.");
        return;
    }

    EditUserWindow* win = new EditUserWindow(selectedCustomer);
    win->show();
}

void AdminWindow::onEditSelfClicked() {
    EditUserWindow* win = new EditUserWindow(currentAdmin);
    win->show();
}


void AdminWindow::onChangePasswordClicked() {
    Customer* selectedCustomer = getSelectedCustomer();
    if (!selectedCustomer) {
        QMessageBox::warning(this, "هشدار", "لطفاً یک مشتری را انتخاب کنید.");
        return;
    }

    bool ok;
    QString newPass = QInputDialog::getText(
        this, "تغییر رمز عبور", "رمز عبور جدید را وارد کنید:",
        QLineEdit::Password, "", &ok
        );

    if (ok && !newPass.isEmpty()) {
        selectedCustomer->setPassword(newPass.toStdString());
        QMessageBox::information(this, "موفق", "رمز عبور با موفقیت تغییر یافت.");
    } else if (ok) {
        QMessageBox::warning(this, "خطا", "رمز عبور نمی‌تواند خالی باشد.");
    }
}

void AdminWindow::onShowAccountsClicked() {
    Customer* selectedCustomer = getSelectedCustomer();
    if (!selectedCustomer) {
        QMessageBox::warning(this, "هشدار", "لطفاً یک مشتری را انتخاب کنید.");
        return;
    }

    ShowAccountsWindow* win = new ShowAccountsWindow(selectedCustomer);
    win->show();
}

void AdminWindow::onManageAdminsClicked() {
    AdminManagerWindow* win = new AdminManagerWindow();
    win->show();
}

void AdminWindow::onDeleteAccountClicked() {
    Customer* selectedCustomer = getSelectedCustomer();
    if (!selectedCustomer) {
        QMessageBox::warning(this, "خطا", "لطفاً یک مشتری انتخاب کنید.");
        return;
    }

    DeleteAccountWindow* win = new DeleteAccountWindow(selectedCustomer);
    win->show();
}

void AdminWindow::onExitClicked() {
    close();
}
void AdminWindow::updateClock() {
    QString timeText = QDateTime::currentDateTime().toString("hh:mm:ss   yyyy/MM/dd");
    if (clockLabel) {
        clockLabel->setText(timeText);
    }
}
