#include <string>
#include <sstream>

namespace cods {

/// Convert value into a string.
template <typename T>
std::string convert(const T &val) {
  std::ostringstream ss;
  ss << val;
  return ss.str();
}

} // cods
