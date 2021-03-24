#ifndef NETWORK_DEMO_H
#define NETWORK_DEMO_H
#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QJsonParseError>
#include <QJsonObject>

#include <iostream>
#include <vector>

using namespace std;


struct netData
{
    int count;
    QString pinyinIndexes;
    int id ;
    QString name;
};

class network_demo :public QObject
{
    Q_OBJECT
public:
    network_demo(QObject *parent = nullptr);
    vector<netData> getv()
    {
        return  m_vNetData;
    }
public slots:
    void getAlldata();
private slots:
    void getdeta(QNetworkReply *reply);
private:
    QNetworkAccessManager *m_pmanager;

    //测试解析json
    void test();
    vector<netData> m_vNetData;
signals:
    void sigfinish();

};

#endif // NETWORK_DEMO_H
