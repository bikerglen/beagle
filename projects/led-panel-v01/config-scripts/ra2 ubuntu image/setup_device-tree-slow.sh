#!/bin/sh
rm /lib/firmware/BB-BONE-LOGIBONE-SLOW.dtbo
dtc -O dtb -o BB-BONE-LOGIBONE-SLOW.dtbo -b 0 -@ BB-BONE-LOGIBONE-SLOW.dts
cp BB-BONE-LOGIBONE-SLOW.dtbo /lib/firmware
sh -c "echo -4 > /sys/devices/bone_capemgr.9/slots "
sh -c "echo -5 > /sys/devices/bone_capemgr.9/slots "
sh -c "echo -6 > /sys/devices/bone_capemgr.9/slots "
sh -c "echo BB-BONE-LOGIBONE:SLOW > /sys/devices/bone_capemgr.9/slots "
cat  /sys/devices/bone_capemgr.9/slots
#insmod logibone_ra2_dm.ko
