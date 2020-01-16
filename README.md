# C++ Exercise: Counting Areas

An application that can be used to count the number of coloured areas in an image.

## Build Instructions

Building this project is easy. Simply change the current the working directory to the project folder, and then run the following command:

```shell
g++ main.cpp image.cpp -o count-areas
```

## How to Use

Once the program has been complied, run the following command to start the program:

```shell
./count-areas <input-filename> --shape <height>,<width>
```

Please note that there is no space between <height> and <width>, otherwise it would cause an error. 

As for the specific example, run the following command. Please pay attention to the current working directory.

```shell
./count-areas sample.bin --shape 256,256
```