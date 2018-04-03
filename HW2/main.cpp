#include<iostream>
#include<fstream>
#include<vector>
#include <iomanip>
#include<map>
using namespace std;
vector<string> split(string str,char c = '\t'){
	int start = 0;
	vector<string> vec;
	
	for(int i = 0 ; i < str.size() ; i++){
		if (str[i]==c)
		{
			vec.push_back(str.substr(start,i-start));
			start = i + 1;
		}
	}
	vec.push_back(str.substr(start,str.size()-start));
	return vec;

}
class CryptoCurrency{
public:
	string date,currency,exchange; 
	float low,high;
	long long int cap;
	CryptoCurrency(){}
	CryptoCurrency(string str){
		vector<string> vec = split(str);
		date = vec[0];
		currency = vec[1];
		exchange = vec[2];
		low = stof(vec[3]);
		high = stof(vec[4]);
		cap = stoll(vec[5]);
		//cout << vec.size() << endl;
	}
};
int main(int argc,char** argv){
	if (argc < 2){
		cout << "Please specifiy your raw data" << endl;
		return -1;
	}
	else{
		ifstream ifs;
		ifs.open(argv[1],ifstream::in);
		string str;
		map<string,map<string,map<string,CryptoCurrency> > > ccs;
		map<string,map<string,long long int> > ccc;
		//vector<CryptoCurrency> ccs;
		while( getline(ifs,str)  ){
			CryptoCurrency c(str);
			ccs[c.date][c.currency][c.exchange]=c;
			ccc[c.date][c.exchange]+=c.cap;
		}
		string cmd;
		while(getline(cin,cmd)){
			if(cmd=="end")
				break;
			vector<string> vec = split(cmd);
			if(vec[0] == "query"){
				
				CryptoCurrency& c = ccs[vec[1]][vec[2]][vec[3]];
				if(c.low == 0 && c.high == 0){
					cout << "none" << endl;
				}else{
					cout << fixed << setprecision(4) << c.low << " " << c.high << " " << c.cap << endl;
				}
			}else if(vec[0] == "price"){
				double price = 0;
				bool max = vec[1] == "max";
				string date = vec[2];
				string currency = vec[3];
				for(auto iter = ccs[date][currency].begin() ; iter != ccs[date][currency].end() ; iter++){
					CryptoCurrency& c = (*iter).second;
					if(iter == ccs[date][currency].begin()){
						price = max ? c.high : c.low;
					}
					if(max){
						price = (price > c.high) ? price : c.high;
					}else{
						price = (price < c.low) ? price : c.low;
					}
					
				}
				if (price == 0){
					cout << "none"  << endl;
				}else{
					cout << fixed << setprecision(4) << price << endl;
				}
			}else if(vec[0] == "cap"){
				long long int cap = ccc[vec[1]][vec[2]];
				if (cap == 0){
					cout << "none"  << endl;
				}else{
					cout << cap  << endl;
				
				}
			}
		}
	}
}
