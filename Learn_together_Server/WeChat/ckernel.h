#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include <QSettings>
#include <QApplication>
#include <QFileInfo>
#include <QInputDialog>
#include <QMessageBox>
#include <map>
#include <QTime>
#include <QBuffer>
#include <QImage>
#include <QSharedPointer>//智能指针头文件
#include "wechatdialog.h"
#include "TcpClientMediator.h"
#include "packdef.h"
#include "logindialog.h"
#include "md5.h"
#include "roomdialog.h"
#include "usershow.h"
#include "audio_read.h"
#include "audio_write.h"
#include "videoread.h"
#include "screenread.h"
#include "threadworker.h"
//协议映射表使用的类型
class Ckernel;
typedef void (Ckernel::* PFUN)( unsigned int lSendIP , char* buf , int nlen ) ;

class SendVideoWorker;
class Ckernel : public QObject
{
    Q_OBJECT
public:
    explicit Ckernel(QObject *parent = nullptr);
    //单例模式
    static Ckernel * GetInstance(){
        static Ckernel ckernel;
        return &ckernel;
    }
public:
    void SetPackMap();//初始化协议映射表
    void initConfig();//初始化配置


signals:
    //多线程发送视频帧信号
    void SIG_SendVideo(char* buf,int nlen);
public slots:
    //发送登录信息：手机号，密码
    void slot_LoginCommit(QString tel,QString pass);
    //发送注册信息：手机号，密码，昵称
    void slot_RegisterCommit(QString tel,QString pass,QString name);
    //回收资源
    void slot_destroy();
    //创建房间槽函数
    void slot_createRoom();
    //加入房间槽函数
    void slot_joinRoom();
    //关闭房间槽函数
    void slot_quitRoom();
    //处理音频开始
    void slot_startAudio();
    //处理音频关闭
    void slot_pauseAudio();
    //发送音频帧
    void slot_audioFrame(QByteArray ba);
    //处理视频开始
    void slot_startVideo();
    //处理视频关闭
    void slot_pauseVideo();
    //发送视频帧
    void slot_sendVideoFrame(QImage img);
    //多线程发送视频帧
    void slot_SendVideo(char *buf,int nlen);
    //刷新图片
    void slot_refreshVideo(int id,QImage& img);
    //开启桌面捕捉
    void slot_startScreen();
    //关闭桌面捕捉
    void slot_pauseScreen();

    //网络数据处理
    void slot_dealData( unsigned int lSendIP , char* buf , int nlen );
    //处理注册回复
    void slot_dealRegisterRs( unsigned int lSendIP , char* buf , int nlen );
    //处理登录回复
    void slot_dealLoginRS( unsigned int lSendIP , char* buf , int nlen );
    //处理创建房间回复
    void slot_dealCreateRoomRS( unsigned int lSendIP , char* buf , int nlen );
    //处理加入房间回复
    void slot_dealJoinRoomRS( unsigned int lSendIP , char* buf , int nlen );
    //房间成员处理请求
    void slot_dealRoomMemberRq( unsigned int lSendIP , char* buf , int nlen );
    //处理退出房间请求
    void slot_dealLeaveRoomRq( unsigned int lSendIP , char* buf , int nlen );
    //音频帧的处理
    void slot_dealAudioFrameRq( unsigned int lSendIP , char* buf , int nlen );
    //视频帧的处理
    void slot_dealVideoFrameRq( unsigned int lSendIP , char* buf , int nlen );


private:
    WeChatDialog * m_pWeChatDlg;
    INetMediator * m_pClient;//添加tcp连接对象
    LoginDialog* m_pLoginDlg;//登陆界面对象
    RoomDialog* m_pRoomDlg;//房间界面对象

    PFUN m_netPackMap[_DEF_PACK_COUNT];//协议映射表数组
    QString m_ServerIp;//保存IP地址
    QString m_name;
    int m_id;
    int m_roomid;

    //////////////
    /// 音频，一个采集，多个播放，每个房间成员1：1map映射
    ///
    Audio_Read * m_pAudio_Read;
    std::map<int,Audio_Write*> m_mapIDToAudioWrite;
    ////////////
    /// 视频采集
    ///

    VideoRead* m_pVideoRead;
    ScreenRead * m_pScreenRead;

    enum client_type{audio_client =0,video_client};
    INetMediator * m_pAVClient[2];

    QSharedPointer<SendVideoWorker> m_pSendVideoWorker;
};

class SendVideoWorker:public ThreadWorker{
    Q_OBJECT
public slots:
    void slot_sendVideo(char* buf,int nlen){
        Ckernel::GetInstance()->slot_SendVideo(buf,nlen);
    }
private:

};

#endif // CKERNEL_H
