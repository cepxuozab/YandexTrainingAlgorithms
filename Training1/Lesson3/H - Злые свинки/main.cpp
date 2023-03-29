#include <fstream>
#include <set>

int main()
{
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");
    int n;
    input >> n;
    std::set<int> s;
    for (int i = 0; i < n; ++i) {
        int a, b;
        input >> a >> b;
        s.insert(a);
    }
    output << s.size();
}
