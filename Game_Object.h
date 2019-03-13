#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <fstream>

class Game_Object {
	protected:                   // access by derived class also

	std::string name ; // = "empty";
	std::string producedBy;
	//
	int number ;
	int prod_num ;
	// int build_time;
	double supply_used;
	// int start_energy;


	// int start_time;
	// int end_time;

	// pure virtual fn to return the clas type of inherited classes
	// virtual std::string get_type()=0;


// it causes error
//  itemName || prodName || id || prodID || supplyUsed
	public:
	Game_Object(std::string n, std::string pn, int num, int pnum, double su) {
		name = n;
		producedBy = pn;
		number = num;
		prod_num = pnum;
		supply_used = su ;

	}


	std::string getName() {
		return name;

	}

	std::string getProducedBy() {
		return producedBy;

	}	

	int getNumber() {
		return number;
	}

	int getProdnum(){
		return prod_num;
	}

	double getSupplyUsed() {
		return supply_used;
	}


	virtual char workerType(){               // for Scv  ???a
		return 'a';
	}

	virtual int getOccupied(){                       // for Scv and TH
		return 0;
	}
	
	virtual void updateOccupied(char c) {           // for scv and TH

	}

	virtual void disengage() {                    // scv wtype=d]

	}
	// time | time neede | Temp | nameOf Item to be build | no | sup neede by item
	virtual void build(int t,int t1, std::multimap <int, Game_Object*> &Temp, std::string nam, int nu, double su) {

	}                                               // ---check

	virtual void updateWorkerType(char c){                 // for scv update wtype

	}

// Speicalllll
	virtual void activate_mule(int t){                 // TH

	}
	virtual std::vector<int> getMule()                    // TH
	{
		std::vector<int> a; 
		return a;
	}
	virtual void mule_update(int t){}                        // TH


	virtual double getEnergy() {                              // for TH
		return 0;
	}

	virtual void energyUpdate() {                         // for TH
  
	}

	~Game_Object() {

	}
};

#endif