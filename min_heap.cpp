#include<iostream>
#include<vector>

using namespace std;

//data-structure for min-heap
class Execution_time{
	private:
		vector<int> work_days;	//

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
			if(i && work_days[i]<work_days[parent(i)]){
				swap(work_days[i],work_days[parent(i)]);
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
				swap(work_days[i],work_days[min]);
				heapify_down(min);
			}
			//cout<<"inside down";
			//print();
			
		}
	
	public:
		int size(){
			return work_days.size();
		}

		void insert(int val){
			work_days.push_back(val);
			heapify(size() - 1);
		}
		//function to increment days as construction work proceeds
		void increment_time(int val){
			work_days[0] += val;
			heapify_down(0); 
		}

		int root(){
			return work_days[0];
		}

		void delete_root(){
			work_days[0] = work_days.back();
			work_days.pop_back();
			heapify_down(0);
		}

		void print(){
			for (int i = 0;i<work_days.size();++i){
				cout<<work_days.at(i)<<" ";
			}
		}
};

int main(){
	Execution_time et;
	et.insert(1);
	et.insert(10);
	et.insert(15);
	et.insert(14);
	et.insert(11);
	et.print();
	et.delete_root();
	//et.increment_time(10);
	
	
	cout<<"\n after delete \n";
	et.print();

	return 0;
}