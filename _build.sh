# ---------------------------------------------------------------------------
# snoop
# ---------------------------------------------------------------------------

# snoopd.lib
cd lib
qmake "CONFIG+=debug" "QT-=gui"
make
make clean
cd ..

# snoopd_gui.lib
cd lib
qmake "CONFIG+=debug" "QT+=gui" "QT+=widgets"
make
make clean
cd ..

# snoop.lib
cd lib
qmake "CONFIG+=release" "QT-=gui"
make
make clean
cd ..

# snoop_gui.lib
cd lib
qmake "CONFIG+=release" "QT+=gui" "QT+=widgets"
make
# make clean
cd ..

# ---------------------------------------------------------------------------
# app
# ---------------------------------------------------------------------------
qmake
make
