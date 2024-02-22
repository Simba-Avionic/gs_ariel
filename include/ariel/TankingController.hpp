#pragma once

#include <thread>

#include "rclcpp/rclcpp.hpp"

class TankingController : public rclcpp::Node
{
public:
    TankingController();
    ~TankingController();
private:
    std::thread read_thread_;
};