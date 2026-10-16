#ifndef MY_HASH_TABLE_ENTRY_H
#define MY_HASH_TABLE_ENTRY_H

typedef struct _entry {
    const char *key;
    void *obj;
    struct _entry *next;
} entry_t;

entry_t *entry_new(const char* key, void *obj, entry_t *next);
entry_t *entry_delete(entry_t *entry);

#endif