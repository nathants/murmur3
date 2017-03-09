#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "murmur3.h"

int main(int argc, char **argv) {
  uint32_t hash[1];
  uint32_t seed = 0;

  if (argc != 2) {
    printf("usage: %s \"string to hash\"\n", argv[0]);
    exit(1);
  }

  MurmurHash3_x86_32(argv[1], strlen(argv[1]), seed, hash);
  printf("%d\n", hash[0]);

  return 0;
}
