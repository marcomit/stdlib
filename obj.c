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

#include "obj.h"
#include <stdio.h>
#include <stdlib.h>

#define objIncrRef(x) (x)->count++
#define objDecrRef(x) (x)->count--

#define objHeader(x) (object_hdr *)((x) - sizeof(object_hdr) + sizeof(void *))

static object_hdr *newhdr(void *ptr, void (*dealloc)(void *)) {
  object_hdr *hdr = malloc(sizeof(object_hdr));
  hdr->count = 1;
  hdr->dealloc = dealloc;
  hdr->ptr = ptr;
  return hdr;
}

object newobject(void *ptr, void (*dealloc)(void *)) {
  object_hdr *hdr = newhdr(ptr, dealloc);
  return &hdr->ptr;
}

object objinc(object obj) {
  if(!obj) return NULL;
  object_hdr *hdr = objHeader(obj);
  
  objIncrRef(hdr);

  return obj;
}

object objdec(object obj) {
  if(!obj) return NULL;

  object_hdr *hdr = objHeader(obj);

  if(hdr->count < 2) {
    if(hdr->dealloc) hdr->dealloc(obj);
    free(hdr);
    return NULL;
  }

  objDecrRef(hdr);
  
  return obj;
}
