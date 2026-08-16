# VHAL - Vendor-only AAOS 15 SocketCAN bridge starter

This repository is intentionally **vendor-focused** and mirrors how a CAN-to-VHAL bridge is typically integrated in AAOS 15 under:

```text
vendor/<your_vendor>/automotive/vhal_can_bridge/
```

In this repo, the starter implementation is placed under:

```text
vendor/example/automotive/vhal_can_bridge/
```

## Direction and scope

- **Vendor-only integration**: no product/lunch redesign is included.
- **SocketCAN-only transport**: VHAL logic is transport-agnostic and reads Linux CAN frames via SocketCAN.
- **`vcan0` and `can0` parity**: interface name is runtime-configurable, so development on `vcan0` and deployment on `can0` use the same bridge logic.
- **Minimal staged evolution**:
  - Phase 1: one CAN frame + one signal + one AAOS property.
  - Phase 2: starter DBC and expanded demo signals (HVAC, powertrain RPM, speed, gear).
- **DBC parser still deferred**: no runtime DBC parser yet; mappings are DBC-aligned but explicitly coded.

## Current signal/property demo set

- `0x123.vehicle_speed_kph` → `PERF_VEHICLE_SPEED` (float)
- `0x200.engine_rpm` → demo engine RPM property placeholder (float)
- `0x200.gear_position` → demo gear property placeholder (int32)
- `0x201.hvac_fan_level` → **vendor custom read-only** property (int32)
- **vendor custom read-write** property implemented via `HandleSetProperty(...)` (int32), with CAN TX wiring marked TODO.

## DBC starter

- [`vendor/example/automotive/vhal_can_bridge/docs/dbc/vhal_can_bridge_demo.dbc`](vendor/example/automotive/vhal_can_bridge/docs/dbc/vhal_can_bridge_demo.dbc)

## How this connects to Android car APIs

1. SocketCAN receiver reads CAN frames.
2. Portable core decoder extracts demo signals from known CAN IDs.
3. VHAL glue maps decoded signals into property updates.
4. CarService consumes VHAL property updates; apps read/write via `CarPropertyManager` based on property access mode.

See detailed architecture and drop-in guidance:

- [`vendor/example/automotive/vhal_can_bridge/docs/architecture.md`](vendor/example/automotive/vhal_can_bridge/docs/architecture.md)
