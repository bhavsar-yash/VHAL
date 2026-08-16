#!/bin/sh
set -eu

IFACE="${1:-vcan0}"

# Vehicle speed: 27.10 kph => raw 2710 (0x0A96) on 0x123
cansend "$IFACE" "123#960A000000000000"

# Powertrain RPM: 1200 rpm => raw 4800 (0x12C0) on 0x200
cansend "$IFACE" "200#C012000000000000"

# Gear position: 4 (Drive) on 0x202
cansend "$IFACE" "202#0400000000000000"

# HVAC fan level: 3 on 0x201
cansend "$IFACE" "201#0300000000000000"
