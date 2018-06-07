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
CC = gcc
CFLAGS += `sdl2-config --cflags` -I../../src/ -c
DEBUG ?= 0
ifeq (DEBUG, 1)
	CFLAGS += -g3
else
	CFLAGS += -O3
endif
ifeq ($(UNAME_S),Linux)
	CFLAGS += -std=c89
endif
WARNINGS = -Wall -Wno-unused-label
LDFLAGS +=
LIBRARIES += -L../../build/ -lSDL2_image -lSDL2_mixer -lcage `sdl2-config --static-libs` 
SOURCES = $(wildcard src/*.c)
OBJECTS = $(addprefix obj/,$(patsubst src/%,%,$(SOURCES:.c=.o) ) )

NO_COLOR=\x1b[0m
INFO_COLOR=\x1b[35;01m

.PHONY: all

all: $(BINARY) resources

../../build/libcage.a:
	@cd ../../ && make build/libcage.a

$(BINARY): deps $(OBJECTS) ../../build/libcage.a
	@mkdir -p build
	@echo -e "Building $(INFO_COLOR)$(BINARY)$(NO_COLOR)"
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)
	@echo "Done!"

obj/%.o: src/%.c
	@mkdir -p obj
	@echo -e "Building $(INFO_COLOR)$@$(NO_COLOR)"
	@$(CC) $< -o $@ $(CFLAGS) $(WARNINGS)

resources:
	@cp -rf res build/

clean:
	rm -rf $(BINARY) $(OBJECTS) build/res deps/**

deps:
