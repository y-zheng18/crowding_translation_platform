#include "database.h"

DataBaseAssignment::DataBaseAssignment()
{
    m_sDataBase = openDataBase();
    m_tableName = "assignment";
    // m_dataBaseName = "test.db";
}

DataBaseAssignment::~DataBaseAssignment()
{
}

/*************************************************************************
【函数名称】        insertAssignmentText
【函数功能】        插入任务文本
【参数】            文本类对象
【返回值】
【开发者及日期】     7/28
*************************************************************************/
bool DataBaseAssignment::insertAssignmentText(const TextInteraction &text)
{
    QSqlQuery query(m_sDataBase);
    m_table_parameters = "(assignmentName varchar(50),"
                         "id varchar(20),"
                         "fileText blob)";
    PLATFORM form = text.getPlatForm();
    if (form == MANAGER_DOWNLOAD)           //发布任务
    {
        m_tableName = "publishText";
    }
    else if (form == TRANS_DOWNLOAD)         //分配任务
    {
        m_tableName = "spliteText";
    }
    else if (form == TRANS_UPLOAD)         //上传子任务
    {
        m_tableName = "translatedText";
    }
    else if (form == MANAGER_UPLOAD)         //整合译文
    {
        m_tableName = "finalText";
    }
    else if (form == MANAGER_REVIEW)
    {
        m_tableName = "review";
    }
    QString sql_create = QString("create table if not exists %1 %2").arg(m_tableName).arg(m_table_parameters);
    if (!query.exec(sql_create))
    {
        qDebug()<<"assgnmentTEXTCreate error"<<query.lastError();
        return false;
    }

    QString value = QString("('%1', '%2' ,'%3')").arg(text.getName()).arg(text.getID()).arg(text.getText());
    QString sql_text = QString("insert into %1 values %2").arg(m_tableName).arg(value);
    if (!query.exec(sql_text))
    {
        qDebug()<<"assgnmentTEXTInsert error"<<query.lastError();
        return false;
    }
    return true;
}

/*************************************************************************
【函数名称】        updateAssignmentText
【函数功能】        更新任务文本
【参数】            文本类对象
【返回值】
【开发者及日期】     7/28
*************************************************************************/

bool DataBaseAssignment::updateAssignmentText(const TextInteraction& text)
{
    QSqlQuery query(m_sDataBase);
    PLATFORM form = text.getPlatForm();
    if (form == MANAGER_DOWNLOAD)           //发布任务
    {
        m_tableName = "publishText";
    }
    else if (form == TRANS_DOWNLOAD)         //分配任务
    {
        m_tableName = "spliteText";
    }
    else if (form == TRANS_UPLOAD)         //上传子任务
    {
        m_tableName = "translatedText";
    }
    else if (form == MANAGER_UPLOAD)         //整合译文
    {
        m_tableName = "finalText";
    }
    else if (form == MANAGER_REVIEW)
    {
        m_tableName = "review";
    }
    QString select_sql = QString("select * from %1 where id = '%3' and assignmentName = '%4'")
            .arg(m_tableName).arg(text.getID()).arg(text.getName());
    if (!query.exec(select_sql))
    {
        qDebug()<<"selectTEXT error!"<<query.lastError();
    }
    int flag = 0;
    while (query.next())
    {
        flag = 1;
    }
    if (!flag)
        return false;
    QString parameter = "fileText";
    QString update_sql = QString("update %1 set %2 = :%2 where id = '%3' and assignmentName = '%4'")
            .arg(m_tableName).arg(parameter).arg(text.getID()).arg(text.getName());
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), text.getText());
    if (!query.exec())
    {
        qDebug()<<"updateTEXT error!"<<query.lastError();
        return false;
    }
    return true;
}

/*************************************************************************
【函数名称】        getAssignmentText
【函数功能】        获取任务文本
【参数】            任务名， 使用者id,文本平台类型美剧
【返回值】
【开发者及日期】     7/28
*************************************************************************/
TextInteraction DataBaseAssignment::getAssignmentText(const QString& assignmentName, const QString& id, const PLATFORM& form)
{
    QSqlQuery query(m_sDataBase);
    if (form == MANAGER_DOWNLOAD)           //发布任务
    {
        m_tableName = "publishText";
    }
    else if (form == TRANS_DOWNLOAD)         //分配任务
    {
        m_tableName = "spliteText";
    }
    else if (form == TRANS_UPLOAD)         //上传子任务
    {
        m_tableName = "translatedText";
    }
    else if (form == MANAGER_UPLOAD)         //整合译文
    {
        m_tableName = "finalText";
    }
    else if (form == MANAGER_REVIEW)
    {
        m_tableName = "review";
    }
    QString parameter = "fileText";
    QString select_sql = QString("select fileText from %1 where id = '%2' and assignmentName = '%3'")
            .arg(m_tableName).arg(id).arg(assignmentName);
    if (!query.exec(select_sql))
    {
        qDebug()<<"selectTEXT error!"<<query.lastError();
        return TextInteraction();
    }
    while (query.next())
    {
        QString text = query.value(0).toString();
        TextInteraction assignmentText(assignmentName, id, text);
        assignmentText.setPlatForm(form);
        return assignmentText;
    }
    return TextInteraction();
}



