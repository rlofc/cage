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
CFLAGS = `sdl2-config --cflags` -c
CFLAGS += -O3
# CFLAGS += -g3
ifeq ($(UNAME_S),Linux)
	CFLAGS += -std=c89
endif
WARNINGS = -Werror -Wall -Wextra -pedantic-errors -Wformat=2 -Wno-import \
		   -Wimplicit -Wmain -Wchar-subscripts -Wsequence-point -Wmissing-braces \
		   -Wparentheses -Winit-self -Wswitch-enum -Wstrict-aliasing=2 -Wundef \
		   -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-qual -Wcast-align \
		   -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wmissing-prototypes \
		   -Wmissing-declarations -Wredundant-decls -Wnested-externs -Winline \
		   -Wdisabled-optimization -Wunused-macros -Wno-unused
LDFLAGS =
LIBRARIES = 
SOURCES = $(wildcard src/*.c)
INIPARSER_SOURCES = $(wildcard src/iniparser/*.c)
OBJECTS = $(addprefix obj/,$(patsubst src/%,%,$(SOURCES:.c=.o) ) )
INIPARSER_OBJECTS = $(addprefix obj/,$(patsubst src/%,%,$(INIPARSER_SOURCES:.c=.o) ) )
LIBRARY = build/libcage.a
CLDOC = python2 ~/.local/bin/cldoc


NO_COLOR=\x1b[0m
INFO_COLOR=\x1b[35;01m

.PHONY: all

all: $(LIBRARY) extra

$(LIBRARY): $(OBJECTS) $(INIPARSER_OBJECTS)
	@mkdir -p build
	@echo -e "Archiving $(INFO_COLOR)$(LIBRARY)$(NO_COLOR)"
	@ar rcs $(LIBRARY) $(OBJECTS) $(INIPARSER_OBJECTS)
	@echo "Done!"

obj/%.o: src/%.c
	@mkdir -p obj
	@echo -e "Building $(INFO_COLOR)$@$(NO_COLOR)"
	@$(CC) $< -o $@ $(CFLAGS) $(WARNINGS)

clean:
	@cd samples/state && $(MAKE) clean
	@cd samples/image && $(MAKE) clean
	@cd samples/sprite && $(MAKE) clean
	@cd samples/timeline && $(MAKE) clean
	@cd samples/callout && $(MAKE) clean
	@cd samples/collisions && $(MAKE) clean
	@cd samples/wizard && $(MAKE) clean
	@rm -rf $(LIBRARY) $(OBJECTS) $(INIPARSER_OBJECTS)
	@rm -rf docs/build

doc:
	@echo "Generating docs.."
	@awk -f literst.awk samples/state/src/state.c > docs/source/state_sample.rst
	@awk -f literst.awk samples/image/src/image.c > docs/source/image_sample.rst
	@awk -f literst.awk samples/sprite/src/sprite.c > docs/source/sprite_sample.rst
	@awk -f literst.awk samples/timeline/src/timeline.c > docs/source/timeline_sample.rst
	@awk -f literst.awk samples/callout/src/callout.c > docs/source/callout_sample.rst
	@awk -f literst.awk samples/collisions/src/collisions.c > docs/source/collisions_sample.rst
	@awk -f literst.awk samples/chipmunk/src/chipmunk.c > docs/source/chipmunk_sample.rst
	@awk -f literst.awk samples/wizard/src/wizard.c > docs/source/wizard.rst
	@awk -f literst.awk samples/tiled/src/tiled.c > docs/source/tiled.rst
	@doxygen cage
	@cp -Rf build/doxygen docs/build
	@cd docs && make html

extra: $(LIBRARY)
	cd samples/state && $(MAKE)
	cd samples/image && $(MAKE)
	cd samples/sprite && $(MAKE)
	cd samples/timeline && $(MAKE)
	cd samples/callout && $(MAKE)
	cd samples/collisions && $(MAKE)
	cd samples/wizard && $(MAKE)
