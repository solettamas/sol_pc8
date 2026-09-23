#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <random>

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
        timer_ = this->create_wall_timer(500ms, std::bind(&SensorSimulator::timer_callback, this));
    }

private:
    void timer_callback()
    {
        static std::default_random_engine generator(std::random_device{}());
        static std::uniform_real_distribution<float> distribution(0.2f, 2.5f);
        
        auto message = sol_pc8::msg::Distances();

        for (size_t i = 0; i < message.values.size(); i++) {
        message.values[i] = distribution(generator);
        }
        
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