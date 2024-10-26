# Pictures to ASCII-ART
## Format Supported

**.jpeg  .jpg  .png  .ppm**


## Usage
### Compilation
To be able to compile without any problems, you will need CMake and GCC.
To use it you'll need few dependencies.
In order for my project to read jpg and png, I used libpng and  libjpeg, so you need these.
```sh
sudo apt install libjpeg-dev
sudo apt install libpng-dev
```

Once this is done.
You need to be in the root of the repo, then
```sh
cmake -B build -S .; make -C build; cp build/src/ascii .
```
### Use of the binary
After that, you'll have a binary that convert any pictures into an ascii art in the root directory.
#### help
```sh
./ascii -?
```
#### exec
```sh
./ascii valid_path_to_picture.jpeg
./ascii valid_path_to_picture.png -r
./ascii -std valid_path_to_picture.ppm --mono -r -r
```

### Miscellaneous
It is also possible to convert .gif to a lot of pictures then apply the binary on each of them in order to display the gif in ASCII.
To do so you need ImageMagick.
```sh
sudo apt-get install imagemagick
```

Once you have ImageMagick you can simply run gif.sh as following
```sh
./gif.sh valid_path_to_gif.gif #-r can be used twice here in order to reduce the size of the gif as it may be massive and don't display well
```