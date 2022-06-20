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
Vector<String> Strip(String& command_line)
{
	unsigned int i = 0, j;
	unsigned int size = command_line.GetSize();
	Vector<String> command;
	while (i < size)
	{
		j = i;
		while (command_line[i] != '\t' && command_line[i] != ' ' && command_line[i] != '/'  && command_line[i] != '[' && command_line[i] != ']' && command_line[i] != '@' && i < size)
		{
			i++;
		}
		command.Add(command_line.GetSubString(j, i));
		i++;
	}

	return command;
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
		if (CommandPrompt::xml_content[i].IsClosingTag())tabulations--;
		bool text = (!CommandPrompt::xml_content[i].IsOpeningTag() && !CommandPrompt::xml_content[i].IsClosingTag());
		for (int j = 0; j < tabulations - text; j++)std::cout << "\t";

		if (CommandPrompt::xml_content[i].IsOpeningTag())tabulations++;
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
	unsigned int j = i+1;
	for (j; j < size; j++)
	{
		if (CommandPrompt::xml_content[i].GetName() == CommandPrompt::xml_content[j].GetName()) 
		{
			return j;
		}
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
	CommandPrompt::xml_content.CheckIds();
	Show();
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
				CommandPrompt::saved = false;
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
		for (int index = i + 1; index < j; index++)
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

		for (int index = i + 1; index < j; index++)
		{
			if (CommandPrompt::xml_content[index].IsOpeningTag())
			{
				if (opening_tag_counter == n - 1)
				{
					CommandMode::Children(CommandPrompt::xml_content[index].GetId());
				}
				opening_tag_counter++;
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
			if (CommandPrompt::xml_content[index].TypeOfData() == "Text")
			{
				std::cout << CommandPrompt::xml_content[index - 1].GetName() << ": " << std::endl;
			}
		}
	}
}
bool CommandMode::Delete(const String& id, const String& key)
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
				Pair<String> empty;
				CommandPrompt::xml_content[i].SetAttribute(j, empty);
				CommandPrompt::saved = false;
				return true;
			}
		}

	}
	return false;
}
void CommandMode::NewChild(const String& id)
{
	int i = SelectId(id);
	if (i != -1)
	{
		if (CommandPrompt::xml_content[i + 1].IsOpeningTag())
		{
			int j = GetClosingTag(i + 1);
			CommandPrompt::xml_content.AddInPosition(i + 1, CommandPrompt::xml_content[j]);
			CommandPrompt::xml_content.AddInPosition(i + 1, CommandPrompt::xml_content[i + 2]);
		}
	}
}


void CommandMode::Xpath(String& command)
{
	if (strstr(command.GetData(), "@"))
	{
		Vector<String> commands = Strip(command);
		ReWrite();
		if (commands[1] == "id")
		{
			unsigned int size = CommandPrompt::xml_content.GetSize();
			for (int i = 0; i < size; i++)
			{
				if (CommandPrompt::xml_content[i] == commands[0])
				{
					int close_location = GetClosingTag(i);
					for (int j = i; j < close_location; j++)
					{
						if (CommandPrompt::xml_content[j].IsOpeningTag())
						{
							std::cout << commands[1] << ": " << CommandPrompt::xml_content[j].GetId() << std::endl;
						}
					}
				}
			}
		}
		else
		{
			unsigned int size = CommandPrompt::xml_content.GetSize();
			for (int i = 0; i < size; i++)
			{
				if (CommandPrompt::xml_content[i] == commands[0])
				{
					int close_location = GetClosingTag(i);
					for (int j = i; j < close_location; j++)
					{
						if (CommandMode::Select(CommandPrompt::xml_content[j].GetId(), commands[1]));
					}
				}
			}
		}
	}
	else if (strstr(command.GetData(), "/"))
	{
		String empty;
		Vector<String> commands = Strip(command);
		commands.Add(empty);
		if (!(commands[2] == ""))
		{
			int n = GetNumber(commands[2]);
			ReWrite();
			unsigned int size = CommandPrompt::xml_content.GetSize();
			int counter = 0;
			for (int i = 0; i < size; i++)
			{
				if (CommandPrompt::xml_content[i] == commands[0] && CommandPrompt::xml_content[i].IsOpeningTag())
				{
					int close_location = GetClosingTag(i);
					for (int j = i+1;  j< close_location; j++)
					{
						
						if (CommandPrompt::xml_content[j] == commands[1] && CommandPrompt::xml_content[i].IsOpeningTag())
						{
							if (counter == n)
							{
								std::cout << commands[1] << ": "<< CommandPrompt::xml_content[j + 1].GetXMLData() << std::endl;
							}
							else n++;
						}
					}
				}
			}
		}
		else
		{
			ReWrite();
			unsigned int size = CommandPrompt::xml_content.GetSize();
			for (int i = 0; i < size; i++)
			{
				if (CommandPrompt::xml_content[i] == commands[0] && CommandPrompt::xml_content[i].IsOpeningTag())
				{
					int close_location = GetClosingTag(i);
					for (int j = i + 1; j < close_location; j++)
					{
						if (CommandPrompt::xml_content[j] == commands[1] && CommandPrompt::xml_content[j].IsOpeningTag())
						{
								std::cout << commands[1] <<": " << CommandPrompt::xml_content[j + 1].GetXMLData() << std::endl;
						}
					}
				}
			}
		}

	}
}