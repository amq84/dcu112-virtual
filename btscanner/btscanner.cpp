#include "btscanner.hpp"
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

std::vector<BTDevice> BTScanner::scanAdapters() {
    std::vector<BTDevice> devices;
    int max_devs = 16;

    for (int dev_id = 0; dev_id < max_devs; ++dev_id) {
        int sock = hci_open_dev(dev_id);
        if (sock < 0) continue;

        char name[248] = {0};
        if (hci_read_local_name(sock, sizeof(name), name, 0) < 0) {
            strcpy(name, "Unknown");
        }

        bdaddr_t bdaddr;
        if (hci_devba(dev_id, &bdaddr) < 0) {
            close(sock);
            continue;
        }

        char addr[19] = {0};
        ba2str(&bdaddr, addr);

        devices.push_back({dev_id, name, addr});
        close(sock);
    }

    return devices;
}
