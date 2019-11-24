#include<iostream>
#include<vector>
#include<fstream>
#include "red_black.hpp"
#include "min_heap.hpp"
#include "main_helper.hpp"

int counter = 0;


int main() {
	MainHelper help;
	Structptr currentBuilding = nullptr;
	std::ifstream fin("sample.txt"); //input stream from a file
	std::ofstream fout; //output stream to a file
	std::vector<std::string> lines;
	std::string inputCommand, method;
	int pos,val1,val2,value;
	bool flag = true;
	int workedDays = 0;
	pos = 0;
	
	std::getline(fin,inputCommand);
	while(flag){
		currentBuilding = help.construction(currentBuilding);
		if(currentBuilding != nullptr){
			++workedDays; 
		}
		pos = inputCommand.find(": ");
		//std::cout<<pos;
		//std::cout<<"\n counter = "<<counter<<"\n";
		if(inputCommand!="" && counter == stoi(inputCommand.substr(0,pos))){

			inputCommand.erase(0,pos+2);
			method = inputCommand.substr(0,inputCommand.find("("));
			//std::cout<<"\nmethod:"<<method<<";";
			inputCommand.erase(0,inputCommand.find("(")+1);
			pos = inputCommand.find(",");
			if(method == "PrintBuilding"){
				if(pos != std::string::npos){
					//when single value is given
					//std::cout<<"single value is given: ="<<pos;
					val1 = stoi(inputCommand.substr(0,pos));
					val2 = stoi(inputCommand.substr(pos+1,inputCommand.size()-2));
					std::cout<<"\n";
					help.rbt.printInorder(help.rbt.getRoot(), val1,val2);
				}else{
					val1 = stoi(inputCommand);
					//std::cout<<"value1:"<<val1;
					Structptr temp = help.rbt.findBuilding(help.rbt.getRoot(),val1);
					help.printOutput(temp);
				}
			}
			else{
				val1 = stoi(inputCommand.substr(0,pos));
				val2 = stoi(inputCommand.substr(pos+1,inputCommand.size()-1));
				help.newNode = help.rbt.initializeNode(val1,val2);
				help.rbt.insert(help.newNode);
				help.mh.insertIntoMinHeap(help.newNode);	
				//std::cout<<"insert at = "<<counter;
			}
			std::getline(fin,inputCommand);	
			if(!fin){
				inputCommand = "";
			}
			//std::cout<<inputCommand;
		}
		if(currentBuilding != nullptr && currentBuilding->executionTime == currentBuilding->totalTime){
			help.printOutput(currentBuilding);
			help.rbt.deleteNode(currentBuilding->building_num);
			workedDays = 0;
			currentBuilding = nullptr;	
		}
		else if(workedDays == 5){
			help.mh.insertIntoMinHeap(currentBuilding);
			workedDays = 0;
			currentBuilding = nullptr;
		}

		counter++;
		if(!fin && help.rbt.getRoot() == help.rbt.getTNIL()){
		std::cout<<"\nexit:0\n";
		break;
		}
		}
	 
	return 0;
}

