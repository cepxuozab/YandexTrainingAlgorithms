#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>

int FindMaxBuityString(std::string_view str, int k);

int main() {
  int k;
  std::string s;
  std::cin >> k >> s;
  std::cout << FindMaxBuityString(s, k) << std::endl;
}

int FindMaxBuityString(std::string_view str, int k) {
  std::unordered_map<char, int> arr;
  int max_beauty = 0, largest_count = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    char c = str[i];
    arr[c]++;
    largest_count = largest_count > arr[c] ? largest_count : arr[c];
    max_beauty - largest_count >= k ? arr[str[i - max_beauty]] -= 1 : max_beauty += 1;
  }
  return max_beauty;
}
