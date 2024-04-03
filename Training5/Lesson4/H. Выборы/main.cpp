#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cstdint>
#include <utility>

struct Party {
    int vote;
    int gift;
    int id;
};

auto operator<(const Party& p1, const Party& p2) -> bool {
    return std::pair(p1.vote, p1.gift) < std::pair(p2.vote, p2.gift);
}

auto check(int64_t mid, std::vector<Party>& party, int choice_id) -> bool {
    int64_t target_choice = party[choice_id].vote + mid;
    for (int i = 0; std::cmp_less(i, party.size()); ++i) {
        if (i == choice_id || party[i].vote < target_choice)
            continue;

        mid = mid - (party[i].vote - target_choice + 1);

        if (mid < 0)
            break;
    }

    if (mid >= 0)
        return true;
    else
        return false;
}

auto binary_search_votes(std::vector<Party> party,
    int64_t max_vote,
    int choice_id) -> int64_t {
    int64_t L = 0;
    int64_t R = max_vote;

    while (L < R) {
        int64_t mid = (L + R) / 2;
        if (check(mid, party, choice_id))
            R = mid;
        else
            L = mid + 1;
    }
    return L;
}

auto binary_search_id(std::vector<Party> party) -> int {
    int choice_id = -1;
    std::sort(party.begin(), party.end());
    std::vector<int64_t> Sum_count(party.size());
    int64_t count = 0;
    for (int i = static_cast<int>(party.size()) - 1; i >= 0; --i) {
        Sum_count[i] = count;
        count += party[i].vote;
    }

    int64_t answer = std::numeric_limits<int64_t>::max();
    int64_t l1, r1, mid1, l2, r2, mid2;
    for (int i = 0; std::cmp_less(i, party.size()); ++i) {
        if (party[i].gift == -1)
            continue;

        l1 = party[i].vote;
        r1 = count;
        while (l1 + 1 < r1) {
            mid1 = (l1 + r1) / 2;
            l2 = 0;
            r2 = party.size();
            while (l2 + 1 < r2) {
                mid2 = (l2 + r2) / 2;
                if (party[mid2].vote >= mid1)
                    r2 = mid2;
                else
                    l2 = mid2;
            }

            if (Sum_count[r2 - 1] - (static_cast<int64_t>(party.size()) - r2) * (mid1 - 1) + party[i].vote <= mid1)
                r1 = mid1;
            else
                l1 = mid1;
        }

        if (answer > r1 + party[i].gift - party[i].vote) {
            answer = r1 + party[i].gift - party[i].vote;
            choice_id = i;
        }
    }
    return party[choice_id].id;
}

void update_data_vote(std::vector<Party>& party, int additional_vote, int choice_id) {
    bool flag = false;
    party[choice_id].vote += additional_vote;
    int n = static_cast<int>(party.size());
    for (int i = 0; i < n && additional_vote != 0; ++i) {
        if (i == choice_id);

        else if (flag && party[i].vote > 0) {
            party[i].vote--;
            additional_vote--;
        }
        else if (party[choice_id].vote > party[i].vote) {}
        else {
            while (party[choice_id].vote <= party[i].vote) {
                party[i].vote--;
                additional_vote--;
            }
        }
        if (i == n - 1) {
            flag = true;
            i = -1;
        }
    }
}

auto main() -> int {

    int n;
    std::cin >> n;
    std::vector<Party> party(n);
    int64_t max_vote = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> party[i].vote >> party[i].gift;
        max_vote += party[i].vote;
        party[i].id = i;
    }


    int choice_id = binary_search_id(party);
    int64_t additional_vote = binary_search_votes(party, max_vote, choice_id);

    std::cout << additional_vote + party[choice_id].gift << '\n';
    std::cout << choice_id + 1 << '\n';
    update_data_vote(party, additional_vote, choice_id);
    for (int i = 0; i < n; ++i)
        std::cout << party[i].vote << " ";
    std::cout << '\n';
    return 0;
}