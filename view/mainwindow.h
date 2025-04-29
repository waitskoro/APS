#pragma once

#include <QMainWindow>
#include <QMessageBox>

#include "authform.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace Connection::Socket {
class ITcpSocket;
}

namespace Connection::View {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    AuthForm *m_authForm;
    QMessageBox *m_msgBox;
};

}
