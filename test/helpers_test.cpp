#include "../src/helpers.h"
#include "catch.hpp"

SCENARIO("Degrees to radians conversion") {
  GIVEN("1 angle in degrees") {
    Helpers helpers;
    double deg;

    WHEN("angle is null") {
      deg = 0;
      double rad = helpers.deg2rad(deg);
      THEN("no error is thrown") { REQUIRE(rad == 0); }
    }

    WHEN("360°") {
      deg = 360;
      double rad = helpers.deg2rad(deg);
      THEN("no error is thrown") { REQUIRE(rad == (2 * M_PI)); }
    }
  }
}

SCENARIO("Radians to degrees conversion") {
  GIVEN("1 angle in radians") {
    Helpers helpers;
    double rad;

    WHEN("angle is null") {
      rad = 0;
      double deg = helpers.rad2deg(rad);
      THEN("no error is thrown") { REQUIRE(deg == 0); }
    }

    WHEN("2 PI") {
      rad = 2 * M_PI;
      double deg = helpers.rad2deg(rad);
      THEN("no error is thrown") { REQUIRE(deg == 360); }
    }
  }
}
