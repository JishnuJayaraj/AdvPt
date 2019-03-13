#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <fstream>

#include "Game_Object.h"
#include "Units.h"

#ifndef BUILDINH_H
#define BUILDING_H


class Scv : public Game_Object {
	private:
		char worker_type;
		int occupied ;

	public:
		Scv(std::string a, std::string b, int c, int d, double e) : Game_Object(a,b,c,d,e) {
			worker_type = 'm' ; // for minerals
			occupied = 1 ;
		}

		char workerType() {
			return worker_type;
		}

		int getOccupied() {
			return occupied;
		}

		void updateOccupied(char c) {
			if (c == '+')
				occupied++;
			if (c == '-')
				occupied--;
		}

		void disengage() {
			worker_type = 'd';
		}

		void updateWorkerType(char c) {
			worker_type=c;
		}

		 void build(int t, int t1, std::multimap <int, Game_Object*>& Temp, std::string nam, int num, double s_u) ;
			         // def at enddddddddd
		 

		~Scv() {

		}

};

class Orbital_Command : public Game_Object
{
	private:
		double energy;
		int occupied;
		std::vector<int> mule;

	public:
		Orbital_Command(std::string a, std::string b, int c, int d, double e) : Game_Object(a,b,c,d,e) {
			energy=50;
			occupied=1;

		}

		int getOccupied() {
			return occupied;
		}

		void updateOccupied(char c) {
			if (c == '+')
				occupied++;
			if (c == '-')
				occupied--;
		}

		double getEnergy() {
			return energy;
		}

		void energyUpdate() {
			if (energy < 200)
				energy += 0.5625;                 // check
		}

// Specialllll
		void activate_mule(int t)
		{
			mule.push_back(t + 90);
			energy -= 50;
		}
		
		std::vector<int> getMule()
		{
			return mule;
		}

		void mule_update(int t)
		{
			int i = 0;
			for (auto it = mule.begin(); it != mule.end(); it++)
			{
				if (mule[i] == t)             // delete the specific mule entry of t
				{
					mule.erase(it);
					break;
				}
				i++;
			}
		}

// ????????????????
		void build(int t, int t1, std::multimap <int, Game_Object*>& Temp, std::string nam, int num, double s_u)
		{
			std::cout<<"\n ~~build() inside orbital command~~\n";
			Temp.insert({ t + t1, new Scv(nam, name, num, number, s_u) });  // WHYYYYYY arg name|game obj name|arb num, |gameObj num
		}

		~Orbital_Command() {

		}
};

class Building : public Game_Object
{
	private:
		int occupied;
	public:

	//std::string get_type(){

	//	return "building";


	//}

	Building(std::string a, std::string b, int c, int d, double e) : Game_Object(a, b, c, d, e) {
		if (a == "barracks_with_reactor" || a == "factory_with_reactor" || a == "starport_with_reactor")
			occupied = 2;
		else
			occupied = 1;
	}

	int getOccupied() {
		return occupied;
	}

	void updateOccupied(char c) {
		if (c == '+')
			occupied++;
		if (c == '-')
			occupied--;
	}

	void build(int t, int t1, std::multimap <int, Game_Object*>& Temp, std::string nam, int num, double s_u) {
		std::cout<<"\n ~~build() inside building~~\n";                            //del
		if (nam == "scv") { 
			Temp.insert({ t + t1, new Scv(nam, name, num, number, s_u) });
			std::cout<<"\n ~~inside build()=insertin new scv\n";
		}
		else if (nam== "barracks_with_tech_lab" || nam == "barracks_with_reactor"||
			nam == "factory_with_reactor"|| nam == "factory_with_tech_lab"|| nam == "starport_with_reactor"|| nam == "starport_with_tech_lab" ) { 
			Temp.insert({ t + t1, new Building (nam, name, num, number, s_u) });
			std::cout<<"\n ~~inside build()=insertin new buildin\n";
			}
		else if (nam == "orbital_command")  {        // planetry fortress???
			Temp.insert({ t + t1, new Orbital_Command(nam, name, num, number, s_u) });
			std::cout<<"\n ~~inside build()=insertin new ORbital com\n";
		}
		else { 
			Temp.insert({ t + t1, new Units (nam, name, num, number, s_u) });
			std::cout<<"\n ~~inside build()=insertin new unit\n";
		}
	}

	~Building() {}


 };

void Scv::build(int t, int t1, std::multimap <int, Game_Object*>& Temp, std::string nam, int num, double s_u)
{
	std::cout<<"\n ~~build() inside Scv~~\n";                                        //del
	Temp.insert({ t + t1, new Building(nam, name, num, number, s_u) });
}

#endif