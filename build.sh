# remove the build directory that has the current code in it
echo "deleting the BUILD directory"
rm -rf build

echo "make a new BUILD directory to start the compiling process"
mkdir -p build
cd build

echo "cmake engage!"
cmake ..

echo "convert this to an executable application -- let's go!!"
cmake --build .
cd ..
echo "declare success -- hooray!"