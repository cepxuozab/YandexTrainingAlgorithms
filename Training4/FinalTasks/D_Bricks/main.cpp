#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <set>
#include <vector>


class BricksCalc {
    int n_;
    std::set<int, std::greater<>> set_;
    std::vector<int> finalList_;
    int finalCount_ = std::numeric_limits<int>::max();
    std::vector<int> arr_;
    std::vector<int64_t> prefixSum_;

public:
    BricksCalc(int n, std::set<int, std::greater<>> set);
    void RecFunc(int max, int sum, std::vector<int> const& list);
    void Print();

private:
    bool CheckCurr(int sum, int curr, std::vector<int>& list);
    void AddList(int i, std::vector<int>& list);
};


int main()
{
    int n;
    int m;
    std::cin >> n >> m;
    int64_t sum = 0;
    std::set<int, std::greater<>> sets;
    for (int i = 0; i < m; i++) {
        int curr;
        std::cin >> curr;
        sum += 2 * curr;
        if (curr > n) {
            continue;
        }
        sets.insert(curr);
    }
    if (sum < n) {
        std::cout << -1;
    } else if (sets.empty()) {
        std::cout << 0;
    } else {
        auto bricks = BricksCalc(n, sets);
        bricks.RecFunc(0, 0, {});
        bricks.Print();
    }
}

BricksCalc::BricksCalc(int n, std::set<int, std::greater<>> set)
    : n_(n)
    , set_(std::move(set))
{
    arr_.resize(set_.size() * 2 + 1);
    prefixSum_.resize(arr_.size());
    int k = 1;
    for (int curr : set_) {
        prefixSum_[k] = (k > 1) ? prefixSum_[k - 1] + curr : curr;
        arr_[k++] = curr;
        prefixSum_[k] = prefixSum_[k - 1] + curr;
        arr_[k++] = curr;
    }
}
void BricksCalc::Print()
{
    std::cout << finalList_.size() << std::endl;
    for (auto&& e : finalList_) {
        std::cout << e << ' ';
    }
}

void BricksCalc::RecFunc(int max, int sum, std::vector<int> const& list)
{
    for (int i = max + 1; i < arr_.size(); i++) {
        int curr = arr_[i];
        if (sum + curr > n_)
            continue;
        if (prefixSum_.back() - prefixSum_[i] < n_ - sum - curr)
            break;
        std::vector<int> newList(list);
        if (prefixSum_.back() - prefixSum_[i] == n_ - sum - curr) {
            AddList(i, newList);
            break;
        } else if (!CheckCurr(sum, curr, newList) && sum + curr + *set_.rbegin() < n_) {
            newList.push_back(curr);
            int newSum = sum + curr;
            RecFunc(i, newSum, newList);
        }
    }
}

bool BricksCalc::CheckCurr(int sum, int curr, std::vector<int>& list)
{
    int diff = n_ - sum - curr;
    if (set_.contains(diff) || (diff % 2 == 0 && set_.contains(diff / 2))) {
        list.push_back(curr);
        if (set_.contains(diff)) {
            list.push_back(diff);
        } else {
            list.push_back(diff / 2);
            list.push_back(diff / 2);
        }
        if (list.size() < finalCount_) {
            finalList_ = list;
            finalCount_ = list.size();
        }
        return true;
    }
    return false;
}

void BricksCalc::AddList(int i, std::vector<int>& list)
{
    for (; i < arr_.size(); i++) {
        list.push_back(arr_[i]);
    }
    if (finalCount_ > list.size()) {
        finalList_ = list;
        finalCount_ = list.size();
    }
}
