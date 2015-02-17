all:
	make build

update:
	git pull

build:
	make debug
	make release
	make app_

debug: libsnoop_d libsnoop_test_d libsnoop_gui_d libsnoop_gui_test_d  

release: libsnoop libsnoop_test libsnoop_gui libsnoop_gui_test

libsnoop_d:
	qmake libsnoop.pro CONFIG+=debug
	make -j8 -f Makefile
	make clean -f Makefile

libsnoop_test_d:
	qmake libsnoop_test.pro CONFIG+=debug
	make -j8 -f Makefile
	make clean -f Makefile

libsnoop_gui_d:
	qmake libsnoop_gui.pro CONFIG+=debug
	make -j8 -f Makefile
	cp ui_* src
	make clean -f Makefile

libsnoop_gui_test_d:
	qmake libsnoop_gui_test.pro CONFIG+=debug
	make -j8 -f Makefile
	cp ui_* src
	make clean -f Makefile

libsnoop:
	qmake libsnoop.pro CONFIG+=release
	make -j8 -f Makefile
	make clean -f Makefile

libsnoop_test:
	qmake libsnoop_test.pro CONFIG+=release
	make -j8 -f Makefile
	make clean -f Makefile

libsnoop_gui:
	qmake libsnoop_gui.pro CONFIG+=release
	make -j8 -f Makefile
	cp ui_* src
	make clean -f Makefile

libsnoop_gui_test:
	qmake libsnoop_gui.pro CONFIG+=release
	make -j8 -f Makefile
	cp ui_* src
	make clean -f Makefile

app_:
	cd app && \
	qmake snoop_app.pro CONFIG+=release && \
	make -j8 -f Makefile && \
	make clean -f Makefile && \
	cd ..

clean:
	echo "clean in GNUmakefile"
	rm -rf *.o
	rm -rf moc_*.*
	rm -rf Makefile

