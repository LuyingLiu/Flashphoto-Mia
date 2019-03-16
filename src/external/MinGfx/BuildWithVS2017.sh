if [ ! -d src ]; then
git clone https://github.com/ivlab/MinGfx.git src
cd src
git checkout csci3081
cd ..
mkdir -p build
cd build
cmake -G "Visual Studio 15 2017 Win64" -DAUTOBUILD_DEPENDENCIES=ON -DAUTOBUILD_EXECUTE_NOW=ON -DCMAKE_BUILD_TYPE=Release ../src
cmake --build . --target install
fi
