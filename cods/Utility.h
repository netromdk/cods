#include <string>
#include <sstream>

#include "cods/Global.h"

CODS_BEGIN_NAMESPACE

/// Convert value into a string.
template <typename T>
std::string convert(const T &val) {
  std::ostringstream ss;
  ss << val;
  return ss.str();
}

CODS_END_NAMESPACE
