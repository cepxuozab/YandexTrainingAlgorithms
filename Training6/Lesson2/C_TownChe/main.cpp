#include <iostream>
#include <span>
#include <vector>
void ReadData(std::vector<int>& distances, int& max_distance, std::istream& input = std::cin);

auto NumberToChoose(std::span<int> distances, int max_distance) -> int64_t;

int main() {
    int max_distance = 0;
    std::vector<int> distances;
    ReadData(distances, max_distance);
    std::cout << NumberToChoose(distances, max_distance) << std::endl;
}

void ReadData(std::vector<int>& distances, int& max_distance, std::istream& input) {
    int number_of_monuments;
    std::cin >> number_of_monuments >> max_distance;
    distances.resize(number_of_monuments);
    for (auto& dist : distances) {
        input >> dist;
    }
}

auto NumberToChoose(std::span<int> distances, int max_distance) -> int64_t {
    size_t const size = distances.size();
    size_t j = 0;
    int64_t answer = 0;
    for (size_t i = 0; i < size; ++i) {
        while (j < size && distances[j] - distances[i] <= max_distance) {
            j++;
        }
        answer += (size - j);
    }
    return answer;
}