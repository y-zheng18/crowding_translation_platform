#ifndef DATABASE_H
#define DATABASE_H


/*************************************************************************
【文件名】                 DataBase.h
【功能模块和目的】          实现数据库操作封装，在对象层面上搭建数据库平台
【开发者及日期】           2019/7/21-7/30
*************************************************************************/
#include <QString>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QTextStream>
#include <QPixmap>
#include <QBuffer>
#include <QByteArray>
#include <QVector>

#include "user.h"
#include "assignment.h"
#include "textinteraction.h"
#include "signupinteraction.h"
#include "messageinformbox.h"
#include "certification.h"
//封装数据库常用操作，并派生出不同类以适应不同用户对象需求


/*************************************************************************
【类名】             DataBase
【功能】             数据库抽象类，虚函数便于实现多态
【接口说明】         增删、更新、查询，在子类重写
【开发者及日期】      2019/7/21-7/24
【更改记录】
*************************************************************************/
class DataBase
{
public:
    DataBase();
    DataBase(const QString& dbName, const QString& parameters = "",const QString& tbName = "");

    virtual ~DataBase();

    inline void setTableName(const QString& tbName)
    {
        m_tableName = tbName;
    }

    inline void setParameters(const QString& parameters)
    {
        m_table_parameters = parameters;
    }

    bool            deleteData(const QString& parameter, const QString& value);

    virtual bool    search(const QString&, const QString& parameter = "id");
    virtual bool    updateData(const QString&, const QString&, const QString&);
    virtual bool    updateInt(const QString&, const int&, const QString&);
    virtual bool    updateFloat(const QString&, const float&, const QString&);
protected:
    static QSqlDatabase  m_sDataBase;
    static QString       m_sDataBaseName;
    QString              m_tableName;                   //表格名
    QString              m_table_parameters;            //表格参数
    static QSqlDatabase  openDataBase();

};

/*************************************************************************
【类名】             DataBaseAssignment
【功能】             数据库任务类，实现任务存取
【接口说明】         增删、更新、查询，及获取任务对象
【开发者及日期】      2019/7/25-7/29
【更改记录】
*************************************************************************/
class DataBaseAssignment:public DataBase
{
public:
    DataBaseAssignment();
    ~DataBaseAssignment();

    //文本交互类对象获取、插入、更新
    bool             insertAssignmentText(const TextInteraction& text);
    bool             updateAssignmentText(const TextInteraction& text);
    TextInteraction  getAssignmentText(const QString& assignmentName, const QString& id, const PLATFORM& form);

    //任务类对象获取、插入、更新
    bool                 insertAssignment(const Assignment&);
    Assignment           getAssignment(const QString& assignmentName);
    QVector<Assignment>  getAllAssignment();
    bool    updateAssignment(const Assignment&);
    bool    searchAssignment(const QString& id, const QString& name,
                            const QString& parameter_1 = "id", const QString& parameter_2 = "assignmentName");          //利用id、任务名双重匹配查找
    bool    search(const QString&, const QString& parameter = "assignmentName");                                        //利用任务名单重匹配查找


    //报名类对象获取、插入、更新
    bool insertSignUp(const SignUpInteraction& signUp);
    bool updateSignUp(const SignUpInteraction& signUp);
    QVector<SignUpInteraction> getSignUp(const QString& assignmentName, const QString& selectorId, const SIGNUP& form);

private:
    bool    updateData(const QString& assignmentName, const QString& value, const QString& parameter);
    bool    updateInt(const QString& assignmentName, const int& value, const QString& parameter);
    bool    updateFloat(const QString& assignmentName, const float& value, const QString& parameter);
};


/*************************************************************************
【类名】             DataBaseUser
【功能】             数据库用户类，实现用户存取
【接口说明】         增删、更新、查询，及获取用户对象
【开发者及日期】      2019/7/21-7/24
【更改记录】
*************************************************************************/
class DataBaseUser:public DataBase
{
public:
    DataBaseUser();
    ~DataBaseUser();

    User  getUser(const QString& id);
    User  getUserByName(const QString& name);
    QVector<User> getUser();

    bool  insertUser(const User&);
    bool  search(const QString&, const QString& parameter = "username");
    bool  updateData(const QString& id, const QString& value, const QString& parameter);
    bool  updateInt(const QString& id, const int& value, const QString& parameter = "score");
    bool  updateFloat(const QString& id, const float& value, const QString& parameter = "money");
};


/*************************************************************************
【类名】             DataBasePicture
【功能】             数据库图片类，实现图片存取
【接口说明】         增删、更新、查询
【开发者及日期】      2019/7/21-7/22
【更改记录】
*************************************************************************/
class DataBasePicture:public DataBase
{
public:
    DataBasePicture();
    ~DataBasePicture();

    bool insertPictures(const QString& id, const QPixmap& pix);
    bool updataPixture(const QString& id, const QPixmap& pix);
    bool getPictures(const QString& id, QPixmap& picture);
};

/*************************************************************************
【类名】             DataBaseMessage
【功能】             数据库信息类，实现信息存取
【接口说明】         增删、更新、查询，获取消息盒子对象
【开发者及日期】      2019/7/29-7/30
【更改记录】
*************************************************************************/
class DataBaseMessage:public DataBase
{
public:
    DataBaseMessage();
    ~DataBaseMessage();

    bool insertMessage(const Message& newMessage);
    bool updateMessage(const QString& id);
    bool deleteMessage(const QString& id);
    bool getMessage(MessageInformBox& box);
};


/*************************************************************************
【类名】             DataBaseCertification
【功能】             数据库认证类，实现认证信息存取
【接口说明】         增删、更新、查询，获取认证对象
【开发者及日期】      2019/7/27
【更改记录】
*************************************************************************/
class DataBaseCertification:public DataBase
{
public:
    DataBaseCertification();
    ~DataBaseCertification();

    bool insertCertification(const certification& cei);
    bool updateCertification(const certification& cei);
    certification getCertification(const QString& id);
};
#endif // DATABASE_H
