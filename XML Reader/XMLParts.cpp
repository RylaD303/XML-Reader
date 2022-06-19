#include "XMLParts.hpp"

static unsigned int element_counter=0;
String GetElementCounter()
{
	element_counter++;
	unsigned int element_counter_copy = element_counter;
	String number;
	while (element_counter_copy > 0)
	{
		char num = (char)(element_counter_copy % 10 + '0');
		number += (String)&num;
		element_counter_copy /= 10;
	}
	return number;
}




Text::Text(const String& string)
{
	this->XML_data = string;
	this->name = string;
	this->is_open_tag = false;
	this->is_close_tag = false;
}
String Text::TypeOfData()
{
	return "Text";
}
bool operator==(const Text& string1, const Text& string2)
{
	if (string1.XML_data == string2.XML_data)
	{
		return true;
	}
	return false;
}
bool Text::CheckValidity()
{
	unsigned int size = this->XML_data.GetSize();
	for (int i = 0; i < size; i++)
	{
		if (this->XML_data[i] == '>' || this->XML_data[i] == '<')
		{
			return false;
		}
	}
	return true;
}
XMLPart* Text::Clone()
{
	return new Text(*this);
}



void OpeningTag::Split()
{
	unsigned int size = this->XML_data.GetSize(), i=1;
	char delim = ' ';
	while (this->XML_data[i] != ' ' && this->XML_data[i] != '>' && i<size)
	{
		i++;
	}
	this->name = this->XML_data.GetSubString(1, i);
	i++;
	int j = i;
	Pair<String> attribute;
	
	while (this->XML_data[i] != '>' && i<size)
	{
		if (this->XML_data[i] == '=')
		{
			attribute.first = this->XML_data.GetSubString(j, i);
			i+=2;
			j = i;
			while (this->XML_data[i] != '"')
			{
				i++;
			}
			attribute.second = this->XML_data.GetSubString(j, i);
			i +=2;
			j = i--;
			if(attribute.first == "id")
			{ 
				id = attribute.second;
			}
			else attributes.Add(attribute);
		}
		i++;
	}
	if (this->id == "")
	{
		this->id = GetElementCounter();
	}

}
OpeningTag::OpeningTag(const String& string)
{
	this->XML_data = string;
	this->id = "";
	this->is_open_tag = true;
	this->is_close_tag = false;
	this->Split();
}
void OpeningTag::ReWrite()
{
	this->XML_data = (String)"<" + this->name;
	unsigned int size = attributes.GetSize();

	this->XML_data += (String)" id=\"" + this->id + "\"";

	for (unsigned int i = 0; i < size; i++)
	{
		this->XML_data += (String)" " + this->attributes[i].first + "=\"" + this->attributes[i].second + "\"";
	}
	this->XML_data += (String)">";
}
String OpeningTag::TypeOfData()
{
	return "OpeningTag";
}
bool OpeningTag::CheckValidity()
{
	unsigned int size = this->XML_data.GetSize();
	if (this->XML_data[size-1] != '>' || this->XML_data[0] != '<')
	{
		return false;
	}
	for (unsigned int i = 1; i < size-1; i++)
	{
		if (this->XML_data[i] == '>' || this->XML_data[i] == '<' || this->XML_data[i] == '/')
		{
			return false;
		}
	}
	return true;
}
XMLPart* OpeningTag::Clone()
{
	return new OpeningTag(*this);
}



void ClosingTag::Split()
{
	unsigned int size = this->XML_data.GetSize(), i = 2;
	while (this->XML_data[i] != ' ' && this->XML_data[i] != '>' && i < size)
	{
		i++;
	}
	this->name = this->XML_data.GetSubString(2, i);

}

ClosingTag::ClosingTag(const String& string)
{
	this->XML_data = string;
	this->is_open_tag = false;
	this->is_close_tag = true;
	this->Split();
}

String  ClosingTag::TypeOfData()
{
	return "ClosingTag";
}

bool ClosingTag::CheckValidity()
{
	unsigned int size = this->XML_data.GetSize();
	if (this->XML_data[size - 1] != '>' || this->XML_data[0] != '<' || this->XML_data[1]!='/')
	{
		return false;
	}
	for (unsigned int i = 2; i < size - 1; i++)
	{
		if (this->XML_data[i] == '>' || this->XML_data[i] == '<' || this->XML_data[i] == '/')
		{
			return false;
		}
	}
	return true;
}

XMLPart* ClosingTag::Clone()
{
	return new ClosingTag(*this);
}