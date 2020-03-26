#include <stdio.h>
#include <string.h>

#define MAX_READ_LENGTH 20000

typedef struct {
  char read_header[1024];
  char read[MAX_READ_LENGTH];
  char quality_header[1024];
  char qualities[MAX_READ_LENGTH];
  int read_size;
} FastQRead;

void chomp(char *str) {
  int i = strlen(str) - 1;
  while ((i > 0) && (str[i] < ' ')) {
    str[i--] = 0;
  }
}

int get_read(FILE *fp, FastQRead *read) {
  int got_read = 1;

  if (!fgets(read->read_header, 1024, fp)) {
    got_read = 0;
  }

  if (!fgets(read->read, MAX_READ_LENGTH, fp)) {
    got_read = 0;
  }

  if (!fgets(read->quality_header, 1024, fp)) {
    got_read = 0;
  }

  if (!fgets(read->qualities, MAX_READ_LENGTH, fp)) {
    got_read = 0;
  }

  if (got_read == 1) {
    chomp(read->read_header);
    chomp(read->read);
    chomp(read->quality_header);
    chomp(read->qualities);
    read->read_size = strlen(read->read);
  }

  return got_read;
}

void write_read(FastQRead* read, FILE *fp) {
    fprintf(fp, "%s\n", read->read_header);
    fprintf(fp, "%s\n", read->read);
    fprintf(fp, "%s\n", read->quality_header);
    fprintf(fp, "%s\n", read->qualities);
}
