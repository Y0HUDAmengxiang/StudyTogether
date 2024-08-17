#include "ckernel.h"

#define NetPackMap(a) m_netPackMap[a - _DEF_PACK_BASE]
#define MD5_KEY (1234)
//初始化协议映射表
void Ckernel::SetPackMap()
{
    qDebug()<<__func__;
    memset(m_netPackMap,0,sizeof(m_netPackMap));
    NetPackMap(_DEF_PACK_REGISTER_RS) = &Ckernel::slot_dealRegisterRs;
    NetPackMap(_DEF_PACK_LOGIN_RS) = &Ckernel::slot_dealLoginRS;
    NetPackMap(_DEF_PACK_CREATEROOM_RS) = &Ckernel::slot_dealCreateRoomRS;
    NetPackMap(_DEF_PACK_JOINROOM_RS) = &Ckernel::slot_dealJoinRoomRS;
    NetPackMap(_DEF_PACK_ROOM_MEMBER) = &Ckernel::slot_dealRoomMemberRq;
    NetPackMap(_DEF_PACK_LEAVEROOM_RQ) = &Ckernel::slot_dealLeaveRoomRq;
    NetPackMap(_DEF_PACK_AUDIO_FRAME) = &Ckernel::slot_dealAudioFrameRq;
    NetPackMap(_DEF_PACK_AUDIO_FRAME) = &Ckernel::slot_dealAudioFrameRq;
    NetPackMap(_DEF_PACK_VIDEO_FRAME) = &Ckernel::slot_dealVideoFrameRq;
}
//初始化配置
void Ckernel::initConfig()
{
    qDebug()<<__func__;
    m_ServerIp = _DEF_SERVERIP;
    //获取路径，再exe同级的路径下
    QString path = QApplication::applicationDirPath()+"/config.ini";
    //判断配置文件是否存在，有打开，没有创建
    QFileInfo info(path);
    QSettings settings(path,QSettings::IniFormat,NULL);
    if(info.exists()){
        //加载配置文件ip，移动到net组
        settings.beginGroup("Net");
        //读取ip->addr->赋值
        QVariant ip = settings.value("ip");
        QString strip = ip.toString();
        settings.endGroup();
        if(!strip.isEmpty()){
            m_ServerIp = strip;
        }
        qDebug()<<m_ServerIp;
    }else{
        settings.beginGroup("Net");
        settings.setValue("ip",m_ServerIp);
        settings.endGroup();
        qDebug()<<m_ServerIp;
    }

}
Ckernel::Ckernel(QObject *parent) : QObject(parent),m_id(0),m_roomid(0)
{
    qDebug()<<__func__;
    SetPackMap();
    initConfig();
    //显示主窗口
    m_pWeChatDlg = new WeChatDialog;
    //m_pWeChatDlg->show();
    //绑定关闭事件
    connect(m_pWeChatDlg,SIGNAL(SIG_close()),this,SLOT(slot_destroy()));
    connect(m_pWeChatDlg,SIGNAL(SIG_createRoom()),this,SLOT(slot_createRoom()));
    connect(m_pWeChatDlg,SIGNAL(SIG_joinRoom()),this,SLOT(slot_joinRoom()));

    //登陆界面
    m_pLoginDlg = new LoginDialog;
    connect(m_pLoginDlg,SIGNAL(SIG_LoginCommit(QString,QString)),this,SLOT(slot_LoginCommit(QString,QString)));
    connect(m_pLoginDlg,SIGNAL(SIG_close()),this,SLOT(slot_destroy()));
    connect(m_pLoginDlg,SIGNAL(SIG_RegisterCommit(QString,QString,QString)),this,SLOT(slot_RegisterCommit(QString,QString,QString)));
    m_pLoginDlg->show();

    //房间界面
    m_pRoomDlg = new RoomDialog;
    connect(m_pRoomDlg,SIGNAL(SIG_close()),this,SLOT(slot_quitRoom()));
    //绑定开始音频的信号和槽
    connect(m_pRoomDlg,SIGNAL(SIG_audioStart()),this,SLOT(slot_startAudio()));
    //绑定暂停音频的信号和槽
    connect(m_pRoomDlg,SIGNAL(SIG_audioPause()),this,SLOT(slot_pauseAudio()));
    //绑定开始视频的信号和槽
    connect(m_pRoomDlg,SIGNAL(SIG_videoStart()),this,SLOT(slot_startVideo()));
    //绑定暂停视频的信号和槽
    connect(m_pRoomDlg,SIGNAL(SIG_videoPause()),this,SLOT(slot_pauseVideo()));
    //绑定开始桌面捕捉的信号和槽
    connect(m_pRoomDlg,SIGNAL(SIG_screenStart()),this,SLOT(slot_startScreen()));
    //绑定暂停桌面捕捉的信号和槽
    connect(m_pRoomDlg,SIGNAL(SIG_screenPause()),this,SLOT(slot_pauseScreen()));

    m_pAudio_Read = new Audio_Read;
    connect(m_pAudio_Read,SIGNAL(SIG_audioFrame(QByteArray)),this,SLOT(slot_audioFrame(QByteArray)));

    m_pVideoRead = new VideoRead;
    connect(m_pVideoRead,SIGNAL(SIG_sendVideoFrame(QImage)),this,SLOT(slot_sendVideoFrame(QImage)));

    m_pScreenRead = new ScreenRead;
    connect(m_pScreenRead,SIGNAL(SIG_getScreenFrame(QImage)),this,SLOT(slot_sendVideoFrame(QImage)));

    m_pSendVideoWorker = QSharedPointer<SendVideoWorker>(new SendVideoWorker);
    connect(this,SIGNAL(SIG_SendVideo(char* ,int)),m_pSendVideoWorker.data(),SLOT(slot_sendVideo(char*,int)));

    m_pClient = new TcpClientMediator;
    m_pClient->OpenNet(m_ServerIp.toStdString().c_str(),_DEF_PORT);//初始化网络
    connect(m_pClient,SIGNAL(SIG_ReadyData(uint, char *,int)),this,SLOT(slot_dealData(uint, char *,int)));//网络数据处理
    for(int i=0;i<2;i++){
        m_pAVClient[i] = new TcpClientMediator;
        m_pAVClient[i]->OpenNet(m_ServerIp.toStdString().c_str(),_DEF_PORT);
        connect(m_pAVClient[i],SIGNAL(SIG_ReadyData(uint, char *,int)),this,SLOT(slot_dealData(uint, char *,int)));//网络数据处理
    }

    //设置滤镜效果
    connect(m_pRoomDlg,SIGNAL(SIG_setMoji(int)),m_pVideoRead,SLOT(slot_setMoji(int)));

}


