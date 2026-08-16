# AAOS 15 Vendor VHAL + CAN/vCAN Starter

This repository contains a **first-iteration** modular starter for an AAOS 15 custom Vendor VHAL + CAN/vCAN integration.

## Intended data flow

```text
CAN simulator / vCAN / physical CAN
  -> transport abstraction
  -> CAN frame parser + signal decoder (vhal-core)
  -> property mapper (vhal-core)
  -> vendor VHAL glue (vhal-aidl)
  -> CarService
  -> app (CarPropertyManager)
```

## Module overview

- `vhal-core/` (portable C++17, AOSP-independent)
  - CAN frame model
  - transport callback boundary
  - signal decode + property mapping
- `vhal-aidl/` (AAOS integration scaffold)
  - place for AAOS 15 vendor VHAL service glue
  - transport callback -> property update publish path
- `selinux/`
  - starter policy for vendor VHAL service and CAN socket usage
- `app/`
  - minimal AAOS app skeleton subscribing to one property
- `docs/architecture.md`
  - detailed architecture and migration notes

## Development-only vs production-ready

- Development/prototype:
  - `vhal-core/sim/DevelopmentCanTransport` fixed frame emitter
  - TODO-marked VINTF/init/service registration stubs
  - simplified property value model in `vhal-core`
- Production direction:
  - replace development transport with SocketCAN/physical CAN implementation behind `ICanTransport`
  - wire `vhal-aidl` glue to real AAOS 15 generated AIDL vehicle interfaces in your full AOSP tree
  - harden SELinux policy and service lifecycle integration

## Quick host-side sanity check for core path

```bash
cd /home/runner/work/VHAL/VHAL/vhal-core
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

## Migration note (vCAN -> physical CAN)

No decoder/property-mapping API changes are required if transport changes from emulator/vCAN to physical CAN.
Only swap `ICanTransport` implementation (for example, `DevelopmentCanTransport` -> `SocketCanTransport`) and keep `CanSignalDecoder`, `PropertyMapper`, and VHAL publish flow unchanged.
