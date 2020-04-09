#include <uWS/uWS.h>
#include <cmath>
#include <iostream>
#include <string>
#include "PID.h"
#include "helpers.h"
#include "json.hpp"
#include "spdlog/spdlog.h"

// for convenience
using nlohmann::json;
using std::string;

Helpers helpers;

int main() {
  uWS::Hub h;

  PID pid;
  pid.Init(0.15, 0.004, 3.0);

  h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length,
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = helpers.hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          // double speed = std::stod(j[1]["speed"].get<string>());
          // double angle = std::stod(j[1]["steering_angle"].get<string>());
          double steer_value;

          pid.UpdateError(cte);
          steer_value = -pid.TotalError();

          // DEBUG
          spdlog::info("CTE: {} | Steering Value: {}", cte, steer_value);

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = 0.3;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  });  // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    spdlog::info("Environment session connected!");
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code,
                         char *message, size_t length) {
    ws.close();
    spdlog::info("Disconnected from session");
  });

  int port = 4567;
  if (h.listen(port)) {
    spdlog::info("Listening to port {}", port);
  } else {
    spdlog::error("Failed to listen to port {}", port);
    return -1;
  }

  h.run();
}
