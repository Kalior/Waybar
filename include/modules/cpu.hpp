#pragma once

#include <fmt/format.h>
#include <sys/sysinfo.h>
#include <cstdint>
#include <fstream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
#include "ALabel.hpp"
#include "util/sleeper_thread.hpp"

namespace waybar::modules {

class Cpu : public ALabel {
 public:
  Cpu(const std::string&, const Json::Value&);
  ~Cpu() = default;
  auto update(std::string format, waybar::args &args) -> void override;

 private:
  static inline const std::string         data_dir_ = "/proc/stat";
  uint16_t                                getCpuLoad();
  std::tuple<uint16_t, std::string>       getCpuUsage();
  std::vector<std::tuple<size_t, size_t>> parseCpuinfo();

  std::vector<std::tuple<size_t, size_t>> prev_times_;

  util::SleeperThread thread_;
};

}  // namespace waybar::modules
