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
		Putchar("*",33);cout<< "��ӭʹ��ͨѶ¼����ϵͳ!";Putchar("*",33); cout<<endl;
		cout<<endl<<endl;
		static int i=0;
		string passward,id;
		ifstream f(Security::file_name.c_str());
		if(!f)
		{
			f.close();
			Putchar(" ",30);cout<<"�������״�ʹ�ã����㴴��һ���˻�";cout<<endl; 
			cout<<endl;
			Putchar(" ",30);cout<<"�˺ţ�";cin>>id; 
			Putchar(" ",30);cout<<"���룺";cin>>passward;
			Security::Encrypt(id,passward);
			cout<<endl;
			Putchar(" ",30);cout<<"�����˺ųɹ����´ο�ֱ�ӵ�¼";cout<<endl;
			Putchar("_",90);cout<<endl;
			Menu();		
		}
		else
		{
			f.close();
			Putchar(" ",30); cout<<"�������˺�����"<<endl;
			Putchar(" ",30);cout<<"�˺ţ�";cin>>id; 
			Putchar(" ",30);cout<<"���룺";cin>>passward;
			int n=Security::Decode(id,passward);
			if(n==0)
			{
				i++;
				if(i==3)
				{ 
					Putchar(" ",30);cout<<"��������������Ѵ�3�Σ�����������"<<endl;
					DeleteFile("password.txt");
					Enter();
				}
			Putchar(" ",30);cout<<"��������˺Ż�������������������!" <<endl;
			Enter();
			}
			else
			Menu();
		}
	}

