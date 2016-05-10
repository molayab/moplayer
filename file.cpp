#include "file.h"

AudioFile::AudioFile(const char * path) {
  this->stream = fopen(path, "rb");
}

int AudioFile::get_int(char * buffer, FileEndian fe) {
  int result = 0;

  if (fe == LITTLE) {
    for (int n = sizeof(int); n >= 0; --n) {
      result = (result << 8) + buffer[n];
    }
  } else {
    // TODO
  }

  return result;
}

short AudioFile::get_short(char * buffer, FileEndian fe) {
  short result = 0;

  if (fe == LITTLE) {
    for (int n = sizeof(short); n >= 0; --n) {
      result = (result << 8) + buffer[n];
    }
  } else {
    // TODO
  }

  return result;
}
