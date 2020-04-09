#pragma once

#include <cmath>

class Monitor {
 public:
  /**
   * Constructor
   */
  Monitor();

  /**
   * Destructor.
   */
  virtual ~Monitor();

  void update(const float &cte, const float &steering);

  void reset();

  // Average of CTE and angular acceleration
  float mean_cte, mean_lacc;

 private:
  float num_entries, prev_steering, prev_steerdiff;
};