/*************************************************************************
【函数名称】        insertAssignment
【函数功能】        插入任务
【参数】            任务对象
【返回值】
【开发者及日期】     7/26
*************************************************************************/
bool DataBaseAssignment::insertAssignment(const Assignment& m_assignment)
{
    QSqlQuery query(m_sDataBase);
    m_tableName = "assignment";
    m_table_parameters = "(assignmentName varchar(50) primary key,"
                         "publisherID varchar(20),"
                         "managerID varchar(20),"
                         "translatorID blob,"                           //translatorID用一个字符串存入，约定用空格隔开
                         "description blob,"
                         "status int,"
                         "form int,"
                         "reward float,"
                         "fileText blob,"
                         "deadline varchar(30),"
                         "currentDDL varchar(30),"
                         "keywords varchar(255))";
    QString sql_create = QString("create table if not exists %1 %2").arg(m_tableName).arg(m_table_parameters);
    if (!query.exec(sql_create))
    {
        qDebug()<<"assignment error"<<query.lastError();
    }
    QString assignmentName = m_assignment.getName();
    QString publisherID = m_assignment.getPublisherID();
    QString managerID = m_assignment.getManagerID();
    QString description = m_assignment.getDescription();
    float reward = m_assignment.getReward();
    int status = m_assignment.getStatus();
    int form = m_assignment.getTranslationForm();
    int year = m_assignment.get_deadline().date().year();
    int month = m_assignment.get_deadline().date().month();
    int day = m_assignment.get_deadline().date().day();
    int hour = m_assignment.get_deadline().time().hour();
    int minute = m_assignment.get_deadline().time().minute();
    QString time = QString("%1 %2 %3 %4 %5").arg(year).arg(month).arg(day).arg(hour).arg(minute);
    year = m_assignment.get_currentDDL().date().year();
    month = m_assignment.get_currentDDL().date().month();
    day = m_assignment.get_currentDDL().date().day();
    hour = m_assignment.get_currentDDL().time().hour();
    minute = m_assignment.get_currentDDL().time().minute();
    QString c_time = QString("%1 %2 %3 %4 %5").arg(year).arg(month).arg(day).arg(hour).arg(minute);
    QString translators = "";
    QStringList temp = m_assignment.getTranslaors();
    for (int i = 0;i < temp.size();i++)
    {
        translators += temp[i];
        translators += "/";
    }
    QStringList keywords = m_assignment.getKeywords();
    QString keys = "";
    for (int i = 0;i < keywords.size();i++)
    {
        keys += keywords[i];
        keys += "/";
    }
    QDateTime d;
    QString text = m_assignment.getText();
    QString value = QString("('%1', '%2', '%3', '%4', '%5', %6, %7, %8, '%9', '%10', '%11', '%12')")
            .arg(assignmentName).arg(publisherID).arg(managerID)
            .arg(translators).arg(description).arg(status).arg(form).arg(reward).arg(text)
            .arg(time).arg(c_time).arg(keys);
    QString insert = QString("insert into %1 values %2").arg(m_tableName).arg(value);
    if (!query.exec(insert))
    {
        qDebug()<<"InsertAssignment error!"<<query.lastError();
        return false;
    }
    return true;
}


/*************************************************************************
【函数名称】        updateAssignment
【函数功能】        更新任务参数，私有成员，在更新任务时调用
【参数】            任务对象待更新参数
【返回值】
【开发者及日期】     7/26
*************************************************************************/
bool DataBaseAssignment::updateData(const QString& assignmentName,  const QString& value, const QString& parameter)
{
    QSqlQuery query(m_sDataBase);
    m_tableName = "assignment";
    QString update_sql = QString("update %1 set %2 = :%2 where assignmentName = '%3'")
            .arg(m_tableName).arg(parameter).arg(assignmentName);
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), value);
    if (!query.exec())
    {
        qDebug()<<"updateAssignment error!"<<query.lastError();
        return false;
    }
    return true;
}


