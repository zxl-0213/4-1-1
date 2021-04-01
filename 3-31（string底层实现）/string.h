#define _CRT_SECURE_NO_WARNINGS 1;

#pragma once
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
#include<stdio.h>
//简单的string实现；包括构造函数、析构函数、拷贝构造函数。

namespace zxl //自己开辟一块命名空间，因为c++库中有string变量，自己开命名空间方便区分
{
	class string
	{
	public:
		/*string()
			:_str(new char[1])
		{
			_str[0] = '\0';
		}
		string(const char* str)
			:_str(new char[strlen(str) + 1])
		{
			strcpy(_str, str);
		}*/

		//构造函数  
		string(const char* str = "")
			:_str(new char[strlen(str) + 1])//加1是因为要留一个位置给\0；
		{
			strcpy(_str, str);
		}

		//拷贝构造,深拷贝。
		string(const string& s)
			:_str(new char[strlen(s._str)+1])//深拷贝原理：拷贝一块一样的空间，然后指针指向就可以了
		{
			strcpy(_str, s._str);
		}

		//赋值运算符重载,也是利用深拷贝。
		string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* tmp = new char[strlen(s._str) + 1];
				delete[]_str;
				strcpy(tmp,s._str);
				_str = tmp;
			}
			return *this;
		}

		//析构函数
		~string()
		{
			delete[]_str;
			_str = nullptr;
		}
		int size()
		{
			return strlen(_str);
		}
		char& operator[](size_t i)
		{
			return _str[i];
		}

		//以c语言形式输出
		char* c_str()
		{
			return _str;
		}
	private:
		char* _str;
	};
	void string_text1()
	{
		string s1("hello");
		string s2;
		for (size_t i = 0; i < s1.size(); ++i)
		{
			s1[i] += 1;
			cout << s1[i] << " ";
		}
		cout << endl;
		for (size_t i = 0; i < s2.size(); ++i)
		{
			s2[i] += 1;
			cout << s2[i] << " ";
		}
		cout << endl;
	}

	void string_text2()
	{
		string s1("hello");
		string s2(s1);
		string s3;
		s3 = s1;
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		cout << s3.c_str() << endl;
	}
}


//增删改查
namespace zxl2
{
	class string
	{
	public:
		string(const char* str = "")
		{
			_str = new char[strlen(str) + 1];
			_size = strlen(str);
			_capacity = _size;
			strcpy(_str, str);
		}

		string(const string& s)
			:_str(new char[s._size+1])
		{
			_size = s._size;
			_capacity = s._capacity;
			strcpy(_str, s._str);
		}

		~string()
		{
			delete[]_str;
			_str = nullptr;
			_capacity = _size = 0;
		}

		size_t size()const //==size_t size(char* str)
		{
			return _size;
		}
		size_t capacity()
		{
			return _capacity;
		}
		char& operator[](size_t i)
		{
			assert(i < _size);
			return _str[i];
		}
		const char& operator[](size_t i)const
		{
			assert(i < _size);
			return _str[i];
		}
		char* c_str()
		{
			return _str;
		}
		string& operator=(const string& s)
		{
			char* tmp = new char[s._size + 1];
			strcpy(tmp, s._str);
			delete[]_str;
			_size = s._size;
			_capacity = s._capacity;
			_str = tmp;
			return *this;
		}
		//迭代器
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}

		void reserve(const size_t n)
		{
			if (n > _capacity)
			{
				char* newstr = new char[n + 1];
				strcpy(newstr, _str);
				delete[]_str;
				_str = newstr;
				_capacity = n;
			}
		}

