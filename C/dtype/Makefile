dtype.so: dtype.c
	gcc dtype.c -shared -g -o libdtype.so.1 -std=c99 -Wall -Wextra -pedantic -fPIC

install: dtype.so
	sudo cp dtype.h /usr/include/
	sudo cp libdtype.so.1 /usr/lib/
	if [ -e /usr/lib/libdtype.so ]; then rm /usr/lib/libdtype.so; fi
	sudo ln -s /usr/lib/libdtype.so.1 /usr/lib/libdtype.so
	sudo /sbin/ldconfig
