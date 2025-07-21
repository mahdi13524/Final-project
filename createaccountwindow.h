#ifndef CREATEACCOUNTWINDOW_H
#define CREATEACCOUNTWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include "bank_system.h"

class CreateAccountWindow : public QWidget {
    Q_OBJECT

public:
    CreateAccountWindow(Customer* customer, QWidget* parent = nullptr);

private slots:
    void onCreateClicked();

private:
    Customer* currentCustomer;

    QLineEdit* cardEdit;
    QLineEdit* shebaEdit;
    QLineEdit* accNumEdit;
    QLineEdit* cvv2Edit;
    QLineEdit* expireEdit;
    QLineEdit* pass1Edit;
    QLineEdit* pass2Edit;
    QLineEdit* balanceEdit;
    QComboBox* typeBox;
};

#endif
