# Global
src_file = src/base.cc
compiler = g++
project_name = winda

setup:
	mkdir -p app build release

cleanup:
	rm -rf build/* app/* release/*

copyb:
	cp src/style.css app/style.css

copyr:
	cp src/style.css release/style.css


# Linux

LDF = $(shell pkg-config --cflags --libs gtkmm-4.0) -std=c++17 -Wall
LRF = $(shell pkg-config --cflags --libs gtkmm-4.0) -std=c++17 -Wall

lbuild: cleanup copyb lresource
	$(compiler) build/resources.o $(src_file) -o app/$(project_name) $(LDF)
	./ldeps.sh app/$(project_name) app/
	ldd app/$(project_name) > build/dependencies
	patchelf --set-rpath '$$ORIGIN/lib/x86_64-linux-gnu/' app/$(project_name)
	ldd app/$(project_name) > build/actual

lrelease: cleanup copyr lresource
	$(compiler) build/resources.o $(src_file) -o release/$(project_name) $(LRF)
	./ldeps.sh release/$(project_name) release/
	patchelf --set-rpath '$$ORIGIN/lib/x86_64-linux-gnu/' release/$(project_name)
	strip release/$(project_name)

lresource:
	glib-compile-resources --generate-source --target=build/resources.c src/resources.xml
	gcc -c build/resources.c -o build/resources.o $(shell pkg-config --cflags gio-2.0)


# Windows

WDF = $(shell pkg-config --cflags --libs gtkmm-4.0) -std=c++23 -Wall
WRF = $(shell pkg-config --cflags --libs gtkmm-4.0) -std=c++23 -mwindows

wbuild: cleanup wicon copyb
	$(compiler) build/resource.o $(src_file) -o app/$(project_name).exe $(WDF)
	ntldd -R app/$(project_name).exe | grep mingw64 | awk '{print $$3}' | cygpath -u -f - | xargs -I{} cp -u {} ./app/


wrealese: cleanup wicon copyr
	$(compiler) build/resource.o $(src_file) -o release/$(project_name).exe $(WRF)
	ntldd -R release/$(project_name).exe | grep mingw64 | awk '{print $$3}' | cygpath -u -f - | xargs -I{} cp -u {} ./release/


wicon:
	windres src/resource.rc -O coff -o build/resource.o
