# Copyright (c) 2014 Ithai Levi @RLofC
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
#    1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
#
#    2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
#
#    3. This notice may not be removed or altered from any source
#    distribution.
BINARY = build/chipmunk
LDFLAGS += -L./deps/Chipmunk2D/build/src
LIBRARIES += -lchipmunk
CFLAGS += -DTARGET_OS_MAC=0 -DTARGET_OS_IPHONE=0 -DCP_USE_CGTYPES=0
CFLAGS += -I./deps/Chipmunk2D/include/chipmunk
include ../common.mk

deps/Chipmunk2D/src/libchipmunk.a:
	git clone https://github.com/slembcke/Chipmunk2D.git deps/Chipmunk2D
	cd deps/Chipmunk2D && mkdir build && cd build && cmake -DBUILD_DEMOS=OFF \
		-DINSTALL_DEMOS=OFF -DBUILD_SHARED=OFF -DINSTALL_STATIC=OFF .. &&  make

deps: deps/Chipmunk2D/src/libchipmunk.a
