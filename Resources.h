#ifndef RESOURCES_H
#define RESOURCES_H


class Resources {


public :
        double minerals;
        double vespene;
        int supply_used;
        int supply_total;
        double energy;

        // or in unit class?
        int workerOnMineral;
        int workerOnVespene;

        // add worker on build
        // asssign worker to epen or mineral based on nxt build item


        Resources(int minerals,int vespene,int supply_used,int supply_total,int energy){

                this->minerals=minerals;
                this->vespene=vespene;
                this->supply_used=supply_used;
                this->supply_total=supply_total;
                this->energy=energy;
        }


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

        void updateResource(double m,double v,int s) {
                minerals -= m;
                vespene -= v;
                supply_used += s;
        }

        bool checkResource(double min, double ves, int supp) {
                if( (minerals > min) && (vespene > ves) && (supply_total - supply_used > supp) )
                        return true;
                else
                        return false;
        }

// getters

        double getMinerals() {
                return minerals;
        }

        double getVespene() {
                return vespene;
        }

        int getWorkerOnMinerals() {
                return workerOnMineral;
        }

        int getWorkerOnVespene() {
                return workerOnVespene;
        }


};



#endif /* RESOURCES_H */