#include "database.h"
#include <QFile>
//静态变量初始化
QString DataBase::m_sDataBaseName = "translation.db";
QSqlDatabase DataBase::m_sDataBase = DataBase::openDataBase();

DataBase::DataBase()
{
    m_sDataBase = DataBase::openDataBase();
}

DataBase::DataBase(const QString& dbName, const QString& parameters, const QString& tbName):
    m_tableName(tbName),m_table_parameters(parameters)
{

}

DataBase::~DataBase()
{
}


/*************************************************************************
【函数名称】        search
【函数功能】        查找抽象类
【参数】            查找参数、值
【返回值】
【开发者及日期】     7/21
*************************************************************************/
bool DataBase::search(const QString& key, const QString& parameter)
{
    QSqlQuery query(m_sDataBase);
    QString select_sql = QString("select * from %1 where %2 = '%3'").arg(m_tableName).arg(parameter).arg(key);
    if (!query.exec(select_sql))
    {
        qDebug()<<"search error ''"<<query.lastError();
        return false;
    }
    while (query.next())
    {
        return true;
    }
    return false;
}

/*************************************************************************
【函数名称】        delete
【函数功能】        删除抽象类
【参数】            删除参数、值
【返回值】
【开发者及日期】     7/23
*************************************************************************/
bool DataBase::deleteData(const QString& parameter, const QString& value)
{
    QSqlQuery query(m_sDataBase);
    QString delete_sql = QString("delete from %1 where %2 = '%3'").arg(m_tableName).arg(parameter).arg(value);
    if (!query.exec(delete_sql))
    {
        qDebug()<<"delete error!"<<query.lastError();
        return false;
    }
    return true;
}
/*************************************************************************
【函数名称】        updateDATA
【函数功能】        更新抽象类，子类重写，虚函数无实际功能
【参数】
【返回值】
【开发者及日期】     7/22
*************************************************************************/
bool DataBase::updateData(const QString& expression, const QString& parameter, const QString& value)        //子类重写
{
    QSqlQuery query(m_sDataBase);
    QString update_sql = QString("update %1 set %2 = :%2 where %3")
            .arg(m_tableName).arg(parameter).arg(expression);
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), value);
    if (!query.exec())
    {
        qDebug()<<"update error!"<<query.lastError();
        return false;
    }
    return true;
}

bool DataBase::updateInt(const QString &, const int &, const QString &)
{
    return true;
}

bool DataBase::updateFloat(const QString &, const float &, const QString &)
{
    return true;
}


/*************************************************************************
【函数名称】        openDataBase
【函数功能】        打开数据库
【参数】
【返回值】
【开发者及日期】     7/21
*************************************************************************/
QSqlDatabase DataBase::openDataBase()
{
    QSqlDatabase database;
    if (QSqlDatabase::contains("connection"))
    {
        database = QSqlDatabase::database("connection");
        //qDebug()<<"database open!"<<database.lastError();
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE", "connection");
        database.setDatabaseName(m_sDataBaseName);
        //qDebug()<<"database open!"<<database.lastError();
    }
    if (!database.open())
    {
        qDebug()<<"database not open!"<<database.lastError();
    }
    return database;
}



DataBasePicture::DataBasePicture()
{
    m_sDataBase = openDataBase();
    m_tableName = "userPicture";
    m_table_parameters = "(id varchar(15) primary key,"
                         "pixels blob)";
    //m_dataBaseName = "test.db";
}

DataBasePicture::~DataBasePicture()
{
}


/*************************************************************************
【函数名称】        insertPictures
【函数功能】        插入图片
【参数】           图片，图片所属id
【返回值】
【开发者及日期】     7/21
*************************************************************************/
bool DataBasePicture::insertPictures(const QString& id, const QPixmap& pix)
{
    QSqlQuery query(m_sDataBase);
    QString sql_create = QString("create table if not exists %1 %2").arg(m_tableName).arg(m_table_parameters);
    if (!query.exec(sql_create))
    {
        qDebug()<<"pictureCreate error"<<query.lastError();
        return false;
    }

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer, "PNG");

    QString insert = QString("insert into %1 values('%2',?)").arg(m_tableName).arg(id);
    query.prepare(insert);
    query.addBindValue(byteArray);
    if (!query.exec())
    {
        qDebug()<<"insert pixture fail!"<<query.lastError();
        return false;
    }
    return true;
}

/*************************************************************************
【函数名称】        updatePictures
【函数功能】        更新图片
【参数】            图片，图片所属id
【返回值】
【开发者及日期】     7/21
*************************************************************************/
bool DataBasePicture::updataPixture(const QString& id, const QPixmap& pix)
{
    QSqlQuery query(m_sDataBase);
    QString update_sql = QString("update %1 set %2 = :%2 where id = '%3'")
            .arg(m_tableName).arg("pixels").arg(id);
    query.prepare(update_sql);

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer, "PNG");

    query.bindValue(QString(":%2").arg("pixels"), byteArray);
    if (!query.exec())
    {
        qDebug()<<"updatePicture error!"<<query.lastError();
        return false;
    }
    return true;
}

