#ifndef _MYSQL_H
#define _MYSQL_H
#include "packdef.h"
#include <mysql/mysql.h>
#include<list>
#include<string>

using namespace  std;


class CMysql{
public:
    //建立连接
    int ConnectMysql(const char *server, const char *user, const char *password, const char *database);
    //查询
    int SelectMysql(char* szSql,int nColumn,list<string>& lst);
    //更新
    int UpdataMysql(char *szsql);
    //断开连接
    void DisConnect();
private:
    MYSQL *conn;

    pthread_mutex_t m_lock;
};
#endif
/*
 *
*/
