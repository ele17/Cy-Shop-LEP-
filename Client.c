#include <stdio.h>
#include <string.h>
#include "Client.h"
#include "file_utils.h"

  
Client createNewClient(char *nom, char *prenom) {
  Client newClient;
  // Vérifie si le client existe déjà
  Client existingClient = readClientFromFile(nom);
  if ((strcmp(existingClient.nom, nom) == 0) && (strcmp(existingClient.prenom, prenom) == 0)) {
    printf("Un client avec ce nom et prénom existe déjà.\n");
    return existingClient;
  }
  
  strcpy(newClient.nom, nom);
  strcpy(newClient.prenom, prenom);
  newClient.nbAchats = 0;  // Initialise le nombre d'achats à 0
  writeClientToFile(newClient);
  return newClient;
}

/*void makePurchase(Client *client, char *nomProduit) {
    Produit produit = readProductFromFile(nomProduit);
    if (produit.quantite > 0) {
        produit.quantite--;
        updateProductInFile(produit);
        strcat(client->historiqueAchats, nomProduit);
        strcat(client->historiqueAchats, "\n");
        writeClientToFile(*client);
    } else {
        printf("Désolé, ce produit est en rupture de stock.\n");
    }
}*/

void afficherDerniersAchats(Client *client) {
    printf("Derniers achats de %s %s :\n", client->nom, client->prenom);
    for (int i = 0; i < client->nbAchats; i++) {
        printf("%d x %s\n", client->historiqueAchats[i].quantite, client->historiqueAchats[i].nomProduit);
    }
}

void viewPurchaseHistory(Client client) {
    printf("Historique des achats pour %s %s:\n%s", client.nom, client.prenom, client.historiqueAchats);
}

void deleteClient(char *nomClient) {
    deleteClientFromFile(nomClient);
}

