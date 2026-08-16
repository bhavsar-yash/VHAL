# SELinux starter notes

This directory contains minimal starter policy snippets for the vendor CAN VHAL service.

- `vendor_can_vhal.te`: domain skeleton + raw CAN capability starter.
- `file_contexts`: labels service binary.

TODO for production:
- integrate with device/vendor sepolicy locations
- narrow permissions to only required socket types and binder/service usage
- validate with `audit2allow` only as debugging aid (not as final policy source)