/*************************************************************************
【函数名称】        updateInt
【函数功能】        更新int内容，重写基类虚函数，私有成员，在更新任务时调用
【参数】            任务对象int参数及值
【返回值】
【开发者及日期】     7/27
*************************************************************************/
bool DataBaseAssignment::updateInt(const QString& assignmentName, const int& value, const QString& parameter)
{
    QSqlQuery query(m_sDataBase);
    m_tableName = "assignment";
    QString update_sql = QString("update %1 set %2 = :%2 where assignmentName = '%3'")
            .arg(m_tableName).arg(parameter).arg(assignmentName);
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), value);
    if (!query.exec())
    {
        qDebug()<<"updateAssignment error!"<<query.lastError();
        return false;
    }
    return true;
}


/*************************************************************************
【函数名称】        updatefloat
【函数功能】        更新float内容，重写基类虚函数，私有成员，在更新任务函数中调用
【参数】            任务对象float参数及值
【返回值】
【开发者及日期】     7/27
*************************************************************************/
bool DataBaseAssignment::updateFloat(const QString &assignmentName, const float &value, const QString &parameter)
{
    QSqlQuery query(m_sDataBase);
    m_tableName = "assignment";
    QString update_sql = QString("update %1 set %2 = :%2 where assignmentName = '%3'")
            .arg(m_tableName).arg(parameter).arg(assignmentName);
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), value);
    if (!query.exec())
    {
        qDebug()<<"updateAssignment error!"<<query.lastError();
        return false;
    }
    return true;
}

/*************************************************************************
【函数名称】        searchAssignment
【函数功能】        查找任务是否存在
【参数】           任务名与ID作为双重查找
【返回值】
【开发者及日期】     7/28
*************************************************************************/
bool DataBaseAssignment::searchAssignment(const QString& id, const QString& name, const QString& parameter_1, const QString& parameter_2)
{
    QSqlQuery query(m_sDataBase);
    QString select_sql = QString("select * from %1 where %2 = '%3' and %4 = '%5'").arg(m_tableName).
            arg(parameter_1).arg(id).arg(parameter_2).arg(name);
    if (!query.exec(select_sql))
    {
        qDebug()<<"searchASSignment error ''"<<query.lastError();
        return false;
    }
    while (query.next())
    {
        return true;
    }
    return false;
}


