#include "CDProjekt.h"
#include "FunctionLibrary.h"
#include "stdafx.h"
#include <string>
#include <qmessagebox.h>

CDProjekt::CDProjekt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.PasswordEdit->setEchoMode(QLineEdit::Password);
    connect(ui.LogInButton, SIGNAL(clicked()), this, SLOT(LogIn()));
}


void CDProjekt::LogIn()
{
    const std::string inputUsername = FunctionLibrary::ToStdString(ui.UsernameEdit->text());
    const std::string inputPassword = FunctionLibrary::ToStdString(ui.PasswordEdit->text());
    sys = new System(inputUsername, inputPassword);
    if (!sys->IsThisSystemActive())
    {
        QMessageBox::about(this, QStringLiteral("登录失败"), QStringLiteral("用户名或密码错误!"));
    }
    else
    {
        QMessageBox::about(this, QStringLiteral("登录成功"), QStringLiteral("登录成功!"));
    }
}