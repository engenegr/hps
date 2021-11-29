#include <cassert>
#include <fstream>
#include <iostream>
#include "../src/hps.h"

int main() {
  std::vector<double> data({373.15, 101325.0});

  std::ofstream out_file("data.log", std::ofstream::binary);
  std::ifstream in_file("data.log", std::ifstream::binary);

  hps::to_stream(data, out_file);
  out_file.close();

  in_file.seekg(0, in_file.end);
  size_t serialized_size = in_file.tellg();
  in_file.seekg(0, in_file.beg);
  auto parsed = hps::from_stream<std::vector<double>>(in_file);
  assert(parsed == data);

  std::string serialized = hps::to_string(data);
  parsed = hps::from_string<std::vector<double>>(serialized);
  assert(parsed == data);

  parsed = hps::from_char_array<std::vector<double>>(serialized.c_str());
  assert(parsed == data);

  std::cout << "size (B): " << serialized_size << std::endl;
  std::cout << "string size (B): " << serialized.size() << std::endl;

  //double foo [5] = {101325, 101325, 101325, 101325, 373.15};
  //std::string serialized_array = hps::to_string(foo);
  //auto parsed_array = hps::from_string<const double*>(serialized_array);
  //assert(parsed_array == foo);

  return 0;
}
// Compile with C++11 or above.
