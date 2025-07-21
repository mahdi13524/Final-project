#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "bank_system.h"

class CustomerWindow : public QWidget {
    Q_OBJECT

public:
    CustomerWindow(Customer* customer, QWidget* parent = nullptr);

private slots:
    void onShowAccounts();
    void onTransferMoney();
    void onTransferClicked();
    void onChangePinClicked();



private:
    Customer* currentCustomer;
};

#endif
