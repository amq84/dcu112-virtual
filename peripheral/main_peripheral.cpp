#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include "gatt_app.hpp"
#include "advertisement.hpp"

int main()
{
    auto connection = sdbus::createSystemBusConnection();

    Advertisement adv(*connection, "/com/example/adv");
    adv.registerAdvertisement();

    GattApplication app(*connection, "/com/example/gatt");
    app.registerApplication();

    std::cout << "Peripheral running. Advertising...\n";
    connection->enterEventLoop();
}
