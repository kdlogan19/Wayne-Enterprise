
class MinHeap{
	private:
		std::vector<Structptr> work_days;	//

		int parent(int i ){
			return (i-1)/2;
		}

		int right_child(int i){
			return (i * 2 + 2);
		}

		int left_child(int i){
			return (i*2 + 1);
		}

		//making the array a min heap whenever a new element is inserted
		void heapify(int i){
			if(i && work_days[i]->executionTime<work_days[parent(i)]->executionTime){
				std::swap(work_days[i],work_days[parent(i)]);
				heapify(parent(i));
			}else if(i && work_days[i]->executionTime == work_days[parent(i)]->executionTime){
				if(work_days[i]->building_num < work_days[parent(i)]->building_num){
					std::swap(work_days[i],work_days[parent(i)]);
				}
			}
		}

		//making the array a min heap whenever min is changed or deleted
		void heapify_down(){
				if(size()>0){					
					for(int i = 0; i< (size()/2);){
						int min;
						int l = left_child(i);
						int r = right_child(i);
						if(l<size() && r<size()){
							if(work_days[l]->executionTime < work_days[r]->executionTime){
								min  = l;
							}else if(work_days[l]->executionTime == work_days[r]->executionTime){
								if( work_days[l]->building_num < work_days[r]->building_num){
									min  = l;
								}else{
									min = r;
								}
							}else{
							min = r;
							}
						}else if(l<size() && r >=size()){
							min = l;
						}else {
							min = r;
						}

						if(work_days[i]->executionTime > work_days[min]->executionTime){
							std::swap(work_days[i],work_days[min]);
						}else if(work_days[i]->executionTime == work_days[min]->executionTime){
							if( work_days[min]->building_num < work_days[i]->building_num){
							std::swap(work_days[i],work_days[min]);	
							}
						}else{
							break;
						}
						i = min;
						
					}
					}
			}
	
	public:
	
		MinHeap(){
			work_days = {};
		}
		

		int size(){
			int x = work_days.size();
			return x;
		}

		//inserting the new node referenced to redblack tree
	
		void insertIntoMinHeap(Structptr newNode){
			work_days.push_back(newNode);
			heapify(size() - 1);
		}
		//function to increment days as construction work proceeds
		void increment_time(int val){
			work_days[0]->executionTime += val;
			heapify_down(); 
		}

		int rootMinheap(){
			return work_days[0]->executionTime;
		}

		//removing the node at 0th index
		Structptr removeMin(){
			if(size() > 0){
				Structptr min = work_days[0];
				//std::cout<<"print inside remove min: ";
				work_days[0] = work_days[size()-1];
				work_days.pop_back();
				//std::cout<<"print inside remove min: ";
				heapify_down();
				return min;
			}
			return nullptr;
		}

		void printMinHeap(){
			for (int i = 0; i< size(); ++i){
				 std::cout<<"("<<work_days.at(i)->building_num<<","<<work_days.at(i)->executionTime<<","<<work_days.at(i)->totalTime<<")";
			}
		}
};


