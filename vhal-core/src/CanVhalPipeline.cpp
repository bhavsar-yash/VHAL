#include "vhalcore/CanVhalPipeline.h"

#include <chrono>
#include <utility>

namespace vhalcore {

CanVhalPipeline::CanVhalPipeline(ICanTransport& transport,
                                 CanSignalDecoder decoder,
                                 PropertyMapper mapper)
    : mTransport(transport), mDecoder(std::move(decoder)), mMapper(std::move(mapper)) {}

void CanVhalPipeline::start(PropertyPublishCallback publish) {
    mTransport.start([this, publish = std::move(publish)](const CanFrame& frame) {
        const auto decodedSignals = mDecoder.decode(frame);
        const auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(
                             std::chrono::steady_clock::now().time_since_epoch())
                             .count();

        for (const auto& signal : decodedSignals) {
            const auto mapped = mMapper.mapToProperty(signal, now);
            if (mapped.has_value()) {
                publish(*mapped);
            }
        }
    });
}

void CanVhalPipeline::stop() {
    mTransport.stop();
}

}  // namespace vhalcore
