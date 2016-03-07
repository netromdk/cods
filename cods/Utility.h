#include <string>
#include <sstream>

#include "cods/Global.h"

CODS_BEGIN_NAMESPACE

/// Convert value into a string.
template <typename T>
string convert(const T &val) {
  ostringstream ss;
  ss << val;
  return ss.str();
}

CODS_END_NAMESPACE
