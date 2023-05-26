#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "Client.h"
#include "Produit.h"

void writeClientToFile(Client client);
Client readClientFromFile(char *nomClient);
void deleteClientFromFile(char *nomClient);
void updateClientInFile(Client client);

void writeProductToFile(Produit produit);
Produit readProductFromFile(char *nomProduit);
Produit readProductByRefFromFile(int referenceProduit);
void deleteProductFromFile(char *nomProduit);
void updateProductInFile(Produit produit);

void checkAndCreateFile(const char *filename);
void checkAndCreateClientAndProductFiles();
float getProductPrice(char* nomProduit);
// Produit readProductByCategoryFromFile(int categorie);
void ajouterAchat(Client *client, Produit produit, int quantite);
void formaterHistorique(Client *client);


#endif
  
