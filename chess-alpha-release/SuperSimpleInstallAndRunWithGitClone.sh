https://github.com/MICHAEL-ZENGZF/UCI_EECS22L_P1.git
git checkout server
rm -rf build
mkdir build
cd build
cmake ..
make
cd ..
./bin/chess
