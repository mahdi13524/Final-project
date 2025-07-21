#ifndef SHOWACCOUNTSWINDOW_H
#define SHOWACCOUNTSWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include "bank_system.h"

class ShowAccountsWindow : public QWidget {
    Q_OBJECT

public:
    explicit ShowAccountsWindow(Customer* customer, QWidget* parent = nullptr);
};

#endif
