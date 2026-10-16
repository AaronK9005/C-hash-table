#include "hashtable.h"
#include "entry.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _hash_table {
    uint32_t len; // number of objs
    uint32_t size; // size of the entry array
    entry_t ** entries;
    hash_function* hash;
    print_function* print_obj; // custom print for objs
};

static size_t _ht_index(hash_table_t *ht, const char *key)
{
    return
        ht->hash(key, strlen(key))
        & (ht->size - 1); // power of 2 modulo
}

hash_table_t * hash_table_create(uint32_t size, hash_function *hf, print_function *pf)
{
    assert(size != 0);
    assert(IS_PWR2(size));
    assert(hf != NULL);

    hash_table_t *ht = malloc(sizeof(hash_table_t));
    if (!ht)
    {
        return NULL;
    }

    entry_t **entries = calloc(sizeof(entry_t *), size);
    if (!entries)
    {
        free(ht);
        return NULL;
    }

    ht->len = 0;
    ht->size = size;
    ht->entries = entries;
    ht->hash = hf;
    ht->print_obj = pf;

    return ht;
}

void hash_table_destroy(hash_table_t *ht)
{
    if (ht)
    {
        entry_t *tmp = ht->entries;
        while (tmp)
        {
            tmp = entry_delete(tmp);
        }

        free(ht);
    }
}

void hash_table_print(hash_table_t *ht, enum print_mode mode)
{
    assert(ht != NULL);

    for (int i = 0; i < ht->size; i++)
    {
        entry_t *tmp = ht->entries[i];

        if (!tmp)
        {
            if (mode == HTPRINT_ALL)
            {
                printf("%8d: ---\n", i + 1);
            }
            continue;
        }

        printf("%8d: ", i + 1);

        bool is_repeating = false;
        while (tmp)
        {
            if (is_repeating)
            {
                printf("        : ");
            }

            if (ht->print_obj)
            {
                ht->print_obj(tmp->key, tmp->obj);
                putchar('\n');
            }
            else
            {
                printf("%p\n", tmp->obj);
            }

            tmp = tmp->next;
            is_repeating = true;
        }
    }

    printf("hash_table '0x%p' has '%d' entries\n", ht, ht->len);
}

bool hash_table_insert(hash_table_t *ht, const char *key, void *obj)
{
    assert(ht != NULL);
    if (!key || !obj) return false;

    size_t index = _ht_index(ht, key);

    if (hash_table_lookup(ht, key) != NULL) return false;

    // create a new entry
    entry_t *e = entry_new(key, obj, ht->entries[index]);
    if (!e) return false;

    // prepend to linked list
    ht->entries[index] = e;

    ht->len++;

    return true;
}

void *hash_table_lookup(hash_table_t *ht, const char *key)
{
    assert(ht != NULL);
    if (!key) return NULL;

    size_t index = _ht_index(ht, key);

    entry_t *tmp = ht->entries[index];
    while (tmp) // while(tmp != NULL && strcmp(key, tmp->key) != 0) { tmp = tmp->next; }
    {
        if(key[0] == tmp->key[0] && strcmp(key + 1, tmp->key + 1) == 0)
        {
            return tmp->obj;
        }

        tmp = tmp->next;
    }
    
    // return tmp != NULL ? tmp->obj : NULL;
    return NULL;
}

void *hash_table_delete(hash_table_t *ht, const char *key)
{
    assert(ht != NULL);
    if (!key) return NULL;

    size_t index = _ht_index(ht, key);

    entry_t *tmp = ht->entries[index];
    entry_t *prev = NULL;

    while(tmp && (key[0] != tmp->key[0] || strcmp(key + 1, tmp->key + 1) != 0)) 
    {
        prev = tmp;
        tmp = tmp->next;
    }

    if (!tmp) return NULL;

    void *obj = tmp->obj;

    if (prev != NULL)
        prev->next = entry_delete(tmp);
    else
        ht->entries[index] = entry_delete(tmp);
    
    ht->len--;

    return obj;    
}

