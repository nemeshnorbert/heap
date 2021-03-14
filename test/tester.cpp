#include <iostream>
#include <set>

#include "binary_heap.h"

namespace heap {

namespace testing {

enum class binary_heap_command : std::size_t {
  PUSH = 1,
  POP = 2,
  TOP = 3
};

template <typename T>
bool assert_equal(
  std::ostream& out,
  const T& result,
  const T& expected,
  const std::string& comment) {
  if (result != expected) {
    out << comment << '\n';
    out << "Got:\n" << result << '\n';
    out << "Expected:\n" << expected << '\n';
    return false;
  }
  return true;
}

bool run_test(std::ostream& out, std::size_t commands_count) {
  auto array_heap = binary_heap<int>{};
  auto tree_heap = rb_heap<int>{};
  const auto command_types_count = std::size_t{3};
  for (auto command_id = std::size_t{0}; command_id < commands_count; ++command_id) {
    auto command_type = static_cast<binary_heap_command>(
      static_cast<std::size_t>(std::rand()) % command_types_count);
    if (command_type == binary_heap_command::PUSH) {
      auto insert_value = std::rand();
      array_heap.push(insert_value);
      tree_heap.push(insert_value);
    } else if (command_type == binary_heap_command::POP) {
      if (!array_heap.empty() && !tree_heap.empty()) {
        assert_equal(out, array_heap.size(), tree_heap.size(), "Heaps are of different size");
        array_heap.pop();
        tree_heap.pop();
      } else {
        assert_equal(out, array_heap.size(), tree_heap.size(), "Heaps are of different size");
      }
    } else if (command_type == binary_heap_command::TOP) {
      if (assert_equal(out, array_heap.top(), tree_heap.top(), "Wrong heap max")) {
        return false;
      }
    }
  }
  out << "Test passed\n";
  return true;
}

} // namespace testing

} // namespace binary_heap

int main() {
  for (auto attempt_id = std::size_t{0}; attempt_id < 10; ++attempt_id) {
    auto commands_count = 2 * attempt_id;
    if (!heap::testing::run_test(std::cout, commands_count)) {
      return 1;
    }
  }
  return 0;
}