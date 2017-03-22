#pragma once

#include <QMap>

#include "network_global.h"
#include "Package.h"

const qint16 ProtocolVersion = 1010;

enum RequestType
{
	RT_NORMAL = 1,			 //��������
	RT_WITHOUT_RESPONSE = 100, //�޷�������
};

enum ResponseStatus
{
	RS_OK = 0,			 //����
	RS_CLIENT_ERROR, //�ͻ��˴���
	RS_SERVER_ERROR	 //�������˴���
};

class NETWORK_EXPORT Request:public Package
{
public:
	Request();
	~Request();

	DECLARE_CLASS_NAME(Request)

	virtual bool pack(QDataStream& stream);

	virtual bool unpack(QDataStream& stream);

	void setReqestType(quint8 type);

	quint8 reqestType() const;

	void setData(const QMap<QString, QString>& data);

	const QMap<QString, QString>& data() const;

private:
	quint8 mRequestType;
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

	void setStatus(quint8 status);

	quint8 status() const;

	QByteArray datas() const;

	void setDatas(const QByteArray& data);

private:
	quint8 mStatus;
	QByteArray mDatas;
};