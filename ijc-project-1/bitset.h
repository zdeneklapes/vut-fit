/**
 * bitset.h
 * Řešení IJC-DU1, příklad A), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */


#ifndef BITSET_H
#define BITSET_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <assert.h>

#include "error.h"

typedef unsigned long bitset_t[];
typedef unsigned long bitset_index_t;

// STEG-DECODE
// needed indexes
#define INDEX_MSG(index) (index) / CHAR_BIT
// on which bit i am
#define INDEX_REST_MSG(index) (index) % CHAR_BIT
// set bit in char type
#define setbit(jmeno_pole, index, vyraz)                                \
    (vyraz) == 1                                                        \
        ? (jmeno_pole[INDEX_MSG(index)] |= 1U << INDEX_REST_MSG(index)) \
        : (jmeno_pole[INDEX_MSG(index)] &= ~(1U << (INDEX_REST_MSG(index))))

#define setbit_encode(jmeno_pole, index, vyraz) \
    (vyraz) == 1                                \
        ? (jmeno_pole[(index)] |= 1U)           \
        : (jmeno_pole[(index)] &= ~1U)
#define getbit(jmeno_pole, index) (((jmeno_pole)[INDEX_MSG(index)] >> (INDEX_REST_MSG(index))) & 1U) == 1 ? 1 : 0

// PRIMES
// how many bits ul have
#define UNSIGNED_LONG_BITS (CHAR_BIT * sizeof(bitset_index_t))
// pro nastaveni bitset_create => velikosti pole bitu; plus 2 aby se byl prostor i pro prvni index na velikost pole
#define INDEX_REST(index) (bitset_index_t)(index) % UNSIGNED_LONG_BITS
#define NEED_INDEXES(velikost) (((bitset_index_t)(velikost) / (UNSIGNED_LONG_BITS)) + 2)
// zjisti index pole bitu na kterem se bude pracovat; zacina se od indexu 1 ,index 0 je velikost pole
// for bitset_setbit and bitset_getbit
#define INDEX(index) ((index) / UNSIGNED_LONG_BITS) + 1
// create unsigend long pole
// static_assert control the size over 200,000,000
#define bitset_create(jmeno_pole, velikost)                                                                                                \
    static_assert(200000000 >= (velikost) && (velikost) > 2, "Pole muze byt velke od 1 do 200,000,000/64 -> Byla zadana spatna hodnota!"); \
    bitset_index_t(jmeno_pole)[NEED_INDEXES(velikost)] = {0};                                                                              \
    (jmeno_pole)[0] = (velikost);
// alokuje unsigned long
#define bitset_alloc(jmeno_pole, velikost)                                                 \
    assert(200000000 >= (velikost) && (velikost) > 2);                                     \
    bitset_index_t *(jmeno_pole) = calloc(NEED_INDEXES(velikost), sizeof(bitset_index_t)); \
    if ((jmeno_pole) == NULL)                                                              \
        error_exit("bitset_alloc: Chyba alokace paměti");                                  \
    (jmeno_pole)[0] = (velikost);

#ifndef USE_INLINE
#define bitset_free(jmeno_pole) free(jmeno_pole)
// return size of pole
#define bitset_size(jmeno_pole) jmeno_pole[0]
#define bitset_setbit(jmeno_pole, index, vyraz)                                                                          \
    if ((bitset_index_t)(index) > jmeno_pole[0])                                                                         \
    {                                                                                                                    \
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (bitset_index_t)index, (bitset_index_t)jmeno_pole[0]); \
    }                                                                                                                    \
    (vyraz) == 1                                                                                                         \
        ? (jmeno_pole[INDEX(index)] |= 1UL << INDEX_REST(index))                                                         \
        : (jmeno_pole[INDEX(index)] &= ~(1UL << (INDEX_REST(index))))

// posunu jmeno_pole[na indexu] o tolik bitu na kterem chci zjistit bit a pak dam AND
#define FIND_BIT(jmeno_pole, index)                                \
    (((jmeno_pole)[INDEX(index)] >> INDEX_REST((index))) & 1U) > 0 \
        ? 1                                                        \
        : 0
// must be used like this, because error_exit return void and tertiary operator must return bool
#define bitset_getbit(jmeno_pole, index)                                                                                              \
    (((bitset_index_t)(index) > (jmeno_pole)[0])                                                                                      \
         ? ((error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (bitset_index_t)(index), (bitset_index_t)(jmeno_pole)[0])), 0) \
         : (FIND_BIT(jmeno_pole, index)))

#else // USE_INLINE

inline bitset_index_t bitset_size(bitset_t jmeno_pole) {
    return jmeno_pole[0];
}

inline void bitset_free(bitset_index_t *jmeno_pole) {
    free(jmeno_pole);
}

inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, unsigned int vyraz) {
    if ((bitset_index_t) (index) > jmeno_pole[0])
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (bitset_index_t) index,
                   (bitset_index_t) jmeno_pole[0]);

    if (vyraz == 1)
        jmeno_pole[INDEX(index)] |= 1UL << INDEX_REST(index);
    else
        jmeno_pole[INDEX(index)] &= ~(1UL << (INDEX_REST(index)));
}

inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index) {
    if ((bitset_index_t) (index) > jmeno_pole[0])
        return (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (bitset_index_t) index,
                           (bitset_index_t) jmeno_pole[0]), 0);
    else
        return (jmeno_pole[INDEX(index)] >> INDEX_REST((index)) & 1U) > 0 ? 1 : 0;
}

#endif // USE_INLINE
#endif // BITSET_H
