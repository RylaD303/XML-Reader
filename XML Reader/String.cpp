#include "String.h"
#include<cstring>


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
	char data[2048];
	in.getline(data, 2048);
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



void String::GetTags(Vector<String>& strings)
{
	unsigned int i = 0,j;
	while (this->data[i] == '\t')
	{
		i++;
	}
	j = i;
	while (i < this->size)
	{
		if (this->data[i] == '<')
		{
			if (i != j)
			{
				strings.Add(this->GetSubString(j, i));
			}
			j = i;
			while (this->data[i] != '>' && i < this->size);
			{
				i++;
			}
			strings.Add(this->GetSubString(j, i + 1));
			j = i + 1;
		}
		i++;
	}

	String last_word = this->GetSubString(j,i);
	
	if (!(last_word == "") && !(last_word== " "))
	{
		strings.Add(last_word);
	}

}