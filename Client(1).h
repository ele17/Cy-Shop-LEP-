#ifndef CLIENT_H
#define CLIENT_H

typedef struct {
    char nomProduit[50];
    int quantite;
    float prixUnitaire; 
} Achat;

typedef struct {
    char nom[50];
    char prenom[50];
    Achat historiqueAchats[100];
    int nbAchats;
    char historiqueFormate[500];
} Client;

Client createNewClient(char *nom, char *prenom);
void makePurchase(Client *client, char *nomProduit);
void viewPurchaseHistory(Client client);
void deleteClient(char *nomClient);


#endif // CLIENT_H
