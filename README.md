# e2spd - emacspeak to speech-dispatcher

A C++ program that links the emacspeak audio desktop to the linux speech-dispatcher.
e2spd tries to establish a connection to a speech-dispatcher instance. If successful, it will  then read commands from standard input to forward to the speech-dispatcher.
It is normally invoked by emacspeak, but can be run standalone.
Currently only tested on arch linux.


# Installation
## Requirements

 - speech-dispatcher
 - libspeechd
 - C++ compiler with at least C++17 capabilities
  - boost
 - cmake >= 3.27.1

On arch, an up-to-date libspeechd can be installed with the libspeechd-git package from the AUR.

$ yay libspeechd-git

## Building

Assuming e2spd as the repo directory.

 $ cd e2spd
  $ mkdir build && cd build
 $ cmake ..
 $ make

You can verify that it works by doing

$ ./e2spd

You should hear a message saying that e2spd is running. You can then try typing

q {Hello, world!!}
d

You should hear "Hello world!". If you don't hear anything, there might be a problem with speech-dispatcher or your audio configuration.

## Installing

To link up with emacspeak, do the following while in /e2spd/build, or wherever you invoked cmake.

 $ cp ./e2spd /PATH-TO-EMACSPEAK/servers/e2spd
 $ echo "e2spd" >> /PATH-TO-EMACSPEAK/servers.servers 

You can then run emacs with emacspeak and try it out once by doing M-x dtk-select-server and typing e2spd at the prompt.
To make it permanent, add

(setq dtk-speech-server-program "e2spd")

to your .emacs file.

## Credits

Thanks to the emacspeak developers for an excellent audio desktop environment.
You can find emacspeak at

https://github.com/tvraman/emacspeak

Also thanks to Bart Bunting, whose previous attempt at a speech-dispatcher bridge I studied for e2spd.

https://github.com/bartbunting/espd

