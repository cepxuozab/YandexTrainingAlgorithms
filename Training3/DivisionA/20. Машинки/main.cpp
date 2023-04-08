#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <vector>

#define parent(i) (i - 1) >> 1
#define left(i) (i << 1) + 1
#define right(i) (i << 1) + 2

static const auto FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr; }();

    class Heap {
        std::vector<int> heap, idx;
        std::vector<std::deque<int>> prior;
        int len = 0;

    public:
        Heap(int n)
            : heap(n)
            , idx(n, -1)
            , prior(n)
        {
        }

        void MakeHeap(std::vector<int> const& seq)
        {
            for (int i = 0; i < seq.size(); i++) {
                prior[seq[i]].push_back(i);
            }
        }
        int getIdx(int i) const
        {
            return idx[i];
        }
        int getLen() const
        {
            return len;
        }
        void add(int item)
        {
            idx[item] = len;
            heap[len] = item;
            siftup(len++);
        }

        void remove()
        {
            swap(0, --len);
            idx[heap[len]] = -1;
            siftdown(0);
        }

        void erase(int i)
        {
            prior[i].pop_front();
        }
        void siftup(int i)
        {
            while (i && greater(i, parent(i))) {
                swap(i, parent(i));
                i = parent(i);
            }
        }

    private:
        void swap(int i, int j)
        {
            std::swap(heap[i], heap[j]);
            std::swap(idx[heap[i]], idx[heap[j]]);
        }
        bool greater(int i, int j)
        {
            if (!prior[heap[i]].empty() && !prior[heap[j]].empty())
                return prior[heap[i]].front() > prior[heap[j]].front();
            return prior[heap[i]].empty() && !prior[heap[j]].empty();
        }

        void siftdown(int i)
        {
            while (true) {
                int j = i;
                if (left(j) < len && greater(left(j), i))
                    i = left(j);
                if (right(j) < len && greater(right(j), i))
                    i = right(j);
                if (i != j)
                    swap(i, j);
                else
                    break;
            }
        }
    };
    int main()
    {
        if (freopen("input.txt", "r", stdin) == nullptr) {
            puts("Can't open input.txt");
            return 1;
        }
        int n, k, p;
        std::cin >> n >> k >> p;
        std::vector<int> seq(p);
        for (int& elem : seq) {
            std::cin >> elem;
            elem--;
        }
        Heap my_heap(n);
        my_heap.MakeHeap(seq);
        int answer = 0;
        for (int car : seq) {
            my_heap.erase(car);
            if (int idx = my_heap.getIdx(car); idx != -1) {
                my_heap.siftup(idx);
                continue;
            }
            if (my_heap.getLen() < k) {
                my_heap.add(car);
            }
            else {
                my_heap.remove();
                my_heap.add(car);
            }
            answer++;
        }
        std::cout << answer;
    }
