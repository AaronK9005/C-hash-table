#include <stdio.h>

#include "hashtable.h"

uint64_t hash(const char* key, size_t keylen)
{
    uint32_t result = 0;
    for (size_t i = 0; i < keylen; i++)
    {
        result += key[i];
    }
    return result;
}

void printfunc(const char *key, void *obj)
{
    printf("key = '%s', value = '%d'", key, *(int*)obj);
}

int main(int argc, char const *argv[])
{
    hash_table_t *ht = hash_table_create(32, hash, NULL);
    if (!ht) return 1;

    {
        int vals[] = { 1, 2, 3, 4 };

        hash_table_insert(ht, "A@", &vals[0]);
        hash_table_insert(ht, "A@@", &vals[1]);
        hash_table_insert(ht, "A@@@", &vals[2]);
        hash_table_insert(ht, "A@@@@", &vals[3]);
    }

    hash_table_print(ht, HTPRINT_NONEMPTY);

    hash_table_delete(ht, "A@");

    hash_table_print(ht, HTPRINT_NONEMPTY);

    return 0;
}   