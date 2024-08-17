#include "wechatdialog.h"
#include "ui_wechatdialog.h"

WeChatDialog::WeChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WeChatDialog)
{
    ui->setupUi(this);
    setWindowTitle("视频会议");
}

WeChatDialog::~WeChatDialog()
{
    qDebug()<<__func__;
    delete ui;
}
//关闭事件
void WeChatDialog::closeEvent(QCloseEvent *event)
{
    qDebug()<<__func__;
    if(QMessageBox::question(this , "提示","是否退出") == QMessageBox::Yes){
        Q_EMIT SIG_close();
        event->accept();//执行关闭
    }else{
        event->ignore();//忽略操作
    }
}
//设置主界面用户信息
void WeChatDialog::setInfo(QString name, int icon)
{
    ui->lb_name->setText(name);
}

//加入会议按钮
void WeChatDialog::on_pb_join_clicked()
{
    Q_EMIT SIG_joinRoom();
}

//创建会议按钮
void WeChatDialog::on_pb_create_clicked()
{
    Q_EMIT SIG_createRoom();
}

