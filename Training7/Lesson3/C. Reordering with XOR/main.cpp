#include <algorithm>
#include <bit>
#include <iostream>
#include <vector>

struct Number {
  size_t value;
  int index;
};

inline void MoveBit(size_t &num, int start_pos, int target_pos) {
  num ^= 1UL << start_pos;
  num |= 1UL << target_pos;
}

inline int HighestBit(size_t a) { return 8 * sizeof(a) - std::countl_zero(a); }

inline void ShiftBitsToRight(std::vector<Number> &arr) {
  for (auto &a : arr) {
    int bits_count = std::popcount(a.value);
    a.value = (1UL << bits_count) - 1;
  }
}

inline bool CheckResult(std::vector<Number> &arr) {
  size_t result = 0UL;
  for (const auto &a : arr) {
    result ^= a.value;
  }
  return result == 0UL;
}

void CalculateRepetitions(std::vector<Number> &arr,
                          std::vector<int> &bit_repetitions,
                          [[maybe_unused]] int highest_bit) {
  for (const auto &a : arr) {
    Number a_copy = a;
    size_t i = 0;
    while (a_copy.value != 0) {
      bit_repetitions[i] += a_copy.value & 1;
      a_copy.value >>= 1;
      ++i;
    }
  }
}

void BottomUp(std::vector<Number> &arr, std::vector<int> &bit_repetitions,
              int highest_bit) {
  for (int i = highest_bit; i > 0 && bit_repetitions[i] < 2; --i) {
    if (bit_repetitions[i] & 1) {
      for (auto it = std::next(arr.rbegin()); it != arr.rend(); ++it) {
        size_t &value = it->value;
        int last_bit = std::countr_one(value) - 1;
        if (last_bit >= 0) {
          MoveBit(value, last_bit, i);
          ++bit_repetitions[i];
          --bit_repetitions[last_bit];
          break;
        }
      }
    }
  }

  size_t num_index = 0;
  for (size_t i = 0; i < bit_repetitions.size(); ++i) {
    num_index %= arr.size();
    if (bit_repetitions[i] & 1) {
      while ((arr[num_index].value & (1UL << i)) == 0UL) {
        num_index = (num_index + 1) % arr.size();
      }
      size_t &value = arr[num_index].value;
      int first_zero = HighestBit(value);
      if (first_zero <= highest_bit) {
        MoveBit(value, i, first_zero);
        ++bit_repetitions[first_zero];
        --bit_repetitions[i];
        ++num_index;
      }
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<Number> arr(n);
  int highest_bit = 0;
  int index = 0;
  for (auto &a : arr) {
    std::cin >> a.value;
    a.index = index;
    highest_bit = std::max(highest_bit, HighestBit(a.value) - 1);
    ++index;
  }
  ShiftBitsToRight(arr);
  std::sort(arr.begin(), arr.end(),
            [](Number &a1, Number &a2) { return a1.value < a2.value; });

  std::vector<int> bit_repetitions(highest_bit + 1, 0);
  CalculateRepetitions(arr, bit_repetitions, highest_bit);
  BottomUp(arr, bit_repetitions, highest_bit);

  if (CheckResult(arr)) {
    std::sort(arr.begin(), arr.end(),
              [](Number &a1, Number &a2) { return a1.index < a2.index; });
    for (const auto &a : arr) {
      std::cout << a.value << ' ';
    }
  } else {
    std::cout << "impossible";
  }
  std::cout << '\n';

  return 0;
}