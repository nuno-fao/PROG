#include "Packet.h"

unsigned Packet::lastID;
Packet::Packet(vector<string> sites, Date inicio, Date fim, double precoPessoa,unsigned totalPersons, unsigned maxPessoas): sites(sites), begin(inicio), end(fim), pricePerPerson(precoPessoa),totalPersons(totalPersons), maxPersons(maxPessoas) {
	available = true;
}
Packet::Packet(unsigned id, vector<string> sites, Date inicio, Date fim, double precoPessoa,unsigned totalPersons, unsigned maxPessoas): id(id),sites(sites), begin(inicio), end(fim), pricePerPerson(precoPessoa),totalPersons(totalPersons), maxPersons(maxPessoas) {
    available = true;
}
Packet::Packet(){
}

  // metodos GET

unsigned Packet::getId() const{

	return id;
}

vector<string> Packet::getSites() const{

	return sites;
}

Date Packet::getBeginDate() const{
	return begin;
}

Date Packet::getEndDate() const{

	return end;
}

double Packet::getPricePerPerson() const{

	return pricePerPerson;
}

unsigned Packet::getMaxPersons() const{

	return maxPersons;
}

unsigned Packet::getTotalPersons() const{
    return totalPersons;
}

unsigned Packet::getLastID(){
    return  lastID;
}

//function that returns full destination of a packet in a string
string Packet::getFullDestination() const{
    string ids = "";
    unsigned i;
	if (sites.size() > 1) {
		ids += sites.at(0) + " - ";
		for (i = 1; i < sites.size(); i++) {
			if (i == sites.size() - 1) {
				ids += sites.at(i);
			}
			else {
				ids += sites.at(i);
				ids += ", ";
			}
		}
	}
	else {
		ids += sites.at(0);
	}
    return ids;
}

bool Packet::getAvailability() const{
    return available;
}


  // metodos SET

void Packet::setId(unsigned id){

	this->id = id;
}

void Packet::setSites(vector<string> sites){

	this->sites = sites;
}

void Packet::setBeginDate(Date begin){

	this->begin = begin;
}

void Packet::setEndDate(Date end){

	this->end = end;
}

void Packet::setPricePerPerson(double pricePerPerson) {

	this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPersons(unsigned maxPersons){

	this->maxPersons = maxPersons;
}

void Packet::setAvailable(bool available) {
	this->available = available;
}

void Packet::setLastID(unsigned ID){
    lastID=ID;
}
void Packet::setTotalPersons(unsigned totalPersons){
    this->totalPersons=totalPersons;
}

void Packet::showFullInfo(){
    cout<<"ID: "<<getId()<<endl;
    cout<<"Destination: "<<getFullDestination()<<endl;
    cout<<"Beginning Date: "<<getBeginDate().getDate()<<endl;
    cout<<"Ending Date: "<<getEndDate().getDate()<<endl;
    cout<<"Price per Person: "<<getPricePerPerson()<<endl;
    cout<<"Total Persons: "<<getTotalPersons()<<endl;
    cout<<"Reserved Places: "<<getMaxPersons()<<endl<<endl;
}

/*********************************
 * Show Packet information
 ********************************/  

// shows a packet content 
//ostream& operator<<(ostream& out, const Packet & packet){

//  // REQUIRES IMPLEMENTATION
//}

//when two packets are compared with '==' it compares their id's
bool operator == (Packet const &packet1,Packet const &packet2){
    if(packet1.getId()==packet2.getId()){
        return true;
    }
    return false;
}
