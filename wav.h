#ifndef WAV_H
#define WAV_H

#include "file.h"

typedef struct wav_header {
  // WAVE RIFF Header
  char  chunk_id[4];
  int   chunk_size;
  char  format[4];

  // Subchunk FMT
  char  subchunk_id[4];
  int   subchunk_size;
  short audio_format;
  short channels;
  int   sample_rate;
  int   byte_rate;
  short block_align;
  short bits_sample;
  short extra_param_size;

  // Data subchunk
  char  data_id[4];
  int   data_size;
} wav_header;

class Wav : public AudioFile {
public:
  Wav(const char *);
  wav_header * get_header();
};

#endif /* WAV_H */
