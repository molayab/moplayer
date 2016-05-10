# moplayer
MoPlayer is a media player made in C/C++ helped with PortAudio to write PCM in the system's sound controller. With this project I'd like do a multi platform media player with FFT Spectrum Analyzer.

# Prerequistes 
* PortAudio library - http://portaudio.com/

# Compiling (Temp)
TODO: Make the Makefile for the project.

``` bash
  $ g++ -o soundtest sound.cpp file.cpp wav.cpp -g -lportaudio 
  $ ./soundtest
```

# Warning 
On OSX 10.11 or prior:

```
  140: This application, or a library it uses, is using the deprecated Carbon Component Manager for hosting Audio Units. Support for this will be removed in a future release. Also, this makes the host incompatible with version 3 audio units. Please transition to the API's in AudioComponent.h.
