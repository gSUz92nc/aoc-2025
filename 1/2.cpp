#include <charconv>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>

const static int dial_config = 100;

std::string load_input() {
  std::string input{std::istreambuf_iterator<char>(std::cin),
                    std::istreambuf_iterator<char>{}};
  return input;
}

struct spin_state {
  int new_value{};
  int num_crossed_zero{};
};

spin_state spin(int current_value, char direction, int turns) {

  spin_state new_state{};

  if (direction == 'L') {
    new_state.new_value =
        std::abs(current_value - turns + dial_config) % dial_config;
    new_state.num_crossed_zero =
        std::abs((current_value - turns - dial_config) / dial_config);

    if (current_value == 0) {
      new_state.num_crossed_zero--;
    }
  } else if (direction == 'R') {
    new_state.new_value = (current_value + turns) % dial_config;
    new_state.num_crossed_zero = (current_value + turns) / dial_config;
  } else {
    std::cout << "Invalid direction!" << direction;
    std::exit(-1);
  }

  if (new_state.new_value == 0 && new_state.num_crossed_zero > 0) {
    new_state.num_crossed_zero--;
  }

  return new_state;
}

int calculate_password(std::string_view input) {
  size_t index{0};
  int password{0};

  // Starts at 50
  int current_value{50};

  while (index < input.size()) {

    size_t end = input.find('\n', index);

    if (end == std::string_view::npos) {
      end = input.size();
    }

    std::string_view move{input.substr(index, end - index)};

    int turns;
    auto result =
        std::from_chars(move.data() + 1, move.data() + move.size(), turns);

    if (result.ec == std::errc::invalid_argument) {
      std::cout << "Could not convert string to int!";
    }

    spin_state post_spin_state{spin(current_value, input.at(index), turns)};

    if (post_spin_state.new_value == 0) {
      password++;
    }

    password += post_spin_state.num_crossed_zero;
    current_value = post_spin_state.new_value;

    std::cout << "Move: " << move
              << " New position: " << post_spin_state.new_value << ", "
              << post_spin_state.num_crossed_zero << '\n';
    size_t next_nl = input.find("\n", index);

    if (next_nl == std::string_view::npos) {
      break;
    }
    index = next_nl + 1;
  }

  return password;
}

int main() { std::cout << calculate_password(load_input()); }
