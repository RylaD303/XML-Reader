#pragma once
#include"Vector.hpp"
#include"String.h"
/**
	Pair structure, why, because.
*/
template<typename T>
struct Pair
{
	T first;
	T second;
};

/**
	Bsae calss for xml parts
*/
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
	/**
		Classic getter
	*/
	const String GetId() const
	{
		return this->id;
	}
	/**
		Returns pair of the atribute. first value is the key, second is the value of the key.
	*/
	const Pair<String> GetAttribute(unsigned int index)
	{
		return this->attributes[index];
	}
	/**
		Classic getter, returns size of atributes array
	*/
	const unsigned int GetSize() const
	{
		return this->attributes.GetSize();
	}
	/**
		Classic getter
	*/
	const String& GetName() const
	{
		return this->name;
	}
	/**
		Classic getter
	*/
	const bool IsOpeningTag() const
	{
		return this->is_open_tag;
	}
	/**
		Classic getter
	*/
	const bool IsClosingTag() const
	{
		return this->is_close_tag;
	}
	/**
		Classic getter
	*/
	const String& GetXMLData() const
	{
		return this->XML_data;
	}
	/**
		Classic setter
	*/
	void SetXMLData(const String& _data)
	{
		this->XML_data = _data;
	}
	/**
		Classic setter
	*/
	void SetId(const String& _id)
	{
		this->id = _id;
	}
	/**
		Classic setter
	*/
	void SetName(const String& _name)
	{
		this->name = _name;
	}
	/**
		Classic setter
	*/
	void SetAttribute(const unsigned int& index, const Pair<String>& _attribute)
	{
		if (_attribute.first == "")
		{
			this->attributes.Remove(index);
		}
		else this->attributes[index] = _attribute;
	}
	/**
		ReWrite function changes the xml data based on what atributes it has. includes "id"
	*/
	virtual void ReWrite() = 0;
	/**
		Classic  destructor for base class
	*/
	virtual ~XMLPart() = default;
	/**
		Returns the type of tag the cml part is
	*/
	virtual String TypeOfData() = 0;
	/**
		Checks if tag is valid ot not
	*/
	virtual bool CheckValidity() = 0;
	/**
		Clones the memory of the tag
	*/
	virtual XMLPart* Clone() = 0;
	/**
		Operator == for xml parts. it basically checks if their names are equal. in other words <opening id=1> = <opening> = </opening>
	*/
	friend bool operator==(const XMLPart& string1, const String& string2)
	{
		if (string1.name == string2)
		{
			return true;
		}
		return false;
	}
};
/**
	Xml part text. its just the text from the xml file.
*/
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

/**
	Xml part opening tag. This part gets its job done automatically. it just finds its own atributes and sets its own id, if it doesnt have one gived it itself.
*/
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


/**
	Xml part closing tag. Just reads the information and sets itself
*/
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