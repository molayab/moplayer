#ifndef FILE_H
#define FILE_H

#include <cstdlib>
#include <cstring>
#include <cstdio>

typedef enum FileEndian {
  BIG,
  LITTLE
} FileEndian;

class AudioFile {
protected:

public:
  FILE * stream;
  AudioFile(const char *);
  //virtual void * get_header() = 0;

  short   get_short(char *, FileEndian = LITTLE);
  int     get_int(char *, FileEndian = LITTLE);

  void    read(char *, size_t);
};

#endif /* FILE_H */
