#include "show_wid.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>

show_wid::show_wid(QWidget *parent)
    :QWidget(parent)
{
    /*样式表有效*/
    this->setAttribute(Qt::WA_StyleSheet, true);
    this->setAttribute(Qt::WA_SetStyle, true);
    this->setAttribute(Qt::WA_StyledBackground, true);

    this->setStyleSheet("QWidget{border:1px solid #999999;}");

    for (int i =0;i<16;i++)
    {
        vector<netData> d;
        m_vnode['A'+i] = d;
    }

    this->resize(300,500);
}


void show_wid::setdata(vector<netData> data)
{
    for (auto a:data)
    {
        addwid(a.pinyinIndexes,a);
    }

    bool b = true;
    for (auto a:m_vnode)
    {
        if(a.second.size()<=0)
        {
            continue;
        }
        wid_node *w = new wid_node();
        w->setsheet(b);
        b = !b;
        w->adddata(a.second);
        m_pwid.push_back(w);
    }
}

void show_wid::UpddataUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    for (auto a:m_pwid)
    {
        layout->addWidget(a);
        a->upD();
    }
    layout->setSpacing(0);
    layout->setMargin(0);
}

void show_wid::addwid(QString s, netData d)
{

   m_vnode[s.toLatin1().data()[0]].push_back(d);

}

wid_node::wid_node(QWidget *parent)
    :QWidget(parent)
{
    /*样式表有效*/
    this->setAttribute(Qt::WA_StyleSheet, true);
    this->setAttribute(Qt::WA_SetStyle, true);
    this->setAttribute(Qt::WA_StyledBackground, true);
    m_ptitle = new QLabel(this);
}

void wid_node::setsheet(bool b)
{
    QString qss;
    if(b)
    {
        qss = "QWidget{background-clolr:rgb(246,245,243);border:1px solid #999999;}";
    }
    else
    {
        qss = "QWidget{background-clolr:rgb(240,237,232);border:1px solid #999999;}";
    }

    this->setStyleSheet(qss);
}

void wid_node::upD()
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_ptitle);
    QGridLayout *gri = new QGridLayout();
    for (size_t i =0;i<m_vdata.size();i++)
    {
        littlenode *l = new littlenode(this);
        l->setdata(m_vdata[i].name,m_vdata[i].count);
        gri->addWidget(l,0,i,1,1);
    }
    layout->addLayout(gri);
    gri->setSpacing(0);
    gri->setMargin(0);
    layout->setSpacing(0);
    layout->setMargin(0);

}

littlenode::littlenode(QWidget *parent)
    :QWidget(parent)
{
    /*样式表有效*/
    this->setAttribute(Qt::WA_StyleSheet, true);
    this->setAttribute(Qt::WA_SetStyle, true);
    this->setAttribute(Qt::WA_StyledBackground, true);

    this->setStyleSheet("QWidget{opacity: 0; border:1px solid #999999;}"
                        "QLabel{font-family:simhei;}"
                        "QPushButton{border:1px solid #999999;border-radius:5px;}");

    QHBoxLayout *layout = new QHBoxLayout(this);
    m_plab = new QLabel(this);
    m_p = new QPushButton(this);
    layout->addWidget(m_plab);
    layout->addWidget(m_p);
    layout->setSpacing(0);
    layout->setMargin(0);
}

void littlenode::setdata(QString str, int n)
{
    m_plab->setText(str);
    m_p->setText(QString::number(n));
}

