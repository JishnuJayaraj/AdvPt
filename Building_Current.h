

#include <iostream>

#include <vector>

#include "Building.h"


class Building_Current {

    private:
        struct item {
            Building build;
            bool is_working ;
        };

        std::vector<item> currentList;



public:

    std::string get_type() {

        return "current building";
    }
    

    bool isFreeBuilding(std::string name) {

        bool result = false ;

        for(int i=0; i< currentList.size(); ++i) {

            if(currentList[i].build.name == name && currentList[i].is_working == false)
                return true;

        }

        return false;

    }


    bool useFreeBuilding(std::string name) {

    	for(int i=0; i!= currentList.size(); ++i){
            if(currentList[i].build.name== name && currentList[i].is_working==false){
                currentList[i].is_working= true;
                return true;
    	    }
    	}
        return false;      

    }

    void freeBuilding(std::string name){

          for(int i=0; i!= currentList.size(); ++i){
            if(currentList[i].build.name==name and currentList[i].is_working==true){

    	        		   currentList[i].is_working=false;

    	    }
        }

    }

    bool searchBuilding(std::string name){

        for(int i=0; i!= currentList.size(); ++i){
            if(currentList[i].build.name==name){
                return true;
        	}
        }
    return false;
    }

    void deleteBuilding(std::string name){

        for(int i=0; i!= currentList.size(); ++i){
            if(currentList[i].build.name==name){
                currentList.erase(currentList.begin()+i);
                return;
           	}
        }

    }

    void addItem (Building name){

        item *newitem = new item;
        newitem->build = name;
        newitem->is_working=false;
        currentList.push_back(*newitem);

    }
/*
    void print(){

        for(int i=0;i<currentList.size();i++){
            std::cout<<currentList[i].build.name<<currentList[i].build<<std::endl;

        }
    }
*/



}