/*************************************************************************
【函数名称】        search
【函数功能】        查找任务是否存在
【参数】           任务名单重查找
【返回值】
【开发者及日期】     7/27
*************************************************************************/
bool DataBaseAssignment::search(const QString& value, const QString& parameter)
{
    QSqlQuery query(m_sDataBase);
    QString select_sql = QString("select * from %1 where %2 = '%3'").arg(m_tableName).arg(parameter).arg(value);
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
【函数名称】        getAssignment
【函数功能】        获取任务
【参数】           任务名
【返回值】          任务对象
【开发者及日期】     7/28
*************************************************************************/
Assignment DataBaseAssignment::getAssignment(const QString& assignmentName)
{
    QSqlQuery query(m_sDataBase);
    m_tableName = "assignment";
    QString select_sql = QString("select publisherID, managerID, translatorID,"
                                 "description, status, form, reward, fileText, deadline, currentDDL, keywords "
                                 "from %1 where assignmentName = '%2'").arg(m_tableName).arg(assignmentName);
    if (!query.exec(select_sql))
    {
        qDebug()<<"getAssignment fail bug2"<<query.lastError();
        return Assignment();
    }
    while (query.next())
    {
        QString publisherID = query.value(0).toString();
        QString managerID = query.value(1).toString();
        QString description = query.value(3).toString();
        int status = query.value(4).toInt();
        int form = query.value(5).toInt();
        float reward = query.value(6).toFloat();
        QString text = query.value(7).toString();

        QString time = query.value(8).toString();
        int year = time.section(" ", 0, 0).toInt();
        int month = time.section(" ", 1, 1).toInt();
        int day = time.section(" ", 2, 2).toInt();
        int hour = time.section(" ", 3, 3).toInt();
        int minute = time.section(" ", 4, 4).toInt();
        QTime t;
        t.setHMS(hour, minute, 0);
        QDateTime ddl;
        ddl.setDate(QDate(year, month, day));
        ddl.setTime(t);
        time = query.value(9).toString();
        year = time.section(" ", 0, 0).toInt();
        month = time.section(" ", 1, 1).toInt();
        day = time.section(" ", 2, 2).toInt();
        hour = time.section(" ", 3, 3).toInt();
        minute = time.section(" ", 4, 4).toInt();
        t.setHMS(hour, minute, 0);
        QDateTime c_ddl;
        c_ddl.setDate(QDate(year, month, day));
        c_ddl.setTime(t);

        QString trans = query.value(2).toString();
        QStringList translators = QStringList();
        QString temp = "";
        for (int i = 0;i < trans.size();i++)
        {
            if(trans[i] != '/')
            {
                temp += trans[i];
            }
            else
            {
               translators.push_back(temp);
                temp = "";
            }
        }
        QString keys = query.value(10).toString();
        QStringList keywords = QStringList();
        temp = "";
        for (int i = 0;i < keys.size();i++)
        {
            if(keys[i] != '/')
            {
                temp += keys[i];
            }
            else
            {
               keywords.push_back(temp);
                temp = "";
            }
        }
        Assignment assgnmnt( assignmentName, publisherID, managerID,translators,
                             description, status, form, reward, text, keywords);
        assgnmnt.setDDL(ddl);
        assgnmnt.setCurrentDDL(c_ddl);
        return assgnmnt;
    }
    return Assignment();
}


/*************************************************************************
【函数名称】        getAllAssignment
【函数功能】        获取任务列表，方便展示
【参数】           任务名
【返回值】          任务对象Vecotr
【开发者及日期】     7/31
*************************************************************************/
QVector<Assignment> DataBaseAssignment::getAllAssignment()
{
    QVector<Assignment> assList;
    QSqlQuery query(m_sDataBase);
    m_tableName = "assignment";
    QString select_sql = QString("select assignmentName from assignment");
    if (!query.exec(select_sql))
    {
        qDebug()<<"getAssignment fail bug2"<<query.lastError();
    }
    QStringList assNameList;
    while (query.next())
    {
        QString assgnmentName = query.value(0).toString();
        assNameList.push_back(assgnmentName);
    }
    for (int i = 0;i <assNameList.size();i++)
    {
        assList.push_back(Assignment(assNameList[i]));
    }
    return assList;
}


/*************************************************************************
【函数名称】        updateAssignment
【函数功能】        更新任务，调用私有成员函数
【参数】           任务对象
【返回值】          是否更新成功 bool
【开发者及日期】     7/28
*************************************************************************/
bool DataBaseAssignment::updateAssignment(const Assignment& m_assignment)
{
    QStringList TranslatorID = m_assignment.getTranslaors();
    QString translators = "";
    for (int i = 0;i < TranslatorID.size();i++)
    {
        translators += TranslatorID[i];
        translators += "/";
    }
    QStringList keywords = m_assignment.getKeywords();
    QString keys = "";
    for (int i = 0;i < keywords.size();i++)
    {
        keys += keywords[i];
        keys += "/";
    }
    QString assignmentName = m_assignment.getName();
    updateData(assignmentName, m_assignment.getManagerID(), "managerID");
    updateData(assignmentName, m_assignment.getPublisherID(), "publisherID");
    updateData(assignmentName, translators, "translatorID");
    updateData(assignmentName, keys, "keywords");
    updateData(assignmentName, m_assignment.getDescription(), "description");
    updateInt(assignmentName, m_assignment.getStatus(), "status");
    updateInt(assignmentName, m_assignment.getTranslationForm(), "form");
    updateFloat(assignmentName, m_assignment.getReward(), "reward");
    updateData(assignmentName, m_assignment.getText(), "fileText");
    int year = m_assignment.get_deadline().date().year();
    int month = m_assignment.get_deadline().date().month();
    int day = m_assignment.get_deadline().date().day();
    int hour = m_assignment.get_deadline().time().hour();
    int minute = m_assignment.get_deadline().time().minute();
    QString time = QString("%1 %2 %3 %4 %5").arg(year).arg(month).arg(day).arg(hour).arg(minute);
    updateData(assignmentName, time, "deadline");
    year = m_assignment.get_currentDDL().date().year();
    month = m_assignment.get_currentDDL().date().month();
    day = m_assignment.get_currentDDL().date().day();
    hour = m_assignment.get_currentDDL().time().hour();
    minute = m_assignment.get_currentDDL().time().minute();
    QString c_time = QString("%1 %2 %3 %4 %5").arg(year).arg(month).arg(day).arg(hour).arg(minute);
    updateData(assignmentName, c_time, "currentDDL");
}


/*************************************************************************
【函数名称】        insertSignUp
【函数功能】        插入报名
【参数】            报名类对象
【返回值】          是否插入成功 bool
【开发者及日期】     7/29-7/31
*************************************************************************/
bool DataBaseAssignment::insertSignUp(const SignUpInteraction &signUp)
{
    QSqlQuery query(m_sDataBase);
    m_table_parameters = "(assignmentName varchar(50),"
                         "selectorID varchar(20),"
                         "candidateID varchar(20),"
                         "result int)";
    SIGNUP form = signUp.getPlatForm();
    if (form == MANAGER_SIGN_UP)           //负责人报名
    {
        m_tableName = "managerSignUp";
    }
    else if (form == TRANS_SIGN_UP)         //分配任务
    {
        m_tableName = "translatorSignUp";
    }
    QString sql_create = QString("create table if not exists %1 %2").arg(m_tableName).arg(m_table_parameters);
    if (!query.exec(sql_create))
    {
        qDebug()<<"signUp Create error"<<query.lastError();
        return false;
    }

    QString value = QString("('%1', '%2' ,'%3', %4)").arg(signUp.getName()).arg(signUp.getSelector())
            .arg(signUp.getCandidate()).arg(int(signUp.getResult()));
    QString sql_text = QString("insert into %1 values %2").arg(m_tableName).arg(value);
    if (!query.exec(sql_text))
    {
        qDebug()<<"signUp Insert error"<<query.lastError();
        return false;
    }
    return true;
}


/*************************************************************************
【函数名称】        upDateSignUp
【函数功能】        更新报名
【参数】            报名类对象
【返回值】          是否更新成功 bool
【开发者及日期】     7/20
*************************************************************************/
bool DataBaseAssignment::updateSignUp(const SignUpInteraction& signUp)
{
    QSqlQuery query(m_sDataBase);
    SIGNUP form = signUp.getPlatForm();
    if (form == MANAGER_SIGN_UP)           //负责人报名
    {
        m_tableName = "managerSignUp";
    }
    else if (form == TRANS_SIGN_UP)         //分配任务
    {
        m_tableName = "translatorSignUp";
    }
    QString select_sql = QString("select * from %1 where candidateID = '%2' and assignmentName = '%3'")
            .arg(m_tableName).arg(signUp.getCandidate()).arg(signUp.getName());
    if (!query.exec(select_sql))
    {
        qDebug()<<query.lastError();
    }
    int flag = 0;
    while (query.next())
    {
        flag = 1;
    }
    if (flag == 0)
        return false;
    QString parameter = "result";
    QString update_sql = QString("update %1 set %2 = :%2 where candidateID = '%3' and assignmentName = '%4'")
            .arg(m_tableName).arg(parameter).arg(signUp.getCandidate()).arg(signUp.getName());
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), int(signUp.getResult()));
    if (!query.exec())
    {
        qDebug()<<"signUp upDATE error"<<query.lastError();
        return false;
    }
    return true;
}
/*************************************************************************
【函数名称】        getSignUp
【函数功能】        获取报名列表
【参数】           任务名、选拔人ID
【返回值】          报名列表
【开发者及日期】     7/31
*************************************************************************/
QVector<SignUpInteraction> DataBaseAssignment::getSignUp(const QString& assignmentName, const QString& selectorId, const SIGNUP& form)
{
    QSqlQuery query(m_sDataBase);
    if (form == MANAGER_SIGN_UP)           //负责人报名
    {
        m_tableName = "managerSignUp";
    }
    else if (form == TRANS_SIGN_UP)         //分配任务
    {
        m_tableName = "translatorSignUp";
    }
    QString sql_select = QString("select candidateID, result "
                                 "from %1 where assignmentName = '%2' and selectorID = '%3'")
            .arg(m_tableName).arg(assignmentName).arg(selectorId);
    //qDebug()<<sql_select;
    if (!query.exec(sql_select))
    {
        qDebug()<<"signUp select error"<<query.lastError();
    }
    QVector<SignUpInteraction> signUpMessage;
    while (query.next())
    {
        QString candidateID = query.value(0).toString();
        ISCHOSEN result = ISCHOSEN(query.value(1).toInt());
        SignUpInteraction temp(assignmentName, selectorId, candidateID, result);
        temp.setPlatForm(form);
        signUpMessage.push_back(temp);
    }
    return signUpMessage;
}
