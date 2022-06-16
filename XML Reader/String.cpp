#include "String.h"
#include<cstring>

static bool started_new_tag = false;

void String::Free()
{
	delete[] this->data;
}
String::String(const char* data)
{
	this->size = strlen(data);
	this->data = new char[this->size + 1];
	strcpy_s(this->data, this->size + 1, data);
}
String::String(const String& other)
{
	this->size = other.GetSize();
	this->data = new char[this->size + 1];
	strcpy_s(this->data, this->size + 1, other.GetData());
}
String::~String()
{
	this->Free();
}

char* String::GetData() const
{
	return this->data;
}
int String::GetSize() const
{
	return this->size;
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		Free();
		this->size = other.GetSize();
		this->data = new char[this->size + 1];
		strcpy_s(this->data, other.GetSize() + 1, other.GetData());
	}
	return *this;
}

String String::operator+(const String& other)
{
	String copy(*this);
	copy += other;
	return copy;

}
String& String::operator+=(const String& other)
{
	char* data = new char[this->size + 1];
	strcpy_s(data, this->size + 1, this->data);
	this->Free();
	this->data = new char[this->size + other.GetSize() + 1];
	strcpy_s(this->data, this->size + 1, data);
	delete[] data;
	this->size += other.GetSize();
	strcat_s(this->data, this->size + 1, other.GetData());
	return *this;
}

std::istream& operator>>(std::istream& in, String& other)
{
	char data[1024];
	int i = 0;
	if (started_new_tag)
	{
		data[i] = '<';
		i++;
		started_new_tag = false;
	}
	in >> data[i];
	while (data[i] != '\n' && (data[i] != '<' || i == 0) && data[i] != '>')
	{
		if (!(i == 0 && data[i] == '\t'))
		{
			i++;
			in >> data[i];
		}
	}
	if (data[i] == '<') started_new_tag = true;
	other = data;

	return in;
}
std::ostream& operator<<(std::ostream& out, const String& other)
{
	out << other.GetData();

	return out;
}

char& String::operator[](const unsigned int i) const
{
	return this->data[i];
}
char& String::operator[](const unsigned int i)
{
	return this->data[i];
}



bool operator==(const String& string1, const String& string2)
{
	bool equal = true;
	if (string1.size == string2.size)
	{
		for (unsigned int i = 0; i <= string1.size; i++)
		{
			if (string1.data[i] != string2.data[i])
			{
				equal = false;
				break;
			}
		}
	}
	else
	{
		equal = false;
	}
	return equal;
}

String String::GetSubString(const unsigned int i, const unsigned int j)
{
	if (i >= this->size || j >= this->size)std::cout << "NANI?!" << std::endl;
	char delim = this->data[j];
	this->data[j] = '\0';
	String copy(this->data + i);
	this->data[j] = delim;
	return copy;
}