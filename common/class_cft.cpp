/* 2354180 ���Ϻ� �ƿ� */ 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
/* ����Լ���Ҫ��ͷ�ļ���ע������ */
#include "../include/class_cft.h"
#include<string>
#include<fstream>
#include<sstream>
#include<climits>
using namespace std;

/* ���������Զ��庯����ʵ�֣��Ѹ��������ݲ�ȫ�� */
static bool checkip(const char* ip)
{

	int num = 0;      // ��ǰ�ε�����
	int dotCount = 0; // ��ĸ���
	int len = strlen(ip);


	for (int i = 0; i < len; i++) {
		// ��鵱ǰ�ַ��Ƿ�������
		if (ip[i] >= '0' && ip[i] <= '9') {
			num = num * 10 + (ip[i] - '0'); // �ۼӵ�ǰ�ε�����

			// ��������Ƿ񳬳���Χ
			if (num > 255) {

				return false;
			}
		}
		// ����Ƿ�������
		else if (ip[i] == '.') {
			dotCount++;

			// ��������������3����IP��ַ���Ϸ�
			if (dotCount > 3) {

				return false;
			}

			// �����û�����֣����ǰ�����ֲ��Ϸ�
			if (i == 0 || ip[i - 1] < '0' || ip[i - 1]>'9') {

				return false;
			}

			num = 0; // ����num����ʼ��һ�ε����ֽ���
		}
		// ������������ַǵ��ַ�
		else {

			return false;
		}
	}

	// ������һ���Ƿ�Ϊ��
	if (ip[len - 1] == '.') {

		return false;
	}

	// ����ĸ����Ƿ�������3������ζ����4�Σ�
	if (dotCount != 3) {

		return false;
	}
	return true;

}
static unsigned int strtout(string value)
{
	unsigned int val;
	istringstream ss(value);

	int num[4] = { 0 };

	char dot;  // �������� `.`

	// ʹ�� >> ��������ȡ���ֲ����� `.` ����
	ss >> num[0] >> dot >> num[1] >> dot >> num[2] >> dot >> num[3];
	val = (num[0] << 24) | (num[1] << 16) | (num[2] << 8) | num[3];
	return val;
}
static char* trantolow(const char* const name)
{
	char* new_name = new char[strlen(name) + 1];
	strcpy(new_name, name);
	for (int i = 0; i < (int)strlen(new_name); i++) {
		if (new_name[i] >= 'A' && new_name[i] <= 'Z') {
			new_name[i] = new_name[i] + 32;
		}
	}
	return new_name;
}

static int comp_sen(config_file_tools& mcfg, const char* const name)
{
	
		int i = 0;
		while (i < mcfg.group_num) {
			if (strcmp(name, mcfg.LIST[i].group_name.c_str()) == 0) {
				break;
			}
			i++;
		}
	
	
	return i;

}
static int comp_insen(config_file_tools& mcfg, const char* const name)
{

	char* new_name = trantolow(name);
	
	int i = 0;
	while (i < mcfg.group_num) {
		char* new_gname = trantolow(mcfg.LIST[i].group_name.c_str());
		if (strcmp(new_name, new_gname) == 0) {
			delete[] new_gname;
			break;
		}
		delete[] new_gname;
		i++;
	}
	delete[] new_name;
	
	return i;
		
}


static string vanish_space(string line)
{
	string new_line;
	int start = 0;
	int end = line.size() - 1;

	while (start < (int)line.size() &&(line[start] == ' '|| line[start] == '\t')) {
		start++;
	}
	while (end >= 0 && (line[end] == ' ' || line[end] == '\t')) {
		end--;
	}
	
	if (start > end) {
		new_line= "";
	}
	else {
		if (line.size() > 1 && line[end] == '\n' && line[end - 1] == '\r') {
			end = end - 2;
		}
		else if (line[end] == '\n') {
			end--;
		}

		new_line = line.substr(start, end - start + 1);
	}
	return new_line;
}

