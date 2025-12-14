#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::string load_input() {
  std::string input{std::istreambuf_iterator<char>(std::cin),
                    std::istreambuf_iterator<char>{}};
  return input;
}

int mod(int a, int b) {
  int c = a % b;
  return c < 0 ? c + b : c;
}

std::vector<int> calculate_positions(std::string_view input) {
  size_t start{0};

  // Starts at 50
  std::vector<int> positions{50};

  while (start < input.size()) {
    size_t end = input.find('\n', start);

    // safety check incase there are no more new lines
    if (end == std::string_view::npos) {
      end = input.size();
    }

    std::string_view move{input.substr(start, end - start)};
    char direction{move.front()};
    int num_of_turns{};

    // Help from perplexity
    auto [ptr, ec] = std::from_chars(move.data() + 1, move.data() + move.size(),
                                     num_of_turns);

    if (ec != std::errc() || ptr != move.data() + move.size()) {
      std::cerr << "Invalid state while extracting numbers from line! "
                << static_cast<int>(ec) << std::endl;
      exit(-1);
    }

    if (direction == 'L') {
      positions.push_back(mod(positions.back() - num_of_turns, 100));
    } else if (direction == 'R') {
      positions.push_back(mod(positions.back() + num_of_turns, 100));
    } else {
      std::cerr << "Invalid direction has to be one of 'L' or 'R'!";
      exit(-1);
    }

    start = end + 1;
  }
  return positions;
}

int main() {
  std::vector<int> positions{calculate_positions(load_input())};
  std::cout << std::count(positions.begin(), positions.end(), 0);
}
