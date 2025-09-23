#pragma once
#include <vector>
#include <string>

struct BTDevice {
    int id;
    std::string name;
    std::string address;
};

class BTScanner {
public:
    static std::vector<BTDevice> scanAdapters();
};
