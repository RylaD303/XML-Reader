#include "XMLParts.hpp"







Text::Text(const String& string)
{
	this->XML_data = string;
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









String OpeningTag::GetName() const
{
	return this->name;
}
unsigned int OpeningTag::GetNumberOfAttributes() const
{
	return this->attributes.GetSize();
}
Pair<String> OpeningTag::GetAttribute(unsigned int index) const
{
	return this->attributes[index];
}
String OpeningTag::GetId() const
{
	return this->id;
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

}

OpeningTag::OpeningTag(const String& string)
{
	this->XML_data = string;
	this->id = "";
	this->Split();
}

String OpeningTag::TypeOfData()
{
	return "OpeningTag";
}
bool operator==(const OpeningTag& string1, const OpeningTag& string2)
{
	if (string1.name == string2.name)
	{
		return true;
	}
	return false;
}
bool OpeningTag::CheckValidity()
{
	unsigned int size = this->XML_data.GetSize();
	if (this->XML_data[size] != '>' || this->XML_data[0] != '<')
	{
		return false;
	}
	for (int i = 1; i < size-1; i++)
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