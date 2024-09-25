#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

class SubscribeAddressBook : public rclcpp::Node {
public:
    SubscribeAddressBook() : Node("subscribe_address_book") {
        auto topic_callback = [this](more_interfaces::msg::AddressBook::UniquePtr msg) {
            RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->first_name.c_str());
        };

        subscription_ = this->create_subscription<more_interfaces::msg::AddressBook>(
            "address_book", 10, topic_callback);
    }

private:
    rclcpp::Subscription<more_interfaces::msg::AddressBook>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SubscribeAddressBook>());
    rclcpp::shutdown();

    return 0;
}
