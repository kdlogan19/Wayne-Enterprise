

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

        void printOutput(Structptr bnum){
            std::cout<<"\n("<<bnum->building_num<<","<<bnum->executionTime<<","<<bnum->totalTime<<")";
        }

};