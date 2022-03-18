# About

A command-line program used to perform various operations on bitmap images using **region quadtrees**.

It's name, *Quadtree Image Manipulation Program* (abbreviated as **QTIMP**), is inspired by **GIMP**.

# Usage

```
Usage: qtimp [OPTION]...
Image manipulation using quadtrees.

  -h, --help          Print help and exit
  -V, --version       Print version and exit
  -u, --union         Find the union of two bitmaps
  -n, --intersect     Find the intersection of two bitmaps
  -r, --invert        Complement all pixels in an image
  -p, --properties    Display bitmap properties
  -c, --convert       Convert a color image to B&W
  -i, --infile=FILE   Input one or more bitmaps
  -o, --outfile=FILE  Save the output to a specific path/image
  ```

# Requirements

An image must meet the below requirements to achieve proper results.
>- Must be a black-and-white bitmap image.
>- Image size must be a power of **two**.
>- To perform a union/intersection of two images, both images must be of the same size to obtain a proper output.
>- The bit depth of a bitmap image must be equal to 24 bit without a colortable.

# Examples

- Perform a **Union** of two images:

```
qtimp -u -i 512x512_hatandtie.bmp -i 512x512_specsandmustache.bmp -o 512x512_facewithtie.bmp
```

| Image One |                               Image Two |                             Union |
:-------------------------:|:-------------------------:|:-------------------------:
![](https://raw.githubusercontent.com/hyPnOtICDo0g/QTIMP/main/sample/input/512x512_hatandtie.bmp)  |  ![](https://raw.githubusercontent.com/hyPnOtICDo0g/QTIMP/main/sample/input/512x512_specsandmustache.bmp) | ![](https://raw.githubusercontent.com/hyPnOtICDo0g/QTIMP/main/sample/output/512x512_facewithtie.bmp)

- Perform an **Intersection** of two images:

```
qtimp -n -i 256x256_eyes.bmp -i 256x256_mouth.bmp -o 256x256_googlyface.bmp
```

| Image One |                               Image Two |                             Intersection |
:-------------------------:|:-------------------------:|:-------------------------:
![](https://raw.githubusercontent.com/hyPnOtICDo0g/QTIMP/main/sample/input/256x256_eyes.bmp)  |  ![](https://raw.githubusercontent.com/hyPnOtICDo0g/QTIMP/main/sample/input/256x256_mouth.bmp) | ![](https://raw.githubusercontent.com/hyPnOtICDo0g/QTIMP/main/sample/output/256x256_googlyface.bmp)

> Optionally, the `--invert` flag can be passed along with `--union` or `--intersect` to invert the union/intersection of two images.

```
qtimp -n -i 256x256_eyes.bmp -i 256x256_mouth.bmp -o 256x256_googlyface.bmp -r
```

Otherwise, it can be used to invert a single image as well.

- Invert a bitmap image:

```
qtimp -r -i 256x256_mouth.bmp -o 256x256_mouth_inverted.bmp
```

- Display properties of a bitmap image:

```
qtimp -p -i 64x64_checkerboard_regular.bmp
```

```
Properties (64x64_checkerboard_regular.bmp):
Image resolution: 64x64 | bit depth: 24
Total pixels: 12288 | whites: 6144 | blacks: 6144
Tree level: 6 | Total nodes: 85 | greys: 21 | whites: 32 | blacks: 32
Raw image size: ~0.012 MB | Quadtree size: ~0.004 MB | Size reduction: ~67%
```

- Convert a color bitmap to B&W:

```
qtimp -c -i 64x64_color_face.bmp -o 64x64_bw_face.bmp
```
# Download

- Binaries for Linux and Windows are available in the [releases](https://github.com/hyPnOtICDo0g/QTIMP/releases/latest) section.

# Build

## Dependencies

- GCC <=9.4.0 (linux)
- MinGW-w64 <=8.1.0 (windows)
- make
- git

> Building using other versions of GCC haven't been tested. Expect build errors.

## Procedure

- Clone the repo.

    ```
    git clone https://github.com/hyPnOtICDo0g/QTIMP --depth=1
    ```

- Navigate to the repo's folder.

    ```
    cd QTIMP
    ```

### Linux

```
make linux
````

### Windows

> Dependencies can be installed via [scoop](https://scoop.sh).

```
scoop install git mingw
make windows
```