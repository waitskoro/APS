#pragma once

#include <QMovie>
#include <QWidget>
#include <QStyledItemDelegate>

namespace Ui {
class Loader;
}

namespace Common::View {

class Loader : public QWidget
{
    Q_OBJECT

public:
    explicit Loader(QWidget *parent = nullptr);
    ~Loader();

    void viewGif(bool visible);
    void setText(QString &text);
    void setVisibleButtonOk(bool visible);

public slots:
    void on_cancel_clicked();

signals:
    void cancel();

private:
    Ui::Loader *ui;

    QMovie *m_movie;
};

}
