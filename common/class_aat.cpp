/* 2354180 王韵涵 计科 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "../include/class_aat.h"
//如有必要，可以加入其它头文件
using namespace std;



#if !ENABLE_LIB_COMMON_TOOLS //不使用lib才有效

/* ---------------------------------------------------------------
	 允许加入其它需要static函数（内部工具用）
   ---------------------------------------------------------------- */
static int len(ST_EXTARGS_TYPE type)
{
	if (type == ST_EXTARGS_TYPE::boolean) {
		return 4;
	}
	else if (type == ST_EXTARGS_TYPE::int_with_default) {
		return 14;
	}
	else if (type == ST_EXTARGS_TYPE::int_with_error) {
		return 12;
	}
	else if (type == ST_EXTARGS_TYPE::int_with_set_default) {
		return 17;
	}
	else if (type == ST_EXTARGS_TYPE::int_with_set_error) {
		return 15;
	}
	else if (type == ST_EXTARGS_TYPE::double_with_default) {
		return 17;
	}
	else if (type == ST_EXTARGS_TYPE::double_with_error) {
		return 15;
	}
	else if (type == ST_EXTARGS_TYPE::double_with_set_default) {
		return 20;
	}
	else if (type == ST_EXTARGS_TYPE::double_with_set_error) {
		return 18;
	}
	else if (type == ST_EXTARGS_TYPE::str) {
		return 6;
	}
	else if (type == ST_EXTARGS_TYPE::str_with_set_default) {
		return 20;
	}
	else if (type == ST_EXTARGS_TYPE::str_with_set_error) {
		return 18;
	}
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default) {
		return 17;
	}
	else if(type == ST_EXTARGS_TYPE::ipaddr_with_error) {
		return 15;
	}
	return 0;
}

static void print_type(ST_EXTARGS_TYPE type,int width)
{
	cout << left;

	if (type == ST_EXTARGS_TYPE::boolean) {
		cout << setw(width) << "Bool";
	}
	else if (type == ST_EXTARGS_TYPE::int_with_default) {
		cout << setw(width) << "IntWithDefault";
	}
	else if (type == ST_EXTARGS_TYPE::int_with_error) {
		cout << setw(width) << "IntWithError";
	}
	else if (type == ST_EXTARGS_TYPE::int_with_set_default) {
		cout << setw(width) << "IntSETWithDefault";
	}
	else if (type == ST_EXTARGS_TYPE::int_with_set_error) {
		cout << setw(width) << "IntSETWithError";
	}
	else if (type == ST_EXTARGS_TYPE::double_with_default) {
		cout << setw(width) << "DoubleWithDefault";
	}
	else if (type == ST_EXTARGS_TYPE::double_with_error) {
		cout << setw(width) << "DoubleWithError";
	}
	else if (type == ST_EXTARGS_TYPE::double_with_set_default) {
		cout << setw(width) << "DoubleSETWithDefault";
	}
	else if (type == ST_EXTARGS_TYPE::double_with_set_error) {
		cout << setw(width) << "DoubleSETWithError";
	}
	else if (type == ST_EXTARGS_TYPE::str) {
		cout << setw(width) << "String";
	}
	else if (type == ST_EXTARGS_TYPE::str_with_set_default) {
		cout << setw(width) << "StringSETWithDefault";
	}
	else if (type == ST_EXTARGS_TYPE::str_with_set_error) {
		cout << setw(width) << "StringSETWithError";
	}
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default) {
		cout << setw(width) << "IPAddrWithDefault";
	}
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_error) {
		cout << setw(width) << "IPAddrWithError";
	}
	
	
}
static string uttostr(unsigned int def)
{
	int num[4] = { 0 };
		unsigned char* ptr = (unsigned char*)(&def);
	for (int j = 0; j < 4; j++) {
		num[j] = ptr[j];
	}
	ostringstream ss;
	ss << num[0] << "." << num[1] << "." << num[2] << "." << num[3];
	return ss.str(); //此句根据需要修改
}
static unsigned int strtout(string value)
{
	u_int val;
	istringstream ss(value);
	
	int num[4] = { 0 };

	char dot;  // 用于跳过 `.`

	// 使用 >> 操作符读取数字并跳过 `.` 符号
	ss >> num[0] >> dot >> num[1] >> dot >> num[2] >> dot >> num[3];
	val = (num[0] << 24) | (num[1] << 16) | (num[2] << 8) | num[3];
	return val;
}
static int checknum(const char* content1)
{
	int start = 0;
	if (content1[0] == '-') {  // 如果第一个字符是负号
		if (strlen(content1) == 1) return 0;  // 只有负号没有数字的情况不是有效数字
		start = 1;  // 从第二个字符开始检查
	}
	bool decimal = false;
	for (size_t i =start; i <strlen(content1); i++) {
		if (content1[i] == '.') {
			if (decimal || i == start || i == strlen(content1)-1) {
				return 0;
			}
			decimal= true;
			
		}

		else if (content1[i] < '0' || content1[i]>'9') {
			
			return 0;//不是数
		}

	}
	return 1;//是数
}
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

