all:
	make PFD.zip

clean:
	rm -f PFD.log
	rm -f PFD.zip
	rm -f RunPFD
	rm -f RunPFD.tmp
	rm -f TestPFD

diff: RunPFD RunPFD.in RunPFD.out
	RunPFD < RunPFD.in > RunPFD.tmp
	diff RunPFD.out RunPFD.tmp
	rm RunPFD.tmp

doc: PFD.c++
	doxygen Doxyfile

turnin-list:
	turnin --list tmtorres cs378pj1

turnin-submit: PFD.zip
	turnin --submit tmtorres cs378pj1 PFD.zip

turnin-verify:
	turnin --verify tmtorres cs378pj1

PFD.log:
	git log > PFD.log

PFD.zip: PFD.c++ PFD.h PFD.log RunPFD.c++ RunPFD.in RunPFD.out SpherePFD.c++ TestPFD.c++ TestPFD.out
	zip -r PFD.zip html/ PFD.c++ PFD.h PFD.log RunPFD.c++ RunPFD.in RunPFD.out SpherePFD.c++ TestPFD.c++ TestPFD.out

RunPFD: PFD.h PFD.c++ RunPFD.c++
	g++ -pedantic -std=c++0x -Wall PFD.c++ RunPFD.c++ -o RunPFD

RunPFD.out: RunPFD RunPFD.in
	valgrind RunPFD < RunPFD.in >& RunPFD.out

TestPFD: PFD.h PFD.c++ TestPFD.c++
	g++ -pedantic -std=c++0x -Wall PFD.c++ TestPFD.c++ -o TestPFD -lcppunit -ldl

TestPFD.out: TestPFD
	valgrind TestPFD >& TestPFD.out