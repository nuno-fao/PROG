#ifndef ALLFUNCS_H
#define ALLFUNCS_H

#include "TypeStruDef.h"

void clearInput(void);

opChoose mainmenu(void);

//void infoprint(void);

vector<Client> readClients(void);
vector<TravelPack> readPacks(void);

void removePack(vector<TravelPack> &packlist);
void removeClient(vector<Client> &clientlist);

void writePacks(vector<TravelPack> packlist);
void writeClients(vector<Client> clientlist);

void addClient(vector<Client> &clientlist, vector<TravelPack> packlist);
void addPack(vector<TravelPack> &packlist);

void printclientinfo(Client client);
void printpackinfo(TravelPack pack);

void buypack(vector<TravelPack> &packlist, Client &client, string packid);

void ChangeClientData(vector<Client> &client, opChoose index);
void ChangePackData(TravelPack &pack);

void printclientinfo2(Client client);
void printpackinfo2(TravelPack pack);

#endif