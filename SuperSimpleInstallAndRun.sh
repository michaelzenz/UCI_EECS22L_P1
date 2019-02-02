sudo apt update
sudo apt install pkg-config gtk+2.0 cmake libasound2

sudo wget -O /usr/local/bin/rmate https://raw.github.com/aurora/rmate/master/rmate
sudo chmod a+x /usr/local/bin/rmate

rm -rf build
mkdir build
cd build
cmake ..
make
cd ..
./bin/chess
