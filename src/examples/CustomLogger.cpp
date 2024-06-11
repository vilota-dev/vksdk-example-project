#include <iostream>
#include <memory>
#include <stdexcept>
#include <string_view>
#include <thread>
#include <vk_sdk/Sdk.hpp>

// Helper receiver to trigger logging by throwing an exception.
class MyThrowingReceiver : public vkc::Receiver<vkc::Image> {
    vkc::ReceiverStatus handle(const vkc::Message<vkc::Shared<vkc::Image>>& message) override {
        throw std::runtime_error("Custom receiver exception.");
    }
};

// Custom logging callback that logs to standard error.
void myLoggingCallback(vkc::LogLevel level, std::string_view message) {
    std::cerr << "[" << vkc::convertLogLevelToString(level) << "] " << message << std::endl;
}

int main() {
    // By default, if you do not install a logging callback, the library logs to stdout.
    // Here, we install our custom logging callback to log to stderr.
    vkc::installLoggingCallback(myLoggingCallback);

    auto visualkit = vkc::VisualKit::create();
    visualkit->source().install("S0/imu", std::make_unique<MyThrowingReceiver>());
    visualkit->source().start();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    visualkit->source().stop();
}