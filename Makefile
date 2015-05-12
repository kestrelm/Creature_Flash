FLASCC=~/Projects/CrossBridge/sdk/usr/bin/clang++
FILES = main.cpp gason.cpp MeshBone.cpp CreatureModule.cpp
INCLUDES = ./glm
AS3COMPILERARGS = java $(JVMARGS) -jar $(call nativepath, ~/Projects/CrossBridge/sdk/usr/lib/asc2.jar) -merge -md

build: $(FILES)
	~/Projects/CrossBridge/sdk/usr/bin/swig -as3 -module CreatureWrapper -outdir . -includeall -ignoremissing -o CreatureWrapper.cpp swig.h

	java $(JVMARGS) -jar $(call nativepath, ../../sdk/usr/lib/asc2.jar) -merge -md -import $(call nativepath,../../sdk/usr/lib/builtin.abc) -import $(call nativepath,../../sdk/usr/lib/playerglobal.abc) CreatureWrapper.as
	# rename the output so the compiler doesn't accidentally use both this .as file along with the .abc file we just produced
	mv CreatureWrapper.as CreatureWrapper.as3

	~/Projects/CrossBridge/sdk//usr/bin/clang++ $(BASE_CFLAGS) -O4 $(FILES) -I$(INCLUDES) -Wc++11-extensions -emit-swc=sample.Creature  -o Creature.swc

include ../Makefile.common

clean:
	rm -f *.swf *.swc *.bc *.exe *.as *.as3
