Pictures to ASCII-ART
Format Supported : .jpeg, .jpg, .png, .ppm

To be able to compile without any problems, you will need CMake and GCC.

To use it you'll need few dependencies.
In order for my project to read jpg and png, I used libpng and  libjpeg, so you need these.
```
sudo apt install libjpeg-dev
sudo apt install libpng-dev
```

Once this is done.
You need to be in the root of the repo, then
```
mkdir build; cd build/; cmake ..; make; cp src/ascii ../; cd ../
```

After that, you'll have a binary that convert any pictures into an ascii art in the root directory.