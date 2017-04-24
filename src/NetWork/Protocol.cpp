#include "Protocol.h"

Request::Request()
	:mRequestType(RT_NORMAL)
{
	mHeader.Version = ProtocolVersion;
}

Request::~Request()
{

}

void Request::setReqestType(quint8 type)
{
	mRequestType = type;
}

quint8 Request::reqestType() const
{
	return mRequestType;
}

void Request::setData(const QMap<QString, QString>& data)
{
	mRequestData = data;
}

bool Request::pack(QDataStream& stream)
{
	Package::pack(stream);

	stream << mRequestType << mRequestData;
	return true;
}

bool Request::unpack(QDataStream& stream)
{
	try{
		if (!Package::unpack(stream))
			return false;

		if (mHeader.Version != ProtocolVersion)
			return false;

		stream >> mRequestType >> mRequestData;
	}
	catch (...){
		return false;
	}
	
	return true;
}

const QMap<QString, QString>& Request::data() const
{
	return mRequestData;
}

//////////////////////////////////////////////////////////////////////////

Response::Response()
	:mStatus(RS_OK)
{
	mHeader.Version = ProtocolVersion;
}

Response::~Response()
{

}

void Response::setStatus(quint8 status)
{
	mStatus = status;
}

quint8 Response::status() const
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
	if (!Package::pack(stream))
		return false;

	stream << mStatus << mDatas;
	return true;
}

bool Response::unpack(QDataStream& stream)
{
	try
	{
		if (!Package::unpack(stream))
			return false;

		if (mHeader.Version != ProtocolVersion)
			return false;

		stream >> mStatus >> mDatas;
	}
	catch (...)
	{
		return false;
	}
	return true;
}
