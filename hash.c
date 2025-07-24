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


#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifndef MURMUR_SEED

#define MURMUR_SEED 0x9747b28c

#endif 

#define ROL(x) (x) <<= 1
#define SHIFT(k, l, r) ((k) << (l)) | ((k) >> r)  

static inline uint64_t ptrToInt(void *ptr) {
  union {
    void *ptr;
    uint64_t u;
  } val;
  val.ptr = ptr;
  return val.u;
}

static inline uint64_t murmur_scramble(uint64_t key) {
  key *= 0xcc9e2d51;
  key = SHIFT(key, 15, 17);
  key *= 0x1b873593;
  return key;
}

uint64_t murmur3_hash(const uint8_t *key, size_t len) {
  uint64_t hash = MURMUR_SEED;
  uint64_t k;

  for (size_t i = len >> 2; i; i--) {
    memcpy(&k, key, sizeof(uint64_t));
    key += sizeof(uint64_t);
    hash ^= murmur_scramble(k);
    hash = SHIFT(hash, 13, 19);
    hash = hash * 5 + 0xe6546b64;
  }
  k = 0;

  for (size_t i = len & 3; i; i--) {
    k <<=8;
    k |= key[i - 1];
  }

  hash ^= murmur_scramble(k);
  hash ^= len;
	hash ^= hash >> 16;
	hash *= 0x85ebca6b;
	hash ^= hash >> 13;
	hash *= 0xc2b2ae35;
	hash ^= hash >> 16;

  return hash;
}

