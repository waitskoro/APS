#include "loader.h"
#include "ui_loader.h"

#include <QMovie>
#include <QLabel>

using namespace Common::View;

Loader::Loader(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Loader)
    , m_movie(new QMovie("/home/waitskoro/APS/view/source/loader.gif"))
{
    ui->setupUi(this);

    QString style = "background-color: #77AAE5";
    this->setStyleSheet(style);

    ui->label->setMovie (m_movie);
    m_movie->setScaledSize(QSize(50, 50));
}

void Loader::setText(QString &text)
{
    ui->text->setText(text);
}

void Loader::setVisibleButtonOk(bool visible)
{
    ui->cancel->setVisible(visible);
}

void Loader::on_cancel_clicked()
{
    emit cancel();
}

void Loader::viewGif(bool visible)
{
    if (visible) {
        m_movie->start();
        setVisible(true);
    } else {
        m_movie->stop();
        setVisible(false);
    }
}

Loader::~Loader()
{
    delete ui;
}
