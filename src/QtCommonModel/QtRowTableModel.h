#ifndef QTROWTABLEMODEL_H
#define QTROWTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QSharedPointer>

template<typename T>
class QtRowTableModel : public QAbstractTableModel
{
	typedef T Element;
	typedef QSharedPointer<T> ElementPtr;
public:
	QtRowTableModel(bool readOnly = false, QObject *parent = nullptr)
		:QAbstractTableModel(parent)
		, mReadOnly(readOnly)
	{
	
	}

	virtual ~QtRowTableModel(){}

	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const 
	{ 
		return mRows.size(); 
	}

	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const 
	{ 
		return mHeaders.size(); 
	}

	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
	{
		if (orientation == Qt::Horizontal){
			return mHeaders.at(section);
		}
		else{
			return section;
		}
	}

	void setHeaderLabels(const QStringList& headers){ mHeaders = headers; }

	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
	{
		if (!index.isValid())
			return QVariant();

		int row = index.row();
		int col = index.column();
		if (role == Qt::DisplayRole || role == Qt::EditRole){
			if (row >= 0 && row < mRows.size()){
				ElementPtr element = mRows.at(index.row());
				if (!element.isNull())
					return element->data(col);
			}
		}
		else if (role == Qt::TextAlignmentRole){
			return Qt::AlignCenter;
		}
		
		return QVariant();
	}

	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
	{
		if (mReadOnly || !index.isValid())
			return false;

		int row = index.row();
		int col = index.column();
		if (role == Qt::EditRole){
			if (row >= 0 && row < mRows.size()){
				ElementPtr element = mRows.at(index.row());
				if (!element.isNull()){
					return element->setData(col, value);
				}
			}
		}

		return QAbstractTableModel::setData(index, value, role);
	}

	Qt::ItemFlags flags(const QModelIndex &index) const
	{
		return mReadOnly ? QAbstractTableModel::flags() : (QAbstractTableModel::flags() | Qt::ItemIsEditable);
	}

private:
	QList<ElementPtr> mRows;
	QStringList mHeaders;
	bool mReadOnly = false;
};

#endif // QTROWTABLEMODEL_H
