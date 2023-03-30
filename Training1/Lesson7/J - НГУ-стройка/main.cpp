#include <iostream>

#include <algorithm>
#include <vector>

struct Block {
    int Z1, Z2;
    int S;
};

std::istream& operator>>(std::istream& in, Block& block)
{
    int x1, y1;
    int x2, y2;

    in >> x1 >> y1 >> block.Z1 >> x2 >> y2 >> block.Z2;
    block.S = (x2 - x1) * (y2 - y1);

    return in;
}

struct Event {
    int Z;
    int block_S;
    enum { TOP = 0,
        BOTTOM = 1 } type;
};

bool operator<(const Event& a, const Event& b)
{
    return a.Z < b.Z or (a.Z == b.Z and a.type < b.type);
}

std::pair<int, int> findMinBlocksSet(const std::vector<Block>& blocks, int full_S)
{
    std::vector<Event> events(2 * blocks.size());
    for (int i = 0, pos = 0; i < blocks.size(); i++) {
        events[pos] = { blocks[i].Z1, blocks[i].S, Event::BOTTOM };
        pos += 1;

        events[pos] = { blocks[i].Z2, blocks[i].S, Event::TOP };
        pos += 1;
    }
    std::sort(events.begin(), events.end());

    int blocks_num = 0, min_blocks_num = blocks.size() + 1;
    int min_blocks_set_Z = -1;
    for (auto [Z, block_S, type] : events) {
        if (type == Event::BOTTOM) {
            blocks_num += 1;
            full_S -= block_S;
            if (full_S == 0) {
                if (blocks_num < min_blocks_num) {
                    min_blocks_num = blocks_num;
                    min_blocks_set_Z = Z;
                }
            }
        } else // type == Event::TOP
        {
            blocks_num -= 1;
            full_S += block_S;
        }
    }

    return std::make_pair(min_blocks_num, min_blocks_set_Z);
}

int main()
{
    int N, W, L, full_S;
    std::cin >> N >> W >> L;
    full_S = W * L;

    std::vector<Block> blocks(N);
    for (int i = 0, pos; i < N; i++) {
        std::cin >> blocks[i];
    }

    auto [min_blocks_num, min_blocks_set_Z] = findMinBlocksSet(blocks, full_S);

    if (min_blocks_num <= N) {
        std::cout << "YES" << std::endl;
        std::cout << min_blocks_num << std::endl;
        for (int i = 0; i < N; i++) {
            if (blocks[i].Z1 <= min_blocks_set_Z and blocks[i].Z2 > min_blocks_set_Z) {
                std::cout << i + 1 << ' ';
            }
        }
    } else
        std::cout << "NO" << std::endl;
}
