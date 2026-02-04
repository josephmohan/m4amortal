#include "m4a_to_wav.h"

#include <filesystem>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input.m4a>\n";
    return 1;
  }

  const std::string input_path = argv[1];
  if (!std::filesystem::exists(input_path)) {
    std::cerr << "Input file not found: " << input_path << "\n";
    return 1;
  }

  const std::string output_path = m4amortal::default_wav_output_path(input_path);
  if (output_path == input_path) {
    std::cerr << "Input and output paths resolve to the same file.\n";
    return 1;
  }

  m4amortal::ConvertOptions options;
  std::string error;
  if (!m4amortal::convert_m4a_to_wav(input_path, output_path, options, &error)) {
    std::cerr << "Conversion failed: " << error << "\n";
    return 1;
  }

  std::cout << output_path << "\n";
  return 0;
}
