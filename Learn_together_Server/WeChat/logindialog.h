#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QRegExp>
#include <QCloseEvent>
#include <QDebug>
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
signals:
    //登录提交
    void SIG_LoginCommit(QString tel,QString password);
    //注册提交
    void SIG_RegisterCommit(QString tel,QString password,QString name);
    void SIG_close();
public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    //关闭登陆界面窗口
    void closeEvent(QCloseEvent * event);

private slots:
    void on_pb_commit_clicked();

    void on_pb_clear_clicked();

    void on_pb_commit_register_clicked();

    void on_pb_clear_register_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
