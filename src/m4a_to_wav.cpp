#include "m4a_to_wav.h"

#include <filesystem>
#include <sstream>
#include <spawn.h>
#include <string>
#include <sys/wait.h>
#include <vector>

extern char** environ;

namespace m4amortal {
namespace {

bool run_ffmpeg(const std::vector<std::string>& args, std::string* error) {
  std::vector<char*> argv;
  argv.reserve(args.size() + 1);
  for (const auto& arg : args) {
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  argv.push_back(nullptr);

  pid_t pid = 0;
  const int spawn_status =
      posix_spawnp(&pid, "ffmpeg", nullptr, nullptr, argv.data(), environ);
  if (spawn_status != 0) {
    if (error) {
      std::ostringstream oss;
      oss << "Failed to launch ffmpeg (error " << spawn_status << ").";
      *error = oss.str();
    }
    return false;
  }

  int wait_status = 0;
  if (waitpid(pid, &wait_status, 0) < 0) {
    if (error) {
      *error = "Failed waiting for ffmpeg process.";
    }
    return false;
  }

  if (!WIFEXITED(wait_status) || WEXITSTATUS(wait_status) != 0) {
    if (error) {
      std::ostringstream oss;
      oss << "ffmpeg exited with code "
          << (WIFEXITED(wait_status) ? WEXITSTATUS(wait_status) : -1) << ".";
      *error = oss.str();
    }
    return false;
  }

  return true;
}

}  // namespace

std::string default_wav_output_path(const std::string& input_path) {
  std::filesystem::path source(input_path);
  if (source.has_extension()) {
    return source.replace_extension(".wav").string();
  }
  return (source.string() + ".wav");
}

bool convert_m4a_to_wav(const std::string& input_path,
                        const std::string& output_path,
                        const ConvertOptions& options,
                        std::string* error) {
  std::vector<std::string> args = {"ffmpeg", "-y", "-hide_banner", "-loglevel",
                                   "error", "-i", input_path};

  if (options.sample_rate > 0) {
    args.push_back("-ar");
    args.push_back(std::to_string(options.sample_rate));
  }
  if (options.channels > 0) {
    args.push_back("-ac");
    args.push_back(std::to_string(options.channels));
  }

  args.push_back("-acodec");
  args.push_back("pcm_s16le");
  args.push_back("-vn");
  args.push_back(output_path);

  return run_ffmpeg(args, error);
}

}  // namespace m4amortal
