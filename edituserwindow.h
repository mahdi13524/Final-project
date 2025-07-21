#ifndef EDITUSERWINDOW_H
#define EDITUSERWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include "bank_system.h"

class EditUserWindow : public QWidget {
    Q_OBJECT

public:
    EditUserWindow(User* user, QWidget* parent = nullptr);

private slots:
    void onSaveClicked();

private:
    User* currentUser;
    QLineEdit *firstNameEdit;
    QLineEdit *lastNameEdit;
    QLineEdit *nationalCodeEdit;
    QLineEdit *ageEdit;
    QLineEdit *passwordEdit;

};

#endif
