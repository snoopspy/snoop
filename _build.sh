# ---------------------------------------------------------------------------
# lib
# ---------------------------------------------------------------------------
cd lib
make release -f make.file
cd ..

# ---------------------------------------------------------------------------
# app
# ---------------------------------------------------------------------------
cd app
qmake "CONFIG+=release"
make

