#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <tuple>
#include <vector>

[[maybe_unused]] static const auto FastIo = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using Time = int;

struct Task {
    int a = 0;
    Time T = 0;
    int idx = 0;
    int worker = 0;

    explicit Task(int n, Time t, int i);

    auto operator<(Task const& other) const -> bool;
};

auto ReadTasks(int n) -> std::vector<Task>;

void WorkerTasks(Time w, std::vector<Task> tasks);

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    int n;
    Time w;
    std::cin >> n >> w;
    WorkerTasks(w, ReadTasks(n));
}

auto ReadTasks(int n) -> std::vector<Task>
{
    std::vector<Task> tasks;
    tasks.reserve(n);
    for (int i = 0; i < n; ++i) {
        int a;
        Time t;
        std::cin >> a >> t;
        tasks.emplace_back(a, t, i + 1);
    }
    std::ranges::sort(tasks, {}, &Task::a);
    return tasks;
}

void WorkerTasks(Time w, std::vector<Task> tasks)
{
    //tasks.front().worker = 0;
    std::vector<std::vector<Task>> workers{ { tasks.front() } };
    std::priority_queue<Task> task_queue;
    task_queue.push(tasks.front());
    for (size_t i = 1; i < tasks.size(); ++i) {
        auto now = tasks[i];
        auto last = task_queue.top();
        if (last.a + last.T <= now.a) {
            now.worker = last.worker;
            workers[now.worker].push_back(now);
            task_queue.push(now);
            task_queue.pop();
            continue;
        }
        now.worker = (int)workers.size();
        workers.push_back({ now });
        task_queue.push(now);
    }
    std::cout << workers.size() << std::endl;
    for (auto const& worker : workers) {
        for (auto const& task : worker) {
            std::cout << task.idx << ' ';
        }
    }
    std::cout << std::endl;
}

Task::Task(int n, Time t, int i)
    : a(n)
    , T(t)
    , idx(i)
{
}

auto Task::operator<(Task const& other) const -> bool
{
    return a + T > other.a + other.T;
}
