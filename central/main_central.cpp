#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "btscanner.hpp"


int main()
{

    BTScanner scanner;
    auto devices = scanner.scanAdapters();
    std::cout << "Found " << devices.size() << " Bluetooth adapters:\n";
    for (const auto& dev : devices) {
        std::cout << "ID: " << dev.id << ", Name: " << dev.name << ", Address: " << dev.address << "\n";
    }   
    if (devices.empty()) {
        std::cerr << "No Bluetooth adapters found.\n";
        return 1;
    } 

    std::string hciPath = "/org/bluez/hci" + std::to_string(devices[0].id);

    auto conn = sdbus::createSystemBusConnection();
    auto adapter = sdbus::createProxy(*conn, "org.bluez", "hciPath");

    adapter->callMethod("StartDiscovery").onInterface("org.bluez.Adapter1").dontExpectReply();
    std::cout << "Central: scanning...\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Replace with your peripheral MAC address
    std::string devPath = "/org/bluez/hci0/dev_XX_XX_XX_XX_XX_XX";
    auto devProxy = sdbus::createProxy(*conn, "org.bluez", devPath);
    devProxy->callMethod("Connect").onInterface("org.bluez.Device1").dontExpectReply();
    std::cout << "Central: connecting...\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Example path to a characteristic (check with `gdbus introspect`)
    std::string charPath = devPath + "/serviceXXXX/charYYYY";
    auto proxy = sdbus::createProxy(*conn, "org.bluez", charPath);
    std::map<std::string, sdbus::Variant> options;

    // Read the characteristic value
    std::vector<uint8_t> value;
    proxy->callMethod("ReadValue")
        .onInterface("org.bluez.GattCharacteristic1")
        .withArguments(std::map<std::string, sdbus::Variant>{})
        .storeResultsTo(value);

    std::cout << "Read value: ";
    for (auto b : value)
        std::cout << std::hex << static_cast<int>(b) << " ";
    std::cout << std::dec << std::endl;

}
