#include "Serializable.h"
#include <QDataStream>

QDataStream&  operator << (QDataStream& stream, const Serializable& srl)
{
	srl.pack(stream);
	return stream;
}

QDataStream&  operator >> (QDataStream& stream, Serializable& srl)
{
	srl.unpack(stream);
	return stream;
}
