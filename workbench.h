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
//		初始化，把文件数据读取到内存，即放入到list中 
		void init_record();
//		浏览全部 
		void browse_record();
//		添加 
		void add_linkman();
//		查找 
		void find_linkman();
//		修改 
		void edit_record();
//		删除 
		void del_linkman();
//		统计 
		void cal_record();
//		登录功能 
		void login();
//		菜单 
		void addr_menu();
//		内存中信息写入到文件 
		void save_info();

	private:
//		通讯录中信息缓存 
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
//	cout<<" 数据已加载！"<<endl;
}
void Workbench::save_info() {
	fstream file;
	file.open(FileInfo::get_linkman_path().c_str(),ios_base::out);
	list<string>::iterator it = data.begin();
	while(it!=data.end()) {
		file<<*it++<<endl;
	}
	file.close();
//	更新
}

void Workbench::browse_record() {
	cout<<Tools::fill_char("查看通讯录",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("联系人为空！")<<endl;
		return;
	}

	cout<<Tools::fill_char("联系人信息")<<endl;
	Tools::print_border();
	Tools::format_output("分组 姓名 微信 通讯地址 邮箱 手机号");

	list<string>::iterator it;
	for(it=data.begin(); it!=data.end(); it++) {
		string msg = *it;
		Tools::format_output(msg);
	}
}

