#include "logindialog.h"
#include "ui_logindialog.h"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("注册&登录");
    ui->tw_page->setCurrentIndex(0);
}

LoginDialog::~LoginDialog()
{
    qDebug()<<__func__;
    delete ui;
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    qDebug()<<__func__;
    if(QMessageBox::question(this , "提示","是否退出") == QMessageBox::Yes){
        Q_EMIT SIG_close();
        event->accept();//执行关闭
    }else{
        event->ignore();//忽略操作
    }
}
//提交登录信息按钮
void LoginDialog::on_pb_commit_clicked()
{
    qDebug()<<__func__;
    QString strtel = ui->le_tel->text();
    QString strpassword = ui->le_password->text();
    //非空校验
    QString tmpTel = strtel;
    QString tmpPass = strpassword;
    if(tmpTel.remove(" ").isEmpty()||tmpPass.remove(" ").isEmpty()){
        QMessageBox::about(this,"提示","手机号和密码不能为空");
        return ;
    }
    //真实性校验,正则表达式
    QRegExp reg("^1[3-8][0-9]\{6,9\}$");
    bool res = reg.exactMatch(strtel);
    if(!res){
        QMessageBox::about(this,"提示","手机号格式错误");
        return ;
    }
    if(strpassword.length()>20){
        QMessageBox::about(this,"提示","密码长度错误");
    }
    Q_EMIT SIG_LoginCommit(strtel,strpassword);
}

//清空登录信息
void LoginDialog::on_pb_clear_clicked()
{
    qDebug()<<__func__;
    ui->le_password->setText("");
    ui->le_tel->setText("");
}

//提交注册信息
void LoginDialog::on_pb_commit_register_clicked()
{
    qDebug()<<__func__;
    QString strtel = ui->le_tel_register->text();
    QString strpassword = ui->le_password_register->text();
    QString strname = ui->le_name_register->text();
    QString strconfirm = ui->le_confirm_register->text();
    //非空校验
    QString tmpTel = strtel;
    QString tmpPass = strpassword;
    QString tmpname = strname;
    if(tmpTel.remove(" ").isEmpty()||tmpPass.remove(" ").isEmpty()||tmpname.remove(" ").isEmpty()){
        QMessageBox::about(this,"提示","昵称、手机号和密码不能为空");
        return ;
    }
    //真实性校验,正则表达式
    QRegExp reg("^1[3-8][0-9]\{6,9\}$");
    bool res = reg.exactMatch(strtel);
    if(!res){
        QMessageBox::about(this,"提示","手机号格式错误");
        return ;
    }
    if(strpassword.length()>20){
        QMessageBox::about(this,"提示","密码长度错误");
    }
    //判断两次密码输入是否一致
    if(strpassword != strconfirm){
        QMessageBox::about(this,"提示","两次密码内容不一致");
        return ;
    }
    if(strname.length()>10){
        QMessageBox::about(this,"提示","昵称长度不能超过10");
        return ;
    }
    Q_EMIT SIG_RegisterCommit(strtel,strpassword,strname);
}

//清空注册信息
void LoginDialog::on_pb_clear_register_clicked()
{
    qDebug()<<__func__;
    ui->le_confirm_register->setText("");
    ui->le_name_register->setText("");
    ui->le_password_register->setText("");
    ui->le_tel_register->setText("");
}

