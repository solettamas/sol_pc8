#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

#include "sol_pc8/msg/distances.hpp"

class DataProcessor : public rclcpp::Node
{
  public:
    DataProcessor() : Node("data_processor")
    {
      subscription_ = this->create_subscription<sol_pc8::msg::Distances>("distance", 10, std::bind(&DataProcessor::topic_callback, this, _1));
      publisher_ = this->create_publisher<std_msgs::msg::String>("warning", 10);
    }

  private:
    void topic_callback(const sol_pc8::msg::Distances & distances) const
    {
        auto message = std_msgs::msg::String();
        for (size_t i = 0; i < distances.values.size(); i++) {
            if (distances.values[i] < 0.3f) {
                message.data = "Object in first range at sensor #" + std::to_string(i) + "!";
                publisher_->publish(message);
            } else if (distances.values[i] < 0.8f)
            {
                message.data = "Object in second range at sensor #" + std::to_string(i) + "!";
                publisher_->publish(message);
            } else if (distances.values[i] < 1.5f)
            {
                message.data = "Object in third range at sensor #" + std::to_string(i) + "!";
                publisher_->publish(message);
            }

        }
    }
    rclcpp::Subscription<sol_pc8::msg::Distances>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DataProcessor>());
  rclcpp::shutdown();
  return 0;
}