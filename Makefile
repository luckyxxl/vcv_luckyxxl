
SOURCES = $(wildcard src/*.cpp)

include ../../plugin.mk


dist: all
	mkdir -p dist/luckyxxl
	cp LICENSE* dist/luckyxxl/
	cp plugin.* dist/luckyxxl/
	cp -R res dist/luckyxxl/
