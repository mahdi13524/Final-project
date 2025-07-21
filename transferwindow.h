#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include "bank_system.h"

class TransferWindow : public QWidget {
    Q_OBJECT

public:
    TransferWindow(Customer* customer, QWidget* parent = nullptr);

private slots:
    void onTransferClicked();

private:
    Customer* currentCustomer;

    QLineEdit* fromCardEdit;
    QLineEdit* toCardEdit;
    QLineEdit* amountEdit;
    QLineEdit* password2Edit;

    QLabel* resultLabel;
};

#endif
