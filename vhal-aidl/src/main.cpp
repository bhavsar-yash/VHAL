#include "vhalaidl/CanVhalService.h"
#include "vhalcore/DevelopmentCanTransport.h"

int main() {
    // Development bootstrap. Replace DevelopmentCanTransport with SocketCAN transport for vCAN/physical CAN.
    vhalcore::DevelopmentCanTransport transport;
    vhalaidl::CanVhalService service(transport);

    // TODO(aaos15): register binder service and run binder threadpool.
    // TODO(aaos15): load property configs and area configs from final AAOS schema.
    service.start();
    service.stop();

    return 0;
}
