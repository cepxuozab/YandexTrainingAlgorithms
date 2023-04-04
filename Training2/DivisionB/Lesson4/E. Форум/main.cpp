#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <climits>
#include <stdexcept>

static auto const FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct Topic {
    std::string topic_name{};
    std::vector<int> messagesNumber{};
};

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        throw std::invalid_argument("can't read");
    }
    int n;
    std::cin >> n;
    int currentLastMessage = 1;
    std::vector<Topic> topics;
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        std::cin.ignore(INT_MAX, '\n');
        if (num == 0) {
            std::string topic_name;
            getline(std::cin, topic_name);
            auto curr = topics.size();
            topics.emplace_back();
            topics[curr].messagesNumber.push_back(currentLastMessage);
            topics[curr].topic_name = topic_name;
            currentLastMessage += 1;
            getline(std::cin, topic_name);
        }
        else {
            for (auto& topic : topics) {
                for (int a : topic.messagesNumber) {
                    if (a == num) {
                        topic.messagesNumber.push_back(currentLastMessage);
                        currentLastMessage += 1;
                    }
                }
            }
            std::string dummy;
            getline(std::cin, dummy);
        }
    }
    std::string nameOfCurrentBiggestTopic;
    int messagesNumberOfBiggestTopic = 0;
    for (auto const& a : topics) {
        if (a.messagesNumber.size() > messagesNumberOfBiggestTopic) {
            nameOfCurrentBiggestTopic = a.topic_name;
            messagesNumberOfBiggestTopic = a.messagesNumber.size();
        }
    }
    std::cout << nameOfCurrentBiggestTopic << '\n';
}
