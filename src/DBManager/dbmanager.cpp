#include "DBManager.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

DBManager::DBManager(const QString& dbType,QObject *parent)
    : QObject(parent)
	, mDB(nullptr)
{
	mDB = new QSqlDatabase(QSqlDatabase::addDatabase("QOCI"));
	Q_ASSERT_X(mDB != nullptr,"DBManager", "create sqldatabase fail!");
}

DBManager::~DBManager()
{
   close();
   QSqlDatabase::removeDatabase(mDB->connectionName());
   delete mDB;
}

bool DBManager::isOpened() const
{
    return mDB->isOpen();
}

bool DBManager::open(const QString& dbName,const QString& user, const QString& psw, const QString& address,int port)
{
    if(!mDB->isOpen()){
		mDB->setHostName(address);
		mDB->setDatabaseName(dbName);
		mDB->setUserName(user);
		mDB->setPassword(psw);
		mDB->setPort(port);
		return mDB->open();
    }else{
        return true;
    }
}

void DBManager::close()
{
	if (mDB->isOpen())
    {
		mDB->close();
    }
}

bool DBManager::execSql( const QString& sql )
{
	if (!isOpened()) 
		return false;
    QSqlQuery query;
    return query.exec(sql);
}

bool DBManager::update( const QString& table,const QMap<QString,QVariant>& values ,const QString& _where)
{
	if (!isOpened()) 
		return false;

    QSqlQuery query;
    QString datas;
    QList<QString> keyList = values.keys();
    foreach(QString key,keyList){
        if(!datas.isEmpty())
            datas += ",";
        datas += QString("%1=?").arg(key);
    }

    QString sql;
    if(_where.isEmpty())
        sql = QString("UPDATE %1 SET %2").arg(table).arg(datas);
    else
        sql = QString("UPDATE %1 SET %2 WHERE %3").arg(table).arg(datas).arg(_where);
    query.prepare(sql);
    for(int i=0;i<keyList.count();++i)
    {
        query.bindValue(i,values.value(keyList.at(i)));
    }
    return query.exec();
}

bool DBManager::remove( const QString& table,const QString& _where )
{
	if (!isOpened()) 
		return false;

    QSqlQuery query;
    QString sql = QString("DELETE FROM %1 WHERE %2").arg(table).arg(_where);
    return query.exec(sql);
}

bool DBManager::add( const QString& table,const QMap<QString,QVariant>& values )
{
	if (!isOpened()) 
		return false;

    QSqlQuery query;
    QString columns,datas;
    QList<QString> keyList = values.keys();
    foreach(QString key,keyList){
        if(!columns.isEmpty())
            columns += ",";
        columns += key;

        if(!datas.isEmpty())
            datas += ",";
        datas+="?";
    }

    QString sql = QString("INSERT INTO %1 (%2) VALUES (%3)").arg(table).arg(columns).arg(datas);
    query.prepare(sql);

    for(int i=0;i<keyList.count();++i)
    {
        query.bindValue(i,values.value(keyList.at(i)));
    }
    return query.exec();
}

QList<QList<QVariant>> DBManager::query( const QString& table,QStringList& columns/*=QStringList()*/,const QString& _where )
{
    QList<QList<QVariant>> rets;
	if (!isOpened()) 
		return rets;

    QSqlQuery query;
    QString _columns;
    if(columns.count()>0)
        _columns = columns.join(",");
    else
        _columns = "*";

    QString sql;
    if(_where.isEmpty())
        sql = QString("SELECT %1 FROM %2").arg(_columns).arg(table);
    else
        sql = QString("SELECT %1 FROM %2 WHERE %3").arg(_columns).arg(table).arg(_where);
    if(query.exec(sql))
    {
        int colNum = query.record().count();
        
        for(int i=0;i<colNum;++i)
        {
            columns<<query.record().fieldName(i);
        }

        while(query.next())
        {
            QList<QVariant> row;
            for(int i=0;i<colNum;++i)
            {
                row.append(query.value(i));
            }

            rets.append(row);
        }
    }
    return rets;
}
