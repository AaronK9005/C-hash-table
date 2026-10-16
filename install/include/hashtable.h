#ifndef MY_HASH_TABLE_H
#define MY_HASH_TABLE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define IS_PWR2(num) (((num) > 0) && ((num) & ((num) - 1)) == 0)
#define PWR2_MOD(left, right) ((left) & ((right) - 1))

/**
 * @brief Generic hash table, that stores pointers to data
 * 
 */
typedef struct _hash_table hash_table_t;

typedef uint64_t hash_function(const char*, size_t);
typedef void print_function(const char*, void *);

enum print_mode {
    HTPRINT_NONEMPTY,
    HTPRINT_ALL
};

hash_table_t * hash_table_create(uint32_t size, hash_function *hf, print_function *pf);
void hash_table_destroy(hash_table_t *ht);
void hash_table_print(hash_table_t *ht, enum print_mode mode);
bool hash_table_insert(hash_table_t *ht, const char *key, void *obj);
void *hash_table_lookup(hash_table_t *ht, const char *key);
void *hash_table_delete(hash_table_t *ht, const char *key);

#endif