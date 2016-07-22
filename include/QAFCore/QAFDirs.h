#pragma once

#include "qafcore_global.h"
#include "QAFGlobal.h"

namespace QAF
{
	class QAFCORE_EXPORT QAFDirs
	{
	public:
		static QString path(DirType type);

	private:
		QAFDirs(){}
		~QAFDirs(){}
		Q_DISABLE_COPY(QAFDirs)
	};
}