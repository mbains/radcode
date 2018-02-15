/* 
 * File:   Test_AppUpdate.cpp
 * Author: mbai
 * 
 * Created on July 30, 2015, 2:45 PM
 */

#include "test_appupdate.h"
#include "upgrade_mocks.h"
#include "InstallFromFS.h"
#include "libos_exec.h"
#include "InstallFromWeb.h"
#include <cstddef>
#include <iostream>

using ::testing::Return;
using ::testing::_;
using ::testing::SetArgReferee;


namespace appupdate{
    void SearchFilesAPI(UpgradeService * upgrade_service, jsonrpc::Client * rpc_client) 
    {
        UpgradeCol_t available_upgrades;
        int total_packages = 1000;

        Json::Value params;

        UpgraderMock upgrader;
        MockFindUpgrades mock_finder(upgrader);

        upgrade_service->setFinder(&mock_finder);

        //Add a bunch of files
        for(int i = 0; i < total_packages; i++) {
            std::string upgrade = "/mnt/usb/bundle" + std::to_string(i) + ".deb";
            available_upgrades.push_back(upgrade);
        }


        EXPECT_CALL(mock_finder, getUpgrades(_))
        .Times(1)
        .WillRepeatedly(SetArgReferee<0>(available_upgrades));


        //make sure we get the file names back
        Json::Value json_result = rpc_client->CallMethod("searchForFiles", params);
        for(int i = 0; i < total_packages; i++) {
            ASSERT_EQ(available_upgrades.at(i), json_result[i].asString());
        }
    }
    
    void StartUpgradeAPI(UpgradeService * upgrade_service, jsonrpc::Client * rpc_client)
    {
        int dummy_return_value = 42;
    
        Json::Value params;


        UpgraderMock upgrader;
        MockFindUpgrades mock_finder(upgrader);

        upgrade_service->setFinder(&mock_finder);

        EXPECT_CALL(mock_finder, selectUpgrade(0))
        .Times(1)
        .WillRepeatedly(Return(dummy_return_value));

        params["idx"] = 0;
        Json::Value json_result = rpc_client->CallMethod("startUpgrade", params);

        ASSERT_EQ(dummy_return_value, json_result["status"].asInt());
    }
}


Test_Http::Test_Http() :
    m_httpClient(NULL),
    m_rpcClient(NULL),
    m_server(NULL),
    m_rpc(NULL)
{
}


Test_Http::~Test_Http()
{
}

void Test_Http::SetUp() 
{
    m_server = new HttpServer(8385);
    m_rpc = new UpgradeService(*m_server);
    
    std::cout << __func__ << " starting new client\n";
    m_httpClient = new HttpClient("http://localhost:8385");
    
    std::cout << __func__ << " Setting up server\n";
    m_rpcClient = new jsonrpc::Client(*m_httpClient);
    
    m_rpc->StartListening();
    
}

void Test_Http::TearDown() 
{
    std::cout << __func__ << " shutting down server\n";
    m_rpc->StopListening();

    delete m_rpcClient;
    delete m_httpClient;
    delete m_rpc;
    delete m_server;
}



Test_UnixDomain::Test_UnixDomain():
    m_client(NULL),
    m_rpcClient(NULL),
    m_server(NULL),
    m_rpc(NULL)
{
    
}

Test_UnixDomain::~Test_UnixDomain()
{
    
}

void Test_UnixDomain::SetUp() 
{
    m_server = new UnixDomainSocketServer("/tmp/unixsocket");
    m_rpc = new UpgradeService(*m_server);
    
    std::cout << __func__ << " starting new client\n";
    m_client = new UnixDomainSocketClient("/tmp/unixsocket");
    
    std::cout << __func__ << " Setting up server\n";
    m_rpcClient = new jsonrpc::Client(*m_client);
    
    m_rpc->StartListening();
    
}

void Test_UnixDomain::TearDown() 
{
    std::cout << __func__ << " shutting down server\n";
    m_rpc->StopListening();

    delete m_rpcClient;
    delete m_client;
    delete m_rpc;
    delete m_server;
}


