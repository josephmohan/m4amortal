#ifndef M4A_TO_WAV_H
#define M4A_TO_WAV_H

#include <string>

namespace m4amortal {

struct ConvertOptions {
  int sample_rate = 0;
  int channels = 0;
};

std::string default_wav_output_path(const std::string& input_path);

bool convert_m4a_to_wav(const std::string& input_path,
                        const std::string& output_path,
                        const ConvertOptions& options = {},
                        std::string* error = nullptr);

}  // namespace m4amortal

#endif  // M4A_TO_WAV_H
