#-------------------------------------------------
#
# Project created by QtCreator 2019-07-30T00:07:04
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = life_tran_final
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        assignment.cpp \
        assignmentdetails_ui.cpp \
        assignmentmanager.cpp \
        assignmentpublisher.cpp \
        assignmentshow_ui.cpp \
        assignmenttranslator.cpp \
        certification.cpp \
        choosemanager_ui.cpp \
        choosetrans_ui.cpp \
        database.cpp \
        databaseassignment.cpp \
        databasemessage.cpp \
        databaseuser.cpp \
    dialoglogin.cpp \
        edituserfile_ui.cpp \
        editusermessage_ui.cpp \
        m_QInformbox.cpp \
        main.cpp \
        mainwindow.cpp \
        manageroperate_ui.cpp \
        messageinformbox.cpp \
    messageinformbox_ui.cpp \
    platform_manager_ui.cpp \
        publish_ui.cpp \
        recharge_ui.cpp \
        register_ui.cpp \
        resetcode_ui.cpp \
        review_ui.cpp \
        signupinteraction.cpp \
        textinteraction.cpp \
        user.cpp \
        usermessage_ui.cpp \
    translator_ui.cpp

HEADERS += \
        assignment.h \
        assignmentdetails_ui.h \
        assignmentmanager.h \
        assignmentpublisher.h \
        assignmentshow_ui.h \
        assignmenttranslator.h \
        certification.h \
        choosemanager_ui.h \
        choosetrans_ui.h \
        database.h \
    dialoglogin.h \
        edituserfile_ui.h \
        editusermessage_ui.h \
        m_QInformbox.h \
        mainwindow.h \
        manageroperate_ui.h \
        messageinformbox.h \
    messageinformbox_ui.h \
    platform_manager_ui.h \
        publish_ui.h \
        recharge_ui.h \
        register_ui.h \
        resetcode_ui.h \
        review_ui.h \
        signupinteraction.h \
        textinteraction.h \
        user.h \
        usermessage_ui.h \
    translator_ui.h

FORMS += \
        assignmentdetails_ui.ui \
        assignmentshow_ui.ui \
        choosemanager_ui.ui \
        choosetrans_ui.ui \
    dialoglogin.ui \
        edituserfile_ui.ui \
        editusermessage_ui.ui \
        mainwindow.ui \
        manageroperate_ui.ui \
    messageinformbox_ui.ui \
    platform_manager_ui.ui \
        publish_ui.ui \
        recharge_ui.ui \
        register_ui.ui \
        resetcode_ui.ui \
        review_ui.ui \
        usermessage_ui.ui \
    translator_ui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES +=
RC_FILE +=
RC_ICONS = logo.ico