void Test_install_from_fs::SetUp() 
{
    Test_Http::SetUp();
    
    GetCommandOutput cmd;

    std::string output;
    
    ASSERT_EQ(0, cmd.cmd_run("mkdir -p test/outputfiles", output));
    
    
    ASSERT_EQ(0, cmd.cmd_run("sync", output));

    ASSERT_EQ(0, cmd.cmd_run("touch test/outputfiles/upgrade1.deb", output));
    ASSERT_EQ(0, cmd.cmd_run("touch test/outputfiles/upgrade2.deb", output));
    ASSERT_EQ(0, cmd.cmd_run("touch test/outputfiles/upgrade3.deb", output));
    ASSERT_EQ(0, cmd.cmd_run("touch test/outputfiles/upgrade4.deb", output));
    
}

void Test_install_from_fs::TearDown() 
{
    
    Test_Http::TearDown();
    
    GetCommandOutput cmd("rm -r test/outputfiles/");

    std::string output;
    
    ASSERT_EQ(0, cmd.run(output));
    
}

TEST_F(Test_Http, HTTPSearchFilesAPI) 
{
    appupdate::SearchFilesAPI(m_rpc, m_rpcClient);
}

TEST_F(Test_Http, HTTPStartUpgradeAPI) 
{
    appupdate::StartUpgradeAPI(m_rpc, m_rpcClient);
}


TEST_F(Test_UnixDomain, SearchFilesAPI) 
{
    appupdate::SearchFilesAPI(m_rpc, m_rpcClient);
}

TEST_F(Test_UnixDomain, StartUpgradeAPI) 
{
    appupdate::StartUpgradeAPI(m_rpc, m_rpcClient);
}


TEST_F(Test_install_from_fs, TestFindDebs) 
{

    UpgraderMock upgrader;
    Json::Value params;
    InstallFromFS fs(upgrader, ".", boost::regex("(.*deb)"));

    UpgradeCol_t col; 
    fs.getUpgrades(col);

    for(auto item: col) {
        std::cout << item << std::endl;
    }
    

    m_rpc->setFinder(&fs);
 
//    //make sure we get the file names back
    Json::Value json_result = m_rpcClient->CallMethod("searchForFiles", params);
    int indx = 0;
    for(Json::Value val: json_result) {
        
        ASSERT_EQ(col.at(indx++), val.asString());
    }
    std::cout << "Found " << indx << " debians \n";
}

TEST_F(Test_install_from_fs, SelectDebian) 
{
    UpgraderMock upgrader;
    Json::Value params;
    InstallFromFS fs(upgrader, ".", boost::regex("(.*deb)"));

    UpgradeCol_t col; 
    fs.getUpgrades(col);
    
    
    int dummy_return_value = 42;
    
    m_rpc->setFinder(&fs);

    
    EXPECT_CALL(upgrader, apply_upgrade("./test/outputfiles/upgrade1.deb"))
    .Times(1)
    .WillRepeatedly(Return(dummy_return_value));
    EXPECT_CALL(upgrader, apply_upgrade("./test/outputfiles/upgrade2.deb"))
    .Times(1)
    .WillRepeatedly(Return(dummy_return_value+1));
    EXPECT_CALL(upgrader, apply_upgrade("./test/outputfiles/upgrade3.deb"))
    .Times(1)
    .WillRepeatedly(Return(dummy_return_value+2));
    EXPECT_CALL(upgrader, apply_upgrade("./test/outputfiles/upgrade4.deb"))
    .Times(1)
    .WillRepeatedly(Return(dummy_return_value+3));
    
    
    Json::Value json_result = m_rpcClient->CallMethod("searchForFiles", params);
    

    for(int i = 0; i < 4; i++) {
        params["idx"] = i;
        json_result = m_rpcClient->CallMethod("startUpgrade", params);

        ASSERT_EQ(dummy_return_value + i, json_result["status"].asInt());
    }
    
    //out of bounds test
    params["idx"] = 4;
    json_result = m_rpcClient->CallMethod("startUpgrade", params);

    ASSERT_EQ(-1, json_result["status"].asInt());
}

void Test_install_from_web::SetUp() 
{
    
}

void Test_install_from_web::TearDown() 
{
    
}

//TEST_F(Test_install_from_web, Fetch_upgrades) {
//    UpgraderMock upgrader;
//    
//    InstallFromWeb wb(upgrader, "http://localhost:8888");
//    UpgradeCol_t upgrades;
//    wb.getUpgrades(upgrades);
//    ASSERT_EQ(0, wb.selectUpgrade(0));
//}
