#include "gatt_app.hpp"
#include <iostream>

GattApplication::GattApplication(sdbus::IConnection& conn, const std::string& path)
    : conn_(conn), path_(path)
{
    // TODO: implement GattService1 + GattCharacteristic1 here
}

void GattApplication::registerApplication()
{
    auto adapter = sdbus::createProxy(conn_, "org.bluez", "/org/bluez/hci0");
    adapter->callMethod("RegisterApplication")
        .onInterface("org.bluez.GattManager1")
        .withArguments(path_, std::map<std::string, sdbus::Variant>{});
    std::cout << "GATT app registered at " << path_ << "\n";
}
