#include<iostream>
using namespace std;
#include<cstring>
#include"tools.h"
#include"fileinfo.h"
#include"address.h"
#include<fstream> 
vector<string> split_str(string src,string chr){
//	字符串转为字符指针，由于是const类型无法操作，所以需要strcpy函数 
	char *psrc = new char[src.size()+1];
	strcpy(psrc,src.c_str());
	char const *pchr = chr.c_str();
	char *pch = strtok(psrc,pchr);
	vector<string> vet;
	while(pch!=NULL){
//		分隔所得字符指针转为字符串 
		string tmp = pch;
		vet.push_back(tmp);
//		第一个参数为NULL，表示函数继续以上次调用所保存的this指针的位置开始分解
		pch = strtok(NULL,pchr);
	}
	delete psrc;
	return vet;
}
int main(){
	fstream file;
	file.open("xxx",ios_base::out);
	if(!file.is_open()){
		cout<<"文件不存在"<<endl;
	}else{
		cout<<"yes"<<endl;
	}

	
	file.close();
//	cout<<Tools::fill_char("查询结果")<<endl<<endl;
//	Tools::print_border();
//	Tools::format_output("分组 姓名 微信 通讯地址 邮箱 手机号"); 
//	Tools::format_output("3 weixin yang fuzhou 22314213@qq.com 19923454452");
//	cout<<Tools::fill_char("联系人信息")<<endl;
//	Tools::print_border();
//	Tools::format_output("分组 姓名 微信 通讯地址 邮箱 手机号");
	
//	Tools::format_output("3 w yang fuzhoufuzhou q.com 19923454452");
//	Tools::format_output("3 weixin yang 中国福建 22314213@qq.com 19923454452");
}
