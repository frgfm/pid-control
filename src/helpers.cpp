#include "helpers.h"

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
//   else the empty string "" will be returned.
string Helpers::hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_first_of("}");
  if (found_null != string::npos) {
    return "";
  } else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 2);
  }
  return "";
}

// For converting back and forth between radians and degrees.
double Helpers::deg2rad(double x) { return x * pi() / 180; }
double Helpers::rad2deg(double x) { return x * 180 / pi(); }
