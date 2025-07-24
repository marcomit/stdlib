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

#ifndef LIST_H

#define LIST_H

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define listLen(l) (l)->len
#define listPeek(l) (l)->curr
#define listIncrLen(l) (l)->len++
#define listDecrLen(l) (l)->len--

typedef struct listNode listNode;

struct listNode {
  union {
    void *ptr;
    double fl;
    uint64_t uint;
  } value;
  struct listNode *prev;
  struct listNode *next;
};

typedef struct stack {
  listNode *head;
  size_t len;
} stack;

typedef struct queue {
  listNode *head;
  listNode *tail;
  size_t len;
} queue;

typedef struct list {
  listNode *head;
  listNode *tail;
  size_t len;

  listNode *curr;
  size_t index;
} list;

listNode *newListNode();
listNode *newListNodeUint(uint64_t);
listNode *newListNodeDouble(double);
listNode *newListNodePtr(void *);
void freeListNode(listNode *, bool);

/*
 * ############
 * #  STACK   #
 * ############
 */
stack *newStack();
void stackFree(stack *);

void stackPush(stack *, void *);
void stackPushNode(stack *, listNode *);

listNode *stackPop(stack *);

/*
 * ############
 * #   QUEUE  #
 * ############
 */
queue *newQueue();
void queueFree(queue *);
void enqueue(queue *, void *);
void enqueueNode(queue *, listNode *);
listNode *dequeue(queue *);

/*
 * ############
 * #   LIST   #
 * ############
 */
list *newList();
void listFree(list *);
list *listCopy(list *);

void listPush(list *, void *);
void listPushNode(list *, listNode *);
listNode *listPop(list *);

void listPushFront(list *, void *);
void listPushFrontNode(list *, listNode *);
listNode *listPopFront(list *);

// listNode *listPeek(list *);
listNode *listNext(list *);
listNode *listPrev(list *);
listNode *listAt(list *, size_t);

void listSort(list *, int (*compare)(listNode *, listNode *));

#endif // LIST_H
