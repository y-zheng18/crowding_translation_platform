#ifndef M_MESSAGEBOX_H
#define M_MESSAGEBOX_H

/*************************************************************************
【文件名】                 m_QInformBox.h
【功能模块和目的】          自定义通知，继承QMessageBox
【开发者及日期】           2019/7/31
*************************************************************************/
#include <QMessageBox>
class m_QInformBox:public QMessageBox
{
public:
    m_QInformBox();
};

#endif // M_MESSAGEBOX_H
