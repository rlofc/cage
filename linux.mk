# Copyright (c) 2014-2016 Ithai Levi @RLofC
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


# Include this makefile from your project to build your game
# using CAGE. Put this in your Makefile:
# 
#     GAME_BUILD_PATH = build/linux
#     GAME_BINARY = your-game
#     include deps/cage/linux.mk
#
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRENT_DIR := $(dir $(MKFILE_PATH))
CC = gcc # or clang
CFLAGS = `sdl2-config --cflags` -I$(CURRENT_DIR)/src/ -c
# Flip the optimization flag if you want to debug.
CFLAGS += -O3
# CFLAGS += -g3
ifeq ($(UNAME_S),Linux)
	# Note, CAGE is c89 compliant, but your game doesn't have to be.
	# Feel free to change this as needed.
	CFLAGS += -std=c89
endif
WARNINGS = -Werror -Wall -Wextra -pedantic-errors -Wformat=2 -Wno-import \
		   -Wimplicit -Wmain -Wchar-subscripts -Wsequence-point \
		   -Wmissing-braces -Wparentheses -Winit-self -Wswitch-enum \
		   -Wstrict-aliasing=2 -Wundef -Wshadow -Wpointer-arith \
		   -Wbad-function-cast -Wcast-qual -Wcast-align -Wwrite-strings \
		   -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes \
		   -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline \
		   -Wdisabled-optimization -Wunused-macros -Wno-unused
LDFLAGS =
LIBRARIES = `sdl2-config --static-libs` -L$(CURRENT_DIR)/build/ -lSDL2_image \
			-lSDL2_mixer -lcage
SOURCES = $(wildcard src/*.c)
OBJECTS = $(addprefix obj/,$(patsubst src/%,%,$(SOURCES:.c=.o) ) )

NO_COLOR=\x1b[0m
INFO_COLOR=\x1b[35;01m

.PHONY: all

all: $(GAME_BUILD_PATH)/$(GAME_BINARY) resources

$(CURRENT_DIR)/build/libcage.a:
	@cd $(CURRENT_DIR) && make build/libcage.a

$(GAME_BUILD_PATH)/$(GAME_BINARY): $(OBJECTS) $(CURRENT_DIR)/build/libcage.a
	@mkdir -p build
	@echo -e "Building $(INFO_COLOR)$(GAME_BUILD_PATH)$(GAME_BINARY)$(NO_COLOR)"
	@$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBRARIES)
	@echo "Done!"

obj/%.o: src/%.c
	@mkdir -p obj
	@echo -e "Building $(INFO_COLOR)$@$(NO_COLOR)"
	@$(CC) $< -o $@ $(CFLAGS) $(WARNINGS)

resources:
	@cp -rf res $(GAME_BUILD_PATH)

clean:
	rm -rf $(GAME_BUILD_PATH)$(GAME_BINARY) $(OBJECTS) $(GAME_BUILD_PATH)/res
