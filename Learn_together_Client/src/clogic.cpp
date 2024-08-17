#include "clogic.h"

void CLogic::setNetPackMap()
{
    NetPackMap(_DEF_PACK_REGISTER_RQ)    = &CLogic::RegisterRq;
    NetPackMap(_DEF_PACK_LOGIN_RQ)       = &CLogic::LoginRq;
    NetPackMap(_DEF_PACK_CREATEROOM_RQ)    = &CLogic::CreateRoomRq;
    NetPackMap(_DEF_PACK_JOINROOM_RQ)       = &CLogic::JoinRoomRq;
    NetPackMap(DEF_PACK_LEAVERROOM_RQ)      =&CLogic::LeaveRoomRq;
}

#define _DEF_COUT_FUNC_    cout << "clientfd:"<< clientfd << __func__ << endl;

//注册
void CLogic::RegisterRq(sock_fd clientfd,char* szbuf,int nlen)
{
    cout << "clientfd:"<< clientfd << __func__ << endl;
    STRU_REGISTER_RQ* rq = (STRU_REGISTER_RQ*)szbuf;
    STRU_REGISTER_RS rs;

    char sqlStr[1024] = {0};
    sprintf(sqlStr,"select tel from t_user where tel = '%s';",rq->tel);
    list<string> resList;
    if(!m_sql->SelectMysql(sqlStr,1,resList)){
        printf("SelectMysql error: %s\n",sqlStr);
        return;
    }
    else{
        printf("CLogic::RegisterRq: select tel sucess;\n");
    }


    if(resList.size() >0){
        rs.result = tel_is_exist;
    }
    else{
        char sqlStr[1024] = "";

        sprintf(sqlStr,"select name from t_user where name = '%s';",rq->name);
        resList.clear();
        if(!m_sql->SelectMysql(sqlStr,1,resList)){
            printf("select error: %s \n",sqlStr);
            return;
        }
        else{
            printf("CLogic::RegisterRq: select name sucess\n");
        }

        if(resList.size()>0){
            rs.result = name_is_exit;
        }
        else{
            sprintf(sqlStr,"insert into t_user (tel,password,name,icon,feeling) values ('%s','%s','%s',%d,'%s');",rq->tel,rq->password,rq->name,1,"feeling.....");
            if(!m_sql->UpdataMysql(sqlStr)){
                printf("updataMysql error: %s\n",sqlStr);
            }
            else{
                rs.result = register_success;
                printf("user resgin sucess...\n");
            }
        }
    }
    m_tcp->SendData(clientfd,(char*)&rs,sizeof(rs));
}

//登录
void CLogic::LoginRq(sock_fd clientfd ,char* szbuf,int nlen)
{
    cout << "clientfd:"<< clientfd << __func__ << endl;
    STRU_LOGIN_RQ* rq = (STRU_LOGIN_RQ*)szbuf;
    STRU_LOGIN_RS rs;
    char strSql[1024]="";
    list<string> lstRes;
    sprintf(strSql,"select password,id,name from t_user where tel = '%s';"
            ,rq->tel);
    if(!m_sql->SelectMysql(strSql,3,lstRes)){
        printf("select error:%s\n",strSql);
        return;
    }
    if(lstRes.size()==0){
        //return
        rs.result = user_not_exist;
    }
    else{
        if(strcmp(rq->password,lstRes.front().c_str())!=0){
            qDebug()<<rq->password;
            qDebug()<<lstRes.front().c_str();
            rs.result = password_error;
        }
        else{
            lstRes.pop_front();
            int id =atoi(lstRes.front().c_str());
            lstRes.pop_front();

            UserInfo* pInfo = new UserInfo;
            pInfo->m_id = id;
            pInfo->m_roomid = 0;
            pInfo->m_sockfd = clientfd;
            strcpy(pInfo->m_userName,lstRes.front().c_str());

            lstRes.pop_front();

            //判断当前id用户是否在线，在线就强制下线，不在线就添加
            if(m_mapIdToUserInfo.IsExist(pInfo->m_id)){
                //强制下线
                //TODO:
                //远程发送命令，给当前客户端，强制回收

            }
            m_mapIdToUserInfo.insert(pInfo->m_id,pInfo);
            rs.userid = id;
            rs.result = login_success;
            strcpy(rs.m_name,pInfo->m_userName);
        }
    }
    m_tcp->SendData(clientfd,(char*)&rs,sizeof(rs));
}

//create room
void CLogic::CreateRoomRq(sock_fd clientfd, char *szbuf, int nlen)
{
    qDebug()<<__func__;
    STRU_CREATEROOM_RQ* rq = (STRU_CREATEROOM_RQ*)szbuf;
    //1-8的随机数
    int roomID = 0;
    do{
        //
        //1-9999999
        roomID = rand()%99999999 + 1;
    }while(m_mapIDtoRoomId.IsExist(roomID));
    //把链表给他加进去
    list<int> lst;
    lst.push_back(rq->m_UserID);
    printf("room id = %d\n",roomID);
    //随机数 得到房间号，看看有没有房间号，可能循环随机 map roomid -> list
    m_mapIDtoRoomId.insert(roomID,lst);
    STRU_CREATEROOM_RS rs;
    rs.m_RoomId = roomID;
    rs.m_lResult = 1;
    ///?????????????//// update room remember roomid
    /// // chinese input fail

    m_tcp->SendData(clientfd,(char*)&rs,sizeof(rs));

}

//join room
void CLogic::JoinRoomRq(sock_fd clientfd, char *szbuf, int nlen)
{
//    qDebug()<<__func__;
    printf("clientfd:%d JoinRoomRq\n",clientfd);
    //拆包
    STRU_JOINROOM_RQ* rq = (STRU_JOINROOM_RQ*)szbuf;
    STRU_JOINROOM_RS rs;
    //查看房间是否存在
    printf("RoomID:%d\n",rq->m_RoomID);
    if(!m_mapIDtoRoomId.IsExist(rq->m_RoomID)){
        rs.m_lResult = 0;
        m_tcp->SendData(clientfd,(char*)&rs,sizeof(rs));
        return;
    }
    //存在返回成功
    rs.m_lResult = 1;
    /////////////???????????????????????????

    rs.m_RoomID = rq->m_RoomID;
    //根据房间号拿到房间成员的列表
    m_tcp->SendData(clientfd,(char*)&rs,sizeof(rs));
    //////////////?????????????????
    if( ! m_mapIdToUserInfo.IsExist(rq->m_UserID))return;
    UserInfo* joiner = m_mapIdToUserInfo.find(rq->m_UserID);

    STRU_ROOM_MEMBER_RQ joinRq;
    joinRq.m_UserID = rq->m_UserID;
    //段错误核心转储
    //strcpy(joinRq.m_szUSer,joiner->m_userName);
    strcpy(joinRq.m_szUSer,joiner->m_userName);
    //pack to myself
    m_tcp->SendData(clientfd,(char*)&joinRq,sizeof(joinRq));

    list<int> lstRoomMember = m_mapIDtoRoomId.find(rq->m_RoomID );
    //遍历列表--->互换信息
    for(auto ite = lstRoomMember.begin();ite != lstRoomMember.end();++ite){
        int MemberId = *ite;
        //用户不在线，就不将其加入了
        if(!m_mapIdToUserInfo.IsExist(MemberId)) continue;
        //把加入人的信息发送给每一个房间内成员
        UserInfo* memBerInfo = m_mapIdToUserInfo.find(MemberId);
        STRU_ROOM_MEMBER_RQ memRq;
        memRq.m_UserID = memBerInfo->m_id;
        strcpy(memRq.m_szUSer,memBerInfo->m_userName);

        m_tcp->SendData(memBerInfo->m_sockfd,(char*)&joinRq,sizeof(joinRq));
        //房间内成员每个人信息发给加入人
        m_tcp->SendData(clientfd,(char*)&memRq,sizeof(memRq));
    }
    //加入人添加到房间列表
    lstRoomMember.push_back(rq->m_UserID);
    m_mapIDtoRoomId.insert(rq->m_RoomID,lstRoomMember);
}
//leave room
void CLogic::LeaveRoomRq(sock_fd clientfd, char *szbuf, int nlen)
{
    //拆包
    STRU_LEAVEROOM_RQ* rq = (STRU_LEAVEROOM_RQ*)szbuf;
    //查看房间是否存在
    if(!m_mapIDtoRoomId.IsExist(rq->m_Roomid))return;
    //如果房间存在，可以获得用户列表
    list<int> lst = m_mapIDtoRoomId.find(rq->m_Roomid);
    //遍历每个用户
    for(auto ite = lst.begin();ite!=lst.end();){
        int userid = *ite;
        //如果是自己， 从列表中取出 ---从房间移除了
        if(userid == rq->m_nUserID){
            ite = lst.erase(ite);
        }
        else{
            //用户是否在线，在线转发
            if(m_mapIdToUserInfo.IsExist(userid)){
                UserInfo* info = m_mapIdToUserInfo.find(userid);
                m_tcp->SendData(info->m_sockfd,szbuf,nlen);
            }
            ++ite;
        }
    }
    //列表生是否节点数为0,-》map项去掉
    if(lst.size()==0){
        m_mapIDtoRoomId.erase(rq->m_Roomid);
    }
    //更新房间成员列表
    m_mapIDtoRoomId.insert(rq->m_Roomid,lst);
}
void CLogic::AudioFrameRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("---------------------CLogic::AudioFrameRq--------------------------\n");
    printf("client:%d CLogic::AudioFrameRq\n",clientfd);
    //拆包
   char* temp = szbuf;
   //跳过type
   temp += sizeof(int);
   //跳过userid
   int uid = *(int*)temp;
   temp += sizeof(int);
   //获取roomid
   int roomid = *(int*)temp;//按照int获取数据
   //查看房间是否醋在奶
   if(!m_mapIDtoRoomId.IsExist(roomid)){
       return;
   }
   list<int> lst = m_mapIDtoRoomId.find(roomid);
   //获取成员列表
   for(auto ite = lst.begin();ite!= lst.end();++ite){
       int userid = *ite;
       /*屏蔽掉自己不转发*/
       if(uid == userid) continue;
       if(!m_mapIdToUserInfo.IsExist(userid))continue;
       UserInfo* usif = m_mapIdToUserInfo.find(userid);
       //原样转发
       //m_tcp->SendData(usif->m_Audiofd,szbuf,nlen);
       m_tcp->SendData(clientfd,szbuf,nlen);
   }
}

