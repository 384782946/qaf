#ifndef QAFEXCEPTION_H
#define QAFEXCEPTION_H

#include <QException>
#include <cstring>
#include <sstream>
#include "qafcore_global.h"

//声明异常类型
#define QAF_EXCEPTION_SUBCLASS(classname,parentclassname) \
	class classname:public parentclassname{ \
	public:								\
		classname(const char* what, const char* file, int lineNo) : parentclassname(what, file, lineNo){}	\
		virtual classname *clone() const{ return new classname(*this); }	\
		virtual void raise() const { classname exp = *this;  throw exp; }	\
		virtual const char* type() const { return #classname; }				\
	};


static int A = 0, B = 0;
#define AB(a,N) std::make_pair(#a,a) << N
#define A(a) AB(a,B)
#define B(a) AB(a,A)
//简单抛出异常
#define  QAF_EXCEPTION_SIMPLE_THROW(classname,what) classname(what,__FILE__,__LINE__) << A

namespace QAF
{
	class QAFCORE_EXPORT QAFException : public QException
	{
	public:
		QAFException(const char* what, const char* file, int lineNo)
			:mWhat(what), mFile(file), mLineNo(lineNo)
		{
			
		}

		virtual ~QAFException(){}

		virtual const char* type() const { return "QAFException"; }

		virtual QAFException *clone() const{ return new QAFException(*this); }

		virtual void raise() const { QAFException exp = *this;  throw exp; }

		virtual const char* what() const
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
		QAFException& operator << (std::pair<const char*, T> p)
		{
			std::ostringstream os;
			os << p.first << ":" << p.second << "\t";
			mOther += os.str();
			return *this;
		}

		//作为宏迭代的终止条件，用户不应当不应当调用该方法
		QAFException& operator << (int) { raise(); return *this; }

	private:
		std::string mFile;
		int mLineNo;
		std::string mWhat;
		std::string mOther;
		mutable std::string mMessage;
	};

	QAF_EXCEPTION_SUBCLASS(QLogicException, QAFException)
}

#endif // QAFEXCEPTION_H
