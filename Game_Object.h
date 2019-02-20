#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H


#include <string>
#include <iostream>

class Game_Object {
	public:

	std::string name = "empty";
	std::string producedBy;
	//
	int prod_num ;
	int build_time;
	int supply_used;
	// int start_energy;


	int build_starttime;
	int end_time;

	// pure virtual fn to return the clas type of inherited classes
	virtual std::string get_type()=0;

	virtual double energy() {

	}

	virtual void energyUpdate() {

	}

/* it causes error
	Game_Object(std::string n, std::string pn, int num, int sc) {
		name = n;
		producedBy = pn;
		prod_num = num;
		supply_used = sc ;

	}
*/

	std::string name() {
		return name;

	}

	std::string producedBy() {
		return producedBy;

	}	

	int supplyUsed() {
		return supply_used;
	}
	void printResource(){
		std::cout<<name<<" "<<" "<<std::endl;
	}


};

#endif