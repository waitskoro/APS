#pragma once

#include <QWidget>

#include "connection/connectionlist.h"
#include "connection/connectioninfo.h"

namespace Connection {
class IConnectionParameters;
}

namespace Ui {
class AuthForm;
}

namespace Connection::View {

class AuthForm : public QWidget
{
    Q_OBJECT

public:
    explicit AuthForm(QWidget *parent = nullptr);

    ~AuthForm();

public slots:
    void on_save_clicked();
    void on_remove_clicked();
    void on_clearInputs_clicked();

private:
    Ui::AuthForm *ui;

    Connection::ConnectionsList *m_connectionList;

    void onSelectedItemChanged(qint32 id);
    void setConnectionInfo(const ConnectionInfo info);

    ConnectionInfo m_selectedInfo;
};

}
