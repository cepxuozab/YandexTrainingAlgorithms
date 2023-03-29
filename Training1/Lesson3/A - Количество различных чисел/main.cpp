#include <iostream>
#include <unordered_set>
#include <iterator>
int main()
{
    std::unordered_set<int> sets(std::istream_iterator<int>(std::cin),
        {});
    std::cout << sets.size() << std::endl;

    return 0;
}
