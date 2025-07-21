#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H
#include <QLabel>
#include <QTimer>

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "bank_system.h"

class AdminWindow : public QWidget {
    Q_OBJECT

public:
    explicit AdminWindow(Admin* admin, QWidget* parent = nullptr);

private slots:
    void onCreateAccountClicked();
    void onAddCustomerClicked();
    void onExitClicked();
    void onDeleteCustomerClicked();
    void onChangePasswordClicked();
    void onShowAccountsClicked();
    void onManageAdminsClicked();
    void onDeleteAccountClicked();
    void onEditCustomerClicked();
    void onEditSelfClicked();
    void onShowCustomerInfoClicked();
    void updateClock();




private:
    void loadCustomers();
    Customer* getSelectedCustomer();

    Admin* currentAdmin;
    QListWidget* customerList;
    QPushButton* createAccountBtn;
    QLineEdit* searchInput;
    QPushButton* showCustomerInfoBtn;
    QLabel* clockLabel;
    QTimer* timer;

    QPushButton* exitBtn;
};

#endif
