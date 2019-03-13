#ifndef RESOURCES_H
#define RESOURCES_H


class Resources {


public:
        double minerals;
        double vespene;
        double supply_used;
        double supply_total;

        // or in unit class?
        // int workerOnMineral;
        // int workerOnVespene;

        // add worker on build
        // asssign worker to epen or mineral based on nxt build item


        Resources(double minerals,double vespene,double supply_used,double supply_total){

                this->minerals=minerals;             // IC   50
                this->vespene=vespene;                 //   0
                this->supply_used=supply_used;         //   6
                this->supply_total=supply_total;       //   11
                
        }

/*
// setters
        void incrementMinerals() {
                minerals = minerals + 0.7 * workerOnMineral;

        }

        void incrementVespene() {
                vespene = vespene + 0.35 * workerOnVespene;
        }

        void addWorkerOnMineral() {
                workerOnMineral++ ;
        }

        void addWorkerOnVespene() {
                workerOnVespene++ ;
        }
*/


        void updateResource(double m,double v,double su, double st ) {
                minerals += m;
                vespene += v;
                supply_used = su;
                supply_total = st;
        }

        bool checkResource(double min, double ves, double supp) {
                if( (minerals >= min) && (vespene >= ves) && (supply_total - supply_used >= supp) ) { 
                        std::cout<<"\n\tCheck resource condition met";
                        return true;
                }
                else
                        return false;
        }

        void modifyResource(double m, double v, double s) {
                minerals -= m ;
                vespene -= v ;
                supply_used += s ;

        }
// getters

        double getMinerals() {
                return minerals;
        }

        double getVespene() {
                return vespene;
        }
/*
        int getWorkerOnMinerals() {
                return workerOnMineral;
        }

        int getWorkerOnVespene() {
                return workerOnVespene;
        }
*/

        ~Resources() {}

};



#endif /* RESOURCES_H */