# Architecture: AAOS 15 Vendor VHAL + CAN/vCAN Bridge (Starter)

## Goal
Provide a clean first iteration for one complete signal path:

1. Receive CAN frame from development transport
2. Decode one signal (`vehicle_speed_mps`)
3. Map signal to AAOS property (`PERF_VEHICLE_SPEED`)
4. Feed mapped value to vendor VHAL publishing point
5. Observe in app via `CarPropertyManager`

## Layering

```text
[Transport]
  DevelopmentCanTransport (dev-only)
  Future: SocketCanTransport / physical CAN
        |
        v
[Core Decoder + Mapping]
  CanSignalDecoder + PropertyMapper (portable, testable)
        |
        v
[VHAL Glue]
  CanVhalService (AAOS layer, TODO-marked AIDL exact integration)
        |
        v
[AAOS Framework]
  CarService -> CarPropertyManager
        |
        v
[App]
  app/MainActivity.kt
```

## Development-only components

- `DevelopmentCanTransport`: emits one deterministic frame for local validation.
- `vhal-aidl` TODO stubs for exact AAOS 15 service registration / generated type wiring.

## Production-ready direction

- Keep `vhal-core` as reusable C++ library.
- Replace only transport implementation for vCAN/SocketCAN/real CAN.
- Keep decoder and mapper stable.
- Wire output conversion from `VehiclePropertyValue` to platform `VehiclePropValue` in vendor VHAL implementation.

## AAOS 15 integration notes

- Use AIDL VHAL architecture patterns in AAOS 15.
- Exact include paths and namespace names for generated vehicle AIDL headers can differ by branch; this starter keeps TODO markers where tree-specific names must be finalized.
- Service init/VINTF snippets are scaffolding only and must be verified in target device tree.
