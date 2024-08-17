#ifndef CLOGIC_H
#define CLOGIC_H

#include"TCPKernel.h"
#include <stdio.h>
#include <string.h>
#include <list>

class CLogic
{
public:
    CLogic( TcpKernel* pkernel )
    {
        m_pKernel = pkernel;
        m_sql = pkernel->m_sql;
        m_tcp = pkernel->m_tcp;
    }
public:
    //设置协议映射
    void setNetPackMap();
    /************** 发送数据*********************/
    void SendData( sock_fd clientfd, char*szbuf, int nlen )
    {
        m_pKernel->SendData( clientfd ,szbuf , nlen );
    }
    /************** 网络处理 *********************/
    //注册
    void RegisterRq(sock_fd clientfd, char*szbuf, int nlen);
    //登录
    void LoginRq(sock_fd clientfd, char*szbuf, int nlen);

    /*************** create/join room *********************/
    //create room
    void CreateRoomRq(sock_fd clientfd,char* szbuf,int nlen);
    //join room
    void JoinRoomRq(sock_fd clientfd,char* szbuf,int nlen);
    //leave room
    void LeaveRoomRq(sock_fd clientfd,char* szbuf,int nlen);
    
    void AudioFrameRq(sock_fd clientfd,char* szbuf,int nlen);
    void VideoFrameRq(sock_fd clientfd,char* szbuf,int nlen);
    
    void AudioRegister(sock_fd clientfd,char* szbuf,int nlen);
    void VideoRegister(sock_fd clientfd,char* szbuf,int nlen);
    

private:
    TcpKernel* m_pKernel;
    CMysql * m_sql;
    Block_Epoll_Net * m_tcp;

    //STL map 不是线程安全的 ，需要加锁避免添加移除元素出现问题
    MyMap<int ,UserInfo*> m_mapIdToUserInfo;
    MyMap<int,list<int>> m_mapIDtoRoomId;
};

#endif // CLOGIC_H
