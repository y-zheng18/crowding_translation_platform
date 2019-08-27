#include "certification.h"
#include "database.h"
#include <QFile>
certification::certification()
{

}

/*************************************************************************
【函数名称】        certification
【函数功能】        构造函数，第一次构造使用
【参数】           用户id
【返回值】
【开发者及日期】     7/27
*************************************************************************/
certification::certification(const QString &id):m_userId(id)
{
    DataBaseCertification db;
    certification p = db.getCertification(id);
    if (p.getName() != "")
        *this = p;
    else
    {
        m_bIsChecked = false;
    }
}

/*************************************************************************
【函数名称】        certification
【函数功能】        构造函数，方便定义
【参数】            类成员值
【返回值】
【开发者及日期】     7/27
*************************************************************************/
certification::certification(const QString &id, const QString &IDNum, const QString &realName,
                             const QString &qualiText, const QPixmap &pix, const int &checked):
    m_userId(id), m_sIDNum(IDNum), m_sRealName(realName), m_sQualifyText(qualiText), m_pixQualification(pix), m_bIsChecked(checked)
{

}

certification::~certification()
{
    if (m_userId == "" || m_sRealName == "" || m_sIDNum == "")
        return;
    //qDebug()<<m_userId;
    DataBaseCertification db;
    if (!db.insertCertification(*this))
    {
        db.updateCertification(*this);
    }

}

/*************************************************************************
【函数名称】        upLoadPix
【函数功能】        上传任务证明
【参数】
【返回值】
【开发者及日期】     7/27
*************************************************************************/
bool certification::upLoadPix(const QString &fileName)
{
    QPixmap pix;
    if (pix.load(fileName))
    {
        m_pixQualification = pix;
        return true;
    }
    return false;
}
