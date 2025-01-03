/* 2354180 王韵涵 计科 */ 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
/* 添加自己需要的头文件，注意限制 */
#include "../include/class_cft.h"
#include<string>
#include<fstream>
#include<sstream>
#include<climits>
using namespace std;

/* 给出各种自定义函数的实现（已给出的内容不全） */
static bool checkip(const char* ip)
{

	int num = 0;      // 当前段的数字
	int dotCount = 0; // 点的个数
	int len = strlen(ip);


	for (int i = 0; i < len; i++) {
		// 检查当前字符是否是数字
		if (ip[i] >= '0' && ip[i] <= '9') {
			num = num * 10 + (ip[i] - '0'); // 累加当前段的数字

			// 检查数字是否超出范围
			if (num > 255) {

				return false;
			}
		}
		// 检查是否遇到点
		else if (ip[i] == '.') {
			dotCount++;

			// 如果点的数量超过3个，IP地址不合法
			if (dotCount > 3) {

				return false;
			}

			// 如果（没有数字）或点前的数字不合法
			if (i == 0 || ip[i - 1] < '0' || ip[i - 1]>'9') {

				return false;
			}

			num = 0; // 重置num，开始下一段的数字解析
		}
		// 如果遇到非数字非点字符
		else {

			return false;
		}
	}

	// 检查最后一段是否为空
	if (ip[len - 1] == '.') {

		return false;
	}

	// 检查点的个数是否正好是3个（意味着有4段）
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

	char dot;  // 用于跳过 `.`

	// 使用 >> 操作符读取数字并跳过 `.` 符号
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

		// 找出最小的有效索引
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
			break;//下一组开始或已经到结尾
		}
		if (buffer[i].size() > 1 && buffer[i][0] == '[' && buffer[i][buffer[i].size() - 1] == ']') {
			break;
		}
		if (buffer[i].empty()) {//空的直接跳过
			i++;
			continue;
		}
		//非空
		int src=0;
		GROUP.item_num++;
		item T;
		if (_ctype == BREAK_CTYPE::Equal&&(src=buffer[i].find_first_of('='))!=string::npos|| _ctype == BREAK_CTYPE::Space && (src = buffer[i].find_first_of(' ')) != string::npos) {
			
			T.item_name = vanish_space(buffer[i].substr(0, src-1+1));
			T.item_val= vanish_space(buffer[i].substr(src+1, buffer[i].size()-1-src));
			T.raw = buffer[i];
			GROUP.ITEM.push_back(T);

		}
		else {//无分隔符
			T.raw = buffer[i];
			GROUP.ITEM.push_back(T);
		}
		i++;
		

	}

	return i;

}

