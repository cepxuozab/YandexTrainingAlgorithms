#include <iostream>
#include <utility>
#include <vector>

template <typename T = int, typename Compare = std::less<>>
struct Heap {
    Compare cmp = std::less<>();
    std::vector<T> data;
    Heap(Compare comp = std::less<>())
        : cmp(std::move(comp))
    {
    }
    void Insert(T value)
    {
        data.push_back(value);
        Sift_up(Size() - 1);
    }
    T Extract()
    {
        int x = data[0];
        std::swap(data[0], data.back());
        data.pop_back();
        Sift_down(0);
        return x;
    }
    void Sift_up(int i)
    {
        int parent = (i - 1) / 2;
        if (cmp(data[i], data[parent])) {
            std::swap(data[i], data[parent]);
            Sift_up(parent);
        }
    }
    int Size() const
    {
        return data.size();
    }
    void Sift_down(int i)
    {
        int left = 2 * i + 1;
        int right = left + 1;
        if (left < Size()) {
            int next = left;
            if (right < Size()
                && cmp(data[right], data[left])) {
                next = right;
            }
            if (cmp(data[next], data[i])) {
                std::swap(data[next], data[i]);
                Sift_down(next);
            }
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto heap = Heap<int, std::greater<>>(std::greater<>());
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int type;
        std::cin >> type;
        switch (type) {
        case 1:
            std::cout << heap.Extract() << std::endl;
            break;
        case 0:
            int x;
            std::cin >> x;
            heap.Insert(x);
            break;
        default:
            break;
        }
    }
}