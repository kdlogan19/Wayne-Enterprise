#include<iostream>
#include<vector>
#include<fstream>
#include "red_black.hpp"
#include "min_heap.hpp"
#include "main_helper.hpp"

int counter = 0;


int main() {
	MainHelper help;
	std::vector<std::string> result;  //vector to store output
	Structptr currentBuilding = nullptr;
	std::ifstream fin("Sample_input2.txt"); //input stream from a file
	std::ofstream fout("output.txt", std::ios::trunc); //output stream to a file
	std::vector<std::string> lines;
	std::string inputCommand, method, temporary;
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
		if(inputCommand!="" && counter == stoi(inputCommand.substr(0,pos))){

			inputCommand.erase(0,pos+2);
			method = inputCommand.substr(0,inputCommand.find("("));
			inputCommand.erase(0,inputCommand.find("(")+1);
			pos = inputCommand.find(",");
			if(method == "PrintBuilding"){
				if(pos != std::string::npos){
					val1 = stoi(inputCommand.substr(0,pos));
					val2 = stoi(inputCommand.substr(pos+1,inputCommand.size()-2));
					help.rbt.printInorder(help.rbt.getRoot(), val1,val2, temporary);
					temporary.pop_back();
					result.push_back(temporary);
					temporary.clear();

				}else{
					val1 = stoi(inputCommand);
	
					Structptr temp = help.rbt.findBuilding(help.rbt.getRoot(),val1);
					help.printOutput(temp,temporary);
					result.push_back(temporary);
					temporary.clear();
				}
			}
			else{
				val1 = stoi(inputCommand.substr(0,pos));
				val2 = stoi(inputCommand.substr(pos+1,inputCommand.size()-1));
				help.newNode = help.rbt.initializeNode(val1,val2);
				help.rbt.insert(help.newNode);
				help.mh.insertIntoMinHeap(help.newNode);	
			}
			std::getline(fin,inputCommand);	
			if(!fin){
				inputCommand = "";
			}
		}
		if(currentBuilding != nullptr && currentBuilding->executionTime == currentBuilding->totalTime){
			help.printFinish(currentBuilding,counter,temporary);
			result.push_back(temporary);
			temporary.clear();
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
		break;
		}
		}
	for(int i = 0;i<result.size();i++){
		fout<<result.at(i)<<"\n";
	}
	 
	return 0;
}