void CLogic::VideoFrameRq(sock_fd clientfd, char *szbuf, int nlen)
{
    printf("---------------------CLogic::VideoFrameRq--------------------------\n");
    printf("client:%d CLogic::AudioFrameRq\n",clientfd);
    //拆包
    char* temp = szbuf;
    //跳过type
    temp += sizeof(int);
    //读取userid
    int myid = *(int*)temp;
    //跳过userid
    temp += sizeof(int);
    //获取roomid
    int roomid = *(int*)temp;//按照int获取数据
    temp += sizeof(int);

    //查看房间是否醋在奶
    if(!m_mapIDtoRoomId.IsExist(roomid)){
        return;
    }
    list<int> lst = m_mapIDtoRoomId.find(roomid);
    //获取成员列表
    for(auto ite = lst.begin();ite!= lst.end();++ite){
        int userid = *ite;
        //屏蔽掉自己不转发
        printf("myid:%d---userid:%d\n",myid,userid);
        if(myid == userid) continue;
        if(!m_mapIdToUserInfo.IsExist(userid))continue;
        UserInfo* userinfo = m_mapIdToUserInfo.find(userid);
        //原样转发
        printf("send to m_socked:%d\n",userinfo->m_sockfd);
        //m_tcp->SendData(userinfo->m_videofd,szbuf,nlen);
    }
}

//void CLogic::AudioRegister(int clientfd, char *szbuf, int nlen)
//{
//    printf("client:%d CLogic::AudioRegister\n",clientfd);
//    //拆包
//    STRU_AUDIO_REGISTER *rq = (STRU_AUDIO_REGISTER*)szbuf;
//    int userid = rq->m_nUserId;
//    //根据 userid 找到节点 更新fd
//    if(m_mapIdToUserInfo.IsExist(userid)){
//        UserInfo* info = m_mapIdToUserInfo.find(userid);
//        info->m_audiofd = clientfd;
//    }
//}

//void CLogic::VideoRegister(int clientfd, char *szbuf, int nlen)
//{
//    printf("client:%d CLogic::VideoRegister\n",clientfd);
//    //拆包
//    STRU_VIDEO_REGISTER *rq = (STRU_VIDEO_REGISTER*)szbuf;
//    int userid = rq->m_nUserId;
//    //根据 userid 找到节点 更新fd
//    if(m_mapIdToUserInfo.IsExist(userid)){
//        UserInfo* info = m_mapIdToUserInfo.find(userid);
//        info->m_videofd = clientfd;
//    }
//}
