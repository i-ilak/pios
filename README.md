# piOS: Tipping my toes into baremetal programming
[![Build](https://github.com/i-ilak/pios/actions/workflows/Build.yml/badge.svg)](https://github.com/i-ilak/pios/actions/workflows/Build.yml)

So piOS might sound like I'm on a grand mission to create the ultimate Raspberry Pi operating system, 
but truth be told, I just liked the name. What's really happening here is a journey through various online tutorials
about baremetal coding on the Pi, which you can check out in the list below [(see here)](#Notes). 
I'm stepping into the world of embedded software development with almost zero prior experience, and unfortunately, 
my university days didn't touch on this domain. This project is purely a hobby, sparked by a desire to dip my toes 
into the world of embedded systems.

What is the end goal? To be honest, I don't know yet. The things that I would like to get working but are not yet:
* **Filesystem**: I don't want to continue to compile everything I need into the kernel. There is a SD card so let's use it.
* **Bluethooth**: Would be nice to connect an external keyboard or something like this? I have no idea how hard this is.
* **TCP/IP stack**: Would be fun to try to get it connected to the internet. 

## Notes
Honestly, if you are interested in baremetal programming, you can probably use any of the below projects as a 
starting point. Since I don't believe there is one perfect source for the relevant topics, here is a short summary of
what I have been following, reading, and using as template along the way. I'd like to make clear that a good chunk of 
the code in this repository is almost 1-to-1 from the below projects. The goal here was not to create something new
(at least not yet), but rather use the code from these projects to explore how things work, what you can do with it, 
and of course also what potential pitfalls are. I changed some things were I found it appropriate 
(building the project, structure of the code, documentation, etc.).
* [armOS (*Thanos Koutroubas*)](https://github.com/thanoskoutr/armOS): This was the first source I followed and you
will see a large overlap between this project and mine. But this project goes much more into the direction of creating
an OS that I plan. Nevertheless, it was a good source to start and gave me some nice idea of how to structure my
project.
* [Bare metal Raspberry Pi 3 tutorials (*Zoltan Baldaszti*)](https://github.com/bztsrc/raspi3-tutorial/): Really nice 
tutorial that introduces the basic ways of how HW and SW should interact with each other. The individual lessons are
not really connected, so it's quite easy to just pick out what you need.
* [Building an Operating System for the RaspberryPi (*Jake Sandler*)](https://jsandler18.github.io) Has a nice
introduction to setting up dynamic memory allocation for 32-bit systems, but seems a little bit light on some details.
* [Raspberry Pi bare metal experiments (*Brian Widdas*)](https://github.com/brianwiddas/pi-baremetal)
* [Learning operating system development using Linux kernel and Raspberry Pi (*Sergey Matyukevich*)](https://github.com/s-matyukevich/raspberry-pi-os)
Lots of explanations about concepts related to OS development using the Linux kernel and Pi OS as an example.
Helps to understand some of the code out there doing things/solving things and seeing the bigger picture!

One thing that I haven't mentioned so far, but was basically open the whole time, is the documentation of the SoC, 
Broadcom 2835/2837. 

## How to build the project?
The tricky part for this project is the compiler. Since we are writing code that is supposed to run on an ARM 
processor, you will need the corresponding compiler. All compilers to build for ARM CPU's can be found on
[ARM's website](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). 
You will most probably have to cross-compile (`x86`->`arm`) and you will need to be careful if you are compiling the 
kernel for a `32-bit` or a `64-bit` CPU (`arm-none-eabi` vs `aarch64-none-elf`). 
The `CMakeLists.txt` file has all the logic needed to handle which compiler to pick depending on the Raspberry Pi 
Model you want to compile this code for (just make sure they are installed and in the `$PATH`). 
You will find in the top-level `CMakeLists.txt` file a variable that's called `MODEL_X`, where `X` can be `[0,1,2,3,4]`. 
`MODEL_3` and `MODEL_4` have a `64bit` CPU and thus need the `aarch64` compiler.

*Note*: This project was started with a `32bit` board (Pi 0) and thus most of the code was initially written with the 
ARMv6 architecture in mind. For example, the entire memory management code was written with ATAGS (ARM Tags) in mind, 
which where replaced by DTB's (device tree blob's) in ARMv8-a and would thus need a refresh. 
I will do this at some point, but for now I will focus more on exploring some of the capabilities of the `32bit` 
version of the board. 
In short, the `64bit` boards have a lot less functionality compared to the `32bit` boards with this kernel as of now.   

Once you have all of this setup, you should be able to simply `cd` into the root of this repo and run
(assuming you have `cmake` and `ninja-build` installed on your system)
```bash
cmake -G Ninja -B ./build -S .
cmake --build ./build
```
or you can use Docker
```bash
DOCKER_BUILDKIT=1 docker build --progress=plain -f Dockerfile --rm -t pi_os:latest . --output ${PATH_TO_WHERE_YOU_WANT_THE_ELF_AND_IMG}
```

## How to run the kernel?
While the ultimate goal of course is to run the kernel on a Pi, for development it is useful to also run it in `qemu`.
For the `32-bit` version you can use
```bash
# ARMv6 / 32 bit
qemu-system-arm -M raspi0 -serial null -serial stdio -kernel $PATH_TO_ELF/kernel.elf
# ARMv8-a / 64 bit
qemu-system-aarch64 -M raspi3b -serial null -serial stdio -kernel $PATH_TO_ELF/kernel7.elf
```

*Note:* To run the code with `qemu` you use the `.elf`, i.e. the full executable. If you want to test the kernel out 
on a real Raspberry Pi, then you need to move the `.img` file onto the SD card. 

## How to generate documentation?
To generate the documentation you can run
```bash
doxygen .doxyfile
```
Please make sure to install `doxygen` and `graphviz`.
