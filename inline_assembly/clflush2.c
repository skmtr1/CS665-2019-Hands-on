#include <stdio.h>
#include <stdlib.h>

#define SAMPLES 10
#define CACHE_LINE 64
//IGNORE CS665
extern inline __attribute__((always_inline))
inline int time_access_no_flush(const char *adrs){
  volatile unsigned long time;
  asm __volatile__ (
    "  mfence             \n\t"
    "  rdtsc              \n\t"
    "  movl %%eax, %%esi  \n\t"
    "  movl (%1), %%eax   \n\t"
    "  rdtsc              \n\t"
    "  subl %%esi, %%eax  \n\t"
    : "=a" (time)
    : "c" (adrs)
    :  "%esi", "%edx");
  return time;
}

//IGNORE CS665
extern inline __attribute__((always_inline))
inline void flush(const char *adrs) {
  asm __volatile__ ("mfence\nclflush 0(%0)" : : "r" (adrs) :);
}

const char x[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00"
                "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\x00"
                "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\x00"
                "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD\x00";

int main (int argc, char **argv)
{
  unsigned int *times = (unsigned int*) malloc(SAMPLES * sizeof(unsigned int));
  if (times == NULL) {
    return 1;
  }
  int i;
  for (i = 0; i < SAMPLES; i++) {
    // Flush the first time, and then every second time.
    // So that it's uncached, cached, uncached, cached, ...
    if (i % 2 == 0) {
      flush(x);
    }

    times[i] = time_access_no_flush(x);
  }

  for (i = 0; i < SAMPLES; i++) {
    printf("%u\n", times[i]);
  }

  return 0;
}
