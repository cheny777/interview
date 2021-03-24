#ifndef SHOW_WID_H
#define SHOW_WID_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <unordered_map>
#include <map>
using namespace std;
#include "network_demo.h"

class littlenode :public QWidget
{
    Q_OBJECT
public:
    littlenode(QWidget *parent = nullptr);
    void setdata(QString str,int n);
    QLabel *m_plab;
    QPushButton *m_p;
};



class wid_node :public QWidget
{
    Q_OBJECT
public:
    wid_node(QWidget *parent = nullptr);
    //背景设置
    void setsheet(bool b);
    void adddata( vector<netData>d )
    {
        m_vdata = d;
        if(d.size()>0)
        {
            m_ptitle->setText(m_vdata[0].pinyinIndexes);
        }
    }
    void upD();
private:
    vector<netData> m_vdata;

    QLabel *m_ptitle;

};

//显示类
class show_wid :public QWidget
{
    Q_OBJECT
public:
    show_wid(QWidget *parent = nullptr);
    //设置数据
    void setdata(vector<netData> data);

    void UpddataUI();

private:
    map<int, vector<netData>>m_vnode;
    vector<wid_node *> m_pwid;
    void addwid(QString s,netData d);




};

#endif // SHOW_WID_H
