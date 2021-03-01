#ifndef WORKBENCH_HEAD
#define WORKBENCH_HEAD

#include<sstream>
#include"security.h"
#include"tools.h"
#include"fileinfo.h"
#include"address.h"
#include<list>
#include<map>
class Workbench {
	public:
		Workbench() {};
//		��ʼ�������ļ����ݶ�ȡ���ڴ棬�����뵽list�� 
		void init_record();
//		���ȫ�� 
		void browse_record();
//		��� 
		void add_linkman();
//		���� 
		void find_linkman();
//		�޸� 
		void edit_record();
//		ɾ�� 
		void del_linkman();
//		ͳ�� 
		void cal_record();
//		��¼���� 
		void login();
//		�˵� 
		void addr_menu();
//		�ڴ�����Ϣд�뵽�ļ� 
		void save_info();

	private:
//		ͨѶ¼����Ϣ���� 
		list<string> data;
};
void Workbench::init_record() {
	fstream file;
	file.open(FileInfo::get_linkman_path().c_str(),ios_base::in);
	string msg;
	while(!file.eof()) {
		getline(file,msg);
		if(msg!="") {
			data.push_back(msg);
//			cout<<"warn:blank msg!"<<endl;
		}
	}
	file.close();
//	cout<<" �����Ѽ��أ�"<<endl;
}
void Workbench::save_info() {
	fstream file;
	file.open(FileInfo::get_linkman_path().c_str(),ios_base::out);
	list<string>::iterator it = data.begin();
	while(it!=data.end()) {
		file<<*it++<<endl;
	}
	file.close();
//	����
}

void Workbench::browse_record() {
	cout<<Tools::fill_char("�鿴ͨѶ¼",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("��ϵ��Ϊ�գ�")<<endl;
		return;
	}

	cout<<Tools::fill_char("��ϵ����Ϣ")<<endl;
	Tools::print_border();
	Tools::format_output("���� ���� ΢�� ͨѶ��ַ ���� �ֻ���");

	list<string>::iterator it;
	for(it=data.begin(); it!=data.end(); it++) {
		string msg = *it;
		Tools::format_output(msg);
	}
}

