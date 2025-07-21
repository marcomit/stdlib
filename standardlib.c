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

#define NEXT(n) (n) = (n)->next;
#define PREV(n) (n) = (n)->prev;
#define DEFAULT_LIST_COMPARE(a, b) return a < b

listNode *newListNode() {
  listNode *node = malloc(sizeof(listNode));
  if (!node) {
    printf("Error allocating listNode");
    exit(1);
  }
  return node;
}

listNode *newListNodeUint(uint64_t value) {
  listNode *node = newListNode();
  node->value.uint = value;
  return node;
}

listNode *newListNodeDouble(double value) {
  listNode *node = newListNode();
  node->value.fl = value;
  return node;
}

listNode *newListNodePtr(void *value) {
  listNode *node = newListNode();
  node->value.ptr = value;
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

static listNode *listNodeCopy(listNode *node, bool recursive) {
  if (!node)
    return NULL;
  listNode *copy = newListNode();
  copy->value = node->value;
  if (recursive) {
    copy->prev = listNodeCopy(node->prev, recursive);
    copy->next = listNodeCopy(node->next, recursive);
  }
  return copy;
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

void stackPushNode(stack *st, listNode *node) {
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
  NEXT(st->head);
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

void queueFree(queue *q) {
  freeListNode(q->head, true);
  free(q);
}

void enqueueNode(queue *q, listNode *node) {
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
    NEXT(q->tail);
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
  NEXT(q->head);

  if (!q->head) {
    q->tail = NULL;
  }

  q->len--;

  return head;
}

list *newList() {
  list *l = malloc(sizeof(list));
  l->len = 0;
  l->index = 0;
  l->curr = NULL;
  l->tail = NULL;
  l->head = NULL;
  return l;
}

listNode *listAt(list *l, size_t index) {
  listNode *c = l->head;
  for (size_t i = 0; i < index; i++) {
    if (!c)
      return NULL;
    NEXT(c);
  }
  return c;
}

inline listNode *listPeek(list *l) { return l->curr; }

listNode *listNext(list *l) {
  if (l->index >= l->len)
    return NULL;
  if (!l->curr || !l->curr->next)
    return NULL;
  NEXT(l->curr);
  l->index++;
  return listPeek(l);
}

listNode *listPrev(list *l) {
  if (l->index <= 0)
    return NULL;
  if (!l->curr || !l->curr->prev)
    return NULL;
  PREV(l->curr);
  l->index--;
  return listPeek(l);
}

list *listCopy(list *l) {
  list *copy = newList();
  copy->len = l->len;
  if (l->head) {
    copy->head = listNodeCopy(l->head, true);
  }

  listNode *dummy = copy->head;
  while (dummy && dummy->next) {
    NEXT(dummy);
  }
  if (dummy) {
    copy->tail = dummy;
  }

  return copy;
}

typedef int (*listCompare)(listNode *, listNode *);

static void listSwapNodes(list *l, int i, int j) {
  listNode *iValue = listAt(l, i);
  listNode *jValue = listAt(l, j);

  uint64_t val = iValue->value.uint;
  iValue->value.uint = jValue->value.uint;
  jValue->value.uint = val;
}

static int listPartition(list *l, int start, int end, listCompare compare) {
  int p = rand() % l->len;
  int s = start;
  int e = end;

  listNode *mid = listAt(l, p);
  listNode *left = listAt(l, s);
  listNode *right = listAt(l, e);

  listSwapNodes(l, p, end);

  while (s <= end) {
    while (s <= end && compare(left, mid) <= 0) {
      s++;
      NEXT(left);
    }
    while (s <= end && compare(right, mid) >= 0) {
      e--;
      PREV(right);
    }
    listSwapNodes(l, s, e);
  }

  listSwapNodes(l, s, end);

  return s;
}

static int listDefaultCompare(listNode *n1, listNode *n2) {
  return n1->value.uint - n2->value.uint;
}

static void listSortPartition(list *l, int start, int end,
                              listCompare compare) {
  if (start >= end)
    return;

  int mid = listPartition(l, start, end, compare);

  listSortPartition(l, 0, mid - 1, compare);
  listSortPartition(l, mid + 1, end, compare);
}

/*
 * A sample implementation of quicksort
 */
void listSort(list *l, listCompare compare) {
  if (!compare) {
    compare = listDefaultCompare;
  }
  listSortPartition(l, 0, l->len, compare);
}

void listPushNode(list *l, listNode *node) {
  printf("Len: %zu\n", l->len);
  if (l->len == 0) {
    printf("Setting head\n");
    l->head = node;
    printf("Setting tail\n");
    l->tail = node;
    printf("Setted\n");
    l->len = 1;
    return;
  }
  printf("Len greater than 0\n");
  node->prev = l->tail;
  l->tail->next = node;
  NEXT(l->tail);
  printf("Increasing length");
  l->len = 1;
}

void listPush(list *l, void *ptr) {
  listNode *node = newListNode();
  if (!node) {
    printf("Node is null");
  }
  node->value.ptr = ptr;
  listPushNode(l, node);
}
