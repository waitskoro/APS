#include "stateofdatachannels.h"
#include "ui_stateofdatachannels.h"

using namespace Requests::View;

StateOfDataChannels::StateOfDataChannels(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StateOfDataChannels)
{
    ui->setupUi(this);
}

void StateOfDataChannels::onMessageRecieved(Connection::DataChannelMessage msg)
{
    qDebug() << msg.activeChannelsCount;
}

void StateOfDataChannels::showWindow()
{
    show();
}

StateOfDataChannels::~StateOfDataChannels()
{
    delete ui;
}
