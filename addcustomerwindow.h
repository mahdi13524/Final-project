#ifndef ADDCUSTOMERWINDOW_H
#define ADDCUSTOMERWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class AddCustomerWindow : public QWidget {
    Q_OBJECT

public:
    explicit AddCustomerWindow(QWidget* parent = nullptr);

signals:
    void customerAdded();

private slots:
    void onAddClicked();

private:
    QLineEdit* nameEdit;
    QLineEdit* familyEdit;
    QLineEdit* nationalCodeEdit;
    QLineEdit* ageEdit;
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
};

#endif
