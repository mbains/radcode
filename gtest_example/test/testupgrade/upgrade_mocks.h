#include "gmock/gmock.h"
#include "find_upgrades_iface.h"
#include "upgrader_iface.h"

class MockFindUpgrades: public FindUpgradesIface
{
public:
    MockFindUpgrades(UpgraderIface & upgrader):FindUpgradesIface(upgrader){}; 
    MOCK_METHOD1(getUpgrades, void(UpgradeCol_t &));
    MOCK_METHOD1(selectUpgrade, int(int));
};

class UpgraderMock: public UpgraderIface 
{
public:
    MOCK_METHOD1(apply_upgrade, int(std::string));
    
};