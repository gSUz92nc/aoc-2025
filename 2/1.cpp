#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

struct range {
  int min{};
  int max{};
};

std::vector<range> load_input() {

  std::string raw_text{std::istreambuf_iterator<char>(std::cin),
                       std::istreambuf_iterator<char>()};

  std::vector<range> ranges{};

  for (auto segment : raw_text | std::views::split(',')) {
    std::string_view sv{segment};
    auto parts = sv | std::views::split('-');
    auto it = parts.begin();

    ranges.push_back({std::stoi(std::string{std::string_view(*it++)}),
                      std::stoi(std::string{std::string_view(*it)})});
  }

  return ranges;
}

int main() { auto input{load_input()}; }
