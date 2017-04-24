#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "qafcore_global.h"

class QDataStream;

class Serializable
{
public:
	Serializable(){}
	virtual ~Serializable(){}

	virtual void pack(QDataStream& stream) const = 0;
	virtual void unpack(QDataStream& stream) = 0;
};

QAFCORE_EXPORT QDataStream& operator<< (QDataStream&, const Serializable&);
QAFCORE_EXPORT QDataStream& operator>> (QDataStream&, Serializable&);

#endif //SERIALIZABLE_H
