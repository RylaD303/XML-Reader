#pragma once
#pragma once
#include<iostream>
/**
	Classical string class, dynamic char array
*/
class String
{
	/*!
		All data types for the class. it keeps char* and size of the dynamic array;
		Also a private Free function for freeing the memory.
	*/
private:
	char* data;
	unsigned int size;
	void Free();
public:
	/**
		Default constructor and constructor with parameters
	*/
	String(const char* data = "");
	/**
		classic Copy constructor
	*/
	String(const String& other);
	/**
		classic Destructor
	*/
	~String();

	/*!
		classic get() functions
	*/
	char* GetData() const;
	/*!
		classic get() functions
	*/
	int GetSize() const;


	/**
		operator =: for dynamic classes, which deletes the memory if the objects are different,
		and creates new memory to copy the other object
	*/
	String& operator=(const String& other);

	/**
		operator +: returns string of the sticking of the two strings, gets care of dynamic memory.
	*/

	String operator+(const String& other);

	/**
		operator +=: the current object gets added the data from the other, sticking them like two strings together. gets care of dynamic memory.
	*/
	String& operator+=(const String& other);


	/**
		redefinition of the operator - >>. Unputs char* with getline (until end of the line or 2047 symbols).
		Set's enough memory for the entire string written by the user and copies the string into the object.
	*/
	friend std::istream& operator>>(std::istream& in, String& other);
	/**
		redefinition of the operator - <<. Outputs the char* in the memory of the string object. In other words, it outputs the word in the string.
	*/
	friend std::ostream& operator<<(std::ostream& out, const String& other);

	/**
		redefinition of the operator[]const - returns the value in the specified index of the array of chars. It is constant so it is only used for reading.
	*/
	char& operator[](const unsigned int i) const;
	/**
		redefinition of the operator[] - returns the pointer to the value on the specified cell of the array of chars.
		Gives the possiblity to change the value of the cell.
	*/
	char& operator[](const unsigned int i);


	/**
		redefinition of the operator - ==. Retuns true or false value, depending on if both strings contain the same data of chars;
	*/
	friend bool operator==(const String& string1, const String& string2);
};

