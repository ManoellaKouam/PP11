#include <stdio.h>
#include "dlist.h"  // Ce fichier est fourni par le repo

// Déclaration de 5 noeuds statiques
DNode nodes[5];
DList list;

int main(void) {
    // Initialisation des noeuds
    for (int i = 0; i < 5; i++) {
        nodes[i].data = (void*)(long)(i + 1);  // données = 1 à 5
        nodes[i].prev = (i > 0) ? &nodes[i - 1] : NULL;
        nodes[i].next = (i < 4) ? &nodes[i + 1] : NULL;
    }

    // Définir les extrémités de la liste
    list.head = &nodes[0];
    list.tail = &nodes[4];

    // Parcours avant
    printf("Forward: ");
    for (DNode *p = list.head; p != NULL; p = p->next) {
        printf("%ld ", (long)p->data);
    }
    printf("\n");

    // Parcours arrière
    printf("Backward: ");
    for (DNode *p = list.tail; p != NULL; p = p->prev) {
        printf("%ld ", (long)p->data);
    }
    printf("\n");

    return 0;
}
