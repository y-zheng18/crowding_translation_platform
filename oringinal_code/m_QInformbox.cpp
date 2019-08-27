#include "m_QInformbox.h"
/*************************************************************************
【文件名】                 m_QInformBox.h
【功能模块和目的】          自定义通知，继承QMessageBox
【开发者及日期】           2019/7/31
*************************************************************************/
m_QInformBox::m_QInformBox():QMessageBox ()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
}
