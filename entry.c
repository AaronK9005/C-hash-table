#include "entry.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

entry_t *entry_new(const char* key, void *obj, entry_t *next)
{
    entry_t *e = malloc(sizeof(entry_t));
    if (!e) return NULL;

    size_t keylen = strlen(key);
    char *e_key = malloc(keylen + 1);
    if (!e_key) 
    {
        free(e);
        return NULL;
    }
    memcpy(e_key, key, keylen + 1);

    e->key = e_key;
    e->obj = obj;
    e->next = next;

    return e;
}

entry_t *entry_delete(entry_t *entry)
{
    // if (!entry) return NULL;

    entry_t *next = entry->next;

    // assert(entry->key);
    free((void*)entry->key);
    free(entry);

    return next;
}

