#include<iostream>
using namespace std;
#include<cstring>
#include"tools.h"
#include"fileinfo.h"
#include"address.h"
#include<fstream> 
vector<string> split_str(string src,string chr){
//	�ַ���תΪ�ַ�ָ�룬������const�����޷�������������Ҫstrcpy���� 
	char *psrc = new char[src.size()+1];
	strcpy(psrc,src.c_str());
	char const *pchr = chr.c_str();
	char *pch = strtok(psrc,pchr);
	vector<string> vet;
	while(pch!=NULL){
//		�ָ������ַ�ָ��תΪ�ַ��� 
		string tmp = pch;
		vet.push_back(tmp);
//		��һ������ΪNULL����ʾ�����������ϴε����������thisָ���λ�ÿ�ʼ�ֽ�
		pch = strtok(NULL,pchr);
	}
	delete psrc;
	return vet;
}
int main(){
	fstream file;
	file.open("xxx",ios_base::out);
	if(!file.is_open()){
		cout<<"�ļ�������"<<endl;
	}else{
		cout<<"yes"<<endl;
	}

	
	file.close();
//	cout<<Tools::fill_char("��ѯ���")<<endl<<endl;
//	Tools::print_border();
//	Tools::format_output("���� ���� ΢�� ͨѶ��ַ ���� �ֻ���"); 
//	Tools::format_output("3 weixin yang fuzhou 22314213@qq.com 19923454452");
//	cout<<Tools::fill_char("��ϵ����Ϣ")<<endl;
//	Tools::print_border();
//	Tools::format_output("���� ���� ΢�� ͨѶ��ַ ���� �ֻ���");
	
//	Tools::format_output("3 w yang fuzhoufuzhou q.com 19923454452");
//	Tools::format_output("3 weixin yang �й����� 22314213@qq.com 19923454452");
}
