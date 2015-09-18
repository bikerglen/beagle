#!/bin/sh
rm /lib/firmware/BB-BONE-LOGIBONX-SLOW.dtbo
dtc -O dtb -o BB-BONE-LOGIBONX-SLOW.dtbo -b 0 -@ BB-BONE-LOGIBONX-SLOW.dts
cp BB-BONE-LOGIBONX-SLOW.dtbo /lib/firmware
sh -c "echo -0 > /sys/devices/bone_capemgr.9/slots "
sh -c "echo -4 > /sys/devices/bone_capemgr.9/slots "
sh -c "echo -5 > /sys/devices/bone_capemgr.9/slots "
sh -c "echo -6 > /sys/devices/bone_capemgr.9/slots "
sh -c "echo -7 > /sys/devices/bone_capemgr.9/slots "
sh -c "echo BB-BONE-LOGIBONX:SLOW > /sys/devices/bone_capemgr.9/slots "
cat  /sys/devices/bone_capemgr.9/slots
