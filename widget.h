#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "network_demo.h"
#include "show_wid.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void slotfinish();
private:
    Ui::Widget *ui;

    network_demo *m_pdemo;
    show_wid *m_pshow;
};
#endif // WIDGET_H
