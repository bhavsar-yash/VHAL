#include "vhalaidl/CanVhalService.h"

namespace vhalaidl {

namespace {

std::vector<vhalcore::SignalDefinition> buildSignalDefinitions() {
    return {
        {.name = "vehicle_speed_mps",
         .canId = 0x123,
         .startByte = 0,
         .lengthBytes = 2,
         .scale = 0.01F,
         .offset = 0.0F,
         .littleEndian = true},
    };
}

}  // namespace

CanVhalService::CanVhalService(vhalcore::ICanTransport& transport)
    : mPipeline(transport,
                vhalcore::CanSignalDecoder(buildSignalDefinitions()),
                vhalcore::PropertyMapper()),
      mPropertyConfigs(buildPropertyConfigs()) {}

void CanVhalService::start() {
    mPipeline.start([this](const vhalcore::VehiclePropertyValue& value) { publishToVehicleHal(value); });
}

void CanVhalService::stop() {
    mPipeline.stop();
}

void CanVhalService::publishToVehicleHal(const vhalcore::VehiclePropertyValue& value) {
    (void)value;
    (void)mPropertyConfigs;
    // TODO(aaos15): convert vhalcore::VehiclePropertyValue to AIDL VehiclePropValue.
    // TODO(aaos15): convert PropertyConfigScaffold entries to AAOS property configs.
    // TODO(aaos15): publish via the branch-verified AAOS 15 vendor VHAL path.
    // Keep this method as the single integration point between core decoding and AAOS APIs.
}

std::vector<PropertyConfigScaffold> CanVhalService::buildPropertyConfigs() {
    return {
        {.property = vhalcore::PropertyId::PERF_VEHICLE_SPEED, .areaId = 0, .onChange = true},
    };
}

}  // namespace vhalaidl
