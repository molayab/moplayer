#include <iostream>
#include "wav.h"
//#include <ao/ao.h>

using namespace std;


/**int integer_value(char * bytes, bool little_endian = true) {
  int rest = 0;
  if (little_endian) {
    for (int n = sizeof(int); n >= 0, --n) {
      rest = (rest << 8) + bytes[n];
    }
  } else {

  }
}*/


void read() {
  /*ifstream ifs("/Users/molayab/Desktop/La Boda.wav", ios::in | ios::binary);

  wav_header header;

  ifs.read(header.chunk_id, 4);
  ifs.seekg(0, 4);
  ifs.read((char *) &header.chunk_size, 4);

  printf("%d\n", header.chunk_size);*/

  Wav file("/Users/molayab/Desktop/La Boda.wav");

  wav_header * h = file.get_header();

  cout << h->chunk_id << endl;

  delete h;
}

int main(int argc, char ** argv) {

  read();

  return 0;
}
