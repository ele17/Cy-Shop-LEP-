#include <stdio.h>
#include <string.h>
#include "achat.h"
#include "Client.h"
#include "Produit.h"
#include "file_utils.h"

void printMenu() {
    printf("\n1. Voir les derniers achats\n");
    printf("2. Chercher un produit\n");
    printf("3. Finaliser les achats et voir le total\n");
    printf("4. Quitter\n");
}

void startPurchaseMode() {
    int choix;
    char nom[50];
    char prod[50];
    char prenom[50];
    Client client;
    Produit produit;
    float total = 0;
    int quantite;
    int confirmation;
    int oldNbAchats = client.nbAchats;

    printf("Mode Achat\n");
    printf("Avez-vous un compte ?\n");
    printf("1. Oui\n");
    printf("2. Non\n");
    scanf("%d", &choix);
    
  
    switch (choix) {
        case 1:
            printf("Veuillez entrer votre nom:\n");
            scanf("%s", nom);
            printf("Veuillez entrer votre prénom:\n");
            scanf("%s", prenom);
            client = readClientFromFile(nom);
            if(strcmp(client.nom, "") == 0) {
                printf("Aucun client avec ce nom et prénom n'a été trouvé. Veuillez réessayer.\n");
                return;
            }
            break;
        case 2:
            printf("Veuillez entrer votre nom:\n");
            scanf("%s", nom);
            printf("Veuillez entrer votre prénom:\n");
            scanf("%s", prenom);
            client = createNewClient(nom, prenom);
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            return;
    }

// Le client est maintenant connecté et peut commencer à acheter des produits
int continuerAchats = 1;
while (continuerAchats == 1) {
    int modeRecherche;
    printf("Comment voulez-vous rechercher le produit ?\n");
    printf("1. Par nom\n");
    printf("2. Par référence\n");
    // printf("3. Par catégorie\n");
    scanf("%d", &modeRecherche);

    switch(modeRecherche) {
        case 1:
            // searchProductByName();
            printf("Veuillez entrer le nom du produit:\n");
            scanf("%s", prod);
            produit = readProductFromFile(prod);
            printf("Combien voulez-vous en acheter ?\n");
            scanf("%d", &quantite);

            // Vérifie la date de péremption et applique la réduction si nécessaire
            // checkAndUpdatePrice(&produit);

            ajouterAchat(&client, produit, quantite);
            break;
        case 2:
            // searchProductByReference();
            printf("Veuillez entrer la reference du produit:\n");
            scanf("%d", prod);
            produit = readProductByRefFromFile(prod);
            printf("Combien voulez-vous en acheter ?\n");
            scanf("%d", &quantite);

            // Vérifie la date de péremption et applique la réduction si nécessaire
            // checkAndUpdatePrice(&produit);

            ajouterAchat(&client, produit, quantite);
            break;
        /*case 3:
            // searchProductByCategory();
            printf("Veuillez entrer la categorie du produit:\n");
            scanf("%s", prod);
            produit = readProductFromFile(prod);
            printf("Combien voulez-vous en acheter ?\n");
            scanf("%d", &quantite);

            // Vérifie la date de péremption et applique la réduction si nécessaire
            checkAndUpdatePrice(&produit);

            ajouterAchat(&client, produit, quantite);
            break;*/
        default:
            printf("Mode de recherche invalide. Veuillez réessayer.\n");
            continue;
    }
// Calculez le montant total des achats
for (int i = 0; i < client.nbAchats; i++) {
    // Utilisez le prix stocké dans chaque Achat plutôt que le prix actuel du produit
    total += client.historiqueAchats[i].prixUnitaire * client.historiqueAchats[i].quantite;
}
    printf("Voulez-vous continuer vos achats ?\n");
    printf("1. Oui\n");
    printf("2. Non\n");
    scanf("%d", &continuerAchats);
}
    

    printf("Le montant total de vos achats est : %.2f\n", total);

    printf("Confirmez-vous votre achat ?\n");
    printf("1. Oui\n");
    printf("2. Non\n");
    scanf("%d", &confirmation);

    if (confirmation == 1) {
        // Mise à jour du stock des produits après confirmation de l'achat
      printf("bonjour Nombre d'achats : %d\n", client.nbAchats);
      printf("bonjour Nombre d'achats : %d\n", oldNbAchats);
      for (int i = oldNbAchats; i < client.nbAchats; i++) {
        char * nomProduit = client.historiqueAchats[i].nomProduit;
        int quantiteAchetee = client.historiqueAchats[i].quantite;
        Produit produit = readProductFromFile(nomProduit);
        printf("bonjour avant update");
        produit.quantite -= quantiteAchetee;  // Met à jour la quantité du produit
        updateProductInFile(produit);  // Met à jour le fichier du produit
        printf("bonjour apres update");
    }

        printf("Merci pour vos achats !\n");
    } else {
        printf("Achat annulé.\n");
    }

    // Retournez à la page principale
    return;
}
