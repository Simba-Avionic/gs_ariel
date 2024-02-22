#include "TankingController.hpp"

TankingController::TankingController() : Node("tanking_control_demo")
{
    using namespace std::chrono_literals;
    tnk_ctrl_msg_.header.frame_id = "tanking controller demo";
    tnk_ctrl_pub_ = this->create_publisher<gs_interfaces::msg::TankingControl>("/tankowanie/sterowanie", 10);
    tnk_ctrl_timer_ = this->create_wall_timer(500ms, std::bind(&TankingController::publishTnkCtrl, this));
    read_thread_ = std::thread(&TankingController::consoleRead, this);
}

TankingController::~TankingController()
{
}

void TankingController::consoleRead()
{
    std::string buf(256, ' ');
    while(scanf("%s", &buf[0]) && rclcpp::ok())
    {
        if (buf[0] == 'q')
        {
            exit(0);
        }
        else if (buf[0] == 'v')
        {
            if (buf[2] != '_')
            {
                printf("Error: expected '_' at 3rd place in the command");
                continue;
            }
            std::string val_s = buf.substr(3);
            unsigned long val_u = 0;
            try {
                val_u = std::stoul(val_s);
            }
            catch (std::invalid_argument&) {}
            catch (std::out_of_range&) {}
            if (val_u > 100)
                continue;
            if (buf[1] == '1')
            {
                tnk_ctrl_msg_.valve_1 = val_u;
            }
            else if (buf[1] == '2')
            {
                tnk_ctrl_msg_.valve_2 = val_u;
            }
            publishTnkCtrl();
        }
        else if (buf[0] == 'd')
        {
            tnk_ctrl_msg_.decouple = true;
            publishTnkCtrl();
        }
        else if (buf[0] == 'f')
        {
            tnk_ctrl_msg_.decouple = false;
            publishTnkCtrl();
        }
        else if (buf[0] == 't')
        {
            if (buf.size() > 1)
            {
                if (buf[1] == '1')
                    test1();
            }
        }
    }
}

void TankingController::publishTnkCtrl()
{
    tnk_ctrl_msg_.header.stamp = this->now();
    tnk_ctrl_pub_->publish(tnk_ctrl_msg_);
}

void TankingController::test1()
{
    for (int i=0; i<=100; i++)
    {
        tnk_ctrl_msg_.valve_1 = i;
        publishTnkCtrl();
        usleep(30000);
    }
    usleep(500000);
    for (int i=100; i>=0; i--)
    {
        tnk_ctrl_msg_.valve_1 = i;
        publishTnkCtrl();
        usleep(30000);
    }
    usleep(500000);
    for (int i=0; i<=100; i++)
    {
        tnk_ctrl_msg_.valve_2 = i;
        publishTnkCtrl();
        usleep(30000);
    }
    usleep(500000);
    for (int i=100; i>=0; i--)
    {
        tnk_ctrl_msg_.valve_2 = i;
        publishTnkCtrl();
        usleep(30000);
    }
    tnk_ctrl_msg_.decouple = true;
    publishTnkCtrl();        
    usleep(3*1000*1000);
    tnk_ctrl_msg_.decouple = false;
    publishTnkCtrl();
}