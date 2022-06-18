#pragma once
#include"Vector.hpp"
#include"String.h"

template<typename T>
struct Pair
{
	T first;
	T second;
};

class XMLPart
{
protected:
	String name;
	String XML_data;
	bool is_open_tag;
	bool is_close_tag;
public:
	const String& GetName() const 
	{
		return this->name;
	}
	const bool IsOpeningTag() const
	{
		return this->is_open_tag;
	}
	const bool IsClosingTag() const
	{
		return this->is_close_tag;
	}
	const String& GetXMLData() const
	{
		return this->XML_data;
	}
	void SetXMLData(const String& _data)
	{
		this -> XML_data = _data;
	}
	virtual ~XMLPart() = default;
	virtual String TypeOfData() = 0;
	virtual bool CheckValidity() = 0;
	virtual XMLPart* Clone()=0;
	friend bool operator==(const XMLPart& string1, const String& string2)
	{
		if (string1.name == string2)
		{
			return true;
		}
		return false;
	}
};

class Text : public XMLPart
{
public:
	Text(const String& string);
	String TypeOfData() override;
	friend bool operator==(const Text& string1, const Text& string2);
	bool CheckValidity() override;
	XMLPart* Clone() override;
};

class OpeningTag : public XMLPart
{
private:
	Vector<Pair<String>> attributes;
	void Split();
	String id;
public:
	unsigned int GetNumberOfAttributes() const;
	Pair<String> GetAttribute(unsigned int index) const;
	String GetId() const;

	OpeningTag(const String& string);
	String TypeOfData() override;
	bool CheckValidity() override;
	XMLPart* Clone() override;
};

class ClosingTag : public XMLPart
{
private:
	void Split();
public:
	ClosingTag(const String& string);
	String TypeOfData() override;
	bool CheckValidity() override;
	XMLPart* Clone() override;
};