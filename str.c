#include "str.h"
#include <stdlib.h>
#include <string.h>

static inline strhdr *getStrHeader(string str){
  return (strhdr *)(str-sizeof(strhdr));
}

string strnew(size_t len) {
  strhdr *header = malloc(sizeof(strhdr) + len);
  header->len = len;
  return header->buf;
}

void strfree(string str) {
  strhdr *header = getStrHeader(str);
  free(header);
}


string strsubstr(string str, size_t start, size_t end) {
  if(start >= end) return NULL;
  
  strhdr *hdr = getStrHeader(str);

  string substr = strnew(end - start);

  strncpy(substr, str + start, end - start);

  return substr;
}

string *strsplit(string str, const char splt, size_t *count) {
  strhdr *header = getStrHeader(str);

  *count = 0;

  for(size_t i = 0; i < header->len; i++) {
    if(str[i] == splt){
      *count = *count + 1;
    }
  }


  string *res = malloc(sizeof(strhdr) * (*count) + header->len);

  int strIdx = 0;
  int charIdx = 0;
  for(size_t i = 0; i < header->len; i++) {
    if(str[i] == splt) {
      strIdx++;
    }
    res[strIdx][charIdx++] = str[i];
  }

  return res;
}
