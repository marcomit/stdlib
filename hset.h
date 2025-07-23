#include "standardlib.h"
#include "stdbool.h"


typedef struct hset {
  
} hset;


hset *newhset();

bool hsetcontains(hset *, void *);

bool hsetadd(hset *, void *);

void freehset(hset *);
