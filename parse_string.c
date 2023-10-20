#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int8_t parse_antenna_signal_strength(unsigned char antenna_number,
                                            const char *ptr) {
  int8_t antenna0_signal_strength = -99, antenna1_signal_strength = -99;
  if (!ptr) {
    return -99;
  }
  sscanf(ptr, "[%hhd, %hhd]", &antenna1_signal_strength, &antenna0_signal_strength);
  switch (antenna_number) {
  case 0:
    return antenna0_signal_strength;
  case 1:
    return antenna1_signal_strength;
  default:
    return -99;
  }
}

int main() {
  //char input[] = "[-42, -34]";
  char input[] = "";
  char *inp = input;

  printf("antenna0: %d\n", parse_antenna_signal_strength(0,inp));
  printf("antenna1: %d\n", parse_antenna_signal_strength(1,inp));

  return 0;
}
