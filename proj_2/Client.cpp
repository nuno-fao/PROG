#include "Client.h"
#include "iomanip"
//Class constructors

Client::Client() {

}

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address): name(name), VATnumber(VATnumber), familySize(familySize), address(address){

    totalPurchased = 0;

}

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet>  packets, unsigned totalPurchased): name(name), VATnumber(VATnumber), familySize(familySize), address(address), packets(packets), totalPurchased(totalPurchased){
}

  // GET methods

string Client::getName() const{
  
	return name;
}
  
unsigned Client::getVATnumber() const{
  
	return VATnumber;
}

unsigned short Client::getFamilySize() const{
  
	return familySize;
}

Address Client::getAddress() const{
  
	return address;
}

vector<Packet> Client::getPacketList() const{
  
	return packets;
}

double Client::getTotalPurchased() const{

	return totalPurchased;
}

//function that returns client's packets' ids in a string
string Client::getAllIDs() const{
	
	string ids = "";
	for (unsigned i = 0; i < packets.size(); i++) {
		if (i == packets.size() - 1) {
			ids += to_string(packets.at(i).getId());
		}
		else {
			ids += to_string(packets.at(i).getId());
			ids += " ; ";
		}
	}
	return ids;
}

//function that prints client information
void Client::showFullInfo() const {
	cout << "Name: " << getName() << endl << "VAT number: " << getVATnumber() << endl;
	cout << "Family size: " << getFamilySize() << endl << "Adress: " << getAddress().getFullAdress() << endl;
	cout << "Packets bought: " << getAllIDs() << endl << "Total purchases " << getTotalPurchased() << endl;
}
  
  // metodos SET
	  
void Client::setName(string nome) {
  
	name = nome;
}

void Client::setVATnumber(unsigned VATnumber){
  
	this->VATnumber = VATnumber;
}

void Client::setFamilySize(unsigned short familySize){
  
	this->familySize = familySize;
}

void Client::setAddress(Address address){
  
	this->address = address;
}

void Client::setPacketList(vector<Packet> & packets){
  
	this->packets = packets;
}

void Client::setTotalPurchased(double totalPurchased){
  
	this->totalPurchased = totalPurchased;
}

  
  // outros metodos

//when client given to operator '<<' prints client information
ostream& operator<<(ostream& out, const Client & client){

    out << "Name: " << client.getName() << endl << "VAT number: " << client.getVATnumber() << endl
        << "Family size: " << client.getFamilySize() << endl << "Adress: " << client.getAddress().getFullAdress() << endl
        << "Packets bought: " << client.getAllIDs() << endl << "Total purchases " << client.getTotalPurchased() << endl;
    return out;

}
