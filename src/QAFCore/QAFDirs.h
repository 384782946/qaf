#pragma once

#include "QAFGlobal.h"
#include <QString>

namespace QAF
{
	class QAFCORE_EXPORT QAFDirs
	{
	public:
		static QString path(DirType type);

	private:
		QAFDirs();
		~QAFDirs();
		Q_DISABLE_COPY(QAFDirs)
	};
}