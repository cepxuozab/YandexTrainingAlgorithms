#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Device {
public:
    Device(long long k, long long n) {
        updates = vector<bool>(k, false);
        valuable = vector<long long>(n, 0);
        requests = vector<Device *>();
        countPartOfUpdates = 0;
        nowNeedpartOfUpdate = -1;
        iters = 0;
        indexInDevices = devices.size();
        myRequestOK = false;
        idDeviceRequest = -1;
        devices.push_back(this);
    }

    void choose_part_of_update() {
        nowNeedpartOfUpdate = -1;
        long long minCountUpdates = std::numeric_limits<long long>::max();
        for (size_t i = 0; i < updates.size(); ++i) {
            if (!updates[i] && commonUpdates[i] < minCountUpdates) {
                minCountUpdates = commonUpdates[i];
                nowNeedpartOfUpdate = i;
            }
        }
        if (nowNeedpartOfUpdate != -1) {
            ++iters;
        }
    }

    void choose_device_who_have_part_of_update() {
        if (nowNeedpartOfUpdate == -1) {
            return;
        }
        long long minDownloadUpdates = std::numeric_limits<long long>::max();
        Device *deviceRequest = nullptr;
        for (auto *dev: devices) {
            if (dev->updates[nowNeedpartOfUpdate]) {
                if (dev->countPartOfUpdates < minDownloadUpdates) {
                    deviceRequest = dev;
                    minDownloadUpdates = dev->countPartOfUpdates;
                }
            }
        }
        if (deviceRequest != nullptr) {
            deviceRequest->requests.push_back(this);
        }
    }

    void choose_request() {
        long long minCountPartOfUpdates = std::numeric_limits<long long>::max();
        long long iOkDevice = -1;
        long long maxValuable = -1;
        for (size_t i = 0; i < this->requests.size(); ++i) {
            Device *dev = requests[i];
            if (valuable[dev->indexInDevices] > maxValuable) {
                iOkDevice = dev->indexInDevices;
                minCountPartOfUpdates = dev->countPartOfUpdates;
                maxValuable = valuable[dev->indexInDevices];
            } else if (valuable[dev->indexInDevices] == maxValuable) {
                if (minCountPartOfUpdates > dev->countPartOfUpdates) {
                    iOkDevice = dev->indexInDevices;
                    minCountPartOfUpdates = dev->countPartOfUpdates;
                }
            }
        }
        this->requests.clear();
        if (iOkDevice != -1) {
            Device *dev = devices[iOkDevice];
            dev->myRequestOK = true;
            dev->idDeviceRequest = this->indexInDevices;
        }
    }

    void request_OK() {
        if (!myRequestOK)
            return;
        ++countPartOfUpdates;
        updates[nowNeedpartOfUpdate] = true;
        ++commonUpdates[nowNeedpartOfUpdate];
        ++valuable[idDeviceRequest];
        myRequestOK = false;
    }

    static vector<Device *> devices;
    static vector<long long> commonUpdates;
    vector<bool> updates;
    vector<long long> valuable;
    vector<Device *> requests;
    bool myRequestOK;
    int idDeviceRequest;
    long long countPartOfUpdates;
    long long nowNeedpartOfUpdate;
    long long iters;
    long long indexInDevices;
};

vector<Device *> Device::devices;
vector<long long> Device::commonUpdates;


auto decide(long long n, long long k) -> vector<long long> {
    Device::devices = vector<Device *>();
    Device::commonUpdates = vector<long long>(k, 1);
    for (long long i = 0; i < n; ++i) {
        [[maybe_unused]] auto *dev = new Device(k, n);
    }
    Device::devices[0]->countPartOfUpdates = k;
    Device::devices[0]->updates = vector<bool>(k, true);
    while (true) {
        long long thisIsEnd = 0;
        for (Device *dev: Device::devices) {
            if (dev->countPartOfUpdates == k) {
                thisIsEnd += 1;
                continue;
            }
            dev->choose_part_of_update();
        }
        if (thisIsEnd == n) {
            break;
        }

        for (Device *dev: Device::devices) {
            if (dev->countPartOfUpdates == k)
                continue;
            dev->choose_device_who_have_part_of_update();
        }
        for (Device *dev: Device::devices) {
            if (dev->requests.size() == 0)
                continue;
            dev->choose_request();
        }
        for (Device *dev: Device::devices) {
            if (!dev->myRequestOK) {
                continue;
            }
            dev->request_OK();
        }
    }

    vector<long long> ans;
    for (Device *dev: Device::devices) {
        ans.push_back(dev->iters);
    }
    for (Device *dev: Device::devices) {
        delete dev;
    }
    return ans;
}


auto main() -> int {

    long long n, k;
    std::cin >> n >> k;

    vector<long long> v = decide(n, k);
    for (size_t i = 1; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }

    return 0;
}