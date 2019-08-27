#ifndef CERTIFICATION_H
#define CERTIFICATION_H

/*************************************************************************
【文件名】                 Certification.h
【功能模块和目的】          实现用户认证
【开发者及日期】           2019/7/27
*************************************************************************/
#include <QString>
#include <QPixmap>
#include <QVector>

/*************************************************************************
【类名】             certification
【功能】             实现用户认证工功能
【接口说明】         set、upload接口：设置类内部私有变量；get接口：获取类内部私有变量
【开发者及日期】      2019/7/27
【更改记录】
*************************************************************************/
class certification
{
public:
    certification();
    certification(const QString& id);
    certification(const QString& id, const QString& IDNum, const QString& realName,
                  const QString& qualiText, const QPixmap& pix, const int& checked = false);
    ~certification();
    void set_IDNum(const QString& id)
    {
        m_sIDNum = id;
    }

    void set_RealName(const QString& name)
    {
        m_sRealName = name;
    }

    void set_Qualification(const QString& q)
    {
        m_sQualifyText = q;
    }

    void set_checked(bool p)
    {
        m_bIsChecked = p;
    }

    void set_UserId(const QString& id)
    {
        m_userId = id;
    }

    bool upLoadPix(const QString& fileName);

    const QString& getUserID() const
    {
        return m_userId;
    }

    const QString& getIDNum() const
    {
        return m_sIDNum;
    }
    const QString& getName() const
    {
        return m_sRealName;
    }
    const QString& getQualText() const
    {
        return m_sQualifyText;
    }
    const QPixmap& getPix() const
    {
        return m_pixQualification;
    }
    bool getIsChecked() const
    {
        return m_bIsChecked;
    }
private:
    QString m_userId;
    bool m_bIsChecked;              //是否被平台认证
    QString m_sIDNum;
    QString m_sRealName;
    QString m_sQualifyText;       //英语水平等证明
    QPixmap m_pixQualification;
};

#endif // CERTIFICATION_H
