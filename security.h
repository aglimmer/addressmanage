#ifndef SERCUITY_HEAD
#define SERCUITY_HEAD
#include<windows.h>
#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
using namespace std;
//安全加密相关 
class Security {
	public:
		static bool is_phone(string str);
		static bool is_digit(string str);
		static string to_ciphertext(string password,string key="0123456");
};
bool Security::is_digit(string str){
	for(int i=0;i<str.length();i++){
		int ind = int(str[i]);
		if(ind<48 || ind>57){
			return false;
		}
	}
	return true;	
}
bool Security::is_phone(string str) {
	if(str[0]!='1'||str.size()!=11) {
		return 0;
	} else {
		return 1;
	}
}
//字符串加密解密，第一个参数为加密的字符串，第二个参数为密钥 
string Security::to_ciphertext(string password,string key){
	int pw_len = password.length();
	int key_len = key.length();
	string res;
	for(int i=0;i<pw_len;i++){
		int dpos = key[i%key_len];
		dpos = dpos<0?-dpos:dpos;
		char cc = password[i]^(dpos%31);
		res.append(1,cc);
	}
	return res;
}
#endif

