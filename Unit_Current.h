
#include <iostream>
#include <vector>

#include "Building.h"
#include "Units.h"



#ifndef UNITS_CURRENT_H
#define UNITS_CURRENT_H


class Unit_Current {

public:
    struct item {
        Units unit;
        int number;      // toatal number of same units

        bool min_worker;
        bool gas_worker ;

        int gas_collector;     // no of mineral collectors
        int mineral_collector;

    };

    std::vector<item> currentList;


    Unit_Current(){
        
    }

    void addItem(Units unit, bool min_worker, bool gas_worker) {


        // check if it's there in current list
        bool inList =false;
        for(int i=0;i!=currentList.size();++i) {
            if(currentList[i].unit.name == unit.name) {
                currentList[i].number++;
                inList = true ;
                if(min_worker) {
                    currentList[i].mineral_collector++;
                }

                else if(gas_worker){
                    currentList[i].gas_collector++;
                }

            }
        }

        // if not in list 
        if(!inList) {

            item *newItem = new item;

            newItem->unit = unit;
            newItem->number = 1;

        }

    }


    void freeworker(std::string workername){

        for(int i=0; i != currentList.size(); ++i) {
            if(currentList[i].unit.name == workername) {
                
            }
        }

    }


/* added into addItem
    void addworker() {


    }

    void addGasCollector() {

    }
*/

    void removeGasCollector() {

    }



    bool searchUnit(std::string name) {

        for(int i=0; i!= currentList.size(); ++i){
            if(currentList[i].unit.name==name){
                return true;
        	}
        }
        return false; 

    }


    int getNumMineralCollecor() {

    }

    int getNumGasCollecor() {

    }


};



#endif