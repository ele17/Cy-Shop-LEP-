#include <stdio.h>
#include "gestion.h"
#include "achat.h"



int main() {
    int mode;
    checkAndCreateClientAndProductFiles();
    printf("Bienvenue! Veuillez choisir un mode:\n");
    printf("1. Mode Gestion\n");
    printf("2. Mode Achat\n");
    scanf("%d", &mode);

    switch(mode) {
        case 1:
            startManagementMode();
            break;
        case 2:
            startPurchaseMode();
            break;
      case 3:
          printf("3. Quitter\n");
        default:
            printf("Mode invalide. Veuillez choisir 1 pour la gestion ou 2 pour l'achat.\n");
            break;
    }

    return 0;
}
