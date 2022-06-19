#pragma once
#include"XMLContainer.h"
#include<fstream>
class CommandPrompt
{
public:
	static std::fstream file;
	static XMLContainer xml_content;
	static String file_name;
	static bool saved;
	static bool opened;
public:
	static void OpenFile();
	static void SaveFile();
	static void SaveAsFile(String& file_name_to_save_in);
	static void Close();
	static bool Exit();
};

Vector<String> GetCommand(String& command_line);


class CommandMode
{
public:
	static void Print();
	static void Select(const String& id, const String& key);
	static void Set(const String& id, const String& key, const String& value);
	static void Children(const String& id);
	static void Child(const String& id, const String& index);
	static void TextOfElement(const String& id);
	static void Delete(const String& id, const String& key);
	static void NewChild(const String& id);


};