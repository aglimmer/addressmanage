#ifndef INFO_HEAD
#define INFO_HEAD
#include<string>
using namespace std;
//数据文件信息 
class FileInfo{
	public:
//		联系人数据文件位置 
		static string get_linkman_path();
//		密码文件位置 
		static string get_password_path();
//		临时文件位置 
		static string get_temp_path();
		static bool del_file(string str);
	private:
		static string data_folder;
		static string linkman_file;	
		static string password_file;
		static string temp_file;
};
string FileInfo::linkman_file="linkman.dat";
string FileInfo::data_folder="data";
string FileInfo::temp_file="temp.dat";
string FileInfo::password_file="user.dat";
string FileInfo::get_linkman_path(){
	return data_folder+"/"+linkman_file;
}
string FileInfo::get_password_path(){
	return data_folder+"/"+password_file;
}
string FileInfo::get_temp_path(){
	return data_folder+"/"+temp_file;
}
bool FileInfo::del_file(string str){
	int res = remove(str.c_str());
	return res==0?true:false;
}
#endif
