#include <memory>
#include <iostream>
#include <vk_sdk/Sdk.hpp>

// Our custom receiver to receiver messages.
class MyReceiver : public vkc::Receiver<vkc::Image> {
    // Override this method to handle messages.
    vkc::ReceiverStatus handle(const vkc::Message<vkc::Shared<vkc::Image>>& message) override {
        auto image = message.payload.reader();
        std::cout << "Received image"
                  << " (width = " << image.getWidth() 
                  << ", height = " << image.getHeight() 
                  << ", gain  = " << image.getGain() 
                  << ", exposure_time = " << image.getExposureUSec()
                  << ")." << std::endl;
        return vkc::ReceiverStatus::Open;
    }
};

int main() {
    auto visualkit = vkc::VisualKit::create(std::nullopt);

    // Check that the object has been created successfully before proceeding.
    if (visualkit == nullptr) {
        std::cout << "Failed to create visualkit connection." << std::endl;
        return -1;
    }
    
    // Create the receiver that was defined by us.
    auto myReceiver = std::make_unique<MyReceiver>();

    // Install the receiver into the data source so that the receiver can receive messages.
    visualkit->source().install("S1/camd", std::move(myReceiver));
    
    // Start the data source so messages can be received by `myReceiver`.
    visualkit->source().start();

    // Wait for the user to send the CTRL-C signal.
    vkc::waitForCtrlCSignal();

    // Stop the data source.
    //
    // You may pass `true` here if you want the soure to block until all data from it has been sent.
    // In this case, since data from visualkit is infinite, we do not want to block (as it will be forever).
    visualkit->source().stop(false);

    return 0;
}