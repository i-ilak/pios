# piOS
This project is trying to build a simple OS for the RaspberryPi Zero W.
I have zero experience with embedded SW-development and unfortunately also never had a change to look at it in university. This is a hobby project that I started to get some familiarity with the subject.
I don't really have a clear goal, but I'm using other peoples projects on the internet as a reference and will see where it will take me... I have two RaspberryPi's (Zero W, Zero 2 W, and B+) and in the end I would like the code to run on all devices. 

## Notes
Since I don't belive there is one perfect source for the relevant topics, I spend a lot of time reading code from others.
* [armOS (*Thanos Koutroubas*)](https://github.com/thanoskoutr/armOS): This project is pretty much where I want to be at the end (I guess), and its nice to see what will be necessary for this...
    I'd like to make clear that a good chunk of the code in this repository is almost 1-to-1 from the armOS project. I really like what was done there and I think its nice to see how all of the parts are supposed to work in the end.
    I changed some things were I found it appropritate, but at the end of the day I think Thanos did a great job and since I'm just trying to learn more about the subject, this project was a godsend! 
* [Bare metal Raspberry Pi 3 tutorials (*Zoltan Baldaszti*)](https://github.com/bztsrc/raspi3-tutorial/): Really nice tutorial that introduces the basic ways of how HW and SW should interact with each other.

To build the project run
```bash
DOCKER_BUILDKIT=1 docker build --progress=plain -f Dockerfile --rm -t pi_os:latest . --output ./export/
```

To run it in `qemu` you can use
```
qemu-system-arm -M raspi0 -serial null stdio -kernel .export/kernel7.elf
```
