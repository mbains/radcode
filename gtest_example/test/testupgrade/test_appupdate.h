/* 
 * File:   Test_AppUpdate.h
 * Author: mbai
 *
 * Created on July 30, 2015, 2:45 PM
 */

#ifndef TEST_APPUPDATE_H
#define	TEST_APPUPDATE_H

#include "gtest/gtest.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <jsonrpccpp/server/connectors/unixdomainsocketserver.h>
#include <jsonrpccpp/client/connectors/unixdomainsocketclient.h>
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <upgradeservice.h>
#include <jsonrpccpp/client.h>



class Test_Http: public ::testing::Test {
protected:
    Test_Http();
    virtual ~Test_Http();
    
    virtual void SetUp();
    
    virtual void TearDown();
    

    UpgradeService * m_rpc;
    HttpServer * m_server;
    HttpClient * m_httpClient;
    jsonrpc::Client * m_rpcClient;
};


class Test_UnixDomain: public ::testing::Test {
protected:
    Test_UnixDomain();
    virtual ~Test_UnixDomain();
    
    
    virtual void SetUp();
    
    virtual void TearDown();
    
    UpgradeService * m_rpc;
    UnixDomainSocketServer * m_server;
    UnixDomainSocketClient * m_client;
    jsonrpc::Client * m_rpcClient;   
};

class Test_install_from_fs: public Test_Http {
public:
    Test_install_from_fs(){};
    virtual void SetUp();
    virtual void TearDown();
    virtual ~Test_install_from_fs(){};
private:

};

class Test_install_from_web: public ::testing::Test {
public:
    virtual void SetUp();
    virtual void TearDown();
    virtual ~Test_install_from_web(){};
};

#endif	/* TEST_APPUPDATE_H */

