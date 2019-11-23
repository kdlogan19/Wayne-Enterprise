
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
				std::swap(work_days[i]->executionTime,work_days[parent(i)]->executionTime);
				heapify(parent(i));
			}
		}

		//making the array a min heap whenever min is changed or deleted
		void heapify_down(int i){
			int l = left_child(i);
			int r = right_child(i);
			int min = i;
			if(l<=size() && work_days[l] < work_days[i]){
				min  = l;
			}
			if(l<=size() && work_days[r]<work_days[min]){
				min  = r;
			}
			if(i != min){
				std::swap(work_days[i],work_days[min]);
				heapify_down(min);
			}
			//std::cout<<"inside down";
			//print();
			
		}
	
	public:
	
		MinHeap(){
			work_days = {};
		}
		

		int size(){
			return work_days.size();
		}

		//inserting the new node referenced to redblack tree
	
		void insertIntoMinHeap(Structptr newNode){
			work_days.push_back(newNode);
			heapify(size() - 1);
		}
		//function to increment days as construction work proceeds
		void increment_time(int val){
			work_days[0]->executionTime += val;
			heapify_down(0); 
		}

		int rootMinheap(){
			return work_days[0]->executionTime;
		}

		void delete_root(){
			work_days[0] = work_days.back();
			work_days.pop_back();
			heapify_down(0);
		}

		void printMinHeap(){
			for (int i = 0; i< (int)work_days.size(); ++i){
				std::cout<<work_days.at(i)->executionTime<<" ";
			}
		}
};


