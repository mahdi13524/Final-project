#ifndef ADMINMANAGERWINDOW_H
#define ADMINMANAGERWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "bank_system.h"

class AdminManagerWindow : public QWidget {
    Q_OBJECT

public:
    explicit AdminManagerWindow(QWidget* parent = nullptr);

private slots:
    void onAddAdminClicked();
    void onDeleteAdminClicked();
    void refreshAdminList();

private:
    QListWidget* adminList;
};

#endif