/*************************************************************************
【函数名称】        getPictures
【函数功能】        获得图片
【参数】            图片引用，图片所属id
【返回值】
【开发者及日期】     7/23
*************************************************************************/
bool DataBasePicture::getPictures(const QString& id, QPixmap& picture)
{
    QSqlQuery query(m_sDataBase);
    QString sql_create = QString("create table if not exists %1 %2").arg(m_tableName).arg(m_table_parameters);
    if (!query.exec(sql_create))
    {
        qDebug()<<"pixtureCreate error"<<query.lastError();
        return false;
    }

    QString select_sql = QString("select pixels from %1 "
                                 "where id = '%2'").arg(m_tableName).arg(id);
    QByteArray byteArray;
    if (!query.exec(select_sql))
    {
        qDebug()<<"select pixture fail!"<<query.lastError();
        return false;
    }
    else
    {
        while (query.next())
        {
            byteArray = query.value(0).toByteArray();
            QPixmap pix;
            pix.loadFromData(byteArray,"PNG");
            picture = pix;
            return true;
        }
    }
    return true;
}



DataBaseCertification::DataBaseCertification()
{
    m_table_parameters = "(id varchar(15) primary key,"
                         "IDNum varchar(20),"
                         "realName varchar(20),"
                         "qText varchar(255),"
                         "isChecked int,"
                         "pixels blob)";
    m_tableName = "certification";
}

DataBaseCertification::~DataBaseCertification()
{

}

bool DataBaseCertification::insertCertification(const certification& cei)
{
    QSqlQuery query(m_sDataBase);

    QString sql_create = QString("create table if not exists %1 %2").arg(m_tableName).arg(m_table_parameters);
    if (!query.exec(sql_create))
    {
        qDebug()<<"certiCreate error"<<query.lastError();
        return false;
    }

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    cei.getPix().save(&buffer, "PNG");

    QString insert = QString("insert into %1 values('%2','%3', '%4', '%5', %6, ?)")
            .arg(m_tableName).arg(cei.getUserID()).arg(cei.getIDNum()).arg(cei.getName())
            .arg(cei.getQualText()).arg(cei.getIsChecked());
    query.prepare(insert);
    query.addBindValue(byteArray);
    if (!query.exec())
    {
        qDebug()<<"insert ceitification fail!"<<query.lastError();
        return false;
    }
    return true;
}

bool DataBaseCertification::updateCertification(const certification& cei)       //实名认证，身份证与姓名无法更新
{
    QSqlQuery query(m_sDataBase);
    QString update_sql = QString("update %1 set %2 = :%2 where id = '%3'")
            .arg(m_tableName).arg("pixels").arg(cei.getUserID());
    query.prepare(update_sql);

    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    cei.getPix().save(&buffer, "PNG");

    query.bindValue(QString(":%2").arg("pixels"), byteArray);
    if (!query.exec())
    {
        qDebug()<<"updatePicture error!"<<query.lastError();
        return false;
    }

    update_sql = QString("update %1 set %2 = :%2 where id = '%3'")
            .arg(m_tableName).arg("qText").arg(cei.getUserID());
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg("qText"), cei.getQualText());
    if (!query.exec())
    {
        qDebug()<<"updateQualified error!"<<query.lastError();
        return false;
    }

    update_sql = QString("update %1 set %2 = :%2 where id = '%3'")
            .arg(m_tableName).arg("isChecked").arg(cei.getUserID());
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg("isChecked"), cei.getIsChecked());
    if (!query.exec())
    {
        qDebug()<<"updateQualified check error!"<<query.lastError();
        return false;
    }
    return true;
}

certification DataBaseCertification::getCertification(const QString& id)
{
    QSqlQuery query(m_sDataBase);

    QString sql_select = QString("select IDNum, realName, qText, "
                                 "isChecked, pixels from %1 where id = '%2'").arg(m_tableName).arg(id);
    if (!query.exec(sql_select))
    {
        qDebug()<<"certi get error"<<query.lastError();
        return certification();
    }
    while (query.next())
    {
        QString idNum = query.value(0).toString();
        QString name = query.value(1).toString();
        QString text = query.value(2).toString();
        int check = query.value(3).toInt();
        QByteArray byteArray = query.value(4).toByteArray();
        QPixmap pix;
        pix.loadFromData(byteArray,"PNG");
        return certification(id, idNum, name, text, pix, check);
    }
    return certification();
}
