#include "Protocol.h"

Request::Request()
	:mRequestId(0)
	, mRequestType(RT_POST)
{

}

Request::~Request()
{

}

void Request::setReqestType(qint8 type)
{
	mRequestType = type;
}

qint8 Request::reqestType() const
{
	return mRequestType;
}

void Request::setRequestId(qint32 id)
{
	mRequestId = id;
}

qint32 Request::reqestId() const
{
	return mRequestId;
}

void Request::setData(const QMap<QString, QString>& data)
{
	mRequestData = data;
}

bool Request::pack(QDataStream& stream)
{
	Package::pack(stream);

	stream << mRequestId << mRequestType << mRequestData;
	return true;
}

bool Request::unpack(QDataStream& stream)
{
	Package::unpack(stream);

	stream >> mRequestId >> mRequestType >> mRequestData;
	return true;
}

const QMap<QString, QString>& Request::data() const
{
	return mRequestData;
}

//////////////////////////////////////////////////////////////////////////

Response::Response()
	:mRequestId(0)
	, mStatus(RS_OK)
{

}

Response::~Response()
{

}

void Response::setStatus(qint8 status)
{
	mStatus = status;
}

qint8 Response::status() const
{
	return mStatus;
}

QByteArray Response::datas() const
{
	return mDatas;
}

void Response::setDatas(const QByteArray& data)
{
	mDatas = data;
}

bool Response::pack(QDataStream& stream)
{
	Package::pack(stream);

	stream << mRequestId << mStatus << mDatas;
	return true;
}

bool Response::unpack(QDataStream& stream)
{
	Package::unpack(stream);

	stream >> mRequestId >> mStatus >> mDatas;
	return true;
}

qint32 Response::reqestId() const
{
	return mRequestId;
}

void Response::setReqestId(qint32 id)
{
	mRequestId = id;
}
