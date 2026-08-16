#include <cassert>

#include "vhalcore/CanVhalPipeline.h"
#include "vhalcore/DevelopmentCanTransport.h"
#include "vhalcore/SignalModel.h"
#include "vhalcore/VehiclePropertyValue.h"

int main() {
    vhalcore::DevelopmentCanTransport transport;

    vhalcore::CanSignalDecoder decoder({
        {.name = "vehicle_speed_mps",
         .canId = 0x123,
         .startByte = 0,
         .lengthBytes = 2,
         .scale = 0.01F,
         .offset = 0.0F,
         .littleEndian = true},
    });

    vhalcore::PropertyMapper mapper;
    vhalcore::CanVhalPipeline pipeline(transport, std::move(decoder), std::move(mapper));

    bool published = false;
    pipeline.start([&published](const vhalcore::VehiclePropertyValue& value) {
        published = true;
        assert(value.property == vhalcore::PropertyId::PERF_VEHICLE_SPEED);
        assert(!value.floatValues.empty());
        assert(value.floatValues[0] == 10.0F);
    });

    assert(published);
    pipeline.stop();

    return 0;
}