static void row_extractcon(config_file_tools &mcfg,vector<string>buffer, int row, const enum BREAK_CTYPE _ctype)//现在进来的全是有效内容
{
	if (buffer.empty()) {
		return;
	}
	int i = 0;
	while (i <(int) buffer.size()) { // 检查 i 是否小于 buffer.size()
		if (!buffer[i].empty()) {
			break;
		}
		i++;
	}
	if (i >= (int)buffer.size()) {
		return; 
	}

	int start = 0;
	int end = buffer[i].size() - 1;//代表下标，所以要-1
	if (buffer[i].size() > 1 && buffer[i][start] == '[' && buffer[i][end] == ']') {//是正常配置
		mcfg.ftype = TYPE_NORMAL;
		while (i < (int)buffer.size()) {
			group GROUP;
			GROUP.group_name = buffer[i];//要不要处理内部的前后空格？
			i=normal_type(GROUP, buffer, i+1,row,_ctype);
			mcfg.LIST.push_back(GROUP);
			mcfg.group_num++;
			if (i == row) {
				break;
			}
		}
	}
	else {//简单或者混合
		//先处理第一个
		group GROUP;
		GROUP.group_name = "";
		i = normal_type(GROUP, buffer, i, row, _ctype);
		mcfg.LIST.push_back(GROUP);
		mcfg.group_num++;
		//处理后续
		if (i == row) {
			mcfg.ftype = TYPE_SIMPLE;
			
		}
		else {
			mcfg.ftype = TYPE_MIX;
			while (i < (int)buffer.size()){
				group GROUP;
				GROUP.group_name = buffer[i];//要不要处理内部的前后空格？
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
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const char* const _cfgname, const enum BREAK_CTYPE _ctype)
{
	cfgname = _cfgname;
	item_separate_character_type = _ctype;
	//打开文件
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
		line += c;  // 将字符添加到当前行缓存中
		line_length++;

		// 如果遇到 \n判断是否超长
		if (c == '\n') {
			// 检查是否是 Windows 格式的行结束符（\r\n）
			if (line_length >= 2 && line[line_length - 2] == '\r') {
				// Windows 格式
				if (line_length > MAX_LINE) {
					infile.close();
					cout << "非法格式的配置文件,第[" << row << "]行超过最大长度 1024.";
					list_success = false;
					return;
				}
			}
			else {
				// Linux 格式\n
				if (line_length > MAX_LINE) {
					infile.close();
					cout << "非法格式的配置文件,第[" << row << "]行超过最大长度 1024.";
					list_success = false;
					return;
				}
			}

			// 清空当前行 重置长度
			
			buffer.push_back(line);
			row++;
			line_length = 0;
			line.clear();
		}
		/*全部都是注释行！！！*/

	}
	// 检查最后一行(无结束符情况
	if (!line.empty() ) {
		if (line_length > MAX_LINE) {
			infile.close();
			cout << "非法格式的配置文件,第[" << row + 1 << "]行超过最大长度 1024.";
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
	//读取完毕，开始处理每一行
	row_extractef(buffer, row);
	row_extractcon(*this, buffer, row, _ctype);


	/* 按需完成 */
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::config_file_tools(const string& _cfgname, const enum BREAK_CTYPE _ctype)
{
	cfgname = _cfgname;
	item_separate_character_type = _ctype;
	
	//打开文件
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
		line += c;  // 将字符添加到当前行缓存中
		line_length++;

		// 如果遇到 \n判断是否超长
		if (c == '\n') {
			// 检查是否是 Windows 格式的行结束符（\r\n）
			if (line_length >= 2 && line[line_length - 2] == '\r') {
				// Windows 格式
				if (line_length > MAX_LINE) {
					infile.close();
					cout << "非法格式的配置文件,第[" << row << "]行超过最大长度 1024.";
					list_success = false;
					return;
				}
			}
			else {
				// Linux 格式\n
				if (line_length > MAX_LINE) {
					infile.close();
					cout << "非法格式的配置文件,第[" << row << "]行超过最大长度 1024.";
					list_success = false;
					return;
				}
			}

			// 清空当前行 重置长度

			buffer.push_back(line);
			row++;
			line_length = 0;
			line.clear();
		}
		/*全部都是注释行！！！*/

	}
	// 检查最后一行(无结束符情况
	if (!line.empty()) {
		if (line_length > MAX_LINE) {
			infile.close();
			cout << "非法格式的配置文件,第[" << row + 1 << "]行超过最大长度 1024.";
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
	//读取完毕，开始处理每一行
	row_extractef(buffer, row);
	row_extractcon(*this, buffer, row, _ctype);



	/* 按需完成 */
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
config_file_tools::~config_file_tools()
{

	/* 按需完成 */
}


/***************************************************************************
  函数名称：
  功    能：判断读配置文件是否成功
  输入参数：
  返 回 值：true - 成功，已读入所有的组/项
		   false - 失败，文件某行超长/文件全部是注释语句
  说    明：
***************************************************************************/
bool config_file_tools::is_read_succeeded() const
{
	if (list_success)
		return true;
	else
		return false;

	/* 按需完成，根据需要改变return的值 */
	return true;
}

/***************************************************************************
  函数名称：
  功    能：返回配置文件中的所有组
  输入参数：vector <string>& ret : vector 中每项为一个组名
  返 回 值：读到的组的数量（简单配置文件的组数量为1，组名为"）
  说    明：
***************************************************************************/
int config_file_tools::get_all_group(vector <string>& ret)
{
	/* 按需完成，根据需要改变return的值 */

	for (int i = 0; i < group_num; i++) {
		ret.push_back ( LIST[i].group_name);
	}

	return group_num;
}

/***************************************************************************
  函数名称：
  功    能：查找指定组的所有项并返回项的原始内容
  输入参数：const char* const group_name：组名
		   vector <string>& ret：vector 中每项为一个项的原始内容
		   const bool is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：项的数量，0表示空
  说    明：
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

	/* 按需完成，根据需要改变return的值 */
	return  LIST[i].item_num;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：
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

	/* 按需完成，根据需要改变return的值 */
	return  LIST[i].item_num;

}

/***************************************************************************
  函数名称：
  功    能：取某项的原始内容（=后的所有字符，string方式）
  输入参数：const char* const group_name
		   const char* const item_name
		   string &ret
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
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

	
	
	/* 按需完成，根据需要改变return的值 */
	return 0;
}

/***************************************************************************
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_raw(const string& group_name, const string& item_name, string& ret, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_raw(group_name.c_str(), item_name.c_str(), ret, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：1 - 该项的项名存在
		   0 - 该项的项名不存在
  说    明：
***************************************************************************/
int config_file_tools::item_get_null(const char* const group_name, const char* const item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
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
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_null(const string& group_name, const string& item_name, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_null(group_name.c_str(), item_name.c_str(), group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   char& value                                ：读到的char的值（返回1时可信，返回0则不可信）
		   const char* const choice_set = nullptr     ：合法的char的集合（例如："YyNn"表示合法输入为Y/N且不分大小写，该参数有默认值nullptr，表示全部字符，即不检查）
		   const char def_value = DEFAULT_CHAR_VALUE  ：读不到/读到非法的情况下的默认值，该参数有默认值DEFAULT_CHAR_VALUE，分两种情况
															当值是   DEFAULT_CHAR_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_CHAR_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：1 - 取到正确值
			   未取到值/未取到正确值，设置了缺省值（包括设为缺省值）
		   0 - 未取到（只有为未指定默认值的情况下才会返回0）
  说    明：
***************************************************************************/
int config_file_tools::item_get_char(const char* const group_name, const char* const item_name, char& value,
						const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
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
				if (ss.fail()) {//不可信 读到非法
					if (def_value == DEFAULT_CHAR_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//读到正确
				if (!choice_set) {//nullptr不检查
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
				if (ss.fail()) {//不可信 读到非法
					if (def_value == DEFAULT_CHAR_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//读到正确
				if (!choice_set) {//nullptr不检查
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
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_char(const string& group_name, const string& item_name, char& value,
						const char* const choice_set, const char def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_char(group_name.c_str(), item_name.c_str(), value, choice_set, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为int型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   int& value                                 ：读到的int的值（返回1时可信，返回0则不可信）
		   const int min_value = INT_MIN              : 期望数据范围的下限，默认为INT_MIN
		   const int max_value = INT_MAX              : 期望数据范围的上限，默认为INT_MAX
		   const int def_value = DEFAULT_INT_VALUE    ：读不到/读到非法的情况下的默认值，该参数有默认值 DEFAULT_INT_VALUE，分两种情况
															当值是   DEFAULT_INT_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_INT_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
***************************************************************************/
int config_file_tools::item_get_int(const char* const group_name, const char* const item_name, int& value,
						const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 按需完成，根据需要改变return的值 */
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
				if (ss.fail()) {//不可信 读到非法
					if (def_value == DEFAULT_INT_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//读到正确
				if (val<=max_value&&val>=min_value) {//nullptr不检查
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
				if (ss.fail()) {//不可信 读到非法
					if (def_value == DEFAULT_INT_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//读到正确
				if (val <= max_value && val >= min_value) {//nullptr不检查
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
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_int(const string& group_name, const string& item_name, int& value,
						const int min_value, const int max_value, const int def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_int(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为double型
  输入参数：const char* const group_name                  ：组名
		   const char* const item_name                   ：项名
		   double& value                                 ：读到的int的值（返回1时可信，返回0则不可信）
		   const double min_value = __DBL_MIN__          : 期望数据范围的下限，默认为INT_MIN
		   const double max_value = __DBL_MAX__          : 期望数据范围的上限，默认为INT_MAX
		   const double def_value = DEFAULT_DOUBLE_VALUE ：读不到/读到非法的情况下的默认值，该参数有默认值DEFAULT_DOUBLE_VALUE，分两种情况
																当值是   DEFAULT_DOUBLE_VALUE 时，返回0（值不可信）
																当值不是 DEFAULT_DOUBLE_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false     : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false      : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
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
				if (ss.fail()) {//不可信 读到非法
					if (def_value == DEFAULT_DOUBLE_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//读到正确
				if (val <= max_value && val >= min_value) {//nullptr不检查
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
				if (ss.fail()) {//不可信 读到非法
					if (def_value == DEFAULT_DOUBLE_VALUE) {
						return 0;
					}
					else {
						value = def_value;
						return 1;
					}
				}
				//读到正确
				if (val <= max_value && val >= min_value) {//nullptr不检查
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
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_double(const string& group_name, const string& item_name, double& value,
						const double min_value, const double max_value, const double def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_double(group_name.c_str(), item_name.c_str(), value, min_value, max_value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为char * / char []型
  输入参数：const char* const group_name                  ：组名
		   const char* const item_name                   ：项名
		   char *const value                             ：读到的C方式的字符串（返回1时可信，返回0则不可信）
		   const int str_maxlen                          ：指定要读的最大长度（含尾零）
																如果<1则返回空串(不是DEFAULT_CSTRING_VALUE，虽然现在两者相同，但要考虑default值可能会改)
																如果>MAX_STRLEN 则上限为MAX_STRLEN
		   const char* const def_str                     ：读不到情况下的默认值，该参数有默认值DEFAULT_CSTRING_VALUE，分两种情况
																当值是   DEFAULT_CSTRING_VALUE 时，返回0（值不可信）
																当值不是 DEFAULT_CSTRING_VALUE 时，令value=def_value并返回1（注意，不是直接=）
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：1、为简化，未对\"等做转义处理，均按普通字符
		   2、含尾零的最大长度为str_maxlen，调用时要保证有足够空间
		   3、如果 str_maxlen 超过了系统预设的上限 MAX_STRLEN，则按 MAX_STRLEN 取
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
					if (ss.fail()) {//不可信 读到非法
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
					if (ss.fail()) {//不可信 读到非法
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
					if (ss.fail()) {//不可信 读到非法
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
					if (ss.fail()) {//不可信 读到非法
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
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_cstring(const string& group_name, const string& item_name, char* const value,
						const int str_maxlen, const char* const def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return item_get_cstring(group_name.c_str(), item_name.c_str(), value, str_maxlen, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为 string 型
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   string &value                              ：读到的string方式的字符串（返回1时可信，返回0则不可信）
		   const string &def_value                    ：读不到情况下的默认值，该参数有默认值DEFAULT_STRING_VALUE，分两种情况
															当值是   DEFAULT_STRING_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_STRING_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：为简化，未对\"等做转义处理，均按普通字符
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
				if (ss.fail()) {//不可信 读到非法
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
				if (ss.fail()) {//不可信 读到非法
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
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_string(const string& group_name, const string& item_name, string& value,
						const string& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_string(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}

/***************************************************************************
  函数名称：
  功    能：取某项的内容，返回类型为 IPv4 地址的32bit整型（主机序）
  输入参数：const char* const group_name               ：组名
		   const char* const item_name                ：项名
		   unsigned int &value                        ：读到的IP地址，32位整型方式（返回1时可信，返回0则不可信）
		   const unsigned int &def_value              ：读不到情况下的默认值，该参数有默认值DEFAULT_IPADDR_VALUE，分两种情况
															当值是   DEFAULT_IPADDR_VALUE 时，返回0（值不可信）
															当值不是 DEFAULT_IPADDR_VALUE 时，令value=def_value并返回1
		   const bool group_is_case_sensitive = false : 组名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
		   const bool item_is_case_sensitive = false  : 项名是否大小写敏感，true-大小写敏感 / 默认false-大小写不敏感
  返 回 值：
  说    明：
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
				if (ss.fail()) {//不可信 读到非法
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
				if (ss.fail()) {//不可信 读到非法
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
  函数名称：
  功    能：组名/项目为string方式，其余同上
  输入参数：
  返 回 值：
  说    明：因为工具函数一般在程序初始化阶段被调用，不会在程序执行中被高频次调用，
		   因此这里直接套壳，会略微影响效率，但不影响整体性能（对高频次调用，此方法不适合）
***************************************************************************/
int config_file_tools::item_get_ipaddr(const string& group_name, const string& item_name, unsigned int& value,
						const unsigned int& def_value, const bool group_is_case_sensitive, const bool item_is_case_sensitive)
{
	/* 本函数已实现 */
	return this->item_get_ipaddr(group_name.c_str(), item_name.c_str(), value, def_value, group_is_case_sensitive, item_is_case_sensitive);
}
