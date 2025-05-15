#pragma once

#include <QWidget>

#include "common/messagesinfo.h"

namespace Ui {
class StateOfDataChannels;
}

namespace Requests::View {

class StateOfDataChannels : public QWidget
{
    Q_OBJECT

public:
    explicit StateOfDataChannels(QWidget *parent = nullptr);
    ~StateOfDataChannels();

    void onMessageRecieved(Connection::DataChannelMessage);

public slots:
    void showWindow();

private:
    Ui::StateOfDataChannels *ui;
};

}
