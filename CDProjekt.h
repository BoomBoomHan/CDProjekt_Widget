#pragma once
#include "System.h"
#include <QtWidgets/QMainWindow>
#include "ui_CDProjekt.h"

class CDProjekt: public QMainWindow
{
    Q_OBJECT

private:
    Ui::CDProjektClass ui;
    //系统类
    System* sys;

public:
    CDProjekt(QWidget* parent = Q_NULLPTR);

public slots:
    //登录按钮点击事件
    void LogIn();
};
