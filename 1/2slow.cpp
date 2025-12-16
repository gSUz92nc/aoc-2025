// Can't figure out the maths for the the 2nd part so instead im going to try a
// "brute force" methodology where I simulate the clicks
#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

std::vector<int> load_input() {
  std::vector<int> moves{};
  std::string currentLine{};

  while (std::getline(std::cin, currentLine)) {
    moves.push_back(std::stoi(currentLine.substr(1)) *
                    (currentLine.at(0) == 'R' ? 1 : -1));
  }

  return moves;
}

struct click_info {
  int new_value{};
  int clicks{};
};

click_info countClicks(int currentValue, int move) {

  int clicks{0};

  while (move != 0) {

    if (move > 0) {
      move--;
      currentValue++;
    } else if (move < 0) {
      move++;
      currentValue--;
    }

    if (currentValue >= 100) {
      currentValue -= 100;
    } else if (currentValue < 0) {
      currentValue += 100;
    }

    if (currentValue == 0) {
      clicks++;
    }
  }

  return {currentValue, clicks};
}

int main() {
  auto all_moves{load_input()};
  int clicks{0};
  int currentValue{50};

  for (const auto &move : all_moves) {
    auto result = countClicks(currentValue, move);
    currentValue = result.new_value;
    clicks += result.clicks;

    std::cout << "New Value: " << result.new_value << "\nClicks: " << result.clicks
              << "\n";
  }

  std::cout << clicks;
}