void Workbench::add_linkman() {
	Address addrs;
	cout<<Tools::fill_char("�����ϵ��",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("��ϵ��Ϊ��,��ѡ�񴴽�")<<endl;
	}
	cout<<"��������:0.Ĭ�� 1.ͬ�� 2.���� 3.���� 4.���� 5.ͬѧ 6.�Զ���"<<endl;
	cout<<"��ѡ��";
	cin>>addrs.num;
	cout<<"΢�ź�:";
	cin>>addrs.weichat;
	cout<<"����:";
	cin>>addrs.name;
	cout<<"ͨѶ��ַ:";
	cin>>addrs.addr;
	cout<<"�����ַ:";
	cin>>addrs.email;
	cout<<"�ֻ���:";
	cin>>addrs.phone;
	int b=Security::is_phone(addrs.phone);
	while(b==0) {
		cout<<endl;
		cout<<Tools::fill_char("������������������")<<endl;
		cout<<"�ֻ���:";
		cin>>addrs.phone;
		b=Security::is_phone(addrs.phone);
	}
	data.push_back(addrs.to_string());
	save_info();
	cout<<Tools::fill_char("��ӳɹ�����Ϣ����")<<endl;
	Tools::format_output("���� ���� ΢�� ͨѶ��ַ ���� �ֻ���");
	Tools::print_border();
	Tools::format_output(addrs.to_string());
	int select;
	cout<<Tools::fill_char("��ѡ���Ƿ���������ϵ����Ϣ:1.������2.����")<<endl;
	cout<<"��ѡ��:";
	cin>>select;
	if(select==1)
		add_linkman();
	else if(select==2)
		return;
}
//#include "find.cpp"
void Workbench::find_linkman() {
	cout<<Tools::fill_char("������ϵ��",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("��ϵ��Ϊ��")<<endl;
		return;
	}
	string str;

	bool b=false;
	cout<<"������Ҫ���ҵ���Ϣ:";
	cin>>str;
	list<string>::iterator it = data.begin();
	int start;
	while(it!=data.end()) {
		start = (*it).find(str);
		if(start>0) {
			b = true;
			Tools::format_output(*it);
		}
		++it;
	}
	if(!b) {
		cout<<Tools::fill_char("��Ϣû�ҵ���")<<endl;
	}
	int select;
	cout<<Tools::fill_char("�Ƿ��������:1.���� 2.����")<<endl;
	cout<<"��ѡ��";
	cin>>select;
	if(select==1)
		find_linkman();
	else
		return;
}
void Workbench::edit_record() {
	cout<<Tools::fill_char("�޸���ϵ��",'*')<<endl;

	if(data.empty()) {
		cout<<Tools::fill_char("��ϵ��Ϊ�գ�")<<endl;
		return;
	}
	string obstr;
	cout<<"������Ҫ�޸ĵ���Ϣ��";
	cin>>obstr;
	cout<<endl;

	bool b=false;

//	������Ϣ
	int len=obstr.length();
	list<string>::iterator it;
	for(it=data.begin(); it!=data.end(); it++) {
		string str = *it;
		int index=str.find(obstr);
//		�ҵ�
		if(index!=-1) {
			string sub=str.substr(index,len);
			cout<<Tools::fill_char("��ϵ����Ϣ")<<endl;
			Tools::format_output(str);
			cout<<"�Ƿ�ȷ���滻:"<<sub<<endl;
			int select;
			cout<<"ѡ��1.ȷ�� 2.ȡ��"<<endl;
			cin>>select;
			cout<<endl;
			if(select==1) {
				b=true;
				string re;
				cout<<"�����������滻����Ϣ��";
				cin>>re;
				str.replace(index,len,re);
				*it = str;
			} else {
				break;
			}
		}
	}
	if(b) {
		save_info();
		cout<<Tools::fill_char("�ѳɹ����棡")<<endl;
	} else {
		cout<<Tools::fill_char("��Ϣδ�ҵ���")<<endl;
	}
	int again;
	cout<<Tools::fill_char("�Ƿ������ǰ����:1.���� 2.����")<<endl;
	cout<<"��ѡ��";
	cin>>again;
	cout<<endl;
	if(again==1) {
		edit_record();
	}

}
void Workbench::del_linkman() {
	cout<<Tools::fill_char("ɾ����Ϣ",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("��ϵ��Ϊ�գ�")<<endl;
		return;
	}
	string obstr;
	cout<<"������Ҫɾ����Ϣ��";
	cin>>obstr;
	bool b=false;
	list<string>::iterator it;
	string str;
	int k=0,arr[500];
	for(it=data.begin(); it!=data.end(); it++) {
		str = *it;
		int index=str.find(obstr);
		if(index<0) {
			b=true;
			arr[k]=0;
		} else {
//			Ҫɾ������Ϣ��ʾ����
			Tools::format_output(str);
			arr[k]=1;
		}
//		����
		k++;
	}
	if(b) {
		cout<<Tools::fill_char("�Ƿ�ɾ��������Ϣ��1.ɾ�� 2.��ѡ 3.�˳�",'*')<<endl;
		int select;
		cout<<"��ѡ��";
		cin>>select;
		cout<<endl;
		if(select==1) {
			int cnt = 0;
			for(it=data.begin(); it!=data.end(); it++) {
				if(arr[cnt]==1) {
					it = data.erase(it);
					cnt++;
				}
				cnt++;
			}
			save_info();
			cout<<Tools::fill_char("��ϵ����ɾ��!")<<endl;
			cout<<Tools::fill_char("ѡ��1.�˳� 2.����")<<endl;
			int again;
			cout<<"��ѡ��";
			cin>>again;
			switch(again) {
				case 1:
					return;
					break;
				case 2:
					del_linkman();
					break;
			}
		} else if(select==2) {
			del_linkman();
		} else {
			return;
		}
	} else {
		cout<<Tools::fill_char("��Ҫɾ���ĵ���Ϣû�ҵ�����ѡ��1.���� 2.�˳�")<<endl;
		unsigned again;
		cin>>again;
		if(again==1)
			del_linkman();
		else
			return;
	}
}
void Workbench::cal_record() {
	cout<<Tools::fill_char("ͳ����Ϣ",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("��ϵ����ϢΪ��")<<endl;
		return;
	}

	string calc;
	const int N = 7;
	string gstr[N]= {"Ĭ�ϣ�","ͬ�£�","���ˣ�","���ѣ�","���ˣ�","ͬѧ��","������"};
	map<string,int> res;
	list<string>::iterator it;
	for(it=data.begin(); it!=data.end(); it++) {
		calc = *it;
		//�ҵ����ַ�Ϊ��Ӧ����
		if(calc!="") {
//		����ҵ�����һ���ַ����ǣ���pos=0
			int pos = calc.find_first_of(" ");
			if(pos!=-1) {
				string sub = calc.substr(0,pos);
				res[sub] += 1;
			}
		}
	}
	for(int i=0; i<N; i++) {
		string rs = gstr[i]+Tools::num_to_string(i);
		cout<<Tools::fill_char(rs,' ')<<endl;
	}
	cin.get();
	cout<<"���س�������..."<<endl;
	//ʹ�� get �����򵥵���ͣ��Ļֱ�����س��������Ҳ���Ҫ�洢�ַ�
	cin.get();
	return;
}
void Workbench::addr_menu() {
	init_record();
	while(true) {
		cout<<Tools::fill_char("΢��ͨѶ¼����ϵͳ",'&')<<endl<<endl;
		cout<<Tools::fill_char("��Ҫ����",'*')<<endl<<endl;
		cout<<Tools::fill_char("1.�鿴",' ')<<endl;
		cout<<Tools::fill_char("2.���",' ')<<endl;
		cout<<Tools::fill_char("3.����",' ')<<endl;
		cout<<Tools::fill_char("4.�޸�",' ')<<endl;
		cout<<Tools::fill_char("5.ɾ��",' ')<<endl;
		cout<<Tools::fill_char("6.ͳ��",' ')<<endl;
		cout<<Tools::fill_char("7.�ر�",' ')<<endl;
		cout<<Tools::fill_char("+",'+')<<endl;
		cout<<"��ѡ�����:";
		int n;
		cin>>n;
		switch(n) {
			case 1:
				browse_record();
				break;
			case 2:
				add_linkman();
				break;
			case 3:
				find_linkman();
				break;
			case 4:
				edit_record();
				break;
			case 5:
				del_linkman();
				break;
			case 6:
				cal_record();
				break;
			case 7:
				break;
		}
		if(n==7) {
			break;
		}
	}

}
void Workbench::login() {
	cout<<Tools::fill_char("ͨѶ¼����ϵͳ",'&')<<endl<<endl;
	static int cnt=0;
	string password,id;
	fstream file;
	file.open(FileInfo::get_password_path().c_str(),ios_base::in);
	string blank="";
	const int blank_len=50;
	blank.append(blank_len,' ');
	if(!file.is_open()) {
		file.open(FileInfo::get_password_path().c_str(),ios_base::out);
		cout<<"�״�ʹ�ã�������û�";
		cout<<endl;
		cout<<blank<<"�˺ţ�";
		cin>>id;
		cout<<blank<<"���룺";
		cin>>password;
		cout<<endl;
		password = Security::to_ciphertext(password);
//		д��
		file<<id<<endl<<password<<endl;
		cout<<Tools::fill_char("�����˺ųɹ����´ο�ֱ�ӵ�¼")<<endl;
		cout<<Tools::fill_char("-")<<endl;
		file.close();
	}

	cout<<Tools::fill_char("�û���¼",'*')<<endl;
	cout<<blank<<"�˺ţ�";
	cin>>id;
	cout<<blank<<"���룺";
	cin>>password;
	string pw = Security::to_ciphertext(password);
	string fid,fpw;
	getline(file,fid);
	getline(file,fpw);

	if(fid!=id && fpw!=pw) {
		cout<<"�˺Ż�������������������!" <<endl;
		login();
	} else {
		addr_menu();
	}

}
#endif
