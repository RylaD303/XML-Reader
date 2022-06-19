#include <iostream>
#include "CommandPrompt.h"
static bool CheckXMLFileValidity(const String& file_name)
{
    unsigned int size = file_name.GetSize();
    if (size >= 5)
    {
        return !(file_name[size - 1] != 'l' && file_name[size - 2] != 'm' && file_name[size - 3] != 'x' && file_name[size - 4] != '.' && file_name[size - 5] == '.');
    }
    return false;
}
String CommandPrompt::file_name = "";
bool CommandPrompt::saved = true;
bool CommandPrompt::opened = false;
XMLContainer CommandPrompt::xml_content;
std::fstream CommandPrompt::file;
String help_message(",print, select <id> <key>, set <id> <key>  <value>, children <id>, child <id> <n>, text <id>, delete <id>  <key>,xpath <id> < XPath >");
int main()
{
    std::cout << "Welcome to xml reader. \n Available commands: open,exit, save, saveas, close, help\n";
    String command;
    std::cin >> command;
    while (true)
    {
        Vector<String> commands = GetCommand(command);
        unsigned int size = commands.GetSize();
        if (commands[0] == "help" && size == 1)
        {
            std::cout << "Available commands: open,exit, save, saveas, close, help";
            if (CommandPrompt::opened) std::cout << help_message;
            std::cout << "\n";
        }
        else if (commands[0] == "open" && size == 2 && CheckXMLFileValidity(commands[1]))
        {
            CommandPrompt::file_name = commands[1];
            CommandPrompt::OpenFile();
        }
        else if (commands[0] == "save" && size == 1)
        {
            CommandPrompt::SaveFile();
        }
        else if (commands[0] == "saveas" && size == 2 && CheckXMLFileValidity(commands[1]))
        {
            CommandPrompt::SaveAsFile(commands[1]);
        }
        else if (commands[0] == "close" && size == 1)
        {
            CommandPrompt::Close();
        }
        else if (commands[0] == "exit" && size == 1)
        {
            if(CommandPrompt::Exit())
                return 0;
        }
        else if (commands[0] == "print" && size == 1)
        {
            if (CommandPrompt::opened)
            {
                CommandMode::Print();
            }
            else
            {
                std::cout << "Open a file first" << std::endl;
            }
        }
        else if (commands[0] == "select" && size == 3)
        {
            if (CommandPrompt::opened)
            {
                if (!CommandMode::Select(commands[1], commands[2]))
                {
                    std::cout << "Not found" << std::endl;
                }
            }
            else
            {
                std::cout << "Open a file first" << std::endl;
            }
        }
        else if (commands[0] == "set" && size == 4)
        {
            if (CommandPrompt::opened)
            {
                if(!CommandMode::Set(commands[1], commands[2], commands[3]));
                {
                    std::cout << "Not found" << std::endl;
                }
            }
            else
            {
                std::cout << "Open a file first" << std::endl;
            }
        }
        else if (commands[0] == "children" && size == 2)
        {
            if (CommandPrompt::opened)
            {
                CommandMode::Children(commands[1]);
            }
            else
            {
                std::cout << "Open a file first" << std::endl;
            }
        }
        else if (commands[0] == "child" && size == 3)
        {
            if (CommandPrompt::opened)
            {
                CommandMode::Child(commands[1], commands[2]);
            }
            else
            {
                std::cout << "Open a file first" << std::endl;
            }
        }
        else if (commands[0] == "text" && size == 2)
        {
            if (CommandPrompt::opened)
            {
                CommandMode::TextOfElement(commands[1]);
            }
            else
            {
                std::cout << "Open a file first" << std::endl;
            }
        }
        else if (commands[0] == "delete" && size == 3)
        {
            if (CommandPrompt::opened)
            {
                if (!CommandMode::Delete(commands[1], commands[2]))
                {
                    std::cout << "Not found" << std::endl;
                }
            }
            else
            {
                std::cout << "Open a file first" << std::endl;
            }
        }
        else if (commands[0] == "xpath" && size == 2)
        {
            if (CommandPrompt::opened)
            {
                CommandMode::Xpath(commands[1]);
            }
            else
            {
                std::cout << "Open a file first" << std::endl;
            }
        }
        else std::cout << "Impropable command, try again!\n" << std::endl;
        std::cout << "Available commands: open,exit, save, saveas, close, help";
        if (CommandPrompt::opened) std::cout << help_message;
        std::cout << "\n";
    }
}
