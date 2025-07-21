#ifndef DELETEACCOUNTWINDOW_H
#define DELETEACCOUNTWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "bank_system.h"

class DeleteAccountWindow : public QWidget {
    Q_OBJECT

public:
    explicit DeleteAccountWindow(Customer* customer, QWidget* parent = nullptr);

private slots:
    void onDeleteClicked();

private:
    Customer* currentCustomer;
    QListWidget* accountList;
};

#endif
