# AAOS 15 vendor SocketCAN VHAL bridge architecture

## Why this lives under `vendor/`

This bridge is hardware/vendor integration code (CAN topology, signal mapping, service policy), so it belongs under a vendor path in AAOS source trees, for example:

```text
vendor/<your_vendor>/automotive/vhal_can_bridge/
```

Keeping it in `vendor/` avoids coupling to generic emulator/product targets and matches typical AAOS bring-up ownership boundaries.

## SocketCAN-only transport

The transport layer uses Linux SocketCAN directly. No emulator-only transport is added in the VHAL path.

- Development: `vcan0`
- Vehicle hardware: `can0`

Only the interface name changes at runtime; the decoder and VHAL mapping logic stay identical.

## Starter DBC phase

The repository now includes a small starter DBC at:

```text
docs/dbc/vhal_can_bridge_demo.dbc
```

Scope is intentionally limited:
- vehicle speed
- powertrain RPM
- gear position
- HVAC fan level

The implementation is DBC-aligned but still uses explicit decode logic (no full DBC parser yet).

## Vendor custom properties (demo)

Two vendor custom demo properties are included in the VHAL glue layer:

- **Read-only** vendor property (updated from CAN): HVAC fan level.
- **Read-write** vendor property (set by client, echo update generated): drive mode request.

> TODO: Finalize property IDs, access metadata, and permissions against your exact AAOS 15 property config and AIDL interfaces in your platform tree.

## Why full DBC parsing is still deferred

During bring-up, explicit mappings keep behavior deterministic and simpler to debug.

Future work can replace hard-coded decode branches with parser-driven tables while preserving module boundaries.

## AAOS 15 integration shape (AIDL-oriented)

The bridge is structured to plug into a vendor VHAL integration layer:

1. `can/` receives SocketCAN frames.
2. `core/` decodes/massages signal values (portable C++ logic).
3. `vhal/` translates decoded values into AAOS property updates.
4. CarService surfaces these values to apps through `CarPropertyManager`.

> TODO: Wire concrete classes to your exact AAOS 15 VHAL service entry points and generated AIDL interfaces in your platform checkout.

## Recommended drop-in tree

```text
vendor/<your_vendor>/automotive/vhal_can_bridge/
├── Android.bp
├── core/
│   ├── include/vhal_can_bridge/
│   └── src/
├── can/
│   ├── include/vhal_can_bridge/
│   └── src/
├── vhal/
│   ├── include/vhal_can_bridge/
│   └── src/
├── init/
├── sepolicy/
├── app/
├── docs/
└── sim/
```

## Module responsibilities

- `core/`: Portable decode/mapping logic (no SocketCAN or Android framework dependencies).
- `can/`: SocketCAN transport and transport abstraction.
- `vhal/`: AAOS glue translating decoded signals to property updates.
- `init/`: init service startup declaration.
- `sepolicy/`: minimal SELinux policy starter for vendor daemon/service.
- `app/`: tiny AAOS app example using `CarPropertyManager`.
- `sim/`: optional development helpers (`vcan0`/`can0` frame injection).
