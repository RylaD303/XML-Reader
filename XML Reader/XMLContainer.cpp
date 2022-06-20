#include "XMLContainer.h"


void XMLContainer::CheckIds()
{
	unsigned int size = this->parts.GetSize();
	for (unsigned int i = 0; i < size; i++)
	{
		if (!(this->parts[i]->GetId() == ""))
		{
			for (unsigned int j = i + 1; j < size; j++)
			{
				if (this->parts[i]->GetId() == this->parts[j]->GetId())
				{
					this->parts[i]->SetId((String) this->parts[i]->GetId() +  "_1");
					this->parts[j]->SetId((String)this->parts[j]->GetId() + "_2");
					this->CheckIds();
					break;
				}
			}
		}
	}

}



XMLContainer::~XMLContainer()
{
	unsigned int size = parts.GetSize();
	for (unsigned int i = 0; i < size; i++)
	{
		delete parts[i];
	}
}
unsigned int XMLContainer::GetSize() const
{
	return this->parts.GetSize();
}
void XMLContainer::Add(const XMLPart& xml_part)
{
	unsigned int size = xml_part.GetXMLData().GetSize();
	if (xml_part.GetXMLData()[0] == '<' && xml_part.GetXMLData()[1] == '/' && xml_part.GetXMLData()[size - 1] == '>')
	{
		ClosingTag closing_tag(xml_part.GetXMLData());
		this->parts.Add(closing_tag.Clone());
	}
	else if (xml_part.GetXMLData()[0] == '<' && xml_part.GetXMLData()[size - 1] == '>')
	{
		OpeningTag opening_tag(xml_part.GetXMLData());
		this->parts.Add(opening_tag.Clone());
	}
	else
	{
		Text text(xml_part.GetXMLData());
		this->parts.Add(text.Clone());
	}
}
void XMLContainer::Add(const String& xml_part)
{
	unsigned int size = xml_part.GetSize();
	if (xml_part[0] == '<' && xml_part[1] == '/' && xml_part[size - 1] == '>')
	{
		ClosingTag closing_tag(xml_part);
		this->parts.Add(closing_tag.Clone());
	}
	else if (xml_part[0] == '<' && xml_part[size - 1] == '>')
	{
		OpeningTag opening_tag(xml_part);
		this->parts.Add(opening_tag.Clone());
	}
	else
	{
		Text text(xml_part);
		this->parts.Add(text.Clone());
	}
}
void XMLContainer::AddInPosition(unsigned int i, const XMLPart& xml_part)
{
	unsigned int size = xml_part.GetXMLData().GetSize();
	if (xml_part.GetXMLData()[0] == '<' && xml_part.GetXMLData()[1] == '/' && xml_part.GetXMLData()[size - 1] == '>')
	{
		ClosingTag closing_tag((String)"</" + xml_part.GetName() + ">");
		this->parts.AddInPosition(i, closing_tag.Clone());
	}
	else if (xml_part.GetXMLData()[0] == '<' && xml_part.GetXMLData()[size - 1] == '>')
	{
		OpeningTag opening_tag((String)"<" + xml_part.GetName() + ">");
		this->parts.AddInPosition(i, opening_tag.Clone());
	}
	else
	{
		Text text(xml_part.GetXMLData());
		this->parts.AddInPosition(i, text.Clone());
	}
}
void XMLContainer::Remove(const unsigned int i, const unsigned int j)
{
	for (int index = j; index >= i; index--)
	{
		this->parts.Remove(index);
	}
}
XMLPart& XMLContainer::operator[](unsigned int i)
{
	return *this->parts[i];
}
const XMLPart& XMLContainer::operator[](unsigned int i) const
{
	return *this->parts[i];
}