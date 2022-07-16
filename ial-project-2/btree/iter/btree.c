/*
 * Binárny vyhľadávací strom — iteratívna varianta
 *
 * S využitím dátových typov zo súboru btree.h, zásobníkov zo súborov stack.h a
 * stack.c a pripravených kostier funkcií implementujte binárny vyhľadávací
 * strom bez použitia rekurzie.
 */

// Vypracoval: Zdenek Lapes <xlapes02>

#include "../btree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializácia stromu.
 *
 * Užívateľ musí zaistiť, že incializácia sa nebude opakovane volať nad
 * inicializovaným stromom. V opačnom prípade môže dôjsť k úniku pamäte (memory
 * leak). Keďže neinicializovaný ukazovateľ má nedefinovanú hodnotu, nie je
 * možné toto detegovať vo funkcii.
 */
void bst_init(bst_node_t **tree) {
    (*tree) = NULL;
}

/*
 * Nájdenie uzlu v strome.
 *
 * V prípade úspechu vráti funkcia hodnotu true a do premennej value zapíše
 * hodnotu daného uzlu. V opačnom prípade funckia vráti hodnotu false a premenná
 * value ostáva nezmenená.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
bool bst_search(bst_node_t *tree, char key, int *value) {
    if (!tree)
        return false;

    bst_node_t *tmp = tree;
    do {
        if (key < tmp->key)
            tmp = tmp->left;
        else if (key > tmp->key)
            tmp = tmp->right;
        else if (tmp->key == key) {
            *value = tmp->value;
            return true;
        }
    } while (tmp);
    return false;
}

/*
 * Vloženie uzlu do stromu.
 *
 * Pokiaľ uzol so zadaným kľúčom v strome už existuje, nahraďte jeho hodnotu.
 * Inak vložte nový listový uzol.
 *
 * Výsledný strom musí spĺňať podmienku vyhľadávacieho stromu — ľavý podstrom
 * uzlu obsahuje iba menšie kľúče, pravý väčšie.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_insert(bst_node_t **tree, char key, int value) {
    bst_node_t *tmp = *tree;

    // alocation
    bst_node_t *tmp_alloc = (bst_node_t *) malloc(sizeof(bst_node_t));
    if (tmp_alloc) {
        tmp_alloc->key = key;
        tmp_alloc->value = value;
        tmp_alloc->left = NULL;
        tmp_alloc->right = NULL;
    } else {
        return;
    }

    // logic
    if (!(*tree)) {
        *tree = tmp_alloc;
    } else {
        while (tmp) {
            if (key < tmp->key) {                    // smaller
                if (tmp->left)
                    tmp = tmp->left;
                else {
                    tmp->left = tmp_alloc;
                    return;
                }
            } else if (key > tmp->key) {            // greater
                if (tmp->right)
                    tmp = tmp->right;
                else {
                    tmp->right = tmp_alloc;
                    return;
                }
            } else {                                // equal
                tmp->value = value;
                free(tmp_alloc);
                return;
            } // gt|lt|eq
        } // while
    } // if (*tree)
}

/*
 * Pomocná funkcia ktorá nahradí uzol najpravejším potomkom.
 *
 * Kľúč a hodnota uzlu target budú nahradené kľúčom a hodnotou najpravejšieho
 * uzlu podstromu tree. Najpravejší potomok bude odstránený. Funkcia korektne
 * uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkcia predpokladá že hodnota tree nie je NULL.
 *
 * Táto pomocná funkcia bude využitá pri implementácii funkcie bst_delete.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
    // vars
    bst_node_t *to_delete = NULL;
    bst_node_t *rm = (*tree); // need to rebind ptr otherwise => overwriting tree and target as well
    bst_node_t *rm_prev = (*tree);

    // go to right_most
    while (rm->right) { // go to right-most
        rm_prev = rm;
        rm = rm->right;
    }

    target->key = rm->key;
    target->value = rm->value;

    if (rm->left) {        // if left => remap left
        to_delete = rm;
        rm_prev->right = rm->left;
        free(to_delete);
        to_delete = NULL;
    } else {                    // else delete right-most
        free(rm);
        rm = NULL;
        rm_prev->right = NULL; // after free ptr is not null
    }
}

/*
 * Odstránenie uzlu v strome.
 *
 * Pokiaľ uzol so zadaným kľúčom neexistuje, funkcia nič nerobí.
 * Pokiaľ má odstránený uzol jeden podstrom, zdedí ho otec odstráneného uzla.
 * Pokiaľ má odstránený uzol oba podstromy, je nahradený najpravejším uzlom
 * ľavého podstromu. Najpravejší uzol nemusí byť listom!
 * Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkciu implementujte iteratívne pomocou bst_replace_by_rightmost a bez
 * použitia vlastných pomocných funkcií.
 */
