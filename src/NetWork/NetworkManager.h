#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "network_global.h"

#include <QObject>
#include <QUrl>
#include <QMap>
#include <QByteArray>

class QNetworkAccessManager;
class QNetworkReply;
class QFile;

enum HTTPRequestType{
    RT_GET,
    RT_POST,
    RT_UPLOAD,
    RT_DOWNLOAD
};

struct HTTPRequest{
    int unique;
    int type;
    QFile* file;
    QNetworkReply* reply;

    HTTPRequest(){
        unique = -1;
        type = RT_GET,
        file = NULL;
        reply = NULL;
    }
};

class NETWORK_EXPORT NetworkManager : public QObject
{
    Q_OBJECT

public:
    enum NetworkFlag
    {
        NF_SUCCESS = 0,
        NF_FILE_NOT_EXIST,
        NF_FILE_CANNOT_READ,
        NF_REQUEST_ERROR,
    };

    NetworkManager(QObject *parent);
    ~NetworkManager();

    void doGet(int unique,const QUrl& url);

    void doPost(int unique,const QUrl& url,const QMap<QString,QString>& data);

    void doUploadFile(int unique,const QUrl& url,QString filePath); //ͼƬΪjpeg�ļ�-

	void doDownloadFile(int unique,const QUrl& url,QString savePath);

signals:
    void replyArrived(int,const QByteArray&);
    void replyError(int,int);
	void downloadProgress(int unique,qint64 currentValue,qint64 maxValue);

protected slots:
    void replyFinished(QNetworkReply*);

	//for download
	void on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal );
	void on_readyRead();

protected:
	QString saveFileName(const QUrl& url);

    void addRequest(int unique,HTTPRequest request);

    HTTPRequest getRequest(int unique);

	int findRequest(QNetworkReply*);

	void removeRequest(int);

private:
    QNetworkAccessManager* mNetworkAccess;
    QMap<int,HTTPRequest> mRequests;
};

#endif // NETWORKMANAGER_H
