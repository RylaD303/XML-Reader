#pragma once
#include"XMLParts.hpp"
class XMLContainer
{
private:
	Vector<XMLPart*> parts;
public:
	void CheckIds();
	~XMLContainer();
	unsigned int GetSize() const;
	void Add(const XMLPart& xml_part);
	void Add(const String& xml_part);
	void Remove(const unsigned int i, const unsigned int j);
	XMLPart& operator[](const unsigned int i);
	const XMLPart& operator[](const unsigned int i) const;
};

