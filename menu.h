#include<iostream>
#include<cstring>
#include<string>
#include<fstream>
#include"security.h"
using namespace std;
class Menu {
  public:
  	static void Enter();
 
};
void Menu::Enter()
	{
		Putchar("*",33);cout<< "欢迎使用通讯录管理系统!";Putchar("*",33); cout<<endl;
		cout<<endl<<endl;
		static int i=0;
		string passward,id;
		ifstream f(Security::file_name.c_str());
		if(!f)
		{
			f.close();
			Putchar(" ",30);cout<<"这是你首次使用，请你创建一个账户";cout<<endl; 
			cout<<endl;
			Putchar(" ",30);cout<<"账号：";cin>>id; 
			Putchar(" ",30);cout<<"密码：";cin>>passward;
			Security::Encrypt(id,passward);
			cout<<endl;
			Putchar(" ",30);cout<<"创建账号成功，下次可直接登录";cout<<endl;
			Putchar("_",90);cout<<endl;
			Menu();		
		}
		else
		{
			f.close();
			Putchar(" ",30); cout<<"请输入账号密码"<<endl;
			Putchar(" ",30);cout<<"账号：";cin>>id; 
			Putchar(" ",30);cout<<"密码：";cin>>passward;
			int n=Security::Decode(id,passward);
			if(n==0)
			{
				i++;
				if(i==3)
				{ 
					Putchar(" ",30);cout<<"你输入密码错误已达3次，请重置密码"<<endl;
					DeleteFile("password.txt");
					Enter();
				}
			Putchar(" ",30);cout<<"你输入的账号或密码有误，请重新输入!" <<endl;
			Enter();
			}
			else
			Menu();
		}
	}

