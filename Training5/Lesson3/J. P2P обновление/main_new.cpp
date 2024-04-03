#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

struct Response {
    int from_id{};
    int to_id{};
    int part_id{};
};
struct Request {
    int from_id{};
    int part_id{};
};


struct Network;

struct Device {
    int id{};
    std::vector<bool> is_part_downloaded;
    int downloaded_parts_count{};
    std::vector<int> other_id_to_worth;
    Network &network;
    std::vector<Request> requests;
    int time{};

    Device(int id_, Network &network1, bool value = false);

    void SendRequest();

    void AddRequest(int device_id, int part_id);

    void HandleResponse(int device_id, int part_id);

    void HandleRequests();
};


struct Network {
    std::vector<Device> devices;
    std::vector<int> parts_count;
    int n{};
    int k{};
    std::vector<Response> responses;

    Network(int n_, int k_);

    void HandleResponses();

    void SendRequests();

    void HandleRequests();
};


Device::Device(int id_, Network &network1, bool value) : id(id_), network(network1) {
    is_part_downloaded.resize(network.k, value);
    downloaded_parts_count = value ? network.k : 0;
    other_id_to_worth.resize(network.n, 0);
}

void Device::SendRequest() {
    if (downloaded_parts_count == network.k) {
        return;
    }
    int part_id = std::find(is_part_downloaded.begin(), is_part_downloaded.end(), false) - is_part_downloaded.begin();
    auto part_count = network.parts_count[part_id];
    for (auto part: std::ranges::iota_view(part_id + 1, network.k)) {
        if (is_part_downloaded[part]) {
            continue;
        }
        if (network.parts_count[part] < part_count) {
            part_count = network.parts_count[part];
            part_id = part;
        }
    }
    auto *best_device = &network.devices[0];
    for (auto &device: network.devices) {
        if (device.is_part_downloaded[part_id] &&
            device.downloaded_parts_count < best_device->downloaded_parts_count) {
            best_device = &device;
        }
    }
    best_device->AddRequest(id, part_id);
    time += 1;
}

void Device::AddRequest(int device_id, int part_id) {
    requests.push_back(Request(device_id, part_id));
}

void Device::HandleResponse(int device_id, int part_id) {
    is_part_downloaded[part_id] = true;
    network.parts_count[part_id] += 1;
    downloaded_parts_count += 1;
    other_id_to_worth[device_id] += 1;
}

void Device::HandleRequests() {
    if (requests.empty()) {
        return;
    }
    auto best_request = requests[0];
    for (auto &request: requests) {
        if (other_id_to_worth[request.from_id] > other_id_to_worth[best_request.from_id]) {
            best_request = request;
        } else if (other_id_to_worth[request.from_id] == other_id_to_worth[best_request.from_id]) {
            if (network.devices[request.from_id].downloaded_parts_count <
                network.devices[best_request.from_id].downloaded_parts_count) {
                best_request = request;
            }
        }
    }
    requests.clear();
    network.responses.push_back(Response(id, best_request.from_id, best_request.part_id));
}

Network::Network(int n_, int k_) : parts_count(k_, 1), n(n_), k(k_) {
}

void Network::HandleResponses() {
    for (auto &response: responses) {
        devices[response.to_id].HandleResponse(response.from_id, response.part_id);
    }
    responses.clear();
}

void Network::SendRequests() {
    for (auto &device: devices) {
        device.SendRequest();
    }

}

void Network::HandleRequests() {
    for (auto &device: devices) {
        device.HandleRequests();
    }
}

auto Check(Network const &network, int k) -> bool {
    for (auto &device: network.devices) {
        if (device.downloaded_parts_count != k) {
            return false;
        }
    }
    return true;
}

auto PeerToPeer(int n, int k) -> std::vector<int> {
    auto network = Network(n, k);
    network.devices.emplace_back(0, network, true);
    for (int i: std::ranges::iota_view(1, n)) {
        network.devices.emplace_back(i, network);
    }
    while (not Check(network, k)) {
        network.SendRequests();
        network.HandleRequests();
        network.HandleResponses();
    }
    std::vector<int> ans;
    for (int i: std::ranges::iota_view(1, n)) {
        ans.push_back(network.devices[i].time);
    }
    return ans;
}

auto main() -> int {
    int n, k;
    std::cin >> n >> k;
    auto ans = PeerToPeer(n, k);
    for (int i: ans)std::cout << i << ' ';
}