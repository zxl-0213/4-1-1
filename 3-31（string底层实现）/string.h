#define _CRT_SECURE_NO_WARNINGS 1;

#pragma once
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
#include<stdio.h>
//�򵥵�stringʵ�֣��������캯���������������������캯����

namespace zxl //�Լ�����һ�������ռ䣬��Ϊc++������string�������Լ��������ռ䷽������
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

		//���캯��  
		string(const char* str = "")
			:_str(new char[strlen(str) + 1])//��1����ΪҪ��һ��λ�ø�\0��
		{
			strcpy(_str, str);
		}

		//��������,�����
		string(const string& s)
			:_str(new char[strlen(s._str)+1])//���ԭ������һ��һ���Ŀռ䣬Ȼ��ָ��ָ��Ϳ�����
		{
			strcpy(_str, s._str);
		}

		//��ֵ���������,Ҳ�����������
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

		//��������
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

		//��c������ʽ���
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


//��ɾ�Ĳ�
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
		//������
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
			_str[_size] = '\0';//����������Ӧ����\0������
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

		//����һ���ַ�
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

		//����һ���ַ���
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

		//ɾ���ַ�
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

		//����һ���ַ�
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
		//����һ���ַ���
		size_t find(const size_t pos, const char* str)
		{
			char* tmp = strstr(_str, str);
			if (tmp != nullptr)
			{
				return tmp - _str;
			}
			return std::string::npos;
		}

		//����<(s1<s2)
		bool operator<(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret < 0;
		}
		//����=��s1==s2��
		bool operator==(const string& s)
		{
			int ret = strcmp(_str, s._str);
			return ret == 0;
		}
		//����>(s1>s2)
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
	
	//�������
	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i=0; i < s.size(); ++i)
		{
			
			cout << s[i];
		}
		return out;
	}

	//��������getlineҲ��������ֻ����if�б����������в�ͣ
	istream& operator>>(istream& in, string& s)
	{
		char ch;
		ch = in.get();//get�ǻ�ȡ�ַ���
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
	//���ֱ���
	void string_text1()
	{
		string s1("hello");
		string s2(s1);
		string s3;
		s3 = s1;
		cout << s3 << endl;
		//��һ�ֱ���
		for (size_t i=0; i < s2.size(); ++i)
		{
			s2[i] += 1;
			cout << s2[i]<<" ";
		}
		cout << endl;
		//�ڶ��ֱ���
		string::iterator it = s2.begin();
		while (it != s2.end())
		{
			*it -= 1;
			cout << *it << " ";
			it++;
		}
		cout << endl;
		//��Χfor
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

	//insert��resize��erase
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

//�ô�ͳ����д��ʵ��string�ļ򵥹����磺���졢��������������ֵ��
namespace zxl3
{
	class string
	{
	public:
		//���캯��
		string(const char* str = "")
			:_str(new char[strlen(str)+1])
		{
			strcpy(_str, str);
		}
		//��������(��ͳд��)���Լ��������Լ�����
		//string s2(s3)
		/*string(const string& s)
			:_str(new char[strlen(s._str)+1])
		{
			strcpy(_str, s._str);
		}*/
		//����������д��
		//˼��������ñ��������죬Ȼ����ȡ��ɹ�
		//Ҳ���Ǳ�Ķ����죬Ȼ�󽻻���ֵ
		//string s1(s2)
		string(const string& s)
			:_str(nullptr)
		{
			string tmp(s._str);
			swap(_str, tmp._str);
		}
		//���ظ�ֵ����ͳд����
		//s1 = s3;
		/*string& operator=(const string& s)
		{
			char* tmp = new char[strlen(s._str) + 1];
			strcpy(tmp, s._str);
			delete[]_str;
			_str = tmp;
			return *this;
		}*/
		//��д���ĸ�ֵ
		string& operator=(const string& s)
		{
			string tmp(s._str);
			swap(_str, tmp._str);
			return *this;
		}
		//��������
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
