#include "roomdialog.h"
#include "ui_roomdialog.h"

RoomDialog::RoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoomDialog)
{
    ui->setupUi(this);

    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(5);
    ui->wdg_list->setLayout(m_mainLayout);
    //测试代码
//    for(int i=0;i<55;i++){
//        UserShow * user = new UserShow;
//        user->slot_setInfo(i+1,QString("测试%1").arg(i+1));
//        slot_addUserShow(user);
//    }
}

RoomDialog::~RoomDialog()
{
    delete ui;
}

void RoomDialog::slot_setInfo(QString roomid)
{
    QString title = QString ("房间号：%1").arg(roomid);
    setWindowTitle(title);
    ui->lb_title->setText(title);
}
//添加用户显示控件
void RoomDialog::slot_addUserShow(UserShow *user)
{
    m_mainLayout->addWidget(user);
    m_mapIDToUserShow[user->m_id]=user;
}
//移除用户控件
void RoomDialog::slot_removeUserShow(UserShow *user)
{
    user->hide();
    m_mainLayout->removeWidget(user);
}
//将音频勾选取消
void RoomDialog::slot_setAudioCheck(bool check)
{
    ui->cb_audio->setChecked(check);
}

void RoomDialog::slot_removeUserShow(int id)
{
    if(m_mapIDToUserShow.count(id)>0){
        UserShow * user = m_mapIDToUserShow[id];
        slot_removeUserShow(user);
    }
}
//清除用户信息
void RoomDialog::slot_clearUserShow()
{
    for(auto ite = m_mapIDToUserShow.begin();ite!=m_mapIDToUserShow.end();++ite){
        slot_removeUserShow(ite->second);
    }
}
//刷新图片
void RoomDialog::slot_refreshUser(int id, QImage &img)
{
    //预览图的id要与刷新的图片id一致
    if(ui->wdg_userShow->m_id ==id){
        ui->wdg_userShow->slot_setImage(img);
    }

    if(m_mapIDToUserShow.count(id)>0){
        UserShow * user = m_mapIDToUserShow[id];
        user->slot_setImage(img);
    }
}
//勾选视频选项
void RoomDialog::slot_setVedioCheck(bool check)
{
    ui->cb_vedio->setChecked(check);
}

void RoomDialog::slot_setBigImgID(int id, QString name)
{
    ui->wdg_userShow->slot_setInfo(id,name);
}
//勾选视频选项
void RoomDialog::slot_setScreenCheck(bool check)
{
    ui->cb_desk->setChecked(check);
}
//重写关闭事件
void RoomDialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"退出提示","是否退出会议") == QMessageBox::Yes){
        Q_EMIT SIG_close();
        event->accept();
        return ;
    }
    event->ignore();
}
//点击X按钮退出
void RoomDialog::on_pb_close_clicked()
{
    this->close();
}
//点击退出房间按钮
void RoomDialog::on_pb_quit_clicked()
{
    this->close();
}

//打开或关闭音频
void RoomDialog::on_cb_audio_clicked()
{
    if(ui->cb_audio->isChecked()){
        Q_EMIT SIG_audioStart();
        //ui->cb_audio->setChecked(false);
    }else{
        //ui->cb_audio->setChecked(true);
        Q_EMIT SIG_audioPause();
    }
}

//打开或关闭视频
void RoomDialog::on_cb_vedio_clicked()
{
    if(ui->cb_vedio->isChecked()){
        ui->cb_desk->setChecked(false);
        Q_EMIT SIG_screenPause();
        Q_EMIT SIG_videoStart();
        //ui->cb_audio->setChecked(false);
    }else{
        //ui->cb_audio->setChecked(true);
        Q_EMIT SIG_videoPause();
    }
}

//打开或关闭桌面捕捉
void RoomDialog::on_cb_desk_clicked()
{
    if(ui->cb_desk->isChecked()){
        ui->cb_vedio->setChecked(false);
        Q_EMIT SIG_videoPause();
        Q_EMIT SIG_screenStart();
        //ui->cb_audio->setChecked(false);
    }else{
        //ui->cb_audio->setChecked(true);
        Q_EMIT SIG_screenPause();
    }
}

//滤镜切换
void RoomDialog::on_cb_moji_currentIndexChanged(int index)
{
    Q_EMIT SIG_setMoji(index);
}

