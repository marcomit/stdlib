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
#include "standardlib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

listNode *newListNode() {
  listNode *node = malloc(sizeof(listNode));
  if(!node) {
    printf("Error allocating listNode");
    exit(1);
  }
  return node;
}

void freeListNode(listNode *node, bool recursive) {
  if (!node)
    return;
  if (recursive) {
    freeListNode(node->prev, recursive);
    freeListNode(node->next, recursive);
  }
  free(node);
}

stack *newStack() {
  stack *st = malloc(sizeof(stack));
  return st;
}

void freeStack(stack *st) {
  if (!st) {
    return;
  }
  free(st);
}

static void stackPushNode(stack *st, listNode* node){
  if (!st->head) {
    st->head = node;
    st->len = 1;
    return;
  }
  node->next = st->head;
  st->head = node;
  st->len++;

}

void stackPush(stack *st, void *ptr) {
  listNode *node = newListNode();
  node->value.ptr = ptr;
  stackPushNode(st, node);
}

void stackPushDouble(stack *st, double value) {
  listNode *node = newListNode();
  node->value.fl = value;
  stackPushNode(st, node);
}

void stackPushUint(stack *st, uint64_t uint) {
  listNode *node = newListNode();
  node->value.uint = uint;
  stackPushNode(st, node);
}

listNode *stackPop(stack *st) {
  if (st->len == 0 || !st->head)
    return NULL;
  listNode *current = st->head;
  st->head = st->head->next;
  st->len--;
  return current;
}

void inline stackFree(stack *st) {
  freeListNode(st->head, true);
  free(st);
}

queue *newQueue() {
  queue *q = malloc(sizeof(queue));
  q->len = 0;
  q->head = NULL;
  q->tail = NULL;
  return q;
}

void queueFree(queue *q){
  freeListNode(q->head, true);
  free(q);
}

static void enqueueNode(queue *q, listNode *node) {
  if (!q) {
    return;
  }
  if (!q->head) {
    q->head = node;
    q->len = 1;
  }
  if (!q->tail) {
    q->tail = node;
    q->len = 1;
  } else {
    q->tail->next = node;
    q->tail = q->tail->next;
    q->len++;
  }
}

void enqueue(queue *q, void *data) {
  listNode *node = newListNode();
  node->value.ptr = data;
  enqueueNode(q, node);
}

void enqueueDouble(queue *q, double data) {
  listNode *node = newListNode();
  node->value.fl = data;
  enqueueNode(q, node);
}

void enqueueUint(queue *q, uint64_t uint) {
  listNode *node = newListNode();
  node->value.uint = uint;
  enqueueNode(q, node);
}


listNode *dequeue(queue *q) {
  if (!q)
    return NULL;

  if (!q->head || q->len == 0)
    return NULL;

  listNode *head = q->head;
  q->head = q->head->next;

  if (!q->head) {
    q->tail = NULL;
  }

  q->len--;

  return head;
}
