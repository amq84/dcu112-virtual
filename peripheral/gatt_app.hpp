#pragma once
#include <sdbus-c++/sdbus-c++.h>
#include <string>

class GattApplication {
public:
    GattApplication(sdbus::IConnection& conn, const std::string& path);
    void registerApplication();

private:
    sdbus::IConnection& conn_;
    std::string path_;
};
