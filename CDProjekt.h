#pragma once
#include "System.h"
#include <QtWidgets/QMainWindow>
#include "ui_CDProjekt.h"

class CDProjekt: public QMainWindow
{
    Q_OBJECT

private:
    Ui::CDProjektClass ui;
    //ϵͳ��
    System* sys;

public:
    CDProjekt(QWidget* parent = Q_NULLPTR);

public slots:
    //��¼��ť����¼�
    void LogIn();
};
