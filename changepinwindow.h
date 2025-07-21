#ifndef CHANGEPINWINDOW_H
#define CHANGEPINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>
#include "bank_system.h"

class ChangePinWindow : public QWidget {
    Q_OBJECT

public:
    explicit ChangePinWindow(Customer* customer, QWidget* parent = nullptr);

private slots:
    void onChangeClicked();

private:
    Customer* currentCustomer;

    QComboBox* cardBox;
    QLineEdit* newPin1Edit;
    QLineEdit* newPin2Edit;
    QPushButton* changeBtn;
};

#endif
