# Engine Simulator Mod loader
## Please read the full readme before complaining on discord
![Alt text](docs/public/loaderFullHD.png?raw=true)
---
## **Warning: project is in development and will change frequently**
---

## What is this?

This is a mod loader for the [engine-sim](https://github.com/ange-yaghi/engine-sim) by [ange-yaghi aka AngeTheGreat](https://github.com/ange-yaghi)

Original:  
This is a real-time internal combustion engine simulation **designed specifically to produce engine audio and simulate engine response characteristics.** It is NOT a scientific tool and cannot be expected to provide accurate figures for the purposes of engineering or engine tuning.

## How do I install it?

You install it like normally. All the lua files must be located in `assets/lua`! You can check the documentation for further detail on what vars you can use, functions and others.

Original:  
This is a code repository and might not look like other software that you're used to downloading and installing (if you're not familiar with programming). To download a ready-to-use version of the application, navigate to the [releases page](https://github.com/ange-yaghi/engine-sim/releases), find the most recent release (ex. `v0.1.5a`), click "Assets" and download the .zip file with a name that starts with `engine-sim-build`. Unzip this file, then run `bin/engine-sim-app.exe`. The simulator should then start normally.

## How do I build it? (Ignore this section if you're not a developer and you want to use the loader!)
**Note: this project currently only builds on Windows!**

### Step 1 - Clone the repository
```git clone --recurse-submodules https://github.com/loader-engine/engine-sim-modloader```

### Step 2 - Install CMake
Install the latest version of CMake [here](https://cmake.org/) if it's not already installed.

### Step 3 - Install Dependencies
You will need to install the following dependencies and CMake will need to be able to locate them (ie. they need to be listed on your PATH):

    1. SDL2
    2. SDL2_image
    3. Boost (make sure to build the optional dependencies)
    4. Flex and Bison

### Step 4 - Build and Run
From the root directory of the project, run the following commands:

```
mkdir build
cd build
cmake ..
cmake --build .
```

If these steps are successful, a Visual Studio solution will be generated in ```build```. You can open this project with Visual Studio and then run the ```engine-sim-app``` project. If you encounter an error telling you that you're missing DLLs, you will have to copy those DLLs to your EXE's directory.
