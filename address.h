#ifndef ADDRESS_HEAD
#define ADDRESS_HEAD
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
#include"tools.h"
//ͨѶ¼�ֶ� 
struct Address{
	unsigned num;
	string weichat;
	string name;
	string addr;
	string email;
	string phone;
	string to_string(){
		string res;
		res += Tools::num_to_string(num)+" ";
		res += Tools::replace_str(name," ","")+" ";
		res += Tools::replace_str(weichat," ","")+" ";
		res += Tools::replace_str(addr," ","")+" ";
		res += Tools::replace_str(email," ","")+" ";
		res += Tools::replace_str(phone," ","")+" ";
		return res;
	}
	

	 
	friend ostream &operator<<(ostream &os,Address addrs){
		os<<addrs.num<<" "<<addrs.weichat<<" "<<addrs.name<<" "<<addrs.addr<<" "<<addrs.email<<" "<<addrs.phone<<endl;
		return os;
	}
};

#endif
