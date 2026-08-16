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
- **Minimal first implementation**: one CAN frame model, one signal decode path, one AAOS property mapping.
- **DBC deferred**: no full DBC parser in this phase; mappings are intentionally hard-coded for bring-up.

## How this connects to Android car APIs

1. SocketCAN receiver reads CAN frames.
2. Portable core decoder extracts one signal from one frame ID.
3. VHAL glue maps that signal to one AAOS property update.
4. CarService consumes VHAL property updates; apps read via `CarPropertyManager`.

See detailed architecture and drop-in guidance:

- [`vendor/example/automotive/vhal_can_bridge/docs/architecture.md`](vendor/example/automotive/vhal_can_bridge/docs/architecture.md)
