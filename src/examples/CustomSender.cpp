#include "vk_sdk/capnp/Shared.hpp"
#include "vk_sdk/capnp/imu.capnp.h"
#include <iostream>
#include <memory>
#include <vk_sdk/Sdk.hpp>

int main() {
    auto visualkit = vkc::VisualKit::create(std::nullopt);

    // Check that the object has been created successfully before proceeding.
    if (visualkit == nullptr) {
        std::cout << "Failed to create visualkit connection." << std::endl;
        return -1;
    }

    // Make a capnp object.
    auto builder = std::make_unique<capnp::MallocMessageBuilder>();
    auto imuBuilder = builder->initRoot<vkc::Imu>();

    // Note: 
    // You should set the fields for the imu via `imuBuilder` if you want to see something sensible.
    // For brevity here, we skip setting the fields here.
    
    // <INSERT INITIALIZATION OF FIELDS HERE>

    auto shared = vkc::Shared<vkc::Imu>(std::move(builder));

    // Obtain a receiver from the sink so that we can write to it.
    auto imuReceiver = visualkit->sink().obtain("S0/imu", vkc::Type<vkc::Imu>());
    
    // Start the sink for it to start receiving messages.
    visualkit->sink().start();

    // Call the receiver of the sink to handle the message.
    imuReceiver->handle(shared);

    // Stop the sink. 
    //
    // You may pass `true` here if you want the sink to block until all data from the source has been sent to it.
    //
    // See the documentation for `stop` for more information how to do this correctly.
    visualkit->sink().stop(false);

    return 0;
}