#include "advertisement.hpp"
#include <iostream>

Advertisement::Advertisement(sdbus::IConnection& conn, const std::string& path)
    : conn_(conn), path_(path)
{
    // TODO: implement org.bluez.LEAdvertisement1 interface here with UUID, type, etc.
}

void Advertisement::registerAdvertisement()
{
    auto adapter = sdbus::createProxy(conn_, "org.bluez", "/org/bluez/hci0");
    adapter->callMethod("RegisterAdvertisement")
        .onInterface("org.bluez.LEAdvertisingManager1")
        .withArguments(path_, std::map<std::string, sdbus::Variant>{});
    std::cout << "Advertisement registered at " << path_ << "\n";
}

