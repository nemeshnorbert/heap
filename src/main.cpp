#include <iostream>

#include "binary_heap.h"

int run() {
  std::ostream& out = std::cout;
  std::istream& in = std::cin;
  auto heap = heap::binary_heap<int, std::greater<int>>{};
  auto commands_count = std::size_t{0};
  in >> commands_count;
  for (auto command_id = std::size_t{0}; command_id < commands_count; ++command_id) {
    auto command_name = std::string{};
    in >> command_name;
    if (command_name == "Insert") {
      auto value = int{0};
      in >> value;
      heap.push(value);
    } else if (command_name == "ExtractMax") {
      if (heap.empty()) {
        out << "The heap is empty!\n";
      } else {
        std::cout << heap.top() << '\n';
        heap.pop();
      }
    } else {
      out << "Unknown command: " << command_name << '\n';
    }
  }
  return 0;
}

int main()
{
    run();
    return 0;
}
