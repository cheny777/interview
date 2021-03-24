#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pdemo = new network_demo(this);
    m_pshow = new show_wid(this);
    m_pshow->move(0,100);

    connect(m_pdemo,SIGNAL(sigfinish()),this,SLOT(slotfinish()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    m_pdemo->getAlldata();


}

void Widget::slotfinish()
{
    m_pshow->setdata(m_pdemo->getv());
    m_pshow->UpddataUI();
}
