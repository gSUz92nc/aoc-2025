#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

struct Range {
  long long int min{0};
  long long int max{0};
};

std::vector<Range> load_input() {
  std::string raw_text{std::istreambuf_iterator<char>(std::cin),
                       std::istreambuf_iterator<char>()};
  std::vector<Range> ranges{};

  for (auto segment : raw_text | std::views::split(',')) {
    std::string_view sv{segment};
    auto parts = sv | std::views::split('-');
    auto it = parts.begin();

    ranges.push_back({std::stoll(std::string{std::string_view(*it++)}),
                      std::stoll(std::string{std::string_view(*it)})});
  }

  return ranges;
}

template <typename T> bool all_elements_equal(const std::vector<T> &vec) {
  if (vec.empty()) {
    return true;
  }

  const T &first{vec.at(0)};

  return std::all_of(vec.begin() + 1, vec.end(), [&first](const T &elem) {
    return elem == first;
  }); // Don't understand how to do lambdas so this got form:
      // https://www.w3tutorials.net/blog/checking-if-all-elements-of-a-vector-are-equal-in-c/
}

auto processRange(Range range) {

  std::cout << "Processing Range: " << range.min << '-' << range.max << '\n';

  long long int sum{0};

  for (auto i{range.min}; i <= range.max; i++) {
    std::cout << i << '\n';

    std::string num_as_string{std::to_string(i)};
    size_t digits{num_as_string.length()};

    for (int chunk_size{1}; chunk_size <= digits / 2; chunk_size++) {

      std::vector<std::string> chunks{};
      // std::cout << "Chunk size: " << chunk_size << '\n';
      for (int chunk_index{1};
           chunk_index <= std::ceil(digits / static_cast<double>(chunk_size));
           chunk_index++) {
           
        chunks.push_back(num_as_string.substr(chunk_size * (chunk_index - 1), chunk_size));
      }

      std::cout << "Chunk Size " << chunk_size << ':';
      for (auto &&chunk : chunks) {
        std::cout << ' ' << chunk;
      }
      std::cout << '\n';

      if (all_elements_equal(chunks)) {
        std::cout << "Invalid ID: " << i << '\n';
        sum += i;
        break;
      }
    }
  }
  return sum;
}

int main() {
  auto input{load_input()};

  long long int sum{0};

  for (const auto &range : input) {
    sum += processRange(range);
  }

  std::cout << "Final Sum: " << sum;
}
