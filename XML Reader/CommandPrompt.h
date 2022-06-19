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
	static void CommandMode();
};

Pair<String> GetCommand(String& command_line);