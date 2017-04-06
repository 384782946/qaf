#include "HTTPManager.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
#include <QStringList>
#include <QtNetwork/QHttpMultiPart>
#include <QFile>
#include <QFileInfo>

HTTPManager::HTTPManager(QObject *parent)
    : QObject(parent)
{
    mNetworkAccess = new QNetworkAccessManager(this);

    connect(mNetworkAccess, SIGNAL(finished(QNetworkReply*)),
        this, SLOT(replyFinished(QNetworkReply*)));
}

HTTPManager::~HTTPManager()
{

}

void HTTPManager::replyFinished( QNetworkReply* reply)
{
    int key = findRequest(reply);
    HTTPRequest request = getRequest(key);
    if(reply->error() == QNetworkReply::NoError)
    {
		if(request.type == RT_DOWNLOAD){
			QString fileName = request.file->fileName();
			request.file->close();
			request.file->deleteLater();

			emit replyArrived(key,fileName.toUtf8());
		}else{
			QByteArray bytes = reply->readAll();
			emit replyArrived(key,bytes);
		}
    }else{
        emit replyError(key,reply->error(),reply->errorString());

        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug("found error ...code:%d %d\n",statusCode.toInt(),reply->error());
        qDebug(qPrintable(reply->errorString()));
    }

	removeRequest(key);
    reply->deleteLater();
}

void HTTPManager::on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if(reply){
        int key = findRequest(reply);
        emit downloadProgress(key,bytesReceived,bytesTotal);
    }
}

void HTTPManager::on_readyRead()
{
	QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
	if(reply){
		int key = findRequest(reply);
        HTTPRequest myrequest = getRequest(key);
		if(myrequest.file){
			myrequest.file->write(reply->readAll());
		}
	}
}

QString HTTPManager::saveFileName(const QUrl& url)
{
	QString path = url.path();
    QFileInfo fi = QFileInfo(path);
    QString basename = fi.fileName();

	if(basename.isEmpty()){
		basename = "temp_download";
	}

	if(QFile::exists((basename))){
		//alread exists,don't overwrite
		int i = 0;
		basename += '.';
		while(QFile::exists(basename+QString::number(i))){
			++i;
		}

		basename += QString::number(i);
	}

	return basename;
}

void HTTPManager::addRequest(int unique,HTTPRequest request)
{
	mRequests.insert(unique,request);
}

HTTPRequest HTTPManager::getRequest(int unique)
{
	return mRequests.value(unique);
}

int HTTPManager::findRequest(QNetworkReply* reply)
{
    foreach(int unique,mRequests.keys()){
        HTTPRequest request = mRequests.value(unique);
		if(request.reply == reply){
			return unique;
		}
	}

	return -1;
}

void HTTPManager::removeRequest(int unique)
{
	if(mRequests.contains(unique)){
        HTTPRequest request = mRequests.value(unique);
		mRequests.remove(unique);
	}
}

void HTTPManager::doPost(int unique, const QUrl& url,const QMap<QString,QString>& data )
{
    QNetworkRequest request;

    request.setUrl(url);
    //header
     request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
//     request.setRawHeader("Accept","text/html,application/xhtml+xml,*/*");
//     request.setRawHeader("Referer","http://localhost:8888/login");
//     request.setRawHeader("Accept-Language","zh-CN");
//     request.setRawHeader("X-Requested-With","XMLHttpRequest");
//     request.setRawHeader("User-Agent","Mozilla/5.0 (compatible;MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)");
//     request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
//     request.setRawHeader("Accept-Encoding","gzip,deflate");
//     request.setRawHeader("Host","localhost:8888");
//     request.setRawHeader("Content-Length","18");
//     request.setRawHeader("Connection","keep-Alive");
//     request.setRawHeader("Cache-Control","no-cache");

    QByteArray postData;
    QStringList keys = data.keys();
    foreach(QString key,keys)
    {
        postData.append(QString("%1=%2&").arg(key).arg(data.value(key)));
    }
   
    QNetworkReply* reply = mNetworkAccess->post(request,postData);

    HTTPRequest myrequest;
	myrequest.unique = unique;
	myrequest.type = RT_POST;
	myrequest.reply = reply;
    addRequest(unique,myrequest);
}

void HTTPManager::doGet(int unique, const QUrl& url )
{
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply* reply = mNetworkAccess->get(request);
    
    HTTPRequest myrequest;
	myrequest.unique = unique;
	myrequest.type = RT_GET;
	myrequest.reply = reply;
	addRequest(unique,myrequest);
}

void HTTPManager::doUploadFile( int unique,const QUrl& url,QString filePath )
{
    QFile *file = new QFile(filePath);
    if(!file->open(QIODevice::ReadOnly))
    {
        emit replyError(unique,NF_FILE_CANNOT_READ,"upload:file can not be opened.");
        return;
    }
//    QFileInfo fileInfo(filePath);
//    if(!fileInfo.exists() || !fileInfo.isFile())
//    {
//        emit replyError(unique,NF_FILE_NOT_EXIST,"upload:file can not be opened.");
//        return;
//    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //QHttpPart textPart;
    //textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
    //textPart.setBody(fileInfo.fileName().toLatin1());

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image\"; filename=\""+filePath+"\"")); //注意这里的filename必须正确设定，否则会出现没有上传文件的错误

    imagePart.setBodyDevice(file);
    file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

   // multiPart->append(textPart);
    multiPart->append(imagePart);

    QNetworkRequest request(url);
    //request.setRawHeader("User-Agent","Mozilla/5.0 (compatible;MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)");
    //request.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data");

    QNetworkReply *reply = mNetworkAccess->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
    
    HTTPRequest myrequest;
	myrequest.unique = unique;
	myrequest.type = RT_UPLOAD;
	myrequest.reply = reply;
	addRequest(unique,myrequest);
}

void HTTPManager::doDownloadFile(int unique,const QUrl& url,QString savePath)
{
	QString fileName = saveFileName(url);
	QFile* file = new QFile(fileName);
	if (!file->open(QIODevice::WriteOnly)) {
		file->deleteLater();
        emit replyError(unique,NF_FILE_CANNOT_READ,"download:file can not be opened.");
		qDebug()<<"error open file:"<<fileName;
		return;
	}

	QNetworkRequest request;
	request.setUrl(url);
	QNetworkReply* reply = mNetworkAccess->get(request);
	connect(reply,SIGNAL(downloadProgress(qint64, qint64)),this,SLOT(on_downloadProgress(qint64, qint64)));
	connect(reply,SIGNAL(readyRead()),this,SLOT(on_readyRead()));
	
    HTTPRequest myrequest;
	myrequest.unique = unique;
	myrequest.type = RT_DOWNLOAD;
	myrequest.reply = reply;
	myrequest.file = file;
	addRequest(unique,myrequest);
}
