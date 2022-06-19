#include "CommandPrompt.h"

Vector<String> GetCommand(String& command_line)
{
	unsigned int i = 0, j;
	unsigned int size = command_line.GetSize();
	Vector<String> command;
	while (i < size)
	{
		while ((command_line[i] == '\t' || command_line[i] == ' ') && i < size)
		{
			i++;
		}
		j = i;
		while (command_line[i] != '\t' && command_line[i] != ' ' && i < size)
		{
			i++;
		}
		command.Add(command_line.GetSubString(j, i));
	}
	
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
static int SelectId(const String& id)
{
	unsigned int size = CommandPrompt::xml_content.GetSize();
	for (unsigned int i = 0; i < size; i++)
	{
		if (CommandPrompt::xml_content[i].GetId() == id)
		{
			return i;
		}
	}
	return -1;
}
static int GetClosingTag(const int i)
{
	unsigned int size = CommandPrompt::xml_content.GetSize();
	int j = i+1;
	for (j; j > size; j++)
	{
		if (CommandPrompt::xml_content[i] == CommandPrompt::xml_content[j].GetName())
			return j;
	}

	return j;
}
static int GetNumber(const String& _n)
{
	unsigned int size = _n.GetSize();
	long long number = 0;
	for (unsigned int i = 0; i < size; i++)
	{
		number *= 10;
		number += (long long)(_n[i] - '0');
	}
	return number;
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



void CommandMode::Print()
{
	Show();
}
bool CommandMode::Select(const String& id, const String& key)
{
	int i = SelectId(id);
	if(i!=-1)
	{
		unsigned int number_of_attributes = CommandPrompt::xml_content[i].GetSize();
		for (unsigned int j = 0; j < number_of_attributes; j++)
		{
			Pair<String> attribute = CommandPrompt::xml_content[i].GetAttribute(j);
			if (attribute.first == key)
			{
				std::cout << key<<": "<< attribute.second << std::endl;
				return true;
			}
		}

	}
	return false;
}
bool CommandMode::Set(const String& id, const String& key, const String& value)
{
	int i = SelectId(id);
	if (i != -1)
	{
		unsigned int number_of_attributes = CommandPrompt::xml_content[i].GetSize();
		for (unsigned int j = 0; j < number_of_attributes; j++)
		{
			Pair<String> attribute = CommandPrompt::xml_content[i].GetAttribute(j);
			if (attribute.first == key)
			{
				attribute.second = value;
				CommandPrompt::xml_content[i].SetAttribute(j, attribute);
				std::cout << "Successfully changed" << std::endl;
				return true;
			}
		}

	}
	return false;
}
void CommandMode::Children(const String& id)
{
	int i = SelectId(id);
	if (i != -1)
	{
		int j = GetClosingTag(i);
		for (int index = i + 1; index <= j; index++)
		{
			CommandPrompt::xml_content[index].ReWrite();
			unsigned int size = CommandPrompt::xml_content[index].GetSize();
			std::cout << "Part:" << CommandPrompt::xml_content[index].TypeOfData()<<": " << CommandPrompt::xml_content[index].GetName() << std::endl;
			for (unsigned int jndex = 0; jndex < size; jndex++)
			{
				std::cout << CommandPrompt::xml_content[index].GetAttribute(jndex).first<< "=\"" << CommandPrompt::xml_content[index].GetAttribute(jndex).second<<"\"\n";
			}
			std::cout << "\n";
		}
	}

}
void CommandMode::Child(const String& id, const String& _n)
{
	int i = SelectId(id);
	unsigned int n = GetNumber(_n);
	unsigned int opening_tag_counter = 0;
	if (i != -1)
	{
		int j = GetClosingTag(i);

		for (int index = i + 1; index <= j; index++)
		{
			if (CommandPrompt::xml_content[index].IsOpeningTag())
			{
				opening_tag_counter++;
				if (opening_tag_counter == n - 1)
				{
					CommandMode::Children(CommandPrompt::xml_content[index].GetId());
				}
			}
		}
	}
}
void CommandMode::TextOfElement(const String& id)
{
	int i = SelectId(id);
	if (i != -1)
	{
		int j = GetClosingTag(i);
		for (int index = i + 1; index <= j; index++)
		{
			if(CommandPrompt::xml_content[index].TypeOfData() == "Text")
			ìf()
		}
	}
}
/*static void Delete(const String& id, const String& key);
static void NewChild(const String& id);
static void Xpath(const String& command);*/