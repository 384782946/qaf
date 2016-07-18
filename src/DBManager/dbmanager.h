#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "dbmanager_global.h"
#include <QObject>
#include <QMap>
#include <QStringList>
#include <QList>
#include <QVariant>

class QSqlDatabase;

class DBMANAGER_EXPORT DBManager : public QObject
{
public:
	DBManager(const QString& dbType,QObject *parent = 0);
    ~DBManager();

    inline bool isOpened() const;

	bool open(const QString& dbName,const QString& user, const QString& psw, const QString& address,int port);

    bool execSql(const QString& sql);

    bool update(const QString& table,const QMap<QString,QVariant>& values,const QString& _where = "");

    bool remove(const QString& table,const QString& _where = "");

    bool add(const QString& table,const QMap<QString,QVariant>& values);

    QList<QList<QVariant>> query(const QString& table,/*[Output]*/QStringList& columns=QStringList(),const QString& _where = "");

    void close();

private:
    QSqlDatabase* mDB;
};

#endif // DBMANAGER_H
