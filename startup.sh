#!/usr/bin/env bash

setxkbmap -option caps:escape
xset r rate 300 50
xinput --set-prop 9 'libinput Accel Profile Enabled' 0, 1
xset m 0 0
#VM
#xrandr --size 1920x1080
feh --bg-fill ~/.wallpapers/background
dwmblocks &
dunst &
picom &
