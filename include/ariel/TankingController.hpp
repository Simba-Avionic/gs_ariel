#pragma once

#include <thread>
#include <string>
#include <stdio.h>
#include <chrono>

#include "rclcpp/rclcpp.hpp"

#include "gs_interfaces/msg/tanking_control.hpp"

class TankingController : public rclcpp::Node
{
public:
    TankingController();
    ~TankingController();
private:
    gs_interfaces::msg::TankingControl tnk_ctrl_msg_;
    rclcpp::Publisher<gs_interfaces::msg::TankingControl>::SharedPtr tnk_ctrl_pub_;
    rclcpp::TimerBase::SharedPtr tnk_ctrl_timer_;
    void publishTnkCtrl();
    std::thread read_thread_;
    void consoleRead();
    void test1();
};