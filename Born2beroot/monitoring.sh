#!/bin/bash

#########################################################################
#                                                                       #
#               Architecture                                            #
#                                                                       #
#########################################################################

arch=$(uname -a)


#########################################################################
#                                                                       #
#               Physical Processors                                     #
#                                                                       #
#########################################################################

pcpu=$(grep "physical id" /proc/cpuinfo | sort | uniq | wc -l)


#########################################################################
#                                                                       #
#               Virtual Processors                                      #
#                                                                       #
#########################################################################

vcpu=$(grep "^processor" /proc/cpuinfo | wc -l)


#########################################################################
#                                                                       #
#               Memory Usage                                            #
#                                                                       #
#########################################################################

memt=$(free -m | awk '$1 == "Mem:" {print $2}')
memu=$(free -m | awk '$1 == "Mem:" {print $3}')
mempc=$(free -m | awk '$1 == "Mem:" {printf ("%.2f%%"), $3/$2*100}')


#########################################################################
#                                                                       #
#               Disk Usage                                              #
#                                                                       #
#########################################################################

dskt=$(df -Bg | grep '^/dev/' | grep -v '/boot$' | awk '{dt += $2} END {print dt}')
dsku=$(df -Bm | grep '^/dev/' | grep -v '/boot$' | awk '{du += $3} END {print du}')
dskpc=$(df -Bm | grep '^/dev/' | grep -v '/boot$' | awk '{dt += $2} {du += $3} END {printf ("%d%%"), du/dt*100}' )


#########################################################################
#                                                                       #
#               CPU Usage                                               #
#                                                                       #
#########################################################################

cpul=$(top -bn1 | grep '^%Cpu' | cut -c 9- | xargs | awk '{printf("%.1f%%", $1 + $3)}')


#########################################################################
#                                                                       #
#               Last Boot                                               #
#                                                                       #
#########################################################################

last=$(who -b | awk '$1 == "system" {print $3 " " $4}')


#########################################################################
#                                                                       #
#               LVM Active                                              #
#                                                                       #
#########################################################################

lvmt=$(lsblk | grep "lvm" | wc -l)
lvmu=$(if [ $lvmt -eq 0 ]; then echo no; else echo yes; fi)


#########################################################################
#                                                                       #
#               Active TCP connections                                  #
#                                                                       #
#########################################################################

ctcp=$(cat /proc/net/sockstat{,6} | awk '$1 == "TCP:" {print $3}')


#########################################################################
#                                                                       #
#               Logged Users                                            #
#                                                                       #
#########################################################################

ulog=$(users | wc -w)


#########################################################################
#                                                                       #
#               IP & MAC                                                #
#                                                                       #
#########################################################################

ipad=$(hostname -I)
maca=$(ip link show | awk '$1 == "link/ether" {print $2}')


#########################################################################
#                                                                       #
#               Sudo commands                                           #
#                                                                       #
#########################################################################

sudo=$(cat /var/log/sudo/sudo.log | grep COMMAND | wc -l)

#########################################################################
#########################################################################
##                                                                     ##
##              Script                                                 ##
##                                                                     ##
#########################################################################
#########################################################################

wall -n "========================================================================
- Architecture		:	$arch
- CPU physical		:	$pcpu
- vCPU			:	$vcpu
- Memory usage		:	$memu/${memt}MB ($mempc)
- Disk Usage		:	${dsku}MB/${dskt}GB ($dskpc)
- CPU load		:	$cpul
- Last boot		:	$last
- LVM use		:	$lvmu
- Connections TCP	:	$ctcp ESTABLISHED
- User log		:	$ulog
- Network		:	$ipad ($maca)
- Sudo			:	$sudo cmd
========================================================================="
