#include "edituserwindow.h"

#include <QMessageBox>


EditUserWindow::EditUserWindow(User* user, QWidget* parent)
    : QWidget(parent), currentUser(user) {

    setWindowTitle("ویرایش اطلاعات کاربر");

    firstNameEdit = new QLineEdit(QString::fromStdString(user->getFirstName()));
    lastNameEdit  = new QLineEdit(QString::fromStdString(user->getLastName()));

    nationalCodeEdit = new QLineEdit();
    ageEdit = new QLineEdit();
    passwordEdit = new QLineEdit();

    QPushButton* saveBtn = new QPushButton("ذخیره تغییرات");

    QFormLayout* form = new QFormLayout;
    form->addRow("نام:", firstNameEdit);
    form->addRow("نام خانوادگی:", lastNameEdit);
    form->addRow("کد ملی:", nationalCodeEdit);
    form->addRow("سن:", ageEdit);
    form->addRow("رمز عبور:", passwordEdit);
    form->addWidget(saveBtn);

    setLayout(form);

    connect(saveBtn, &QPushButton::clicked, this, &EditUserWindow::onSaveClicked);
}

void EditUserWindow::onSaveClicked() {
    currentUser->setFirstName(firstNameEdit->text().toStdString());
    currentUser->setLastName(lastNameEdit->text().toStdString());

    currentUser->setNationalCode(nationalCodeEdit->text().toStdString());
    currentUser->setAge(ageEdit->text().toInt());
    currentUser->setPassword(passwordEdit->text().toStdString());

    QMessageBox::information(this, "موفق", "اطلاعات با موفقیت ذخیره شد.");
    close();
}