static void row_extractef(vector<string>& buffer,int row)
{
	for (int i = 0; i < row; i++) {
		if (buffer[i].empty()) {
			continue;
		}

		int index_1 = buffer[i].find(note1);
		int index_2 = buffer[i].find(note2);
		int index_3 = buffer[i].find(note3);
		if (index_1 == string::npos)
			index_1 = INT_MAX;
		if (index_2 == string::npos)
			index_2 = INT_MAX;
		if (index_3 == string::npos)
			index_3 = INT_MAX;

		// �ҳ���С����Ч����
		size_t index_min = min({ index_1, index_2, index_3 });
		if (index_min != INT_MAX&& index_min < buffer[i].size()) {
			buffer[i].erase(index_min);
		}

		buffer[i]=vanish_space(buffer[i]);

		

	}
}

static int normal_type(group& GROUP, vector<string>buffer,int index,int row, const enum BREAK_CTYPE _ctype)
{

	int i = index ;
	while (1) {
		if (i == row){
			break;//��һ�鿪ʼ���Ѿ�����β
		}
		if (buffer[i].size() > 1 && buffer[i][0] == '[' && buffer[i][buffer[i].size() - 1] == ']') {
			break;
		}
		if (buffer[i].empty()) {//�յ�ֱ������
			i++;
			continue;
		}
		//�ǿ�
		int src=0;
		GROUP.item_num++;
		item T;
		if (_ctype == BREAK_CTYPE::Equal&&(src=buffer[i].find_first_of('='))!=string::npos|| _ctype == BREAK_CTYPE::Space && (src = buffer[i].find_first_of(' ')) != string::npos) {
			
			T.item_name = vanish_space(buffer[i].substr(0, src-1+1));
			T.item_val= vanish_space(buffer[i].substr(src+1, buffer[i].size()-1-src));
			T.raw = buffer[i];
			GROUP.ITEM.push_back(T);

		}
		else {//�޷ָ���
			T.raw = buffer[i];
			GROUP.ITEM.push_back(T);
		}
		i++;
		

	}

	return i;

}

