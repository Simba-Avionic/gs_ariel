#include <signal.h>

#include "rclcpp/rclcpp.hpp"

#include "TankingController.hpp"

void signalHandler(int signum)
{
  rclcpp::shutdown();
  exit(signum);
}

int main(int argc, char * argv[])
{
  signal(SIGINT, signalHandler);
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TankingController>());
  rclcpp::shutdown();
  return 0;
}