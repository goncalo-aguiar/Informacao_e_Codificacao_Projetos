all:
	@(if [ ! -d build ]; then mkdir build; fi; cd build;\
	  if [ ! -d opencv-example-bin ]; then mkdir opencv-example-bin; fi; cmake ..; make)

clean:
	rm -rf build ../opencv-example-bin
