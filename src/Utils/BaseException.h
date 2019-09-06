#ifndef QAFEXCEPTION_H
#define QAFEXCEPTION_H

#include <QException>
#include <QDebug>
#include <cstring>
#include <sstream>

//声明异常类型
#define EXCEPTION_SUBCLASS(classname,parentclassname) \
	class classname:public parentclassname{ \
	public:								\
		classname(const char* what, const char* file, int lineNo) : parentclassname(what, file, lineNo){}	\
		virtual classname *clone() const{ return new classname(*this); }	\
		virtual void raise() const { classname exp = *this; qDebug() << exp.what(); throw exp; }	\
		virtual const char* type() const { return #classname; }				\
	};


static int A = 0, B = 0;
#define AB(a,N) std::make_pair(#a,a) << N
#define A(a) AB(a,B)
#define B(a) AB(a,A)
//简单抛出异常
#define  EXCEPTION_SIMPLE_THROW(classname,what) classname(what,__FILE__,__LINE__) << A

class QBaseException : public QException
{
public:
	QBaseException(const char* what, const char* file, int lineNo)
		:mWhat(what), mFile(file), mLineNo(lineNo)
	{
			
	}

	virtual ~QBaseException(){}

	virtual const char* type() const { return "QBaseException"; }

	virtual QBaseException *clone() const{ return new QBaseException(*this); }

	virtual void raise() const { 
		QBaseException exp = *this;  
		qDebug() << exp.what();
		throw exp; 
	}

    virtual const char* what() const noexcept
	{	
		std::ostringstream os;
		os << "Exception:" << type() 
			<< "\tFile:" << mFile 
			<< "\tLine:" << mLineNo
			<< "\tWhat:" << mWhat
			<< "\t" <<mOther;
		mMessage = std::string();
		mMessage += os.str();
		return mMessage.c_str();
	}

	template<typename T>
	QBaseException& operator << (std::pair<const char*, T> p)
	{
		std::ostringstream os;
		os << p.first << ":" << p.second << "\t";
		mOther += os.str();
		return *this;
	}

	//作为宏迭代的终止条件，用户不应当不应当调用该方法
	QBaseException& operator << (int) { raise(); return *this; }

private:
	std::string mFile;
	int mLineNo;
	std::string mWhat;
	std::string mOther;
	mutable std::string mMessage;
};

EXCEPTION_SUBCLASS(QLogicException, QBaseException)

EXCEPTION_SUBCLASS(QRuntimeException, QBaseException)

#endif // QAFEXCEPTION_H