//回收
void Ckernel::slot_destroy()
{
    qDebug()<<__func__;
    if(m_pWeChatDlg){
        //先隐藏窗口
        m_pWeChatDlg->hide();
        //回收主窗口
        delete m_pWeChatDlg;
        m_pWeChatDlg = NULL;
    }
    if(m_pLoginDlg){
        //先隐藏窗口
        m_pLoginDlg->hide();
        //回收主窗口
        delete m_pLoginDlg;
        m_pLoginDlg = NULL;
    }
    if(m_pClient){
        m_pClient->CloseNet();
        delete m_pClient;
        m_pClient = NULL;
    }
    if(m_pRoomDlg){
        m_pRoomDlg->hide();
        delete m_pRoomDlg;
        m_pRoomDlg = NULL;
    }
    if(m_pAudio_Read){
        m_pAudio_Read->pause();
        delete m_pAudio_Read;
        m_pAudio_Read = NULL;
    }
    exit(0);
}
//创建房间槽函数
void Ckernel::slot_createRoom()
{
    qDebug()<<__func__;
    //判断是否在房间内
    if(m_roomid!=0){
        QMessageBox::about(m_pWeChatDlg,"提示","已在房间内，请先退出");
        //QMessageBox::about(m_pWeChatDlg,"提示","房间已存在，请退出");
        return ;
    }
    STRU_CREATEROOM_RQ rq;
    rq.m_nUserID = m_id;
    m_pClient->SendData(0,(char*)&rq,sizeof(rq));
}
//加入房间槽函数
void Ckernel::slot_joinRoom()
{
    qDebug()<<__func__;
    //判断是否在房间内
    if(m_roomid!=0){
        QMessageBox::about(m_pWeChatDlg,"提示","已在房间内");
        return ;
    }
    //弹出窗口，填写房间号，现有问题：点击后不输入房间号会弹出提示框，将这个错误提醒进行判断取消todo
    QString strroom = QInputDialog::getText(m_pWeChatDlg,"加入房间","请输入房间号");
    //if(strroom.size() == 0)
    QRegExp exp("^[0-9]\{1,10\}$");
    if(!exp.exactMatch(strroom)){
        QMessageBox::about(m_pWeChatDlg,"提示","房间号输入不合法");
        return ;
    }
    qDebug()<<strroom;
    STRU_JOINROOM_RQ rq;
    rq.m_nUserId = m_id;
    rq.m_RoomID = strroom.toInt();
    //发送没问题
    m_pClient->SendData(0,(char*)&rq,sizeof(rq));
}
//关闭房间槽函数
void Ckernel::slot_quitRoom()
{
    qDebug()<<__func__;
    //发退出包
    STRU_LEAVEROOM_RQ rq;
    rq.m_nUserId=m_id;
    rq.m_Roomid=m_roomid;
    std::string name = m_name.toStdString();
    strcpy(rq.szUserName,name.c_str());
    m_pClient->SendData(0,(char*)&rq,sizeof(rq));
    //关闭 音频，视频 todo
    m_pAudio_Read->pause();
    m_pRoomDlg->slot_setAudioCheck(false);
    m_pVideoRead->slot_closeVideo();
    m_pRoomDlg->slot_setVedioCheck(false);
    m_pScreenRead->slot_closeVideoScreen();
    m_pRoomDlg->slot_setScreenCheck(false);

    //回收所有人的audiowrite
    for(auto ite =m_mapIDToAudioWrite.begin();ite!=m_mapIDToAudioWrite.end();){
        Audio_Write * pWrite = ite->second;
        ite = m_mapIDToAudioWrite.erase(ite);
        delete pWrite;
    }

    //回收资源
    m_pRoomDlg->slot_clearUserShow();
    m_roomid = 0;

}
//处理音频开始
void Ckernel::slot_startAudio()
{
    qDebug()<<__func__;
    m_pAudio_Read->start();
}
//处理音频关闭
void Ckernel::slot_pauseAudio()
{
    qDebug()<<__func__;
    m_pAudio_Read->pause();
}
///音频数据帧
/// 成员描述
/// int type;
/// int userId;
/// int roomId;
/// int min;
/// int sec;
/// int msec;
/// QByteArray audioFrame;
///
//发送音频帧
void Ckernel::slot_audioFrame(QByteArray ba)
{
    int nPackSize = 6*sizeof(int)+ba.size();
    char * buf = new char[nPackSize];
    char * tmp = buf;

    int type = _DEF_PACK_AUDIO_FRAME;
    int userId = m_id;
    int roomId = m_roomid;
    QTime tm = QTime::currentTime();
    int min = tm.minute();
    int sec = tm.second();
    int msec = tm.msec();

    *(int *)tmp = type;
    tmp += sizeof(int);

    *(int *)tmp = userId;
    tmp += sizeof(int);

    *(int *)tmp = roomId;
    tmp += sizeof(int);

    *(int *)tmp = min;
    tmp += sizeof(int);

    *(int *)tmp = sec;
    tmp += sizeof(int);

    *(int *)tmp = msec;
    tmp += sizeof(int);

    memcpy(tmp,ba.data(),ba.size());

    //m_pClient->SendData(0,buf,nPackSize);
    m_pAVClient[audio_client]->SendData(0,buf,nPackSize);
    delete[] buf;

}
//处理音频开始
void Ckernel::slot_startVideo()
{
    qDebug()<<__func__;
    m_pVideoRead->slot_openVideo();
}
//处理音频关闭
void Ckernel::slot_pauseVideo()
{
    qDebug()<<__func__;
    m_pVideoRead->slot_closeVideo();
}
//刷新图片
void Ckernel::slot_refreshVideo(int id, QImage &img)
{
    m_pRoomDlg->slot_refreshUser(id,img);
}
//发送视频帧
void Ckernel::  slot_sendVideoFrame(QImage img)
{
    // 显示图片
    slot_refreshVideo(m_id,img);
    // 压缩
    QByteArray ba;
    QBuffer qbuf(&ba);// QBuffer 与 QByteArray 字节数组联立联系
    img.save(&qbuf,"JPEG",90);//将图片的数据写入 ba
    //写视频帧 发送
    int nPackSize = 6*sizeof(int)+ba.size();
    char * buf = new char[nPackSize];
    char *tmp =buf;

    *(int*)tmp = _DEF_PACK_VIDEO_FRAME;
    tmp+=sizeof(int);
    *(int*)tmp = m_id;
    tmp+=sizeof(int);
    *(int*)tmp = m_roomid;
    tmp+=sizeof(int);

    //用于舍弃一些延迟帧的参考时间
    QTime tm = QTime::currentTime();
    *(int*)tmp = tm.minute();
    tmp+=sizeof(int);
    *(int*)tmp = tm.second();
    tmp+=sizeof(int);
    *(int*)tmp = tm.msec();
    tmp+=sizeof(int);

    memcpy(tmp,ba.data(),ba.size());
    //发送是一个阻塞函数，如果服务器接收缓冲区由于数据量大，没及时取走缓冲区数据
    //滑动窗口变小 ,send 函数阻塞，影响用户界面响应，出现未响应问题(卡顿)
    //将视频发送，变为一个信号，放到另一个线程执行
//    m_pClient->SendData(0,buf,nPackSize);
//    delete [] buf;
    Q_EMIT SIG_SendVideo(buf,nPackSize);
}
//多线程发送视频帧
void Ckernel::slot_SendVideo(char *buf, int nlen)
{
    char * tmp = buf;
    tmp +=sizeof(int);
    tmp +=sizeof(int);
    tmp +=sizeof(int);

    int min = *(int*)tmp;
    tmp +=sizeof(int);
    int sec = *(int*)tmp;
    tmp +=sizeof(int);
    int msec = *(int*)tmp;
    tmp +=sizeof(int);

    //当前时间
    QTime ctm = QTime::currentTime();
    //数据包时间
    QTime tm(ctm.hour(),min,sec,msec);
    //如果数据包延迟超过300ms，舍弃
    if(tm.msecsTo(ctm)>300){
        qDebug()<<"sendfaile";
        delete[] buf;
        return ;
    }

    //m_pClient->SendData(0,buf,nlen);
    m_pAVClient[video_client]->SendData(0,buf,nlen);
    delete [] buf;
}

