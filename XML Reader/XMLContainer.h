#pragma once
#include"XMLParts.hpp"
class XMLContainer
{
private:
	Vector<XMLPart*> parts;
public:
	/**
		Checks the ids of the elements and changes them if there are any ids that are the same
	*/
	void CheckIds();
	/**
		Classic destructor
	*/
	~XMLContainer();
	/**
		classic getter
	*/
	unsigned int GetSize() const;
	/**
		adds new element to the container. Checks if its opening or closing tag or text.
	*/
	void Add(const XMLPart& xml_part);
	/**
		adds new element extracted from string to the container. Checks if its opening or closing tag or text.
	*/
	void Add(const String& xml_part);
	/**
		adds new element at position i to the container. Checks if its opening or closing tag or text.
	*/
	void AddInPosition(unsigned int i, const XMLPart& xml_part);
	/**
		Removes element from position i to position j
	*/
	void Remove(const unsigned int i, const unsigned int j);
	/**
		classic operator [] for changing values
	*/
	XMLPart& operator[](const unsigned int i);
	/**
		classic operator [] for reading values
	*/
	const XMLPart& operator[](const unsigned int i) const;
};

