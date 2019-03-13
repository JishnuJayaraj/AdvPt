#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <array>
#include <fstream>

#include "Game_Object.h"



#ifndef UNITS_H
#define UNITS_H



class Units : public Game_Object
{


public:
	Units(std::string a, std::string b, int c, int d, double e) : Game_Object(a, b, c, d, e) 
	{}


	//std::string get_type(){

	//	return "unit";

	// }

	~Units() {}

};



#endif