		void resize(const size_t n, const char ch = '\0')
		{
			if (n < _size)
			{
				_str[_size] = '\0';
				_size = n;
			}
			else
			{
				if (n > _capacity)
				{
					reserve(n);
				}
				size_t end = _size;
				for (size_t i = end; i < n; ++i)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[n] = '\0';
			}
		}
		void push_back(const char ch)
		{
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			_size++;
			_str[_size] = '\0';//插入后的数组应该有\0结束。
		}

		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				size_t newcapacity = _size + len;
				reserve(_size + len);
			}
			strcpy(_str + _size, str);
			_size += len;
		}

		string& operator+=(const char ch)
		{
			this->push_back(ch);
			return *this;
		}
		string& operator+=(const char* str)
		{
			this->append(str);
			return *this;
		}

		//插入一个字符
		string& insert(const size_t pos,const char ch)
		{
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapacity);
			}
			size_t end = _size;
			while (end >= pos)
			{
				_str[end + 1] = _str[end];
				end--;
			}
			_str[pos] = ch;
			_size++;
			return *this;
		}

		//插入一个字符串
		string& insert(const size_t pos, const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);

			}
			size_t end = _size;
			while (end >= pos)
			{
				_str[end+len] = _str[end];
				end--;
			}
			strncpy(_str+pos, str, len);
			_size += len;

			return *this;
		}

		//删除字符
		void erase( size_t pos, const size_t len = std::string::npos)
		{
			if (len > (_size - pos))
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				size_t end = _size;
				size_t i = pos + len;
				while (i <= end)
				{
					_str[pos] = _str[i];
					pos++;
					i++;
				}
				_size -= len;
			}
		}

		//查找一个字符
		size_t find(const size_t pos, const char ch)
		{
			for (size_t i=pos; i < _size; ++i)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}
			return std::string::npos;

		}
		//查找一个字符串
		size_t find(const size_t pos, const char* str)
		{
			char* tmp = strstr(_str, str);
			if (tmp != nullptr)
			{
				return tmp - _str;
			}
			return std::string::npos;
		}

		//重载<(s1<s2)
		bool operator<(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret < 0;
		}
		//重载=（s1==s2）
		bool operator==(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret == 0;
		}
		//重载>(s1>s2)
		bool operator>(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret > 0;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	
	//输出重载
	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i=0; i < s.size(); ++i)
		{
			
			cout << s[i];
		}
		return out;
	}

	//输入重载getline也是这样，只不过if判别是遇到换行才停
	istream& operator>>(istream& in, string& s)
	{
		char ch;
		ch = in.get();//get是获取字符，
		while (1)
		{
			if (ch == ' ' || ch == '\n')
			{
				break;
			}
			else
			{
				s += ch;
			}
		}
		return in;
	}
	//三种遍历
	void string_text1()
	{
		string s1("hello");
		string s2(s1);
		string s3;
		s3 = s1;
		cout << s3 << endl;
		//第一种遍历
		for (size_t i=0; i < s2.size(); ++i)
		{
			s2[i] += 1;
			cout << s2[i]<<" ";
		}
		cout << endl;
		//第二种遍历
		string::iterator it = s2.begin();
		while (it != s2.end())
		{
			*it -= 1;
			cout << *it << " ";
			it++;
		}
		cout << endl;
		//范围for
		for (auto e : s2)
		{
			e += 3;
			cout << e << " ";
		}
	}
	void string_text2()
	{
		string s1;
		string s2("hello");
		s2.push_back(' ');
		s2.push_back('w');
		s2.push_back('o');
		cout << s2 <<endl;

		s2.append("rld****");
		cout << s2 << endl;

		s1 += "hello";
		s1 += ' ';
		s1 += "world";
		cout << s1 << endl;

	}

	//insert，resize，erase
	void string_text3()
	{
		string s1("hello");
		s1.insert(1, 'x');
		s1.insert(3, 'z');
		cout << s1 << endl;
		s1.insert(1, "world");
		cout << s1 << endl;

		string s2("hello");
		cout << s2.size() << endl;
		s2.resize(2);
		cout << s2 << endl;
		cout << s2.size() << endl;

		s2.resize(8,'x');
		cout << s2 << endl;
		cout << s2.size() << endl;

		string s3("helloworld");
		s3.erase(2, 2);
		cout << s3 << endl;
		s3.erase(2, 10);
		cout << s3 << endl;
		string s4;
		cin >> s4;
		cout << s4;
	}
	void string_text4()
	{
		string s1("helloworld");
		string s2("helll");
		cout << (s1 > s2) << endl;
		cout << (s1 == s2) << endl;

	}
}

//用传统和新写法实现string的简单功能如：构造、析构、拷贝、赋值。
namespace zxl3
{
	class string
	{
	public:
		//构造函数
		string(const char* str = "")
			:_str(new char[strlen(str)+1])
		{
			strcpy(_str, str);
		}
		//拷贝构造(传统写法)，自己拷贝，自己复制
		//string s2(s3)
		/*string(const string& s)
			:_str(new char[strlen(s._str)+1])
		{
			strcpy(_str, s._str);
		}*/
		//拷贝构造新写法
		//思想就是利用别人来构造，然后窃取其成果
		//也就是别的对象构造，然后交换其值
		//string s1(s2)
		string(const string& s)
			:_str(nullptr)
		{
			string tmp(s._str);
			swap(_str, tmp._str);
		}
		//重载赋值（传统写法）
		//s1 = s3;
		/*string& operator=(const string& s)
		{
			char* tmp = new char[strlen(s._str) + 1];
			strcpy(tmp, s._str);
			delete[]_str;
			_str = tmp;
			return *this;
		}*/
		//新写法的赋值
		string& operator=(const string& s)
		{
			string tmp(s._str);
			swap(_str, tmp._str);
			return *this;
		}
		//析构函数
		~string()
		{
			delete[]_str;
			_str = nullptr;
		}

		size_t size()
		{
			return strlen(_str);
		}
		char operator[](const size_t i)
		{
			return _str[i];
		}
	private:
		char* _str;
	};
	void string_text()
	{
		string s1("hello");
		string s2("world");
		string s3(s2);
		for (size_t i = 0; i < s1.size(); ++i)
		{
			cout << s1[i] << " ";

		}
		cout << endl;
		s1 = s2;
		for (size_t i = 0; i < s2.size(); ++i)
		{
			cout << s2[i] << " ";

		}
		cout << endl;
		for (size_t i = 0; i < s3.size(); ++i)
		{
			cout << s3[i] << " ";

		}
		cout << endl;
	}
}
