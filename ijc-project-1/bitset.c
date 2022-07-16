/**
 * bitset.c
 * Řešení IJC-DU1, příklad A), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#ifdef USE_INLINE

#include "bitset.h"

extern inline bitset_index_t bitset_size(bitset_t jmeno_pole);

extern inline void bitset_free(bitset_index_t *jmeno_pole);

extern inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, unsigned int vyraz);

extern inline int bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);

#endif
