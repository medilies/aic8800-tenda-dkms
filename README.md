# aic8800-tenda-dkms

Linux driver for Tenda WiFi 6 USB adapters built on the AICSemi AIC8800 chip, packaged with DKMS.

It is the driver Tenda ships (`ax300-wifi-adapter-linux-driver.deb`, v1.0.1.2), patched to build on kernels 6.15 to 7.0. Tenda's package compiles the driver once at install time, so it stops working after the next kernel update. With DKMS, it is rebuilt on every kernel update.

Unofficial, not affiliated with Tenda or AICSemi.

## Symptom

The adapter mounts as a ~4 MB USB drive with Windows drivers, and `lsusb` shows `a69c:5721 aicsemi Aic MSC`. That drive is built into the adapter: ejecting it switches the adapter to WiFi mode, which this package does automatically.

## Install

Download the `.deb` from [Releases](https://github.com/medilies/aic8800-tenda-dkms/releases):

```sh
sudo apt install ./aic8800-tenda-dkms_*_all.deb
```

It replaces Tenda's packages (`ax900-wifi-adapter-linux-driver`, `w311miv6-pkg`) if installed.

## Devices

| Adapter | USB ID |
| --- | --- |
| Tenda W311MI V6 (AX300) | `2604:0013` |
| Tenda U2 (AX300) | `2604:0014` |
| Tenda U11 (AX900) | `2604:001f` |
| Tenda U11 Pro (AX900) | `2604:0020` |
| Any of the above in disk mode | `a69c:5721`, `a69c:5723`, `a69c:5725` |

Other AIC8800 IDs in the driver's table are untested: `modinfo aic8800_fdrv | grep alias`.

Tested with a Tenda U2 on Ubuntu 24.04, kernel 7.0. Also builds on 6.8 and 6.17.

## Build

```sh
sudo apt install debhelper dh-dkms
dpkg-buildpackage -b -us -uc   # writes ../aic8800-tenda-dkms_<version>_all.deb
```

## Other distributions

```sh
sudo cp -r src /usr/src/aic8800-tenda-1.0.1.2+kcompat1
sudo dkms install aic8800-tenda/1.0.1.2+kcompat1
sudo cp -r firmware/* /lib/firmware/
sudo cp udev/60-aic8800-modeswitch.rules /etc/udev/rules.d/
```

## Troubleshooting

```sh
lsusb | grep -iE '2604|a69c|368b'   # a69c:572x: still in disk mode
dkms status aic8800-tenda
sudo dmesg | grep -iE 'aic|rwnx'
```

## Changes from Tenda's driver

- Builds on kernels 6.15 to 7.0 (timer, wakeup source and cfg80211 API changes), behind kernel version checks.
- DKMS packaging. Firmware and the udev rule are package files instead of being copied by install scripts.
- The udev rule only fires when the disk is added.
