#!/bin/bash

echo "Today is `date +'%A'`, `date +'%d'` `date +'%B'`, `date +'%Y'`."
pratyush=$(( `date -d "September 14, 2013" +'%s'` - `date +'%s'` ))
x1=$(( $pratyush / (60*60*24*7) ))
y1=$(( $pratyush / (60*60*24) ))
z1=$(( $pratyush / (60*60) ))
weeks1=$x1
days1=$(( $y1 - $(( 7*$x1 )) ))
hours1=$(( $z1 - $(( 24*$y1 )) ))

ayush=$(( `date -d "April 2, 2013" +'%s'` - `date +'%s'` ))
x2=$(( $ayush / (60*60*24*7) ))
y2=$(( $ayush / (60*60*24) ))
z2=$(( $ayush / (60*60) ))
weeks2=$x2
days2=$(( $y2 - $(( 7*$x2 )) ))
hours2=$(( $z2 - $(( 24*$y2 )) ))

bhargava=$(( `date -d "May 27, 2013" +'%s'` - `date +'%s'` ))
x3=$(( $bhargava / (60*60*24*7) ))
y3=$(( $bhargava / (60*60*24) ))
z3=$(( $bhargava / (60*60) ))
weeks3=$x3
days3=$(( $y3 - $(( 7*$x3 )) ))
hours3=$(( $z3 - $(( 24*$y3 )) ))

echo "There are $weeks1 weeks $days1 days $hours1 hours left for the birthday of Pratyush"
echo "There are $weeks2 weeks $days2 days $hours2 hours left for the birthday of Ayush"
echo "There are $weeks3 weeks $days3 days $hours3 hours left for the birthday of Bhargava"

echo "Thank you for asking, `whoami`"

myuptime=`cat /proc/uptime | grep -oE '[0-9]+.[0-9]+ '`
rounded_uptime=$( printf "%.0f" $myuptime )
uptime_in_days=$(( $rounded_uptime / (60*60*24) ))
uptime_in_hours=$(( $rounded_uptime / (60*60) ))
uptime_in_minutes=$(( $rounded_uptime / 60 ))
days_uptime=$uptime_in_days
hours_uptime=$(( $uptime_in_hours - $(( 24*$uptime_in_days )) ))
minutes_uptime=$(( $uptime_in_minutes - $(( 60*$uptime_in_hours )) ))

echo "Your system has been running for $days_uptime days, $hours_uptime:$minutes_uptime hours."

homefolder_location=`df -h / | grep -o '/dev/[a-zA-Z0-9]*'`
disk_usage=`df -h / | grep -oE '[[:digit:]]+%'`

echo "The current disk on which your home folder is located is $homefolder_location and is $disk_usage full"

. /etc/lsb-release

echo "You are running $DISTRIB_ID $DISTRIB_CODENAME and $DISTRIB_RELEASE with Kernel `uname -r`"

total_ram_kb=`grep MemTotal /proc/meminfo | awk '{print $2}'`
free_ram_kb=`grep MemFree /proc/meminfo | awk '{print $2}'`
used_ram_kb=$(( $total_ram_kb-$free_ram_kb ))
total_ram_gb=$(( $total_ram_kb / 1000000 ))
used_percentage=$(( $used_ram_kb*100/$total_ram_kb ))

echo "Your machine has $total_ram_gb GB RAM. Of which $used_percentage% is in use."

words_in_bash=`wc -w scripts/myinfo.sh | grep -oE [0-9]+`
lines_in_bash=`wc -l scripts/myinfo.sh | grep -oE [0-9]+`
chars_in_bash=`sed 's/[ \n\t]*//g' scripts/myinfo.sh | wc -m`

echo "This script has $words_in_bash words, $lines_in_bash lines and $chars_in_bash characters (without counting whitespaces)"
