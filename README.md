# Compile 

## Folder

```bash
mkdir build
cd build
```

## Configure

`cmake ..`

## Compile

Compile both static and dynamic libraries with the following comman 

`cmake --build .`

# Variables

You can pass variables for cmake after the build command 

## BUILD_STATIC_LIBS

Build static library

## BUILD_DYNAMIC_LIBS

Build dynamic (shared) library

# Folders
Dynamic library found in `build/lib/dynamic`
Static library found in `build/lib/static`
