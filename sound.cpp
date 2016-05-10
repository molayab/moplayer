#include <iostream>
#include "wav.h"
#include <portaudio.h>
#include <unistd.h>
#include <math.h>

using namespace std;

char * name;

/**int integer_value(char * bytes, bool little_endian = true) {
  int rest = 0;
  if (little_endian) {
    for (int n = sizeof(int); n >= 0, --n) {
      rest = (rest << 8) + bytes[n];
    }
  } else {

  }
}*/

float hanning_window(short input, size_t pos, size_t size) {
  float i = (float)pos;
  float n = (float)size;

  return input * 0.5f * (1.0f - cos(2.0f * M_PI * i / (n - 1.0f)));
}

void read() {
  Wav file(name);
  /*ifstream ifs("/Users/molayab/Desktop/La Boda.wav", ios::in | ios::binary);

  wav_header header;

  ifs.read(header.chunk_id, 4);
  ifs.seekg(0, 4);
  ifs.read((char *) &header.chunk_size, 4);

  printf("%d\n", header.chunk_size);*/


  wav_header * h = file.get_header();

  cout << " >> File Read:" << endl;
  cout << " > Container -> " << h->chunk_id << endl;
  cout << " > Format -> " << h->format << endl;
  cout << " > Audio Format (1 = PCM) -> " << h->audio_format << endl;
  cout << " > Bits Per Sample -> " << h->bits_sample << endl;
  cout << " > Channels -> " << h->channels << endl;
  cout << " > Byte rate -> " << h->byte_rate << endl;
  cout << " > Sample rate -> " << h->sample_rate << endl;
  cout << " >> Reading samples..." << endl;

  Pa_Initialize();

  PaStreamParameters p;
  p.device = Pa_GetDefaultOutputDevice();

  p.channelCount = (int) h->channels;
  switch(h->bits_sample) {
		case 8: p.sampleFormat = paUInt8; break;
		case 16: p.sampleFormat = paInt16; break;
		case 32: p.sampleFormat = paInt32; break;
		default: break;
	}

  p.suggestedLatency = Pa_GetDeviceInfo(p.device)->defaultHighOutputLatency;
  p.hostApiSpecificStreamInfo = NULL;

  PaStream * stream;

  Pa_OpenStream(&stream, NULL, &p, (double)h->sample_rate, paFramesPerBufferUnspecified, 0, NULL, NULL);

  Pa_StartStream(stream);

  unsigned int samples = 4096;
  size_t sample_len = samples * (h->bits_sample / 8) * h->channels;

  // Buffer
  uint8_t * buffer = new uint8_t[sample_len];
  size_t pointer = 0;

  for(;;) {
    cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";

    // Leer de archivo el buffer y hacer seek al siguiente data.
    size_t n = fread(buffer, sizeof(uint8_t), sample_len, file.stream);

    // Escribir en HW el buffer y los samples a reproducir.
    Pa_WriteStream(stream, buffer, samples);

    pointer += n;
    cout << "Read: " << pointer << " bytes";

    if (n < sample_len) {
      break;
    }
  }
  delete[] buffer;

  Pa_CloseStream(stream);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    perror("No se especifico el archivo");
    return 1;
  }

  name = argv[1];
  read();


  return 0;
}