static void printintset(const int*set, bool def,int value)
{
	int size = 0;
	while (set[size] != INVALID_INT_VALUE_OF_SET) {
		size++;
	}
	
	cout<<"可取值[" ;
		for (int c = 0; c<size; c++) {
			cout << set[c];
			if (c !=size - 1)
				cout << "/";
		}
	cout << "]";
	if (def) {
		cout << " 缺省:" << value;
	}
	
		cout<<")" << endl;
	

}
static void printdoubleset(const double* set, bool def, double value)
{
	int size = 0;
	while (set[size] != INVALID_DOUBLE_VALUE_OF_SET) {
		size++;
	}

	cout << "可取值[";
	for (int c = 0; c < size; c++) {
		cout << set[c];
		if (c != size - 1)
			cout << "/";
	}
	cout << "]";
	if (def) {
		cout << " 缺省:" << value;
	}

	cout << ")" << endl;

}
static void printstrset(const string* set, bool def, string value)
{
	int size = 0;
	while (set[size] != "") {
		size++;
	}

	cout << "可取值[";
	for (int c = 0; c < size; c++) {
		cout << set[c];
		if (c != size - 1)
			cout << "/";
	}
	cout << "]";
	if (def) {
		cout << " 缺省:" << value;
	}

	cout << ")" << endl;
}
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：null
 ***************************************************************************/
args_analyse_tools::args_analyse_tools()
{
	args_name = "";

	extargs_int_set = nullptr;

	extargs_double_set = nullptr;

	extargs_string_set = nullptr;
	

}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：boolean
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const bool def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_bool_default = def;
	args_existed = 0;
	

	extargs_int_set = nullptr;
	extargs_double_set = nullptr;
	extargs_string_set = nullptr;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_default、int_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def, const int _min, const int _max)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_int_default = def;
	extargs_int_min = _min;
	extargs_int_max = _max;
	args_existed = 0;
	extargs_int_value = extargs_int_default;

	extargs_int_set = nullptr;
	extargs_double_set = nullptr;
	extargs_string_set = nullptr;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：int_with_set_default、int_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const int* const set)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_int_default =set[def_of_set_pos];
	args_existed = 0;
	extargs_int_value = extargs_int_default;

	int size = 0;
	while (set[size] != INVALID_INT_VALUE_OF_SET) {
		size++;
	}
	size++;
	extargs_int_set = new int[size];
	if (!extargs_int_set) {
		cout << "申请内存失败" << endl;
		exit(-1);
	}
	for (int i = 0; i < size; i++) {
		extargs_int_set[i] = set[i];
	}

	
	extargs_double_set = nullptr;
	extargs_string_set = nullptr;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str、ipaddr_with_default、ipaddr_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const string def)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	args_existed = 0;

	

	if (type ==ST_EXTARGS_TYPE::str) {
		extargs_string_default = def;
	}
	else if (type == ST_EXTARGS_TYPE::ipaddr_with_default|| type == ST_EXTARGS_TYPE::ipaddr_with_error) {
		istringstream ss (def);
		int num[4] = { 0 };
		
		char dot;  // 用于跳过 `.`

		// 使用 >> 操作符读取数字并跳过 `.` 符号
		ss >> num[0] >> dot >> num[1] >> dot >> num[2] >> dot >> num[3];
		extargs_ipaddr_default = (num[0] << 24) | (num[1] << 16) | (num[2] << 8) | num[3];
	}
	
	extargs_int_set = nullptr;
	extargs_double_set = nullptr;
	extargs_string_set = nullptr;

	extargs_string_value = extargs_string_default;
	extargs_ipaddr_value = extargs_ipaddr_default;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：str_with_set_default、str_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const string* const set)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_string_default = set[def_of_set_pos];
	args_existed = 0;

	extargs_string_value = extargs_string_default;

	int size = 0;
	while (set[size] !="") {
		size++;
	}
	size++;
	extargs_string_set = new string[size];
	if (!extargs_string_set) {
		cout << "申请内存失败" << endl;
		exit(-1);
	}
	for (int i = 0; i < size; i++) {
		extargs_string_set[i] = set[i];
	}

	extargs_int_set = nullptr;
	extargs_double_set = nullptr;
	
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_default、double_with_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const ST_EXTARGS_TYPE type, const int ext_num, const double	def, const double _min, const double _max)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_double_default = def;
	extargs_double_min = _min;
	extargs_double_max = _max;
	args_existed = 0;

	extargs_int_set = nullptr;
	extargs_double_set = nullptr;
	extargs_string_set = nullptr;

	extargs_double_value = extargs_double_default;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：double_with_set_default、double_with_set_error
 ***************************************************************************/
