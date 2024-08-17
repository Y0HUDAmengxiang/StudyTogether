#ifndef WECHATDIALOG_H
#define WECHATDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class WeChatDialog; }
QT_END_NAMESPACE

class WeChatDialog : public QDialog
{
    Q_OBJECT

public:
    WeChatDialog(QWidget *parent = nullptr);
    ~WeChatDialog();
    void closeEvent(QCloseEvent * event);
    //设置主界面用户信息
    void setInfo(QString name,int icon=1);
signals:
    void SIG_close();
    //创建房间信号
    void SIG_createRoom();
    //加入房间信号
    void SIG_joinRoom();

private slots:
    void on_pb_join_clicked();

    void on_pb_create_clicked();

private:
    Ui::WeChatDialog *ui;
};
#endif // WECHATDIALOG_H
