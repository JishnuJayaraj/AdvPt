#include <string>

# include "Game_Object.h"


#ifndef BUILDINH_H
#define BUILDING_H




class Building : public Game_Object
{
	
	public:

	std::string get_type(){

		return "building";


	}

	Building(std::map < std::string, std::tuple <double, double, int, double, std::string, std::string>> building, int time, json *json, resources *resources){

	}
};


#endif