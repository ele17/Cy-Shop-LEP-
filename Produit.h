#ifndef PRODUIT_H
#define PRODUIT_H

typedef struct {
  char nom[50];
  int reference;
  int quantite;
  float prix;
  int taille;
  char datePeremption[20];
} Produit;

Produit createNewProduit(char *nom, int reference, int quantite, float prix, int taille, char* datePeremption);
void updateStock(char *nomProduit, int newQuantite);
void searchProductByName();
void searchProductByReference();
int getMagasinQuantiteTotale();
void checkAndUpdatePrice(Produit *produit);
// void searchProductByCategory();

#endif
