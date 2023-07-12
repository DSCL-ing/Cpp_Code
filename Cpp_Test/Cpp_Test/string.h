#pragma once

#include<string.h>

namespace test{

	class string {
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	public:
		string()
			:_str(new char[1])
			, _size(0)
			, _capacity(0)
		{
			_str[0] = '\0';
		}

		string(const char* s)
			:_size(strlen(s))
		{
			_capacity = _size;
			_str = new char[_capacity + 1];
		}
		~string()
		{
			delete[] _str;
			_size = _capacity = 0;
		}


		
	};




}
