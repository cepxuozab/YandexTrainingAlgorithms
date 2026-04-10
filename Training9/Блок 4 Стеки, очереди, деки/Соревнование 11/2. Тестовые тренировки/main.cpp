#include <iostream>
#include <vector>
#include <string>
#include <utility>

auto main() -> int {
    int n;
    std::cin >> n;

    std::string correct;
    std::cin >> correct;

    int m;
    std::cin >> m;

    std::vector<std::string> answers(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> answers[i];
    }

    std::vector<std::pair<int, int>> result;

    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            int correct_i = 0, correct_j = 0;
            int same_correct_i = 0, same_wrong_i = 0;
            int same_correct_j = 0, same_wrong_j = 0;

            for (int k = 0; k < n; ++k) {
                bool ci = (answers[i][k] == correct[k]);
                bool cj = (answers[j][k] == correct[k]);

                if (ci) {
                    ++correct_i;
                    if (answers[i][k] == answers[j][k]) {
                        ++same_correct_i;
                    }
                } else {
                    if (answers[i][k] == answers[j][k]) {
                        ++same_wrong_i;
                    }
                }

                if (cj) {
                    ++correct_j;
                    if (answers[i][k] == answers[j][k]) {
                        ++same_correct_j;
                    }
                } else {
                    if (answers[i][k] == answers[j][k]) {
                        ++same_wrong_j;
                    }
                }
            }

            int wrong_i = n - correct_i;
            int wrong_j = n - correct_j;

            bool ok_i = (same_correct_i > correct_i / 2) &&
                        (same_wrong_i > wrong_i / 2);

            bool ok_j = (same_correct_j > correct_j / 2) &&
                        (same_wrong_j > wrong_j / 2);

            if (ok_i && ok_j) {
                result.emplace_back(i + 1, j + 1);
            }
        }
    }

    std::cout << result.size() << '\n';
    for (const auto& [a, b] : result) {
        std::cout << a << ' ' << b << '\n';
    }

    return 0;
}