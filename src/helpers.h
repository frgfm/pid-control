#pragma once
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// for convenience
using std::array;
using std::string;
using std::vector;

class Helpers {
 public:
  // Checks if the SocketIO event has JSON data.
  string hasData(string s);

  // Unit conversions
  constexpr double pi() { return M_PI; }
  double deg2rad(double x);
  double rad2deg(double x);
};
