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

    std::cout << "Min: " << ranges.back().min << " Max: " << ranges.back().max
              << '\n';
  }

  return ranges;
}

int count_digits(long long int number) {
  if (number == 0) return 1;
  if (number < 0) number = -number;
  return std::log10(number) + 1;
}

auto processRange(Range range) {

  long long int sum{0};

  for (auto i{range.min}; i <= range.max; i++) {

    int digits{count_digits(i)};

    if (digits % 2 != 0) {
      continue;
    }

    long long int first_chunk =
        i / static_cast<long long int>(std::pow(10, digits / 2));
    long long int second_chunk =
        i % static_cast<long long int>(std::pow(10, digits / 2));

    std::cout << "Num: " << i << " first: " << first_chunk
              << " second: " << second_chunk << '\n';

    if (first_chunk == second_chunk) {
      sum += i;
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
