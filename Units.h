#include <string>
#include <iostream>

#include "Game_Object.h"



#ifndef UNITS_H
#define UNITS_H



class Units : public Game_Object
{
	std::string u_name="empty" ;






	std::string get_type(){

		return "unit";

	}



};



#endif