void Workbench::add_linkman() {
	Address addrs;
	cout<<Tools::fill_char("添加联系人",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("联系人为空,可选择创建")<<endl;
	}
	cout<<"分组类型:0.默认 1.同事 2.亲戚 3.朋友 4.家人 5.同学 6.自定义"<<endl;
	cout<<"请选择：";
	cin>>addrs.num;
	cout<<"微信号:";
	cin>>addrs.weichat;
	cout<<"姓名:";
	cin>>addrs.name;
	cout<<"通讯地址:";
	cin>>addrs.addr;
	cout<<"邮箱地址:";
	cin>>addrs.email;
	cout<<"手机号:";
	cin>>addrs.phone;
	int b=Security::is_phone(addrs.phone);
	while(b==0) {
		cout<<endl;
		cout<<Tools::fill_char("号码有误，请重新输入")<<endl;
		cout<<"手机号:";
		cin>>addrs.phone;
		b=Security::is_phone(addrs.phone);
	}
	data.push_back(addrs.to_string());
	save_info();
	cout<<Tools::fill_char("添加成功，信息如下")<<endl;
	Tools::format_output("分组 姓名 微信 通讯地址 邮箱 手机号");
	Tools::print_border();
	Tools::format_output(addrs.to_string());
	int select;
	cout<<Tools::fill_char("请选择是否继续添加联系人信息:1.继续；2.返回")<<endl;
	cout<<"请选择:";
	cin>>select;
	if(select==1)
		add_linkman();
	else if(select==2)
		return;
}
//#include "find.cpp"
void Workbench::find_linkman() {
	cout<<Tools::fill_char("查找联系人",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("联系人为空")<<endl;
		return;
	}
	string str;

	bool b=false;
	cout<<"请输入要查找的信息:";
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
		cout<<Tools::fill_char("信息没找到！")<<endl;
	}
	int select;
	cout<<Tools::fill_char("是否继续查找:1.继续 2.返回")<<endl;
	cout<<"请选择：";
	cin>>select;
	if(select==1)
		find_linkman();
	else
		return;
}
void Workbench::edit_record() {
	cout<<Tools::fill_char("修改联系人",'*')<<endl;

	if(data.empty()) {
		cout<<Tools::fill_char("联系人为空！")<<endl;
		return;
	}
	string obstr;
	cout<<"请输入要修改的信息：";
	cin>>obstr;
	cout<<endl;

	bool b=false;

//	查找信息
	int len=obstr.length();
	list<string>::iterator it;
	for(it=data.begin(); it!=data.end(); it++) {
		string str = *it;
		int index=str.find(obstr);
//		找到
		if(index!=-1) {
			string sub=str.substr(index,len);
			cout<<Tools::fill_char("联系人信息")<<endl;
			Tools::format_output(str);
			cout<<"是否确定替换:"<<sub<<endl;
			int select;
			cout<<"选择：1.确定 2.取消"<<endl;
			cin>>select;
			cout<<endl;
			if(select==1) {
				b=true;
				string re;
				cout<<"请输入用来替换的信息：";
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
		cout<<Tools::fill_char("已成功保存！")<<endl;
	} else {
		cout<<Tools::fill_char("信息未找到！")<<endl;
	}
	int again;
	cout<<Tools::fill_char("是否继续当前操作:1.继续 2.返回")<<endl;
	cout<<"请选择：";
	cin>>again;
	cout<<endl;
	if(again==1) {
		edit_record();
	}

}
void Workbench::del_linkman() {
	cout<<Tools::fill_char("删除信息",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("联系人为空！")<<endl;
		return;
	}
	string obstr;
	cout<<"请输入要删除信息：";
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
//			要删除的信息显示出来
			Tools::format_output(str);
			arr[k]=1;
		}
//		行数
		k++;
	}
	if(b) {
		cout<<Tools::fill_char("是否删除以上信息：1.删除 2.重选 3.退出",'*')<<endl;
		int select;
		cout<<"请选择：";
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
			cout<<Tools::fill_char("联系人已删除!")<<endl;
			cout<<Tools::fill_char("选择：1.退出 2.继续")<<endl;
			int again;
			cout<<"请选择：";
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
		cout<<Tools::fill_char("你要删除的的信息没找到，请选择：1.重找 2.退出")<<endl;
		unsigned again;
		cin>>again;
		if(again==1)
			del_linkman();
		else
			return;
	}
}
void Workbench::cal_record() {
	cout<<Tools::fill_char("统计信息",'*')<<endl;
	if(data.empty()) {
		cout<<Tools::fill_char("联系人信息为空")<<endl;
		return;
	}

	string calc;
	const int N = 7;
	string gstr[N]= {"默认：","同事：","亲人：","朋友：","家人：","同学：","其他："};
	map<string,int> res;
	list<string>::iterator it;
	for(it=data.begin(); it!=data.end(); it++) {
		calc = *it;
		//找到的字符为对应分组
		if(calc!="") {
//		如果找到，第一个字符就是，则pos=0
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
	cout<<"按回车键返回..."<<endl;
	//使用 get 函数简单地暂停屏幕直到按回车键，并且不需要存储字符
	cin.get();
	return;
}
void Workbench::addr_menu() {
	init_record();
	while(true) {
		cout<<Tools::fill_char("微信通讯录管理系统",'&')<<endl<<endl;
		cout<<Tools::fill_char("主要功能",'*')<<endl<<endl;
		cout<<Tools::fill_char("1.查看",' ')<<endl;
		cout<<Tools::fill_char("2.添加",' ')<<endl;
		cout<<Tools::fill_char("3.搜索",' ')<<endl;
		cout<<Tools::fill_char("4.修改",' ')<<endl;
		cout<<Tools::fill_char("5.删除",' ')<<endl;
		cout<<Tools::fill_char("6.统计",' ')<<endl;
		cout<<Tools::fill_char("7.关闭",' ')<<endl;
		cout<<Tools::fill_char("+",'+')<<endl;
		cout<<"请选择操作:";
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
	cout<<Tools::fill_char("通讯录管理系统",'&')<<endl<<endl;
	static int cnt=0;
	string password,id;
	fstream file;
	file.open(FileInfo::get_password_path().c_str(),ios_base::in);
	string blank="";
	const int blank_len=50;
	blank.append(blank_len,' ');
	if(!file.is_open()) {
		file.open(FileInfo::get_password_path().c_str(),ios_base::out);
		cout<<"首次使用，请添加用户";
		cout<<endl;
		cout<<blank<<"账号：";
		cin>>id;
		cout<<blank<<"密码：";
		cin>>password;
		cout<<endl;
		password = Security::to_ciphertext(password);
//		写入
		file<<id<<endl<<password<<endl;
		cout<<Tools::fill_char("创建账号成功，下次可直接登录")<<endl;
		cout<<Tools::fill_char("-")<<endl;
		file.close();
	}

	cout<<Tools::fill_char("用户登录",'*')<<endl;
	cout<<blank<<"账号：";
	cin>>id;
	cout<<blank<<"密码：";
	cin>>password;
	string pw = Security::to_ciphertext(password);
	string fid,fpw;
	getline(file,fid);
	getline(file,fpw);

	if(fid!=id && fpw!=pw) {
		cout<<"账号或密码有误，请重新输入!" <<endl;
		login();
	} else {
		addr_menu();
	}

}
#endif
