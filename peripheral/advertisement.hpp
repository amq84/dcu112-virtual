#pragma once
#include <sdbus-c++/sdbus-c++.h>
#include <string>

class Advertisement {
public:
    Advertisement(sdbus::IConnection& conn, const std::string& path);
    void registerAdvertisement();

private:
    sdbus::IConnection& conn_;
    std::string path_;
};
