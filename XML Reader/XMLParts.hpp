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
	String XML_data;
	bool is_open_tag;
	bool is_close_tag;
public:
	bool IsOpeningTag() const
	{
		return this->is_open_tag;
	}
	bool IsOpeningTag() const
	{
		return this->is_close_tag;
	}
	String GetXMLData() const
	{
		return this->XML_data;
	}
	void SetXMLData(const String& _data)
	{
		this -> XML_data = _data;
	}
	virtual ~XMLPart() {};
	virtual String TypeOfData() = 0;
	virtual bool CheckValidity() = 0;
	virtual XMLPart* Clone()=0;
	friend bool operator==(const XMLPart& string1, const String& string2)
	{
		if (string1.XML_data == string2)
		{
			return true;
		}
		return false;
	}
};

class Text : XMLPart
{
public:
	Text(const String& string);
	String TypeOfData() override;
	friend bool operator==(const Text& string1, const Text& string2);
	bool CheckValidity() override;
	XMLPart* Clone() override;
};

class OpeningTag : XMLPart
{
private:
	String name;
	Vector<Pair<String>> attributes;
	void Split();
	String id;
public:
	String GetName() const;
	unsigned int GetNumberOfAttributes() const;
	Pair<String> GetAttribute(unsigned int index) const;
	String GetId() const;

	OpeningTag(const String& string);
	String TypeOfData() override;
	friend bool operator==(const OpeningTag& string1, const OpeningTag& string2);
	bool CheckValidity() override;
	XMLPart* Clone() override;
};

class ClosingTag : XMLPart
{
private:
	String name;
	void Split();
public:
	String GetName() const;

	ClosingTag(const String& string);
	String TypeOfData() override;
	friend bool operator==(const ClosingTag& string1, const OpeningTag& string2);
	friend bool operator==(const OpeningTag& string1, const ClosingTag& string2);
	bool CheckValidity() override;
	XMLPart* Clone() override;
};