args_analyse_tools::args_analyse_tools(const char* name, const enum ST_EXTARGS_TYPE type, const int ext_num, const int def_of_set_pos, const double* const set)
{
	args_name = name;
	extargs_type = type;
	extargs_num = ext_num;
	extargs_double_default = set[def_of_set_pos];
	args_existed = 0;

	int size = 0;
	while (set[size] != INVALID_DOUBLE_VALUE_OF_SET) {
		size++;
	}
	size++;
	extargs_double_set = new double[size];
	if (!extargs_double_set) {
		cout << "申请内存失败" << endl;
		exit(-1);
	}
	for (int i = 0; i < size; i++) {
		extargs_double_set[i] = set[i];
	}

	extargs_double_value = extargs_double_default;

	extargs_int_set = nullptr;
	extargs_string_set = nullptr;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
 ***************************************************************************/
args_analyse_tools::~args_analyse_tools()
{
	if (this->extargs_int_set != nullptr) {
		delete []extargs_int_set;
		
	}
	if (this->extargs_double_set != nullptr) {
		delete[]extargs_double_set;
	}
	if (this->extargs_string_set != nullptr) {
		delete[]extargs_string_set;
	}
}

/* ---------------------------------------------------------------
	 允许AAT中自定义成员函数的实现（private）
   ---------------------------------------------------------------- */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_name() const
{
	return this->args_name;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：加!!后，只能是0/1
			已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::existed() const
{
	return !!this->args_existed;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const int args_analyse_tools::get_int() const
{
	return this->extargs_int_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const double args_analyse_tools::get_double() const
{
	return this->extargs_double_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const string args_analyse_tools::get_string() const
{
	return this->extargs_string_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：已实现，不要动
 ***************************************************************************/
const unsigned int args_analyse_tools::get_ipaddr() const
{
	return this->extargs_ipaddr_value;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：将 extargs_ipaddr_value 的值从 0x7f000001 转为 "127.0.0.1"
 ***************************************************************************/
const string args_analyse_tools::get_str_ipaddr() const
{
	int num[4] = { 0 };
	
	unsigned char* ptr = (unsigned char*)(&extargs_ipaddr_value);
	for (int j = 0; j < sizeof(int); j++) {
		num[j] = ptr[j];
	}
	ostringstream ss;
	ss << num[3] << "." << num[2] << "." << num[1] << "." << num[0];
	return ss.str(); //此句根据需要修改
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：follow_up_args：是否有后续参数
			0  ：无后续参数
			1  ：有后续参数
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_process(const int argc, const char* const *const argv, args_analyse_tools* const args, const int follow_up_args)
{
	int cur_args = 1;
	if (argc == 1) {
		return cur_args;
	}
	for (int i = 1; i < argc; i++) {
		int src;
		for (src= 0; args[src].args_name != ""; src++) { // 这里假设 args_name 为空字符串时终止
			if (strcmp(argv[i], args[src].args_name.c_str()) == 0) { // 使用 c_str() 将 std::string 转换为 const char*
				break;
			}
			
		}
		//处理参数名字
		if (args[src].args_name == "") {
		
			if (follow_up_args) {
				return cur_args;
			}
			else {
				if (argv[i][0] != '-' || argv[i][1] != '-') {
					cout << "参数[" << argv[i] << "]格式非法(不是--开头的有效内容)." << endl;
					
				}
				else {
					cout << "参数[" << argv[i] << "]非法." << endl;
				}
				return -1;
			}
		}
		if (args[src].args_existed) {
			cout << "参数[" << argv[i] << "]重复." << endl;
			return -1;
		}
		//处理参数数字 可变参数不考虑
		if (args[src].extargs_type==ST_EXTARGS_TYPE::boolean) {
			args[src].args_existed = 1;
			cur_args++;
			
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_default) {
			
			args[src].args_existed = 1;
			cur_args++;
			
			if (i==argc-1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 范围[" << args[src].extargs_int_min << ".." << args[src].extargs_int_max << "] ";
				cout<<"缺省:"<< args[src].extargs_int_default <<")"<< endl;
				return -1;
			}
			if (argv[i + 1][0] == '-'&& argv[i + 1][1]=='-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:int, 范围[" << args[src].extargs_int_min << ".." << args[src].extargs_int_max << "] ";
				cout << "缺省:" << args[src].extargs_int_default << ")" << endl;
				return -1;
			}
			int ret=checknum(argv[i + 1]);
			if (!ret) {
				cout<< "参数["<<argv[i]<<"的附加参数不是整数. (类型:int, 范围[" << args[src].extargs_int_min << ".." << args[src].extargs_int_max << "] ";
				cout << "缺省:" << args[src].extargs_int_default << ")" << endl;
				return -1;
			}
			int num = stoi(argv[i + 1]);

			if (num >= args[src].extargs_int_min && num <= args[src].extargs_int_max) {
					args[src].extargs_int_value = num;
			}
			else {
					args[src].extargs_int_value = args[src].extargs_int_default;
			}
				
				
		    cur_args++;
			i = i + args[src].extargs_num;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
			args[src].args_existed = 1;
			cur_args++;

			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, 范围[" << args[src].extargs_int_min << ".." << args[src].extargs_int_max << "])" << endl;
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:int, 范围[" << args[src].extargs_int_min << ".." << args[src].extargs_int_max << "])" << endl;
				return -1;
			}
			int ret = checknum(argv[i + 1]);
			if (!ret) {
				cout << "参数[" << argv[i] << "的附加参数不是整数. (类型:int, 范围[" << args[src].extargs_int_min << ".." << args[src].extargs_int_max << "])" << endl;
				return -1;
			}
				
				int num = stoi(argv[i + 1]);
				if (num >= args[src].extargs_int_min && num <= args[src].extargs_int_max) {
					args[src].extargs_int_value = num;
				}
				else {
					cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:int, 范围[" << args[src].extargs_int_min << ".." << args[src].extargs_int_max << "])" << endl;
						return -1;
				}


			cur_args++;
			i = i + args[src].extargs_num;
			
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {
			args[src].args_existed = 1;
			cur_args++;
		
			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, ";
				printintset(args[src].extargs_int_set, true, args[src].extargs_int_default);
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:int, ";
				printintset(args[src].extargs_int_set, true, args[src].extargs_int_default);
				return -1;
			}
			int ret = checknum(argv[i + 1]);
			if (!ret) {
				cout << "参数[" << argv[i] << "的附加参数不是整数. (类型:int, ";
				printintset(args[src].extargs_int_set, true, args[src].extargs_int_default);

				return -1;
			}

				int num = stoi(argv[i + 1]);
				int count;
				for (count = 0; args[src].extargs_int_set[count]!= INVALID_INT_VALUE_OF_SET;count++) {
					if (args[src].extargs_int_set [count] == num)
						break;
				}
				if (args[src].extargs_int_set[count] == INVALID_INT_VALUE_OF_SET) {
					args[src].extargs_int_value = args[src].extargs_int_default;
				}
				else {
					args[src].extargs_int_value = num;
				}

            cur_args++;
			i = i + args[src].extargs_num;

		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
			args[src].args_existed = 1;
			cur_args++;
			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:int, ";
				printintset(args[src].extargs_int_set, false, args[src].extargs_int_default);
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:int, ";
				printintset(args[src].extargs_int_set, false, args[src].extargs_int_default);
				return -1;
			}
			int ret = checknum(argv[i + 1]);
			if (!ret) {
				cout << "参数[" << argv[i] << "的附加参数不是整数. (类型:int, ";
				printintset(args[src].extargs_int_set, false, args[src].extargs_int_default);

				return -1;
			}
				int num = stoi(argv[i + 1]);
				int count;
				for (count = 0; args[src].extargs_int_set[count] != INVALID_INT_VALUE_OF_SET; count++) {
					if (args[src].extargs_int_set[count] == num)
						break;
				}
				if (args[src].extargs_int_set[count] == INVALID_INT_VALUE_OF_SET) {
					cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:int, " ;
					printintset(args[src].extargs_int_set, false, args[src].extargs_int_default);
					
					return -1;
				}
				else {
					args[src].extargs_int_value = num;
				}

				cur_args++;
				i = i + args[src].extargs_num;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_default) {
			args[src].args_existed = 1;
			cur_args++;

			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:double, 范围[" << args[src].extargs_double_min << ".." << args[src].extargs_double_max << "] ";
				cout << "缺省:" << args[src].extargs_double_default << ")" << endl;
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:double, 范围[" << args[src].extargs_double_min << ".." << args[src].extargs_double_max << "] ";
				cout << "缺省:" << args[src].extargs_double_default << ")" << endl;
				return -1;
			}
			int ret = checknum(argv[i + 1]);
			if (!ret) {
				cout << "参数[" << argv[i] << "]的附加参数不是浮点数. (类型:double, 范围[" << args[src].extargs_double_min << ".." << args[src].extargs_double_max << "] ";
				cout << "缺省:" << args[src].extargs_double_default << ")" << endl;
				return -1;
			}
		
				

				double num = stod(argv[i + 1]);
				if (num >= args[src].extargs_double_min && num <= args[src].extargs_double_max) {
					args[src].extargs_double_value = num;
				}
				else {
					args[src].extargs_double_value = args[src].extargs_double_default;
				}


				cur_args++;
			i = i + args[src].extargs_num;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_error) {
			args[src].args_existed = 1;
			cur_args++;

			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:double, 范围[" << args[src].extargs_double_min << ".." << args[src].extargs_double_max << "])" << endl;
				
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:double, 范围[" << args[src].extargs_double_min << ".." << args[src].extargs_double_max << "])"<<endl;
				
				return -1;
			}
			int ret = checknum(argv[i + 1]);
			if (!ret) {
				cout << "参数[" << argv[i] << "]的附加参数不是浮点数. (类型:double, 范围[" << args[src].extargs_double_min << ".." << args[src].extargs_double_max << "])"<<endl;
			
				return -1;
			}
			
				

				double num = stod(argv[i +1]);
				if (num >= args[src].extargs_double_min && num <= args[src].extargs_double_max) {
					args[src].extargs_double_value = num;
				}
				else {
					cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i +1] << ")非法. (类型:double, 范围[";
					
					cout<< args[src].extargs_double_min << ".." << args[src].extargs_double_max << "])" << endl;
					return -1;
				}


				cur_args++;
			i = i + args[src].extargs_num;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_default) {
			args[src].args_existed = 1;
			cur_args++;
			
			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:double, ";
				printdoubleset(args[src].extargs_double_set, true, args[src].extargs_double_default);
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:double, ";
				printdoubleset(args[src].extargs_double_set, true, args[src].extargs_double_default);

				return -1;
			}
			int ret = checknum(argv[i + 1]);
			if (!ret) {
				cout << "参数[" << argv[i] << "的附加参数不是浮点数. (类型:double, ";
				printdoubleset(args[src].extargs_double_set, true, args[src].extargs_double_default);

				return -1;
			}

				double num = stod(argv[i + 1]);
				int count;
				for (count = 0; args[src].extargs_double_set[count] != INVALID_DOUBLE_VALUE_OF_SET; count++) {
					if (args[src].extargs_double_set[count] == num)
						break;
				}
				if (args[src].extargs_double_set[count] == INVALID_DOUBLE_VALUE_OF_SET) {
					args[src].extargs_double_value = args[src].extargs_double_default;
				}
				else {
					args[src].extargs_double_value = num;
				}


				cur_args++;
			i = i + args[src].extargs_num;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
			args[src].args_existed = 1;
			cur_args++;

			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:double, ";
				printdoubleset(args[src].extargs_double_set,false, args[src].extargs_double_default);
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:double, ";
				printdoubleset(args[src].extargs_double_set, false, args[src].extargs_double_default);

				return -1;
			}
			int ret = checknum(argv[i + 1]);
			if (!ret) {
				cout << "参数[" << argv[i] << "的附加参数不是浮点数. (类型:double, ";
				printdoubleset(args[src].extargs_double_set,false, args[src].extargs_double_default);

				return -1;
			}
				

				double num = stod(argv[i +1]);
				int count;
				for (count = 0; args[src].extargs_double_set[count] != INVALID_DOUBLE_VALUE_OF_SET; count++) {
					if (args[src].extargs_double_set[count] == num)
						break;
				}
				if (args[src].extargs_double_set[count] == INVALID_DOUBLE_VALUE_OF_SET) {
					cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:double, ";
					printdoubleset(args[src].extargs_double_set, false, args[src].extargs_double_default);

					return -1;
				}
				else {
					args[src].extargs_double_value = num;
				}



				cur_args++;
			i = i + args[src].extargs_num;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::str) {
			args[src].args_existed = 1;
			cur_args++;

			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string";
				if (args[src].extargs_string_default != "") {
					cout << " 缺省:" << args[src].extargs_string_default;

				}
				cout << ")" << endl;
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:string";
				if (args[src].extargs_string_default != "") {
					cout << " 缺省:" << args[src].extargs_string_default;

				}
				cout << ")" << endl;
				return -1;
			}
			
			
			args[src].extargs_string_value = argv[i + 1];

			cur_args++;
			i = i + args[src].extargs_num;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) {
			args[src].args_existed = 1;
			cur_args++;

			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string, ";

				printstrset(args[src].extargs_string_set, true, args[src].extargs_string_default);
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:string, ";
				printstrset(args[src].extargs_string_set, true, args[src].extargs_string_default);

				return -1;
			}
			int count;
			for (count = 0; args[src].extargs_string_set[count] != ""; count++) {
				if (strcmp(args[src].extargs_string_set[count].c_str(), argv[i + 1]) == 0) {

					break;
				}
					
			}
			if (args[src].extargs_string_set[count] == "") {
				args[src].extargs_string_value = args[src].extargs_string_default;
			}
			else {
				args[src].extargs_string_value = argv[i + 1];
			}

			cur_args++;
			i = i + args[src].extargs_num;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
			args[src].args_existed = 1;
			cur_args++;

			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:string, ";

				printstrset(args[src].extargs_string_set, false, args[src].extargs_string_default);
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:string, ";
				printstrset(args[src].extargs_string_set, false, args[src].extargs_string_default);

				return -1;
			}
			int count;
			for (count = 0; args[src].extargs_string_set[count] != ""; count++) {
				if (strcmp(args[src].extargs_string_set[count].c_str(), argv[i + 1]) == 0) {

					break;
				}

			}
			if (args[src].extargs_string_set[count] == "") {
				cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:string, ";
				printstrset(args[src].extargs_string_set, false, args[src].extargs_string_default);
				return -1;
			}
			else {
				args[src].extargs_string_value = argv[i + 1];
			}

			cur_args++;
			i = i + args[src].extargs_num;


		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
			args[src].args_existed = 1;
			cur_args++;

			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:IP地址 ";
				cout << "缺省:";
				string def = uttostr(args[src].extargs_ipaddr_default);
				cout << def << ")" << endl;
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:IP地址 ";
				cout << "缺省:";
				string def = uttostr(args[src].extargs_ipaddr_default);
				cout << def << ")" << endl;


				return -1;
			}
			if (checkip(argv[i + 1])) {
				args[src].extargs_ipaddr_value = strtout(argv[i + 1]);
			}
			else {
				args[src].extargs_ipaddr_value = args[src].extargs_ipaddr_default;
			}

			cur_args++;
			i = i + args[src].extargs_num;


		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {

			args[src].args_existed = 1;
			cur_args++;

			if (i == argc - 1) {
				cout << "参数[" << argv[i] << "]的附加参数不足. (类型:IP地址)"<<endl;
				
				return -1;
			}
			if (argv[i + 1][0] == '-' && argv[i + 1][1] == '-') {
				cout << "参数[" << argv[i] << "]缺少附加参数. (类型:IP地址)"<<endl;
				


				return -1;
			}
			if (checkip(argv[i + 1])) {
				args[src].extargs_ipaddr_value = strtout(argv[i + 1]);
			}
			else {
				cout << "参数[" << argv[i] << "]的附加参数值(" << argv[i + 1] << ")非法. (类型:IP地址)"<<endl;
				return -1;
			}

			cur_args++;
			i = i + args[src].extargs_num;



		}
	}

	return cur_args;


	
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：友元函数
***************************************************************************/
int args_analyse_print(const args_analyse_tools* const args)
{
	size_t max_name = 4;//标题名字
	int width_name = 0;
	for (int src = 0; args[src].args_name != ""; src++) {
		if (args[src].args_name.size()>max_name) {
			max_name = args[src].args_name.size();
		}
	}
	width_name = max_name + 1;

	size_t max_type = 0;

	for (int src = 0; args[src].args_name != ""; src++) {
		size_t ret = len(args[src].extargs_type);
		if ( ret> max_type) {
			max_type=ret;
		}
	
	}


	int width_type = max_type + 1;


	
	size_t max_def = 8;
	int width_def = 8;//最小的情况 doubledef
	for (int src = 0; args[src]. args_name!= ""; src++) {
		if (args[src].extargs_type==ST_EXTARGS_TYPE::str|| args[src].extargs_type==ST_EXTARGS_TYPE::str_with_set_default
			) {
			if (args[src].extargs_string_default.size() > max_def) {
				max_def = args[src].extargs_string_default.size();
			}

		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
			if (uttostr(args[src].extargs_ipaddr_default).size()> max_def) {
				max_def = uttostr(args[src].extargs_ipaddr_default).size();
			}
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_default) {
			char double_def[100];
			size_t length=sprintf(double_def, "%.6lf", args[src].extargs_double_default);
			if (length > max_def) {
				max_def = length;
			}


		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {
			char int_def[100];
			size_t length=sprintf(int_def, "%d", args[src].extargs_int_default);
			if (length > max_def) {
				max_def =length;
			}

		}
	}
	width_def = max_def + 1;

	int width_exist = 6+1;

	int width_value = 0;
	size_t max_value = 5;

	for (int src = 0; args[src].args_name != ""; src++) {
		if (args[src].args_existed == 0)
			continue;

		if (args[src].extargs_type == ST_EXTARGS_TYPE::str || args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_default||
			args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
			if (args[src].extargs_string_value.size() > max_value) {
				max_value = args[src].extargs_string_value.size();
			}

		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::boolean) {
			if (4> max_value) {//true
				max_value = 4;
			}
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default|| args[src].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
			if (uttostr(args[src].extargs_ipaddr_value).size() > max_value) {
				max_value = uttostr(args[src].extargs_ipaddr_value).size();
			}
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_default
			|| args[src].extargs_type == ST_EXTARGS_TYPE::double_with_error|| args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
			char double_value[100];
			size_t length=sprintf(double_value, "%.6lf", args[src].extargs_double_value);
			if (length> max_value) {
				max_value =length;
			}


		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_default
			|| args[src].extargs_type == ST_EXTARGS_TYPE::int_with_error|| args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
			char int_value[100];
			size_t length=sprintf(int_value, "%d", args[src].extargs_int_value);
			if (length > max_value) {
				max_value = length;
			}

		}

	}
	width_value = max_value + 1;

	size_t max_range = 9;
	int width_range = 0;
	for (int src = 0; args[src].args_name != ""; src++) {
		
		if ( args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_default ||
			args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
			size_t length = 0;
			int i = 0;
			for (i = 0; args[src].extargs_string_set[i] != ""; i++) {
				length += args[src].extargs_string_set[i].size();
			}
			length = length + i-1;//加上/分隔符
			if (length > max_range)
				max_range = length;

		}
		
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_error ) {
			size_t length = 0;
			int i = 0;
			for ( i = 0; args[src].extargs_double_set[i] != INVALID_DOUBLE_VALUE_OF_SET; i++) {
				char double_value[100];
				length+= sprintf(double_value, "%.6lf", args[src].extargs_double_set[i]);

			}
			length = length +i-1;
			if (length > max_range)
				max_range = length;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {
			size_t length = 0;
			int i = 0;
			for ( i = 0; args[src].extargs_int_set[i] != INVALID_INT_VALUE_OF_SET; i++) {
				char int_value[100];
				length += sprintf(int_value, "%d", args[src].extargs_int_set[i]);

			}
			length = length + i- 1;
			if (length > max_range)
				max_range = length;

		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::int_with_error) {
			size_t length = 0;
			char int_value[100];
			length += sprintf(int_value, "%d", args[src].extargs_int_min);
			length+= sprintf(int_value, "%d", args[src].extargs_int_max);
			length = length + 4;//两个dot两个方括号
			if (length > max_range)
				max_range = length;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::double_with_error) {
			size_t length = 0;
			char double_value[100];
			length += sprintf(double_value, "%.6lf", args[src].extargs_double_min);
			length += sprintf(double_value, "%.6lf", args[src].extargs_double_max);
			length = length + 4;//两个dot两个方括号
			if (length > max_range)
				max_range = length;
		}
	

	}
	width_range = max_range + 1;

	//以下是打印部分
	//标题栏
	cout << setw(width_name + width_type + width_exist+width_def+ width_value+ width_range+1) << setfill('=') << '=' << setfill(' ') << endl;
	cout << left;
	cout << " " << setw(width_name) << "name";
	cout << setw(width_type) << "type";
	cout << setw(width_def) << "default";
	cout << setw(width_exist) << "exists";
	cout << setw(width_value) << "value";
	cout << setw(width_range) << "range/set" << endl;
	cout << setw(width_name + width_type + width_exist + width_def + width_value + width_range + 1) << setfill('=') << '=' << setfill(' ') << endl;

	int src;
	for (src = 0; args[src].args_name != ""; src++) {
		//name
		cout << left;
		cout << " " <<setw(width_name)<< args[src].args_name;
		//type
		
		print_type(args[src].extargs_type,width_type);
		//def
		
		if (args[src].extargs_type == ST_EXTARGS_TYPE::boolean) {
			if (args[src].extargs_bool_default == 1)
				cout << setw(width_def) << "true";
			else
				cout << setw(width_def) << "false";
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_default|| args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_default) {

			cout << setw(width_def) << args[src].extargs_int_default;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_default|| args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_default) {
			cout << setw(width_def) <<fixed << setprecision(6) <<args[src].extargs_double_default;
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::str|| args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_default) {
			if (args[src].extargs_type == ST_EXTARGS_TYPE::str && args[src].extargs_string_default == "") {
				cout << setw(width_def) << "/";
			}
			else {
				cout << setw(width_def) << args[src].extargs_string_default;
			}
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default) {
			cout << setw(width_def) << uttostr(args[src].extargs_ipaddr_default);
		}
		else {
			cout << setw(width_def) << "/";
		}
		//exist&value
		cout << left;
		if (args[src].args_existed) {
			cout << setw(width_exist) << "1";
			if (args[src].extargs_type == ST_EXTARGS_TYPE::boolean) {
				
				cout << setw(width_value) << "true";
				
			}
			else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_default
				|| args[src].extargs_type == ST_EXTARGS_TYPE::int_with_error|| args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {

				cout << setw(width_value) << args[src].extargs_int_value;
			}
			else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::double_with_error 
				||args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_default||args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {
				cout << setw(width_value) << fixed << setprecision(6) << args[src].extargs_double_value;
			}
			else if (args[src].extargs_type == ST_EXTARGS_TYPE::str || args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_default
				|| args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
				cout << setw(width_value) << args[src].extargs_string_value;
			}
			else if (args[src].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_default|| args[src].extargs_type == ST_EXTARGS_TYPE::ipaddr_with_error) {
				cout << setw(width_value) << uttostr(args[src].extargs_ipaddr_value);
			}
			else {
				cout << setw(width_value) << "/";
			}


		}
		else {
			
			cout << setw(width_exist) << "0";
			
			cout << setw(width_value) << "/";
		}
		//range&set
		cout << left;
		
		if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::int_with_error ) {
			 cout <<  "[" << args[src].extargs_int_min << ".." << args[src].extargs_int_max << "]";
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_default || args[src].extargs_type == ST_EXTARGS_TYPE::double_with_error) {
			cout << fixed << setprecision(6) << "[" << args[src].extargs_double_min << ".." << args[src].extargs_double_max << "]";
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_default|| args[src].extargs_type == ST_EXTARGS_TYPE::str_with_set_error) {
			
			for (int i = 0; args[src].extargs_string_set[i] != ""; i++) {
				cout << args[src].extargs_string_set[i];
				if (args[src].extargs_string_set[i + 1] != "")
					cout << "/";
			}
			
		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_default || args[src].extargs_type == ST_EXTARGS_TYPE::int_with_set_error) {

			for (int i = 0; args[src].extargs_int_set[i] != INVALID_INT_VALUE_OF_SET; i++) {
				cout << args[src].extargs_int_set[i];
				if (args[src].extargs_int_set[i + 1] != INVALID_INT_VALUE_OF_SET)
					cout << "/";
			}

		}
		else if (args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_default || args[src].extargs_type == ST_EXTARGS_TYPE::double_with_set_error) {

			for (int i = 0; args[src].extargs_double_set[i] != INVALID_DOUBLE_VALUE_OF_SET; i++) {
				cout << args[src].extargs_double_set[i];
				if (args[src].extargs_double_set[i + 1] != INVALID_DOUBLE_VALUE_OF_SET)
					cout << "/";
			}

		}
		else {
			cout << "/";
		}




		cout << endl;
	}
	//结束内容
	//下栏线
	cout << setw(width_name + width_type + width_exist + width_def + width_value + width_range + 1) << setfill('=') << '=' << setfill(' ') << endl;
	cout << endl;




	cout << defaultfloat;

	return 0; //此句根据需要修改
}

#endif // !ENABLE_LIB_COMMON_TOOLS
