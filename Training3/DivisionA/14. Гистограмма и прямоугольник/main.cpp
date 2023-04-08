#include <iostream>
#include <vector>

using namespace std;

int64_t largestRectangleArea(std::vector<int>& height)
{

    int64_t ret = 0;
    height.push_back(0);
    std::vector<int> index;

    for (size_t i = 0; i < height.size(); i++) {
        while (!index.empty() && height[index.back()] >= height[i]) {
            int64_t h = height[index.back()];
            index.pop_back();

            int64_t sidx = !index.empty() ? index.back() : -1;
            if (h * (i - sidx - 1) > ret)
                ret = h * (i - sidx - 1);
        }
        index.push_back(i);
    }

    return ret;
}
int main()
{
    int n;
    cin >> n;
    vector<int> height(n);

    for (auto& x : height) {
        cin >> x;
    }
    std::cout << largestRectangleArea(height);
    return 0;
}
