#include <stddef.h>

typedef char *string;

typedef struct strhdr {
  size_t len;
  char buf[];
} strhdr;


string strnew(size_t);

string strnewlen(string, size_t);
string strsubstr(string, size_t, size_t);

string *strsplit(string, const char, size_t *);
