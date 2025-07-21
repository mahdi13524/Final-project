#include "loginwindow.h"
#include "bank_system.h"
#include "customerwindow.h"
#include "adminwindow.h"
#include<QPropertyAnimation>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    resize(600, 400);
    QLabel* bgLabel = new QLabel(this);
    bgLabel->setPixmap(QPixmap("E:/qt project/untitled/13844.jpg").scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    bgLabel->setGeometry(0, 0, width(), height());
    bgLabel->lower();

    this->setWindowOpacity(0);

    QPropertyAnimation* anim = new QPropertyAnimation(this, "windowOpacity");
    anim->setDuration(1500);
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->start();

    setWindowTitle("ورود به سیستم بانکی");

    QLabel *userLabel = new QLabel("نام کاربری:");
    QLabel *passLabel = new QLabel("رمز عبور:");

    usernameInput = new QLineEdit();
    passwordInput = new QLineEdit();
    passwordInput->setEchoMode(QLineEdit::Password);

    QPushButton *loginBtn = new QPushButton("ورود");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(userLabel);
    layout->addWidget(usernameInput);
    layout->addWidget(passLabel);
    layout->addWidget(passwordInput);
    layout->addWidget(loginBtn);

    setLayout(layout);

    connect(loginBtn, &QPushButton::clicked, this, &LoginWindow::handleLogin);
}

void LoginWindow::handleLogin() {
    QString user = usernameInput->text();
    QString pass = passwordInput->text();

    User *u = login(user.toStdString(), pass.toStdString());

    if (u) {
        if (Admin* a = dynamic_cast<Admin*>(u)) {
            AdminWindow* aw = new AdminWindow(a);
            aw->show();
            this->close();
        } else if (Customer* c = dynamic_cast<Customer*>(u)) {
            CustomerWindow* cw = new CustomerWindow(c);
            cw->show();
            this->close();
        } else {
            QMessageBox::warning(this, "خطا", "نوع کاربر پشتیبانی نمی‌شود.");
        }
    } else {
        QMessageBox::warning(this, "❌ خطا", "نام کاربری یا رمز عبور اشتباه است.");
    }
}
