#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sol_pc8/msg/distances.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class SensorSimulator : public rclcpp::Node
{
public:
    SensorSimulator() : Node("sensor_simulator"), count_(0)
    {
        publisher_ = this->create_publisher<sol_pc8::msg::Distances>("distance", 10);
        timer_ = this->create_wall_timer(
            500ms, std::bind(&SensorSimulator::timer_callback, this));
    }

private:
    void timer_callback()
    {
        auto message = sol_pc8::msg::Distances();
        message.values = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sol_pc8::msg::Distances>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorSimulator>());
    rclcpp::shutdown();
    return 0;
}