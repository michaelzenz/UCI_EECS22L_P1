

sudo apt update
sudo apt install pkg-config gtk+2.0 cmake git

rm -rf build
mkdir build
cd build
cmake ..
make
cd ..
./bin/chess
