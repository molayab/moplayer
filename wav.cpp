#include "wav.h"

Wav::Wav(const char * file) : AudioFile(file) { }

wav_header * Wav::get_header() {
  wav_header * header = new wav_header;

  fread(header->chunk_id, sizeof(header->chunk_id), 1, this->stream);
  fread(&header->chunk_size, sizeof(header->chunk_size), 1, this->stream);
  fread(header->format, sizeof(header->format), 1, this->stream);
  fread(header->subchunk_id, sizeof(header->subchunk_id), 1, this->stream);
  fread(&header->subchunk_size, sizeof(header->subchunk_size), 1, this->stream);
  fread(&header->audio_format, sizeof(header->audio_format), 1, this->stream);
  fread(&header->channels, sizeof(header->channels), 1, this->stream);
  fread(&header->sample_rate, sizeof(header->sample_rate), 1, this->stream);
  fread(&header->byte_rate, sizeof(header->byte_rate), 1, this->stream);
  fread(&header->block_align, sizeof(header->block_align), 1, this->stream);
  fread(&header->bits_sample, sizeof(header->bits_sample), 1, this->stream);

  // Verificar si no PCM, si es asi, leemos los parametros extras de compresion.
  if (header->audio_format > 1) {
    fread(&header->extra_param_size, sizeof(header->extra_param_size), 1, this->stream);

    // Saltamos los parametros (No los incluiremos en el header por ahora)
    fseek(this->stream, (long) header->extra_param_size, SEEK_CUR);
  }

  fread(header->data_id, sizeof(header->data_id), 1, this->stream);
  fread(&header->data_size, sizeof(header->data_size), 1, this->stream);

  return header;
}
