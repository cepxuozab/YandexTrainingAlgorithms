#include <cstdint>
#include <deque>
#include <iostream>
#include <print>
#include <string>
#include <utility>
#include <vector>

namespace {

struct Song {
    std::string name;
    std::int64_t length = 0;
};

struct PlayNext {
    std::int64_t time = 0;
    Song song;
};

}  // namespace

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t song_count = 0;
    std::cin >> song_count;

    std::deque<Song> waiting;
    for (std::size_t i = 0; i < song_count; ++i) {
        Song& song = waiting.emplace_back();
        std::cin >> song.name >> song.length;
    }

    std::size_t play_next_count = 0;
    std::cin >> play_next_count;

    std::vector<PlayNext> play_next_events(play_next_count);
    for (auto& [time, song] : play_next_events) {
        std::cin >> time >> song.name >> song.length;
    }

    std::size_t next_event = 0;
    std::int64_t now = 0;

    while (next_event < play_next_events.size() || !waiting.empty()) {
        while (next_event < play_next_events.size() && play_next_events[next_event].time <= now) {
            waiting.push_front(std::move(play_next_events[next_event].song));
            ++next_event;
        }
        if (waiting.empty()) {
            now = play_next_events[next_event].time;
            continue;
        }
        Song current = std::move(waiting.front());
        waiting.pop_front();
        std::println("{} {}", current.name, now);
        now += current.length;
    }
}