static void row_extractcon(config_file_tools &mcfg,vector<string>buffer, int row, const enum BREAK_CTYPE _ctype)//���ڽ�����ȫ����Ч����
{
	if (buffer.empty()) {
		return;
	}
	int i = 0;
	while (i <(int) buffer.size()) { // ��� i �Ƿ�С�� buffer.size()
		if (!buffer[i].empty()) {
			break;
		}
		i++;
	}
	if (i >= (int)buffer.size()) {
		return; 
	}

	int start = 0;
	int end = buffer[i].size() - 1;//�����±꣬����Ҫ-1
	if (buffer[i].size() > 1 && buffer[i][start] == '[' && buffer[i][end] == ']') {//����������
		mcfg.ftype = TYPE_NORMAL;
		while (i < (int)buffer.size()) {
			group GROUP;
			GROUP.group_name = buffer[i];//Ҫ��Ҫ�����ڲ���ǰ��ո�
			i=normal_type(GROUP, buffer, i+1,row,_ctype);
			mcfg.LIST.push_back(GROUP);
			mcfg.group_num++;
			if (i == row) {
				break;
			}
		}
	}
	else {//�򵥻��߻��
		//�ȴ����һ��
		group GROUP;
		GROUP.group_name = "";
		i = normal_type(GROUP, buffer, i, row, _ctype);
		mcfg.LIST.push_back(GROUP);
		mcfg.group_num++;
		//�������
		if (i == row) {
			mcfg.ftype = TYPE_SIMPLE;
			
		}
		else {
			mcfg.ftype = TYPE_MIX;
			while (i < (int)buffer.size()){
				group GROUP;
				GROUP.group_name = buffer[i];//Ҫ��Ҫ�����ڲ���ǰ��ո�
				i = normal_type(GROUP, buffer, i + 1, row, _ctype);
				mcfg.LIST.push_back(GROUP);
				mcfg.group_num++;
				if (i == row) {
					break;
				}
			}
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::config_file_tools(const char* const _cfgname, const enum BREAK_CTYPE _ctype)
{
	cfgname = _cfgname;
	item_separate_character_type = _ctype;
	//���ļ�
	ifstream infile(cfgname, ios::in | ios::binary);
	
	if (!infile.is_open()) {
		list_success = false;
		return;
	}

	vector<string> buffer;
	int row = 0;
	char c;
	size_t line_length = 0;
	
	string line;
	while (infile.get(c)) {
		line += c;  // ���ַ���ӵ���ǰ�л�����
		line_length++;

		// ������� \n�ж��Ƿ񳬳�
		if (c == '\n') {
			// ����Ƿ��� Windows ��ʽ���н�������\r\n��
			if (line_length >= 2 && line[line_length - 2] == '\r') {
				// Windows ��ʽ
				if (line_length > MAX_LINE) {
					infile.close();
					cout << "�Ƿ���ʽ�������ļ�,��[" << row << "]�г�����󳤶� 1024.";
					list_success = false;
					return;
				}
			}
			else {
				// Linux ��ʽ\n
				if (line_length > MAX_LINE) {
					infile.close();
					cout << "�Ƿ���ʽ�������ļ�,��[" << row << "]�г�����󳤶� 1024.";
					list_success = false;
					return;
				}
			}

			// ��յ�ǰ�� ���ó���
			
			buffer.push_back(line);
			row++;
			line_length = 0;
			line.clear();
		}
		/*ȫ������ע���У�����*/

	}
	// ������һ��(�޽��������
	if (!line.empty() ) {
		if (line_length > MAX_LINE) {
			infile.close();
			cout << "�Ƿ���ʽ�������ļ�,��[" << row + 1 << "]�г�����󳤶� 1024.";
			list_success = false;
			return;
		}
		else {
			buffer.push_back(line);
			row++;
		}
	}
	
	infile.close();
	list_success = true;
	//��ȡ��ϣ���ʼ����ÿһ��
	row_extractef(buffer, row);
	row_extractcon(*this, buffer, row, _ctype);


	/* ������� */
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::config_file_tools(const string& _cfgname, const enum BREAK_CTYPE _ctype)
{
	cfgname = _cfgname;
	item_separate_character_type = _ctype;
	
	//���ļ�
	ifstream infile(cfgname, ios::in | ios::binary);

	if (!infile.is_open()) {
		list_success = false;
		return;
	}

	vector<string> buffer;
	int row = 0;
	char c;
	size_t line_length = 0;

	string line;
	while (infile.get(c)) {
		line += c;  // ���ַ���ӵ���ǰ�л�����
		line_length++;

		// ������� \n�ж��Ƿ񳬳�
		if (c == '\n') {
			// ����Ƿ��� Windows ��ʽ���н�������\r\n��
			if (line_length >= 2 && line[line_length - 2] == '\r') {
				// Windows ��ʽ
				if (line_length > MAX_LINE) {
					infile.close();
					cout << "�Ƿ���ʽ�������ļ�,��[" << row << "]�г�����󳤶� 1024.";
					list_success = false;
					return;
				}
			}
			else {
				// Linux ��ʽ\n
				if (line_length > MAX_LINE) {
					infile.close();
					cout << "�Ƿ���ʽ�������ļ�,��[" << row << "]�г�����󳤶� 1024.";
					list_success = false;
					return;
				}
			}

			// ��յ�ǰ�� ���ó���

			buffer.push_back(line);
			row++;
			line_length = 0;
			line.clear();
		}
		/*ȫ������ע���У�����*/

	}
	// ������һ��(�޽��������
	if (!line.empty()) {
		if (line_length > MAX_LINE) {
			infile.close();
			cout << "�Ƿ���ʽ�������ļ�,��[" << row + 1 << "]�г�����󳤶� 1024.";
			list_success = false;
			return;
		}
		else {
			buffer.push_back(line);
			row++;
		}
	}

	infile.close();
	list_success = true;
	//��ȡ��ϣ���ʼ����ÿһ��
	row_extractef(buffer, row);
	row_extractcon(*this, buffer, row, _ctype);



	/* ������� */
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
config_file_tools::~config_file_tools()
{

	/* ������� */
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ��ж϶������ļ��Ƿ�ɹ�
  ���������
  �� �� ֵ��true - �ɹ����Ѷ������е���/��
		   false - ʧ�ܣ��ļ�ĳ�г���/�ļ�ȫ����ע�����
  ˵    ����
***************************************************************************/
bool config_file_tools::is_read_succeeded() const
{
	if (list_success)
		return true;
	else
		return false;

	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return true;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����������ļ��е�������
  ���������vector <string>& ret : vector ��ÿ��Ϊһ������
  �� �� ֵ������������������������ļ���������Ϊ1������Ϊ"��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_group(vector <string>& ret)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */

	for (int i = 0; i < group_num; i++) {
		ret.push_back ( LIST[i].group_name);
	}

	return group_num;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ָ�����������������ԭʼ����
  ���������const char* const group_name������
		   vector <string>& ret��vector ��ÿ��Ϊһ�����ԭʼ����
		   const bool is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ�����������0��ʾ��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_item(const char* const group_name, vector <string>& ret, const bool is_case_sensitive)
{
	int i = 0;
	if (is_case_sensitive) {
		i = comp_sen(*this, group_name);
	}
	else {
		i = comp_insen(*this, group_name);
	}
	if (i == group_num) {
		return 0;
	}
	else {
		for (int j = 0; j < LIST[i].item_num; j++) {
			ret.push_back(LIST[i].ITEM[j].raw);
		}
	}

	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return  LIST[i].item_num;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::get_all_item(const string& group_name, vector <string>& ret, const bool is_case_sensitive)
{
	int i = 0;
	if (is_case_sensitive) {
		i = comp_sen(*this, group_name.c_str());
	}
	else {
		i = comp_insen(*this, group_name.c_str());
	}
	if (i == group_num) {
		return 0;
	}
	else {
		for (int j = 0; j < LIST[i].item_num; j++) {
			ret.push_back(LIST[i].ITEM[j].raw);
		}
	}

	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return  LIST[i].item_num;

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ���ԭʼ���ݣ�=��������ַ���string��ʽ��
  ���������const char* const group_name
		   const char* const item_name
		   string &ret
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_raw(const char* const group_name, const char* const item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	int i = 0;
	if (group_is_case_sensitive) {
		i = comp_sen(*this, group_name);
	}
	else if(!group_is_case_sensitive){
		i = comp_insen(*this, group_name);
	}
	if (item_is_case_sensitive) {
		for (int j = 0; j < LIST[i].item_num; j++) {
			if (strcmp(item_name, LIST[i].ITEM[j].item_name.c_str()) == 0) {
				ret = LIST[i].ITEM[j].item_val;
				return 0;
			}

		}
	}
	else {
		char* new_name = trantolow(item_name);
		for (int j = 0; j < LIST[i].item_num; j++) {
			char* dst_name = trantolow(LIST[i].ITEM[j].item_name.c_str());
			if (strcmp(dst_name, new_name) == 0) {
				ret = LIST[i].ITEM[j].item_val;
				return 0;
			}
		}

	}

	
	
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_raw(const string& group_name, const string& item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_raw(group_name.c_str(), item_name.c_str(), ret, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��1 - �������������
		   0 - ���������������
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_null(const char* const group_name, const char* const item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int i = 0;
	if (group_is_case_sensitive) {
		i = comp_sen(*this, group_name);
	}
	else if (!group_is_case_sensitive) {
		i = comp_insen(*this, group_name);
	}
	if (item_is_case_sensitive) {
		for (int j = 0; j < LIST[i].item_num; j++) {
			if (strcmp(item_name, LIST[i].ITEM[j].item_name.c_str()) == 0) {
				return 1;
			}

		}
	}
	else {
		char* new_name = trantolow(item_name);
		for (int j = 0; j < LIST[i].item_num; j++) {
			char* dst_name = trantolow(LIST[i].ITEM[j].item_name.c_str());
			if (strcmp(dst_name, new_name) == 0) {
				return 1;
			}
		}

	}

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_null(const string& group_name, const string& item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_null(group_name.c_str(), item_name.c_str(), group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   char& value                                ��������char��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const char* const choice_set = nullptr     ���Ϸ���char�ļ��ϣ����磺"YyNn"��ʾ�Ϸ�����ΪY/N�Ҳ��ִ�Сд���ò�����Ĭ��ֵnullptr����ʾȫ���ַ���������飩
		   const char def_value = DEFAULT_CHAR_VALUE  ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_CHAR_VALUE�����������
															��ֵ��   DEFAULT_CHAR_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_CHAR_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��1 - ȡ����ȷֵ
			   δȡ��ֵ/δȡ����ȷֵ��������ȱʡֵ��������Ϊȱʡֵ��
		   0 - δȡ����ֻ��Ϊδָ��Ĭ��ֵ������²Ż᷵��0��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_char(const char* const group_name, const char* const item_name, char& value,
						const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int i = 0;
	if (group_is_case_sensitive) {
		i = comp_sen(*this, group_name);
	}
	else if (!group_is_case_sensitive) {
		i = comp_insen(*this, group_name);
	}
	if (item_is_case_sensitive) {
		for (int j = 0; j < LIST[i].item_num; j++) {
			if (strcmp(item_name, LIST[i].ITEM[j].item_name.c_str()) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				char ch;
				ss >> ch;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_CHAR_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//������ȷ
				if (!choice_set) {//nullptr�����
					value = ch;
					return 1;

				}
				else {
					for(int i = 0; i < (int)strlen(choice_set);i++){
						if (ch == choice_set[i]) {
							value = ch;
							return 1;
						}
					
					}
					if (def_value == DEFAULT_CHAR_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}

			}

		}

	}
	else {
		char* new_name = trantolow(item_name);
		for (int j = 0; j < LIST[i].item_num; j++) {
			char* dst_name = trantolow(LIST[i].ITEM[j].item_name.c_str());
			if (strcmp(dst_name, new_name) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				char ch;
				ss >> ch;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_CHAR_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//������ȷ
				if (!choice_set) {//nullptr�����
					value = ch;
					return 1;

				}
				else {
					for (int i = 0; i <(int) strlen(choice_set); i++) {
						if (ch == choice_set[i]) {
							value = ch;
							return 1;
						}

					}
					if (def_value == DEFAULT_CHAR_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				
			}
		}

	}

	if (def_value == DEFAULT_CHAR_VALUE) {
		return 0;
	}
	else {
		value = def_value;
		return 1;
	}


	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_char(const string& group_name, const string& item_name, char& value,
						const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_char(group_name.c_str(), item_name.c_str(), value, choice_set, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊint��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   int& value                                 ��������int��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const int min_value = INT_MIN              : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MIN
		   const int max_value = INT_MAX              : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MAX
		   const int def_value = DEFAULT_INT_VALUE    ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵ DEFAULT_INT_VALUE�����������
															��ֵ��   DEFAULT_INT_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_INT_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_int(const char* const group_name, const char* const item_name, int& value,
						const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ������ɣ�������Ҫ�ı�return��ֵ */
	int i = 0;
	if (group_is_case_sensitive) {
		i = comp_sen(*this, group_name);
	}
	else if (!group_is_case_sensitive) {
		i = comp_insen(*this, group_name);
	}
	if (item_is_case_sensitive) {
		for (int j = 0; j < LIST[i].item_num; j++) {
			if (strcmp(item_name, LIST[i].ITEM[j].item_name.c_str()) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				int val;
				ss >> val;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_INT_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//������ȷ
				if (val<=max_value&&val>=min_value) {//nullptr�����
					value =val;
					return 1;

				}
				else {
					if (def_value == DEFAULT_INT_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}

			}

		}

	}
	else {
		char* new_name = trantolow(item_name);
		for (int j = 0; j < LIST[i].item_num; j++) {
			char* dst_name = trantolow(LIST[i].ITEM[j].item_name.c_str());
			if (strcmp(dst_name, new_name) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				int val;
				ss >> val;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_INT_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//������ȷ
				if (val <= max_value && val >= min_value) {//nullptr�����
					value = val;
					return 1;

				}
				else {
					if (def_value == DEFAULT_INT_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
			}
		}

	}

	if (def_value == DEFAULT_INT_VALUE) {
		return 0;
	}
	else {
		value = def_value;
		return 1;
	}


	return 0;


}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_int(const string& group_name, const string& item_name, int& value,
						const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_int(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊdouble��
  ���������const char* const group_name                  ������
		   const char* const item_name                   ������
		   double& value                                 ��������int��ֵ������1ʱ���ţ�����0�򲻿��ţ�
		   const double min_value = __DBL_MIN__          : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MIN
		   const double max_value = __DBL_MAX__          : �������ݷ�Χ�����ޣ�Ĭ��ΪINT_MAX
		   const double def_value = DEFAULT_DOUBLE_VALUE ��������/�����Ƿ�������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_DOUBLE_VALUE�����������
																��ֵ��   DEFAULT_DOUBLE_VALUE ʱ������0��ֵ�����ţ�
																��ֵ���� DEFAULT_DOUBLE_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false     : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false      : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_double(const char* const group_name, const char* const item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	int i = 0;
	if (group_is_case_sensitive) {
		i = comp_sen(*this, group_name);
	}
	else if (!group_is_case_sensitive) {
		i = comp_insen(*this, group_name);
	}
	if (item_is_case_sensitive) {
		for (int j = 0; j < LIST[i].item_num; j++) {
			if (strcmp(item_name, LIST[i].ITEM[j].item_name.c_str()) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				double val;
				ss >> val;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_DOUBLE_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//������ȷ
				if (val <= max_value && val >= min_value) {//nullptr�����
					value = val;
					return 1;

				}
				else {
					if (def_value == DEFAULT_DOUBLE_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}

			}

		}

	}
	else {
		char* new_name = trantolow(item_name);
		for (int j = 0; j < LIST[i].item_num; j++) {
			char* dst_name = trantolow(LIST[i].ITEM[j].item_name.c_str());
			if (strcmp(dst_name, new_name) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				double val;
				ss >> val;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_DOUBLE_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//������ȷ
				if (val <= max_value && val >= min_value) {//nullptr�����
					value = val;
					return 1;

				}
				else {
					if (def_value == DEFAULT_DOUBLE_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
			}
		}

	}

	if (def_value == DEFAULT_DOUBLE_VALUE) {
		return 0;
	}
	else {
		value = def_value;
		return 1;
	}

	return 0;

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_double(const string& group_name, const string& item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_double(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊchar * / char []��
  ���������const char* const group_name                  ������
		   const char* const item_name                   ������
		   char *const value                             ��������C��ʽ���ַ���������1ʱ���ţ�����0�򲻿��ţ�
		   const int str_maxlen                          ��ָ��Ҫ������󳤶ȣ���β�㣩
																���<1�򷵻ؿմ�(����DEFAULT_CSTRING_VALUE����Ȼ����������ͬ����Ҫ����defaultֵ���ܻ��)
																���>MAX_STRLEN ������ΪMAX_STRLEN
		   const char* const def_str                     ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_CSTRING_VALUE�����������
																��ֵ��   DEFAULT_CSTRING_VALUE ʱ������0��ֵ�����ţ�
																��ֵ���� DEFAULT_CSTRING_VALUE ʱ����value=def_value������1��ע�⣬����ֱ��=��
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����1��Ϊ�򻯣�δ��\"����ת�崦��������ͨ�ַ�
		   2����β�����󳤶�Ϊstr_maxlen������ʱҪ��֤���㹻�ռ�
		   3����� str_maxlen ������ϵͳԤ������� MAX_STRLEN���� MAX_STRLEN ȡ
***************************************************************************/
int config_file_tools::item_get_cstring(const char* const group_name, const char* const item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	int i = 0;
	if (group_is_case_sensitive) {
		i = comp_sen(*this, group_name);
	}
	else if (!group_is_case_sensitive) {
		i = comp_insen(*this, group_name);
	}
	if (item_is_case_sensitive) {
		for (int j = 0; j < LIST[i].item_num; j++) {
			if (strcmp(item_name, LIST[i].ITEM[j].item_name.c_str()) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				
				if (str_maxlen < 1) {
					strcpy(value, "");
					return 1;
				}
				else if (str_maxlen > MAX_STRLEN) {
					char* val = new char[MAX_STRLEN];
					ss >> val;
					if (ss.fail()) {//������ �����Ƿ�
						if (def_value == DEFAULT_CSTRING_VALUE) {
							delete[]val;
							return 0;
						}
						else {
							strcpy(value, DEFAULT_CSTRING_VALUE);
							delete[]val;
							return 1;
						}

					}
					strncpy(value, val, MAX_STRLEN - 1);
					strcat(value, "\0");
					delete[]val;
				}
				else {
					char* val = new char[str_maxlen];
					ss >> val;
					if (ss.fail()) {//������ �����Ƿ�
						if (def_value == DEFAULT_CSTRING_VALUE) {
							delete[]val;
							return 0;
						}
						else {
							strcpy(value, DEFAULT_CSTRING_VALUE);
							delete[]val;
							return 1;
						}

					}
					strncpy(value, val, str_maxlen - 1);
					strcat(value, "\0");
					delete[]val;
				}
				
				
				
				
			}

		}

	}
	else {
		char* new_name = trantolow(item_name);
		for (int j = 0; j < LIST[i].item_num; j++) {
			char* dst_name = trantolow(LIST[i].ITEM[j].item_name.c_str());
			if (strcmp(dst_name, new_name) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);

				if (str_maxlen < 1) {
					strcpy(value, "");
					return 1;
				}
				else if (str_maxlen > MAX_STRLEN) {
					char* val = new char[MAX_STRLEN];
					ss >> val;
					if (ss.fail()) {//������ �����Ƿ�
						if (def_value == DEFAULT_CSTRING_VALUE) {
							delete[]val;
							return 0;
						}
						else {
							strcpy(value, DEFAULT_CSTRING_VALUE);
							delete[]val;
							return 1;
						}

					}
					strncpy(value, val, MAX_STRLEN - 1);
					strcat(value, "\0");
					delete[]val;
					return 1;
				}
				else {
					char* val = new char[str_maxlen];
					ss >> val;
					if (ss.fail()) {//������ �����Ƿ�
						if (def_value == DEFAULT_CSTRING_VALUE) {
							delete[]val;
							return 0;
						}
						else {
							strcpy(value, DEFAULT_CSTRING_VALUE);
							delete[]val;
							return 1;
						}

					}
					strncpy(value, val, str_maxlen - 1);
					strcat(value, "\0");
					delete[]val;
					return 1;
				}
			}
		}

	}
	if (def_value == DEFAULT_CSTRING_VALUE) {
		
		return 0;
	}
	else {
		strcpy(value, DEFAULT_CSTRING_VALUE);
		
		return 1;
	}


	return 0;



}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_cstring(const string& group_name, const string& item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return item_get_cstring(group_name.c_str(), item_name.c_str(), value, str_maxlen, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊ string ��
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   string &value                              ��������string��ʽ���ַ���������1ʱ���ţ�����0�򲻿��ţ�
		   const string &def_value                    ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_STRING_VALUE�����������
															��ֵ��   DEFAULT_STRING_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_STRING_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����Ϊ�򻯣�δ��\"����ת�崦��������ͨ�ַ�
***************************************************************************/
int config_file_tools::item_get_string(const char* const group_name, const char* const item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	int i = 0;
	if (group_is_case_sensitive) {
		i = comp_sen(*this, group_name);
	}
	else if (!group_is_case_sensitive) {
		i = comp_insen(*this, group_name);
	}
	if (item_is_case_sensitive) {
		for (int j = 0; j < LIST[i].item_num; j++) {
			if (strcmp(item_name, LIST[i].ITEM[j].item_name.c_str()) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				string val;
				ss >> val;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_STRING_VALUE) {
						return 0;
					}
					else {
						value = DEFAULT_STRING_VALUE;
						return 1;
					}

				}
				value = val;
				return 1;
			}

		}

	}
	else {
		char* new_name = trantolow(item_name);
		for (int j = 0; j < LIST[i].item_num; j++) {
			char* dst_name = trantolow(LIST[i].ITEM[j].item_name.c_str());
			if (strcmp(dst_name, new_name) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				string val;
				ss >> val;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_STRING_VALUE) {
						return 0;
					}
					else {
						value = DEFAULT_STRING_VALUE;
						return 1;
					}

				}
				value = val;
				return 1;
			}
		}

	}
		
	if (def_value == DEFAULT_STRING_VALUE) {
		return 0;
	}
	else {
		value = DEFAULT_STRING_VALUE;
		return 1;
	}

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_string(const string& group_name, const string& item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_string(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡĳ������ݣ���������Ϊ IPv4 ��ַ��32bit���ͣ�������
  ���������const char* const group_name               ������
		   const char* const item_name                ������
		   unsigned int &value                        ��������IP��ַ��32λ���ͷ�ʽ������1ʱ���ţ�����0�򲻿��ţ�
		   const unsigned int &def_value              ������������µ�Ĭ��ֵ���ò�����Ĭ��ֵDEFAULT_IPADDR_VALUE�����������
															��ֵ��   DEFAULT_IPADDR_VALUE ʱ������0��ֵ�����ţ�
															��ֵ���� DEFAULT_IPADDR_VALUE ʱ����value=def_value������1
		   const bool group_is_case_sensitive = false : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
		   const bool item_is_case_sensitive = false  : �����Ƿ��Сд���У�true-��Сд���� / Ĭ��false-��Сд������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int config_file_tools::item_get_ipaddr(const char* const group_name, const char* const item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	int i = 0;
	if (group_is_case_sensitive) {
		i = comp_sen(*this, group_name);
	}
	else if (!group_is_case_sensitive) {
		i = comp_insen(*this, group_name);
	}
	if (item_is_case_sensitive) {
		for (int j = 0; j < LIST[i].item_num; j++) {
			if (strcmp(item_name, LIST[i].ITEM[j].item_name.c_str()) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				string val;
				ss >> val;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_IPADDR_VALUE) {
						return 0;
					}
					else {
						value = DEFAULT_IPADDR_VALUE;
						return 1;
					}

				}
				bool correct=checkip(val.c_str());
				if (correct) {
					value = strtout(val);
					return 1;
				}
				else {
					if (def_value == DEFAULT_IPADDR_VALUE) {
						return 0;
					}
					else {
						value = DEFAULT_IPADDR_VALUE;
						return 1;
					}
				}
				
			}

		}

	}
	else {
		char* new_name = trantolow(item_name);
		for (int j = 0; j < LIST[i].item_num; j++) {
			char* dst_name = trantolow(LIST[i].ITEM[j].item_name.c_str());
			if (strcmp(dst_name, new_name) == 0) {
				istringstream ss(LIST[i].ITEM[j].item_val);
				string val;
				ss >> val;
				if (ss.fail()) {//������ �����Ƿ�
					if (def_value == DEFAULT_IPADDR_VALUE) {
						return 0;
					}
					else {
						value = DEFAULT_IPADDR_VALUE;
						return 1;
					}

				}
				bool correct = checkip(val.c_str());
				if (correct) {
					value = strtout(val);
					return 1;
				}
				else {
					if (def_value == DEFAULT_IPADDR_VALUE) {
						return 0;
					}
					else {
						value = DEFAULT_IPADDR_VALUE;
						return 1;
					}
				}
			}
		}

	}

	if (def_value == DEFAULT_IPADDR_VALUE) {
		return 0;
	}
	else {
		value = DEFAULT_IPADDR_VALUE;
		return 1;
	}
	return 0;

}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����/��ĿΪstring��ʽ������ͬ��
  ���������
  �� �� ֵ��
  ˵    ������Ϊ���ߺ���һ���ڳ����ʼ���׶α����ã������ڳ���ִ���б���Ƶ�ε��ã�
		   �������ֱ���׿ǣ�����΢Ӱ��Ч�ʣ�����Ӱ���������ܣ��Ը�Ƶ�ε��ã��˷������ʺϣ�
***************************************************************************/
int config_file_tools::item_get_ipaddr(const string& group_name, const string& item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* ��������ʵ�� */
	return this->item_get_ipaddr(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}
