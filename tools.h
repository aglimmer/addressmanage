#ifndef TOOL_HEAD
#define TOOL_HEAD
#include<sstream>
#include<string>
#include<vector>
using namespace std;
//工具类，完成字符串填充查找替换等功能 
class Tools {
	public:
		static void format_output(string line);
		static void print_border();
		static vector<string> split_string(string src,string delimstr);
		static string trim_blank(string ss);
		static string fill_char(string str,char ch='+');
		static string replace_str(string src,string curstr,string objstr);
		static string num_to_string(int num);
};

void Tools::print_border(){
	const int str_width[]= {5,15,15,20,20,15};
	int len = sizeof(str_width)/sizeof(int);
	string blank;
	for(int i=0;i<len;i++){
		if(i==0){
			blank += " +-";
		}else {
			blank += "-+-";
		}
		blank.append(str_width[i],'-');
	}
	blank +="+";
	cout<<blank<<endl;
	
}
void Tools::format_output(string content) {
	
//	固定一行6列，及其相应的宽度 
	const int str_width[]= {5,15,15,20,20,15};
	const int len = sizeof(str_width)/sizeof(int);
//	vecotor大小固定6，与之对应 
	vector<string> lab =  split_string(content," ");
	if(lab.size()<len){
		return;
	}
	string temp;
	string blank;
//	每一列 
	for(int i=0; i<len; i++) {
		temp = " | "+lab[i];
		int csize = lab[i].size();
		if(csize<str_width[i]) {
			int rem = str_width[i]-csize;
			temp.append(rem,' ');
		} else if(csize>str_width[i]) {
			temp = lab[i].substr(0,str_width[i]);
		}
		if(i==0){
			blank += " +-";
		}else{
			blank += "-+-";
		}
		blank.append(str_width[i],'-');
		if(i==len-1){
			temp +="|";
			blank +="+";	
		}
		cout<<temp; 
	}
	cout<<endl; 
	cout<<blank<<endl;
}

//字符串分隔，第二个参数指定分隔的字符串，是一个整体而不是字符集
vector<string> Tools::split_string(string src,string delimstr) {
	int len = delimstr.length();
	int pos1 = 0;
	int pos2 = 0;
	string temp;
	vector<string> res;
	while((pos2=src.find(delimstr,pos1))!=-1) {
		//不等于objstr的部分，截取出来拼接
		res.push_back(src.substr(pos1,pos2-pos1));
		pos1 = pos2+len;
	}
//	剩余的部分
	res.push_back(src.substr(pos1));
	return res;

}
string Tools::trim_blank(string ss) {
	string res;
	for(int i=0; i<ss.length(); i++) {
		if(ss[i]!=' ') {
			res+=ss[i];
		}
	}
	return res;
}
string Tools::fill_char(string str,char ch) {
	const int width = 108;
	int side_width=(width-str.length())/2;
	string res=" ";
	res.append(side_width,ch);
	res += str;
	res.append(side_width,ch);
	return res;
}
//在目标串scr中查找子串curstr,找到则把子串curstr全部替换为objstr
string Tools::replace_str(string src,string curstr,string objstr) {

	int curlen = curstr.length();
	int pos1 = 0;
	int pos2 = 0;
	string temp;
	while((pos2=src.find(curstr,pos1))!=-1) {
		//不等于objstr的部分，截取出来拼接
		temp += src.substr(pos1,pos2-pos1);
		temp += objstr;
		pos1 = pos2+curlen;
	}
//	剩余的部分
	temp += src.substr(pos1);
	return temp;

}
string Tools::num_to_string(int num) {
	ostringstream oss;
	oss<<num;
	return oss.str();
}
#endif
