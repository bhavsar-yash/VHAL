#!/bin/sh
set -eu

IFACE="${1:-vcan0}"
RAW_SPEED="${2:-2710}" # 0x0A96 => 27.10 kph with scale 0.01

# ID 0x123, first two bytes little-endian vehicle_speed_kph raw value.
LOW=$(printf '%02X' $((RAW_SPEED & 0xFF)))
HIGH=$(printf '%02X' $(((RAW_SPEED >> 8) & 0xFF)))

# Requires can-utils (cansend)
cansend "$IFACE" "123#${LOW}${HIGH}000000000000"