void bst_delete(bst_node_t **tree, char key) {
    bst_node_t *tmp = (*tree);
    bst_node_t *tmp_prev = (*tree);

    while (tmp) {
        if (key < tmp->key) {     // lt
            tmp_prev = tmp;
            tmp = tmp->left;
        } else if (key > tmp->key) { // gt
            tmp_prev = tmp;
            tmp = tmp->right;
        } else {                  // eq
            if (tmp->left && tmp->right) {               // two branches
                bst_replace_by_rightmost(tmp, &(tmp->left));
                break;
            } else {                                      // one branch
                if (tmp_prev->left->key == key)
                    tmp_prev->left = tmp->left;
                else if (tmp_prev->right->key == key)
                    tmp_prev->right = tmp->right;

                free(tmp);
                tmp = NULL;
            } // gt|lt|non branch
        } // key check
    } // while
}

/*
 * Zrušenie celého stromu.
 *
 * Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po
 * inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených
 * uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_dispose(bst_node_t **tree) {
    stack_bst_t stack;
    stack_bst_init(&stack);
    bst_node_t *to_delete = *tree;

    do {
        if (!(*tree)) {
            if (!stack_bst_empty(&stack)) { // empty
                *tree = stack_bst_top(&stack);
                stack_bst_pop(&stack);
            }
        } else {
            if ((*tree)->right)
                stack_bst_push(&stack, (*tree)->right);

            to_delete = (*tree);
            *tree = (*tree)->left;
            free(to_delete);
            to_delete = NULL;
        }
    } while ((*tree) || (!stack_bst_empty(&stack)));
}

/*
 * Pomocná funkcia pre iteratívny preorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu.
 * Nad spracovanými uzlami zavola bst_print_node a uloží ich do zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit) {
    while (tree) {
        bst_print_node(tree);

        stack_bst_push(to_visit, tree);
        tree = tree->left;
    }
}

/*
 * Preorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_preorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_preorder(bst_node_t *tree) {
    stack_bst_t stack;
    stack_bst_init(&stack);

    bst_leftmost_preorder(tree, &stack);
    while (!stack_bst_empty(&stack)) {
        tree = stack_bst_top(&stack);
        stack_bst_pop(&stack);
        bst_leftmost_preorder(tree->right, &stack);
    }
}

/*
 * Pomocná funkcia pre iteratívny inorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit) {
    while (tree) {
        stack_bst_push(to_visit, tree);
        tree = tree->left;
    }
}

/*
 * Inorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_inorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_inorder(bst_node_t *tree) {
    stack_bst_t stack;
    stack_bst_init(&stack);

    bst_leftmost_inorder(tree, &stack);
    while (!stack_bst_empty(&stack)) {
        tree = stack_bst_pop(&stack);
        bst_print_node(tree);
        bst_leftmost_inorder(tree->right, &stack);
    }
}

/*
 * Pomocná funkcia pre iteratívny postorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov. Do zásobníku bool hodnôt ukladá informáciu že uzol
 * bol navštívený prvý krát.
 *
 * Funkciu implementujte iteratívne pomocou zásobníkov uzlov a bool hodnôt a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit, stack_bool_t *first_visit) {
    while (tree) {
        stack_bst_push(to_visit, tree);
        stack_bool_push(first_visit, true);
        tree = tree->left;
    }
}

/*
 * Postorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_postorder a
 * zásobníkov uzlov a bool hodnôt bez použitia vlastných pomocných funkcií.
 */
void bst_postorder(bst_node_t *tree) {
    bool from_left = false;
    stack_bst_t stack;
    stack_bst_init(&stack);

    stack_bool_t stack_first;
    stack_bool_init(&stack_first);

    bst_leftmost_postorder(tree, &stack, &stack_first);
    while (!stack_bst_empty(&stack)) {
        tree = stack_bst_top(&stack);

        from_left = stack_bool_top(&stack_first);
        stack_bool_pop(&stack_first);

        if (from_left) {
            stack_bool_push(&stack_first, false);
            bst_leftmost_postorder(tree->right, &stack, &stack_first);
        } else {
            stack_bst_pop(&stack);
            bst_print_node(tree);
        }
    }
}
