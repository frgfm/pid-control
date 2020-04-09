#include "Monitor.h"

Monitor::Monitor() { Monitor::reset(); }

Monitor::~Monitor() {}

void Monitor::reset() {
  mean_lacc = 0;
  mean_cte = 0;
  num_entries = 0;
  prev_steering = 0;
  prev_steerdiff = 0;
}

void Monitor::update(const float &cte, const float &steering) {
  // Rescale previous values
  mean_cte *= num_entries / (num_entries + 1);
  mean_lacc *= num_entries / (num_entries + 1);
  // Add new scaled values
  mean_cte += fabs(cte) / (num_entries + 1);
  // Get angular acceleration
  mean_lacc +=
      fabs((steering - prev_steering) - prev_steerdiff) / (num_entries + 1);
  // Update entries
  num_entries += 1;
  prev_steerdiff = steering - prev_steering;
  prev_steering = steering;
}
