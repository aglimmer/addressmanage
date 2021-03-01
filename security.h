#ifndef SERCUITY_HEAD
#define SERCUITY_HEAD
#include<windows.h>
#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
using namespace std;
//��ȫ������� 
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
//�ַ������ܽ��ܣ���һ������Ϊ���ܵ��ַ������ڶ�������Ϊ��Կ 
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

