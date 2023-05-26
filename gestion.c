#include "gestion.h"
#include "Produit.h"
#include "file_utils.h"
#include <stdio.h>

// Afficher les produits en rupture de stock
void displayOutOfStockProducts() {
    int numberOfProducts;
    printf("bonjour dans displayOutOfStockProducts");
    Produit *products = getLowStockProducts(&numberOfProducts);
    if (numberOfProducts==0){
      printf("aucun produit en rupture de stock");
    }
    else{
      printf("Produits en rupture de stock:\n");
      for (int i = 0; i < numberOfProducts; i++) {
          if (products[i].quantite == 0) {
            printf("Nom du produit: %s\n", products[i].nom);
            printf("Référence: %d\n", products[i].reference);
          }
        } 
    }
}

// Afficher les produits avec le stock le plus bas
void displayLowStockProducts() {
    int numberOfProducts;
    Produit *products = getLowStockProducts(&numberOfProducts);

    printf("Produits avec un stock inférieur ou égal à 5:\n");

    // Si nous avons plus de 5 produits, nous limitons l'affichage aux 5 premiers
    int productsToDisplay = numberOfProducts > 5 ? 5 : numberOfProducts;
    int displayedProducts = 0; // nombre de produits affichés

    for (int i = 0; i < numberOfProducts && displayedProducts < productsToDisplay; i++) {
        // On ne tient pas compte des produits dont la quantité en stock est zéro
        if (products[i].quantite > 0) {
            printf("Nom du produit: %s\n", products[i].nom);
            printf("Référence: %d\n", products[i].reference);
            printf("Quantité en stock: %d\n", products[i].quantite);
            displayedProducts++;
        }
    }

    // Libération de la mémoire allouée pour le tableau de produits
    free(products);
}

void createNewProduct() {
    Produit newProduct;
    printf("Entrez le nom du nouveau produit: ");
    scanf("%s", newProduct.nom);
    printf("Entrez le numéro de référence du produit: ");
    scanf("%d", &newProduct.reference);
    printf("Entrez la quantité en stock du produit: ");
    scanf("%d", &newProduct.quantite);
    printf("Entrez le prix du produit: ");
    scanf("%f", &newProduct.prix);
    printf("Entrez la taille du produit (1: petit, 2: moyen, 3: grand): ");
    scanf("%d", &newProduct.taille);
    printf("Entrez la date de péremption du produit (format: jj/mm/aaaa): ");
    scanf("%s", newProduct.datePeremption);

    writeProductToFile(newProduct);
}

void startManagementMode() {
    int choice = 0, quantity = 0, choix=0;
    char nomProduit[50];
    int refProduit;
    Produit produit;
    printf("bonjour dans management mode");
    displayOutOfStockProducts();
    displayLowStockProducts();
    do {
        printf("\n--- Mode Gestion ---\n");
        printf("1. Voir le stock d'un produit spécifique\n");
        printf("2. Augmenter le stock d'un produit spécifique\n");
        printf("3. Créer un nouveau produit\n");
        printf("4. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Voulez-vous rechercher le produit par :\n1. Nom\n2. Référence\n");
                scanf("%d", &choix);
                switch (choix) {
                    case 1:
                        printf("Entrez le nom du produit: ");
                        scanf("%s", nomProduit);
                        produit = readProductFromFile(nomProduit);
                        printf("Quantité en stock de %s: %d\n", produit.nom, produit.quantite);
                        break;
                    case 2:
                        printf("Entrez la référence du produit: ");
                        scanf("%d", &refProduit);
                        produit = readProductByRefFromFile(refProduit);
                        if(produit.reference != -1) {
                            printf("Quantité en stock du produit de référence %s: %d\n", produit.nom, produit.quantite);
                        } else {
                            printf("Le produit avec la référence %d n'a pas été trouvé.\n", refProduit);
                        }
                        break;
                    default:
                        printf("Choix incorrect\n");
                        break;
                }
                break;
            case 2:
                printf("Entrez le nom du produit: ");
                scanf("%s", nomProduit);
                printf("Entrez la quantité a ajouté: ");
                scanf("%d", &quantity);
                updateStock(nomProduit, quantity);
                break;
            case 3:
                createNewProduct();
                break;
            case 4:
                printf("Sortie du mode gestion.\n");
                break;
            default:
                printf("Choix non valide, veuillez réessayer.\n");
                break;
        }
    } while (choice != 4);
}
