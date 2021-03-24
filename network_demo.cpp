#include "network_demo.h"
#include <QJsonArray>
#include <QFile>
network_demo::network_demo(QObject *parent)
    :QObject(parent)
{
    m_pmanager = new QNetworkAccessManager(this);
    //manager具有异步API，当http请求完成后，会通过finished信号进行通知

    connect(m_pmanager,SIGNAL(finished(QNetworkReply *)),this,SLOT(getdeta(QNetworkReply *)));

    //测试
    //test();
}

void network_demo::getAlldata()
{
    QNetworkRequest request;
    QUrl url("http://localhost:8080/list");
    request.setUrl(url);
    request.setRawHeader("Content-Type","application/json");
    //发送异步get请求
    m_pmanager->get(request);
}

void network_demo::getdeta(QNetworkReply *reply)
{
    m_vNetData.clear();
    if(reply->error()!=QNetworkReply::NoError){
        //处理中的错误信息
        qDebug()<<"reply error:"<<reply->errorString();
    }else{
        //请求方式
        qDebug()<<"operation:"<<reply->operation();
        //状态码
        qDebug()<<"status code:"<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug()<<"url:"<<reply->url();
        //qDebug()<<"raw header:"<<reply->rawHeaderList();

        //获取响应信息
        const QByteArray reply_data=reply->readAll();
        qDebug()<<"read all:"<<reply_data;

        //解析json
        QJsonParseError json_error;
        QJsonDocument document = QJsonDocument::fromJson(reply_data, &json_error);

        if(!(json_error.error == QJsonParseError::NoError))
        {
            qDebug()<<tr("解析json文件错误！");
            return;
        }
        QJsonObject jsonObject = document.object();
        QJsonArray array = document.array();
        for(int i=0;i<array.size();i++)
        {
            netData da;
            QJsonValue iconArray = array.at(i);
            QJsonObject data = iconArray.toObject();
            QJsonValue count = data["count"];
            int num = count.toInt();
            QJsonValue iconTxt = data["pinyinIndexes"];
            QString ss  = iconTxt[0].toString();
            qDebug()<<count<<" "<<iconTxt<<" ";
            QJsonValue tag = data["tag"];
            int id =  tag["id"].toInt();
            QString name = tag["name"].toString();

            da.id = id;
            da.name = name;
            da.count = num;
            da.pinyinIndexes = ss;

            m_vNetData.push_back(da);
        }
    }
    reply->deleteLater();
    emit sigfinish();

}

void network_demo::test()
{
    /*解析json文件*/
    QFile file("../test.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError))
    {
        qDebug()<<tr("解析json文件错误！");
        return;
    }
    QJsonObject jsonObject = document.object();
    QJsonArray array = document.array();
    for(int i=0;i<array.size();i++)
    {
        netData da;
        QJsonValue iconArray = array.at(i);
        QJsonObject data = iconArray.toObject();
        QJsonValue count = data["count"];
        int num = count.toInt();
        QJsonValue iconTxt = data["pinyinIndexes"];
        QString ss  = iconTxt[0].toString();
        qDebug()<<count<<" "<<iconTxt<<" ";
        QJsonValue tag = data["tag"];
        int id =  tag["id"].toInt();
        QString name = tag["name"].toString();

        da.id = id;
        da.name = name;
        da.count = num;
        da.pinyinIndexes = ss;

        m_vNetData.push_back(da);
    }
}
