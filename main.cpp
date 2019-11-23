#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include "red_black.hpp"
#include "min_heap.hpp"


int counter = 0;
RedBlackTree bst;
MinHeap mh;
Structptr newNode;

void parse(std::string line){
	std::vector<std::string> parsedInput;
	std::string method,values,day,val1,val2;
	std::cout<<"in parsing";
	int pos = 0;
	line.pop_back(); //removing last bracket ')'

	while(	pos != std::string::npos){
		day = stoi(line.substr(0,line.find(": ")));
		parsedInput.push_back(day);
		std::cout<<"\nday:"<<day;
		line.erase(0,line.find(": ")+2);
		method = line.substr(0,line.find("("));
		std::cout<<"\nmethod: "<<method;
		parsedInput.push_back(method);
		line.erase(0,line.find("(")+1);
		parsedInput.push_back(line);
		/*
		pos = line.find(",");
		if(method == "PrintBuilding"){
			std::cout<<"found by pb";
			if(pos != std::string::npos){
				//when single value is given
				std::cout<<"single value is given: ="<<pos;
				val1 = stoi(line.substr(0,pos));
				val2 = stoi(line.substr(pos+1,line.size()-2));
				std::cout<<"val1: "<<val1<<"val2"<<val2;
			}else{
				val1 = stoi(line);
				std::cout<<"value1:"<<val1;
			}
		}
		else{
			std::cout<<"in insert building ";
			val1 = stoi(line.substr(0,pos));
			val2 = stoi(line.substr(pos+1,line.size()-1));
			std::cout<<"val1: "<<val1<<"val2 = "<<val2;
			newNode = bst.initializeNode(val1,val2);
			bst.insert(newNode);
			mh.insertIntoMinHeap(newNode);

		}
		pos = std::string::npos; */
	}
}



//Insert(int)

int main() {
	std::ifstream fin("sample.txt"); //input stream from a file
	std::ofstream fout; //output stream to a file
	std::vector<std::string> lines;
	std::string inputCommand, method;
	int pos,val1,val2,value;
	bool flag = true;
	
	if(!fin){
		std::cout<<"exit:0";
		return 1;
	}
	std::getline(fin,inputCommand);
	/*
	while (std::getline(fin,line))	{
		lines.push_back(line);
	}
	
	int fileSize  = lines.size();
	
	for(int i=0;i<fileSize; i++){
		//std::cout<<"\n"<<" ";
		//std::cout<<lines.at(i);
	//	parse(lines.at(i));
	//}
	std::string inputCommand = lines[0] ;
	*/
	while(flag){
		pos = inputCommand.find(": ");
		if(counter == stoi(inputCommand.substr(0,pos))){
			inputCommand.erase(0,pos);
			method = inputCommand.substr(0,inputCommand.find("("));
			std::cout<<"\nmethod: "<<method;
			inputCommand.erase(0,inputCommand.find("(")+1);
			pos = inputCommand.find(",");
			if(method == "PrintBuilding"){
				std::cout<<"found by pb";
				if(pos != std::string::npos){
					//when single value is given
					std::cout<<"single value is given: ="<<pos;
					val1 = stoi(inputCommand.substr(0,pos));
					val2 = stoi(inputCommand.substr(pos+1,inputCommand.size()-2));
					std::cout<<"val1: "<<val1<<"val2"<<val2;
				}else{
					val1 = stoi(inputCommand);
					std::cout<<"value1:"<<val1;
				}
			}
			else{
				std::cout<<"in insert building ";
				val1 = stoi(inputCommand.substr(0,pos));
				val2 = stoi(inputCommand.substr(pos+1,inputCommand.size()-1));
				std::cout<<"val1: "<<val1<<"val2 = "<<val2;
				newNode = bst.initializeNode(val1,val2);
				bst.insert(newNode);
				mh.insertIntoMinHeap(newNode);

			}
		
		}

		counter++;
		if(counter == 4){
			flag = false;
		}
	}

    /*

   for(int i = 0; i< 5; ++i){
	  newNode =  bst.initializeNode(i,i+10,i+15);
	  bst.insert(newNode);
	  mh.insertIntoMinHeap(newNode);
   }
   bst.printInorder(bst.getRoot());
//    mh.printMinHeap(); */
	return 0;
}
