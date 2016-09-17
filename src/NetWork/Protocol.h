#pragma once

#include <QMap>

#include "network_global.h"
#include "Package.h"

enum RequestType
{
	RT_HEAD,
	RT_POST
};

enum ResponseStatus
{
	RS_OK,
	RS_SERVER_ERROR
};

class NETWORK_EXPORT Request:public Package
{
public:
	Request();
	~Request();

	DECLARE_CLASS_NAME(Request)

	virtual bool pack(QDataStream& stream);

	virtual bool unpack(QDataStream& stream);

	void setReqestType(qint8 type);

	qint8 reqestType() const;

	void setRequestId(qint32 id);

	qint32 reqestId() const;

	void setData(const QMap<QString, QString>& data);

	const QMap<QString, QString>& data() const;

private:
	qint32 mRequestId;
	qint8 mRequestType;
	QMap<QString, QString> mRequestData;
};

class NETWORK_EXPORT Response :public Package
{
public:
	Response();
	~Response();

	DECLARE_CLASS_NAME(Response)

	virtual bool pack(QDataStream& stream);

	virtual bool unpack(QDataStream& stream);

	void setStatus(qint8 status);

	qint8 status() const;

	QByteArray datas() const;

	void setDatas(const QByteArray& data);

	qint32 reqestId() const;

	void setReqestId(qint32 id);

private:
	qint32 mRequestId;
	qint8 mStatus;
	QByteArray mDatas;
};