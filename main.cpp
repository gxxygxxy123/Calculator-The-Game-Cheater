#include <iostream>
#include <vector>
#include <cstring>
#include <cmath> 
#include <cstdlib>
#include <algorithm>
#include <sstream>
std::vector<std::string> button;
std::vector<std::string> ans;
bool findit = false;
int to_int(std::string);
int option(int, std::string, bool&);
void DFS(int, int, int);

int main(void){
	/* settings YOU SHOULD SET UP below */
	int init = 8; // THE START NUMBER
	int goal = 30;  // GOAL
	int moves = 5;   // MOVES
	// Enter the button here
	button.push_back("2");
	button.push_back("-4");
	button.push_back("2=>3");
	button.push_back("Reverse");

	/* settings YOU SHOULD SET UP above */
	
	DFS(init,goal,moves);
	if(!findit){
		std::cout << "Not answer found!" << std::endl;
	}
	return 0;
}

int to_int(std::string x){
	int ret = 0;
	if(x[0] == '+'){
		for(std::string::iterator it=x.begin()+1;it != x.end();it++){
			ret = ret*10;
			ret = ret+ (*it - '0');
		}
	}
	else if(x[0] == '-'){
		for(std::string::iterator it=x.begin()+1;it != x.end();it++){
			ret = ret*10;
			ret = ret+ (*it - '0');
		}
		ret = -ret;
	}
	else{
		for(std::string::iterator it=x.begin();it != x.end();it++){
			ret = ret*10;
			ret = ret+ (*it - '0');
		}
	}
	return ret;
}
int option(int x, std::string op, bool &err){
	if(op == "Reverse"){ // reverse integer
		int ret = 0;
		while(x != 0){
			ret = ret*10;
			ret = ret + x%10;
			x = x / 10;
		}
		return ret;
	}
	else if(op == "<<"){
		return x/10;
	}
	else if(op == "+/-"){ // sign change
		return -x;
	}
	else if(op.find("=>") != std::string::npos){
		int found = op.find("=>");
		std::string a = (op.substr(0,found)), b = (op.substr(found+2)); // a=>b
		std::stringstream ss;
		ss << x;
		std::string str = ss.str();
		size_t start_pos = 0;
		while((start_pos = str.find(a, start_pos)) != std::string::npos) {
		        str.replace(start_pos, a.length(), b);
		        start_pos += b.length();
		}
		return to_int(str);
	}
	else if(op.substr(0,2) == "x^"){ // power
		return pow(x, to_int(op.substr(2)));
	}
	else if(op[0] >= '0' && op[0] <= '9'){ // Purple Button (append)
		return x*pow(10,op.length())+to_int(op);
	}
	else if(op[0] == '+' || op[0] == '-'){ // add or minus
		return x+to_int(op);
	}
	else if(op[0] == 'x'){ // multiply
		return x*to_int(op.substr(1));
	}
	else if(op[0] == '/'){ // divide
		int tmp = to_int(op.substr(1));
		if(x % tmp == 0){
			return x/tmp;
		}
		else{
			err = true;
			return 0;
		}
	}
	else{
		std::cout << "Unknown button!" << std::endl;
	}
}
void DFS(int x, int goal, int move){
	if(findit){ // have found the answer
		return;
	}
	if(move == 0){
		if(x == goal){ // find the answer
			std::cout << "WIN!!" << std::endl;
			for(size_t i = 0;i < ans.size();i++){
				std::cout << ans[i] << std::endl;
			}
			findit = true;
		}
		return;
	}
	for(size_t i = 0;i < button.size();i++){
		bool err = false;
		int tmp = option(x, button[i], err);
		if(err){//Error operation
			continue;
		}
		ans.push_back(button[i]);
		DFS(tmp, goal,move-1);
		ans.pop_back();
	}
}

