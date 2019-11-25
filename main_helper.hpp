

class MainHelper{
    public:
        RedBlackTree rbt;
        MinHeap mh;
        Structptr newNode;
        

        Structptr construction(Structptr cb){
            if(cb == nullptr){
                cb = mh.removeMin();
            }
            if(cb != nullptr){
            ++cb->executionTime;
            }
             return cb;
        }

        void printOutput(Structptr bnum, std::string& temp){
            temp += "(" + std::to_string(bnum->building_num) + "," + std::to_string(bnum->executionTime) + "," + std::to_string(bnum->totalTime) + ")";
        }

        //print function - when construction of building is completed
        void printFinish(Structptr bunm,int day,std::string& temp){
            temp += "(" + std::to_string(bunm->building_num) + "," + std::to_string(day) + ")" ;
        }

};