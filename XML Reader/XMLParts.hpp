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
	Vector<Pair<String>> attributes;
	virtual void Split() = 0;
	String id;
	String name;
	String XML_data;
	bool is_open_tag;
	bool is_close_tag;
public:
	const String GetId() const
	{
		return this->id;
	}
	const Pair<String> GetAtribute(unsigned int index)
	{
		return this->attributes[index];
	}
	const unsigned int GetSize() const
	{
		return this->attributes.GetSize();
	}
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
		this->XML_data = _data;
	}
	void SetId(const String& _id)
	{
		this->id = _id;
	}
	void SetName(const String& _name)
	{
		this->name = _name;
	}
	void SetAttribute(const unsigned int& index, const Pair<String>& _attribute)
	{
		if (_attribute.first == "")
		{
			this->attributes.Remove(index);
		}
		else this->attributes[index] = _attribute;
	}
	virtual void ReWrite() = 0;
	virtual ~XMLPart() = default;
	virtual String TypeOfData() = 0;
	virtual bool CheckValidity() = 0;
	virtual XMLPart* Clone() = 0;
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
private:
	void Split() override {};
public:
	void ReWrite() override{};
	Text(const String& string);
	String TypeOfData() override;
	friend bool operator==(const Text& string1, const Text& string2);
	bool CheckValidity() override;
	XMLPart* Clone() override;
};

class OpeningTag : public XMLPart
{
private:

	void Split() override;
public:
	void ReWrite() override;
	OpeningTag(const String& string);
	String TypeOfData() override;
	bool CheckValidity() override;
	XMLPart* Clone() override;
};

class ClosingTag : public XMLPart
{
private:
	void Split() override;
public:
	void ReWrite() override {};
	ClosingTag(const String& string);
	String TypeOfData() override;
	bool CheckValidity() override;
	XMLPart* Clone() override;
};