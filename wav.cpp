#include "wav.h"

Wav::Wav(const char * file) : AudioFile(file) { }

wav_header * Wav::get_header() {
  wav_header * header = new wav_header;

  read(header->chunk_id, 4);

  char * buffer = new char[4];
  read(buffer, 4);
  header->chunk_size =
    (int)((buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0]);

  read(header->format, 4);
  read(header->subchunk_id, 4);

  read(buffer, 4);
  header->subchunk_size =
    (int)((buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0]);

  delete[] buffer;
  buffer = new char[2];

  read(buffer, 2);
  header->audio_format = get_short(buffer);

  read(buffer, 2);
  header->channels = get_short(buffer);

  delete[] buffer;
  buffer = new char[4];

  read(buffer, 4);
  header->sample_rate =
    (int)((buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0]);

  read(buffer, 4);
  header->byte_rate =
    (int)((buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0]);

  delete[] buffer;

  return header;
}
