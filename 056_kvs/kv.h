#ifndef __KV_H__
#define __KV_H__

struct _kvpair_t {
  char * key;
  char * value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t {
  kvpair_t * arr;
  int len;
};
typedef struct _kvarray_t kvarray_t;

kvarray_t * readKVs(const char * fname);

void myReadLine(char * line, kvpair_t * kvarr);

void readKeyorVal(char ** line, char ** target, char sign);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
