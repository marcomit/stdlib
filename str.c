/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2025, Marco Menegazzi
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "str.h"
#include <stdlib.h>
#include <string.h>

static inline strhdr *getStrHeader(string str) {
  return (strhdr *)(str - sizeof(strhdr));
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
  if (start >= end) return NULL;

  strhdr *hdr = getStrHeader(str);

  string substr = strnew(end - start);

  strncpy(substr, str + start, end - start);

  return substr;
}

string *strsplit(string str, const char splt, size_t *count) {
  strhdr *header = getStrHeader(str);

  *count = 0;

  for (size_t i = 0; i < header->len; i++) {
    if (str[i] == splt) {
      *count = *count + 1;
    }
  }

  string *res = malloc(sizeof(strhdr) * (*count) + header->len);

  int strIdx = 0;
  int charIdx = 0;
  for (size_t i = 0; i < header->len; i++) {
    if (str[i] == splt) {
      strIdx++;
    }
    res[strIdx][charIdx++] = str[i];
  }

  return res;
}
