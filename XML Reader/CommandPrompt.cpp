#include "CommandPrompt.h"

Pair<String> GetCommand(String& command_line)
{
	unsigned int i = 0, j;
	unsigned int size = command_line.GetSize();
	while ((command_line[i] == '\t' || command_line[i] == ' ') && i<size)
	{
		i++;
	}
	j = i;
	while (command_line[i] != '\t' && command_line[i] != ' ' && i<size)
	{
		i++;
	}
	Pair<String> command;

	command.first = command_line.GetSubString(j, i);
	while ((command_line[i] == '\t' || command_line[i] == ' ') && i < size)
	{
		i++;
	}
	j = i;
	while (command_line[i] != '\t' && command_line[i] != ' ' && i < size)
	{
		i++;
	}
	command.second = command_line.GetSubString(j, i);
	return command;
}

static bool CheckXMLFileValidity(const String& file_name)
{
	unsigned int size = file_name.GetSize();
	if (size >= 5)
	{
		return !(file_name[size - 1] != 'l' && file_name[size - 2] != 'm' && file_name[size - 3] != 'x' && file_name[size - 4] != '.' && file_name[size - 5] == '.');
	}
	return false;
}

static void ReWrite()
{
	unsigned int size = CommandPrompt::xml_content.GetSize();
	
	for (int i = 0; i < size; i++)
	{
		CommandPrompt::xml_content[i].ReWrite();
	}
}
static void Show()
{
	ReWrite();
	unsigned int size = CommandPrompt::xml_content.GetSize();
	int tabulations = 0;
	for (int i = 0; i < size; i++)
	{
		bool text = (!CommandPrompt::xml_content[i].IsOpeningTag() && !CommandPrompt::xml_content[i].IsClosingTag());
		for (int j = 0; j < tabulations - text; j++)std::cout << "\t";

		if (CommandPrompt::xml_content[i].IsOpeningTag())tabulations++;
		if (CommandPrompt::xml_content[i].IsClosingTag())tabulations--;
		std::cout << CommandPrompt::xml_content[i].GetXMLData() << std::endl;
	}
}
static void WriteFile(std::fstream& _file)
{
	ReWrite();
	unsigned int size = CommandPrompt::xml_content.GetSize();
	int tabulations = 0;
	for (int i = 0; i < size; i++)
	{
		bool text = (!CommandPrompt::xml_content[i].IsOpeningTag() && !CommandPrompt::xml_content[i].IsClosingTag());
		for (int j = 0; j < tabulations - text; j++)std::cout << "\t";

		if (CommandPrompt::xml_content[i].IsOpeningTag())tabulations++;
		if (CommandPrompt::xml_content[i].IsClosingTag())tabulations--;
		_file << CommandPrompt::xml_content[i].GetXMLData() << std::endl;
	}
}
static void YesOrNo(String& answer)
{
	std::cout << "yes/no" << std::endl;
	std::cin>>answer;
	while (!(answer == "no") && !(answer == "yes"))
	{
		std::cout << "Invalid. Try Again." << std::endl;
		std::cin >> answer;
	}
}

void CommandPrompt::OpenFile()
{
	if (CommandPrompt::opened)
	{
		CommandPrompt::Close();
	}
	Vector<String> xml_parts;
	CommandPrompt::file.open(CommandPrompt::file_name.GetData());
	while (!(CommandPrompt::file.eof()))
	{
		String line;
		CommandPrompt::file >> line;
		line.GetTags(xml_parts);
	}
	unsigned int size = xml_parts.GetSize();
	for (unsigned int i = 0; i < size; i++)
	{
		CommandPrompt::xml_content.Add(xml_parts[i]);
	}
	for (unsigned int i = 0; i < size; i++)
	{
		std::cout << CommandPrompt::xml_content[i].GetXMLData() << std::endl;
	}
	CommandPrompt::xml_content.CheckIds();
	CommandPrompt::opened = true;
}
void CommandPrompt::SaveFile()
{
	if (!CommandPrompt::saved)
	{
		CommandPrompt::file.open(CommandPrompt::file_name.GetData());
		unsigned int size = CommandPrompt::xml_content.GetSize();
		WriteFile(CommandPrompt::file);
		CommandPrompt::saved = true;
		file.close();
		std::cout << "File saved." << "\n\n\n";
	}
	else
	{
		std::cout << "Nothing changed" << "\n\n\n";
	}

}
void CommandPrompt::SaveAsFile(String& file_name_to_save_in)
{
	CommandPrompt::file.open(file_name_to_save_in.GetData());
	unsigned int size = CommandPrompt::xml_content.GetSize();
	WriteFile(CommandPrompt::file);
	CommandPrompt::saved = true;
	file.close();
}
void CommandPrompt::Close()
{
	if (!(CommandPrompt::saved))
	{
		std::cout << "Do you wish to save this file?" << std::endl;
		String answer;
		YesOrNo(answer);
		if (answer == "yes")
		{
			SaveFile();
		}
		CommandPrompt::saved = true;
	}
	std::cout << "File closed" << std::endl;
	CommandPrompt::opened = false;
}
bool CommandPrompt::Exit()
{
	if (CommandPrompt::opened)
	{
		CommandPrompt::Close();
	}

	std::cout << "Do you wish to exit?" << std::endl;
	String answer;
	YesOrNo(answer);
	if (answer == "yes")
	{
		return true;
	}
	return false;
}
void CommandPrompt::CommandMode()
{

}