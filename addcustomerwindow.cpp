#include "addcustomerwindow.h"
#include "bank_system.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QMessageBox>

AddCustomerWindow::AddCustomerWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("افزودن مشتری جدید");
    resize(350, 300);

    nameEdit = new QLineEdit();
    familyEdit = new QLineEdit();
    nationalCodeEdit = new QLineEdit();
    ageEdit = new QLineEdit();
    usernameEdit = new QLineEdit();
    passwordEdit = new QLineEdit();

    QPushButton* addBtn = new QPushButton("افزودن");

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("نام:", nameEdit);
    formLayout->addRow("نام خانوادگی:", familyEdit);
    formLayout->addRow("کد ملی:", nationalCodeEdit);
    formLayout->addRow("سن:", ageEdit);
    formLayout->addRow("نام کاربری:", usernameEdit);
    formLayout->addRow("رمز عبور:", passwordEdit);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(formLayout);
    layout->addWidget(addBtn);
    setLayout(layout);

    connect(addBtn, &QPushButton::clicked, this, &AddCustomerWindow::onAddClicked);
}

void AddCustomerWindow::onAddClicked() {
    string name = nameEdit->text().toStdString();
    string family = familyEdit->text().toStdString();
    string nationalCode = nationalCodeEdit->text().toStdString();
    int age = ageEdit->text().toInt();
    string username = usernameEdit->text().toStdString();
    string password = passwordEdit->text().toStdString();

    if (name.empty() || family.empty() || nationalCode.empty() || username.empty() || password.empty() || age <= 0) {
        QMessageBox::warning(this, "خطا", "همه فیلدها را کامل پر کنید.");
        return;
    }

    for (auto* u : users) {
        if (u->getUsername() == username) {
            QMessageBox::warning(this, "خطا", "نام کاربری قبلاً استفاده شده است.");
            return;
        }
    }

    users.push_back(new Customer(name, family, nationalCode, age, username, password));
    QMessageBox::information(this, "✅ موفق", "مشتری با موفقیت افزوده شد!");
    emit customerAdded();
    close();
}
