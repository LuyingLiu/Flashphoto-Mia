all: libimagetools.a flashphoto mia

check-style:
	cd src/flashphoto; make check-style
	cd src/mia; make check-style

check-style-cse:
	cd src/flashphoto; make check-style-cse
	cd src/mia; make check-style-cse

libimagetools.a:
	cd src/imagetools; make -j

flashphoto:
	cd src/flashphoto; make -j

mia:
	cd src/mia; make -j

doc:
	doxygen docs/Doxyfile

tests:
	cd src/tests; make -j

clean:
	rm -rf build

clobber: clean
	cd src/external/MinGfx; make clobber
	cd src/external/googletest; make clean