//桌面捕捉开始
void Ckernel::slot_startScreen()
{
    qDebug()<<__func__;
    m_pScreenRead->slot_openVideoScreen();
}
//桌面捕捉关闭
void Ckernel::slot_pauseScreen()
{
    qDebug()<<__func__;
    m_pScreenRead->slot_closeVideoScreen();
}

//MD5转换函数
static std::string GetMD5(QString value){
    QString str = QString("%1_%2").arg(value).arg(MD5_KEY);
    std::string strSrc = str.toStdString();
    MD5 md5(strSrc);
    return md5.toString();
}
//网络数据处理
void Ckernel::slot_dealData(unsigned int lSendIP, char *buf, int nlen)
{
    //qDebug()<<__func__;
    int type = *(int*)buf;
    if(type >= _DEF_PACK_BASE && type < _DEF_PACK_BASE+_DEF_CONTENT_SIZE){
        //根据协议头获取函数指针
        PFUN pf = NetPackMap(type);
        if(pf){
            (this->*pf)(lSendIP,buf,nlen);
        }
    }
    delete[] buf;
}
//发送注册信息：手机号，密码，昵称
void Ckernel::slot_RegisterCommit(QString tel, QString pass, QString name)
{
    qDebug()<<__func__;
    std::string strtel = tel.toStdString();
    std::string strname = name.toStdString();
    std::string strpassMD5 = GetMD5(pass);

    STRU_REGISTER_RQ rq;
    strcpy(rq.tel , strtel.c_str());
    strcpy(rq.name,strname.c_str());
    strcpy(rq.password , strpassMD5.c_str());

    m_pClient->SendData(0,(char*)&rq,sizeof(rq));
}
//处理注册回复
void Ckernel::slot_dealRegisterRs(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
    STRU_REGISTER_RS* rs = (STRU_REGISTER_RS*)buf;
    switch (rs->result) {
    case tel_is_exist:
        QMessageBox::about(m_pLoginDlg,"提示","手机号已存在，注册失败");
        break;
    case name_is_exist:
        QMessageBox::about(m_pLoginDlg,"提示","昵称已经存在");
        break;
    case register_success:
        QMessageBox::about(m_pLoginDlg,"提示","注册成功");
        break;
    default:break;

    }
}
//发送登录信息：手机号，密码
void Ckernel::slot_LoginCommit(QString tel, QString pass)
{
    qDebug()<<__func__;
    std::string strtel = tel.toStdString();
    std::string strpassMD5 = GetMD5(pass);
    //std::string strpass = pass.toStdString();

    STRU_LOGIN_RQ rq;
    strcpy(rq.tel , strtel.c_str());
    strcpy(rq.password , strpassMD5.c_str());

    m_pClient->SendData(0,(char*)&rq,sizeof(rq));
}
//处理登录回复
void Ckernel::slot_dealLoginRS(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
    STRU_LOGIN_RS* rs = (STRU_LOGIN_RS*)buf;
    switch(rs->result){
    case user_not_exist:
        QMessageBox::about(m_pLoginDlg,"提示","用户不存在，登录失败");
        break;
    case password_error:
        QMessageBox::about(m_pLoginDlg,"提示","密码错误，登陆失败");
        break;
    case login_success:
        {
            //QString strname = QString("用户[%1]登录成功").arg(rs->m_name);
            //QMessageBox::about(m_pLoginDlg,"提示",strname);
            m_id = rs->userid;
            m_name = QString::fromStdString(rs->m_name);
            m_pWeChatDlg->setInfo(m_name);
            m_pLoginDlg->hide();
            m_pWeChatDlg->showNormal();

            //注册视频和音频fd
            STRU_AUDIO_REGISTER rq_audio;
            rq_audio.m_nUserId=m_id;
            m_pAVClient[audio_client]->SendData(0,(char*)&rq_audio,sizeof(rq_audio));

            STRU_VIDEO_REGISTER rq_video;
            rq_video.m_nUserId=m_id;
            m_pAVClient[video_client]->SendData(0,(char*)&rq_video,sizeof(rq_video));
        }
        break;
    }
}
//处理创建房间回复
void Ckernel::slot_dealCreateRoomRS(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
    STRU_CREATEROOM_RS* rs = (STRU_CREATEROOM_RS*)buf;
    m_pRoomDlg->slot_setInfo(QString::number(rs->m_RoomID));
    //把自己的信息放到房间上todo
    UserShow * user = new UserShow;
    connect(user,SIGNAL(SIG_itemClicked(int,QString)),m_pRoomDlg,SLOT(slot_setBigImgID(int,QString)));
    user->slot_setInfo(m_id,m_name);
    m_pRoomDlg->slot_addUserShow(user);

    m_roomid=rs->m_RoomID;
    m_pRoomDlg->showNormal();

    //音频初始化
    m_pRoomDlg->slot_setAudioCheck(false);
    //视频初始化todo
    m_pRoomDlg->slot_setVedioCheck(false);


}
//处理加入房间回复
void Ckernel::slot_dealJoinRoomRS(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
    STRU_JOINROOM_RS* rs = (STRU_JOINROOM_RS*)buf;
    //判断房间号是否存在
    if(rs->m_lResult == 0){//房间号不存在
        QMessageBox::about(m_pWeChatDlg,"提示","房间id不存在，加入失败");
        return ;
    }
    //房间号存在
    //将房间号显示到界面，进行跳转
    m_pRoomDlg->slot_setInfo(QString::number(rs->m_RoomID));
    //跳转，roomid设置
    m_roomid = rs->m_RoomID;
    m_pRoomDlg->showNormal();

    //音频初始化
    m_pRoomDlg->slot_setAudioCheck(false);
    //视频初始化todo
    m_pRoomDlg->slot_setVedioCheck(false);

}
//房间成员处理请求
void Ckernel::slot_dealRoomMemberRq(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
    STRU_ROOM_MEMBER_RQ* rq = (STRU_ROOM_MEMBER_RQ*)buf;
    UserShow * user = new UserShow;
    user->slot_setInfo(rq->m_nUserId,QString::fromStdString(rq->szUser));
    connect(user,SIGNAL(SIG_itemClicked(int,QString)),m_pRoomDlg,SLOT(slot_setBigImgID(int,QString)));
    m_pRoomDlg->slot_addUserShow(user);
    //音频内容
    Audio_Write* aw = NULL;
    //为每个人创建一个播放音频的对象
    if(m_mapIDToAudioWrite.count(rq->m_nUserId) == 0){
        aw = new Audio_Write;
        m_mapIDToAudioWrite[rq->m_nUserId] = aw;
    }


}
//处理退出房间请求
void Ckernel::slot_dealLeaveRoomRq(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
    //拆包
    STRU_LEAVEROOM_RQ * rq = (STRU_LEAVEROOM_RQ*)buf;
    //把个人从ui上面去掉
    if(rq->m_Roomid ==m_roomid){
        m_pRoomDlg->slot_removeUserShow(rq->m_nUserId);
    }
    //for(auto ite = )
    //去掉对应的音频
    if(m_mapIDToAudioWrite.count(rq->m_nUserId)>0){
        Audio_Write * pAw = m_mapIDToAudioWrite[rq->m_nUserId];
        m_mapIDToAudioWrite.erase(rq->m_nUserId);
        delete pAw;
    }

}
//音频帧的处理
void Ckernel::slot_dealAudioFrameRq(unsigned int lSendIP, char *buf, int nlen)
{
    ///音频数据帧
    /// 成员描述
    /// int type;
    /// int userId;
    /// int roomId;
    /// int min;
    /// int sec;
    /// int msec;
    /// QByteArray audioFrame;
    ///
    char * tmp = buf;

    int userId  ;
    int roomId  ;

    tmp += sizeof(int);

    userId = *(int *)tmp;
    tmp += sizeof(int);

    roomId = *(int *)tmp;
    tmp += sizeof(int);

    //跳过时间
    tmp += sizeof(int);
    tmp += sizeof(int);
    tmp += sizeof(int);

    int nbuflen = nlen - 6*sizeof(int);
    QByteArray ba(tmp,nbuflen);
    if(m_roomid == roomId){
        if(m_mapIDToAudioWrite.count(userId) > 0){
            Audio_Write * aw = m_mapIDToAudioWrite[userId];
            //aw->slot_playAudio(ba);
            aw->slot_net_rx(ba);
        }
    }
}
//处理视频帧
void Ckernel::slot_dealVideoFrameRq(unsigned int lSendIP, char *buf, int nlen)
{
    char * tmp = buf;

    int userId  ;
    int roomId  ;

    tmp += sizeof(int);

    userId = *(int *)tmp;
    tmp += sizeof(int);

    roomId = *(int *)tmp;
    tmp += sizeof(int);

    //跳过时间
    tmp += sizeof(int);
    tmp += sizeof(int);
    tmp += sizeof(int);

    int nbuflen = nlen - 6*sizeof(int);
    QByteArray ba(tmp,nbuflen);
    QImage img;
    img.loadFromData(ba);
    if(m_roomid == roomId){
        m_pRoomDlg->slot_refreshUser(userId,img);
    }
}

























