all: arithm_static arithm_statictest arithm_dynamic-static arithm_dynstattest arithm_dynamic-dynamic arithm_dyndyntest

arithm_static: libarithm.a
	gcc main.c -L. -larithm -o arithm_static
libarithm.a:
	gcc -c sum.c sub.c
	ar rc libarithm.a sum.o sub.o
	ranlib libarithm.a
arithm_statictest: 
	./arithm_static 1 1
	./arithm_static

arithm_dynamic-static: libdynarithm.so
	gcc main.c -L. -larithm -o arithm_dynstat
	LD_LIBRARY_PATH=/root:${LD_LIBRARY_PATH}
	export LD_LIBRARY_PATH
libdynarithm.so: labfpic.o
	gcc -shared sum.o sub.o -o libdynarithm.so
labfpic.o: 
	gcc -fPIC -c sum.c sub.c
arithm_dynstattest: 
	./arithm_dynstat 3 3
	./arithm_dynstat

arithm_dynamic-dynamic: libdyn.so
	gcc maindyn.c -o arithm_dyndyn -ldl
libdyn.so: labfpic.o
	gcc -shared sum.o sub.o -o libdyn.so	
arithm_dyndyntest:
	./arithm_dyndyn 3 1
	./arithm_dyndyn
	 	
clean:
	rm -f *.a *.o *.so
