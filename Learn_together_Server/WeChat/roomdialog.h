#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QMessageBox>
#include "usershow.h"
namespace Ui {
class RoomDialog;
}

class RoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RoomDialog(QWidget *parent = nullptr);
    ~RoomDialog();
signals:
    void SIG_close();
    //暂停音频
    void SIG_audioPause();
    //开始音频
    void SIG_audioStart();
    //暂停视频
    void SIG_videoPause();
    //开始视频
    void SIG_videoStart();
    //开始桌面采集
    void SIG_screenStart();
    //暂停桌面采集
    void SIG_screenPause();
    //选择滤镜信号
    void SIG_setMoji(int moji);
public slots:
    //设置房间信息
    void slot_setInfo(QString roomid);

    //添加用户显示控件
    void slot_addUserShow(UserShow * user);
    //移除用户控件
    void slot_removeUserShow(UserShow* user);
    //将音频勾选取消
    void slot_setAudioCheck(bool check);
    //移除用户控件
    void slot_removeUserShow(int id);
    //清除用户信息
    void slot_clearUserShow();
    //刷新图片
    void slot_refreshUser(int id,QImage &img);
    //勾选视频选项
    void slot_setVedioCheck(bool check);
    //刷新显示预览图
    void slot_setBigImgID(int id,QString name);
    //勾选视频选项
    void slot_setScreenCheck(bool check);

private slots:
    //重写关闭事件
    void closeEvent(QCloseEvent* event);

    void on_pb_close_clicked();

    void on_pb_quit_clicked();

    void on_cb_audio_clicked();

    void on_cb_vedio_clicked();

    void on_cb_desk_clicked();

    void on_cb_moji_currentIndexChanged(int index);

private:
    Ui::RoomDialog *ui;
    QVBoxLayout* m_mainLayout;
    std::map<int , UserShow*> m_mapIDToUserShow;
};

#endif // ROOMDIALOG_H
