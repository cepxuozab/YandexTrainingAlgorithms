#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map> // для сортировки по ключу
#include <algorithm>

using Tree = std::unordered_map<std::string, std::vector<std::string>>;

auto read_input() -> std::tuple<int, Tree, std::string>
{
    int n;
    std::cin >> n;
    Tree tree;
    std::unordered_set<std::string> children;
    std::string child, parent;
    for (int i = 0; i < n - 1; ++i)
    {
        std::cin >> child >> parent;
        children.insert(child);
        tree[parent].push_back(child);
    }
    // Найти корень — ключ из tree, которого нет в children
    std::string root;
    for (const auto &[key, _] : tree)
    {
        if (children.find(key) == children.end())
        {
            root = key;
            break;
        }
    }
    return {n, tree, root};
}

void height_dfs(const Tree &tree, const std::string &node, int level, std::unordered_map<std::string, int> &ans)
{
    ans[node] = level;
    auto it = tree.find(node);
    if (it != tree.end())
    {
        for (const auto &child : it->second)
        {
            height_dfs(tree, child, level + 1, ans);
        }
    }
}

auto genealogy(int n, const Tree &tree, const std::string &root) -> std::map<std::string, int>
{
    std::unordered_map<std::string, int> ans;
    height_dfs(tree, root, 0, ans);
    // std::map отсортирует по ключу автоматически
    return std::map(ans.begin(), ans.end());
}

int main()
{
    auto [n, tree, root] = read_input();
    auto result = genealogy(n, tree, root);
    for (const auto &[name, level] : result)
    {
        std::cout << name << ' ' << level << '\n';
    }
    return 0;
}
