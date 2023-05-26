#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Produit.h"
#include "file_utils.h"

#define CAPACITE_MAGASIN 1000

Produit createNewProduit(char *nom, int reference, int quantite, float prix, int taille, char* datePeremption) {
    Produit newProduit;
    strcpy(newProduit.nom, nom);
    newProduit.reference = reference;
    newProduit.quantite = quantite;
    newProduit.prix = prix;
    newProduit.taille = taille;
    strcpy(newProduit.datePeremption, datePeremption);
    writeProductToFile(newProduit);
    return newProduit;
}

void searchProductByName() {
    char nom[50];
    printf("Entrez le nom du produit : ");
    scanf("%s", nom);

    Produit produit = readProductFromFile(nom);
    if (strcmp(produit.nom, "") != 0) {  // Si un produit avec ce nom existe
        printf("Produit trouvé : %s\n", produit.nom);
        printf("Référence: %d\n", produit.reference);
        printf("Prix: %.2f\n", produit.prix);
        printf("Quantité: %d\n", produit.quantite);
        printf("Taille: %d\n", produit.taille);
        printf("Date de péremption: %s\n", produit.datePeremption);
    } else {
        printf("Aucun produit avec ce nom n'a été trouvé.\n");
    }
}

void searchProductByReference() {
    int reference;
    printf("Entrez la référence du produit : ");
    scanf("%d", &reference);

    Produit produit = readProductByRefFromFile(reference);
    if (produit.reference != 0) {  // Si un produit avec cette référence existe
        printf("Produit trouvé : %s\n", produit.nom);
        printf("Référence: %d\n", produit.reference);
        //printf("Catégorie: %d\n", produit.categorie);
        printf("Prix: %.2f\n", produit.prix);
        printf("Quantité: %d\n", produit.quantite);
        printf("Taille: %d\n", produit.taille);
        printf("Date de péremption: %s\n", produit.datePeremption);
    } else {
        printf("Aucun produit avec cette référence n'a été trouvé.\n");
    }
}

/*void searchProductByCategory() {
    int categorie;
    printf("Entrez la catégorie du produit : ");
    scanf("%d", &categorie);

    Produit produit = readProductByCategoryFromFile(categorie);
    if (produit.categorie != 0) {  // Si un produit avec cette catégorie existe
        printf("Produit trouvé : %s\n", produit.nom);
        printf("Référence: %d\n", produit.reference);
        printf("Catégorie: %d\n", produit.categorie);
        printf("Prix: %.2f\n", produit.prix);
        printf("Quantité: %d\n", produit.quantite);
        printf("Taille: %d\n", produit.taille);
        printf("Date de péremption: %s\n", produit.datePeremption);
    } else {
        printf("Aucun produit avec cette catégorie n'a été trouvé.\n");
    }
}*/

void updateStock(char *nomProduit, int newQuantite) {
    Produit produit = readProductFromFile(nomProduit);
    produit.quantite += newQuantite;
    if (produit.quantite * produit.taille + getMagasinQuantiteTotale() > CAPACITE_MAGASIN) {
    printf("L'ajout de ces produits ferait dépasser la capacité du magasin. Operation annulée.\n");
      return;
}
    updateProductInFile(produit);
}

int getMagasinQuantiteTotale() {
    FILE *file = fopen("produits.txt", "r");
    Produit produit;
    int total = 0;

    while (fscanf(file, "%s %d %d %f %d %s\n", produit.nom,
                  &produit.reference, &produit.quantite, &produit.prix,
                  &produit.taille, produit.datePeremption) != EOF) {
        total += produit.quantite * produit.taille; // multiplie la quantité par la taille
    }

    fclose(file);
    return total;
}

// Conversion d'une date au format "JJ/MM/AAAA" en struct tm
struct tm parseDate(char* dateStr) {
    struct tm tm;
    sscanf(dateStr, "%d/%d/%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
    tm.tm_mon--;      // Ajustement pour l'index basé sur zéro
    tm.tm_year -= 1900; // Ajustement pour le comptage à partir de 1900
    tm.tm_hour = 0; 
    tm.tm_min = 0; 
    tm.tm_sec = 0; 
    tm.tm_isdst = -1; // Indique à mktime de déterminer si l'heure d'été est en vigueur
    return tm;
}

// Obtenir la date actuelle
struct tm getCurrentDate() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    tm.tm_hour = 0; 
    tm.tm_min = 0; 
    tm.tm_sec = 0; 
    return tm;
}

// Calculer la différence entre deux dates en jours
int diffDays(struct tm date1, struct tm date2) {
    time_t t1 = mktime(&date1);
    time_t t2 = mktime(&date2);
    return difftime(t2, t1) / (60 * 60 * 24);
}

// Fonction pour vérifier la date de péremption et mettre à jour le prix
void checkAndUpdatePrice(Produit *produit) {
    struct tm currentDate = getCurrentDate();
    struct tm productDate = parseDate(produit->datePeremption);
    int daysUntilExpiry = diffDays(currentDate, productDate);
    if (daysUntilExpiry <= 5) {
        produit->prix *= 0.5;  // Réduction de 50%
        printf("Le produit %s a une réduction de 50%%, nouveau prix: %.2f\n", produit->nom, produit->prix);
    }
}
