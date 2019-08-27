#include "assignmentshow_ui.h"
#include "ui_assignmentshow_ui.h"
#include "assignmentdetails_ui.h"
#include "choosemanager_ui.h"
#include "manageroperate_ui.h"
#include "translator_ui.h"
#include "QGraphicsDropShadowEffect"
assignmentShow_ui::assignmentShow_ui(User& u, Assignment& a, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::assignmentShow_ui),
    m_assignment(a),
    m_user(u)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(300, 300);
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
    QPixmap pix = a.getPix();
    if (!pix.isNull())
    {
        pix.scaled(ui->labelPic->size(), Qt::KeepAspectRatio);
        ui->labelPic->setScaledContents(true);
        ui->labelPic->setPixmap(pix);
    }
    ui->labelName->setText(a.getName());
}


assignmentShow_ui::~assignmentShow_ui()
{

    delete ui;
}


/*************************************************************************
【函数名称】        on_btnShowDetails_clicked
【函数功能】        展示任务详情，分情况对不同使用者展示其任务，具有报名、结账、查看任务明细等功能
【参数】
【返回值】
【开发者及日期】     7/31
*************************************************************************/
void assignmentShow_ui::on_btnShowDetails_clicked()
{
    if (m_user.getID() == m_assignment.getPublisherID() &&
            (m_assignment.getStatus() == RECRUITING_MANAGER || m_assignment.getStatus() == MANAGER_RECUIT_DONE))
    {
        AssignmentPublisher asP(m_assignment.getName());
        ChooseManager_ui* choose = new ChooseManager_ui(m_user, asP);
        choose->exec();
        m_assignment.setPix(asP.getPix());
        m_assignment = Assignment(asP);
    }
    else if (m_user.getID() == m_assignment.getManagerID() &&
             (m_assignment.getStatus() == RECRUITING_TRANSLATOR || m_assignment.getStatus() == MANAGER_RECUIT_DONE
              || m_assignment.getStatus() == PROCCESSING))
    {
        AssignmentManager asManager(m_assignment.getName());
        ManagerOperate_ui* manaOp = new ManagerOperate_ui(m_user, asManager);
        manaOp->exec();
        m_assignment = Assignment(asManager);
        qDebug()<<m_assignment.getName();
    }
    else if (m_assignment.getStatus() == PROCCESSING)
    {
        int flag = 0;
        for (int i = 0;i < m_assignment.getTranslaors().size();i++)
        {
            if (m_assignment.getTranslaors()[i] == m_user.getID())
            {
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            AssignmentTranslator asTran(m_user.getID(), m_assignment.getName());
            translator_ui* tran = new translator_ui(asTran);
            tran->exec();
            m_assignment = Assignment(asTran);
        }

        else
        {
            AssignmentDetails_ui* details = new AssignmentDetails_ui(m_user, m_assignment);
            details->show();
        }
    }
    else
    {
        AssignmentDetails_ui* details = new AssignmentDetails_ui(m_user, m_assignment);
        details->show();
    }
}
