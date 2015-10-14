#
#  Variant GDB/OpenOCD script.
#
#  Copyright (c) 2015 Thibaut VIARD. All right reserved.
#
#  This library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 2.1 of the License, or (at your option) any later version.
#
#  This library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#  See the GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this library; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#

# provide information about available hardware breakpoints
set remote hardware-breakpoint-limit 6
set remote hardware-watchpoint-limit 4

# connect to target, OpenOCD listens on port 3333 by default. Change this value in case of customization.
target remote localhost:3333

# reset and halt core
monitor reset halt

# print ARM Cortex-M registers values
info reg

# create 2 one-stop breakpoints at Reset_Handler() and at main()
thbreak Reset_Handler
thbreak main

# print breakpoints information
info breakpoints

# switch to asynchronous mode
monitor poll
