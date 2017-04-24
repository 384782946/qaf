#ifndef UTILS_H
#define UTILS_H

template<typename T1, typename T2>
class CanConvert
{
	typedef char Type1[1];
	typedef char Type2[2];

	static Type1& test(T2&);
	static Type2& test(...);
	static T1& make();

public:
	enum { ret = (sizeof(test(make())) == sizeof(Type1)) };
};

template<typename T1, typename T2>
class IsSameType
{
public:
	enum { ret = false };
};

template<typename T>
class IsSameType<T, T>
{
public:
	enum { ret = true };
};

#define ASSERT_SAME_TYPE(classname1,classname2) static_assert(IsSameType<classname1,classname2>::ret, #classname1##" is not the same type with "###classname2)
#define ASSERT_CONVERTIBLE_TYPE(classname1,classname2) static_assert(CanConvert<classname1,classname2>::ret,#classname1##" can not convert to "###classname2)

#ifdef QT_DEBUG
#define QT_CONNECT(conenction_name) qDebug() << "Connect:" << connection_name << "Sate:" << QObject::connect
#else
#define QT_CONNECT(connection_name) QObject::connect
#endif

#endif //UTILS_H