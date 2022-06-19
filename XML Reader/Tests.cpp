/*#include "../acutest/include/acutest.h"
void TestString()
{
	String s1("test"), copy(s1), empty("");

	TEST_CHECK((s1 + empty) == s1);
	TEST_CHECK((s1 + empty).GetSize() == s1.GetSize());
	TEST_CHECK(!((s1 + copy) == s1));
	TEST_CHECK((s1 + copy).GetSize() == s1.GetSize() + copy.GetSize());

	const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz\0";
	const size_t ALPHABET_LENGTH = strlen(ALPHABET);

	s1 = "";
	s1 += (String)ALPHABET;

	TEST_CHECK(s1 == ALPHABET);
	TEST_CHECK(s1.GetSize() == ALPHABET_LENGTH);
	TEST_CHECK(strcmp(s1.GetData(), ALPHABET) == 0);
}

void TestVector()
{
	Vector<int> vec1, vec2;
	vec1.Add(1);
	vec1.Add(2);
	vec1.Add(3);
	vec1.Add(4);
	//TEST_CHECK();

	TEST_CHECK(vec1[0] == 1);
	TEST_CHECK(vec1[1] == 2);
	TEST_CHECK(vec2.GetSize() == 0);
	TEST_CHECK(vec1.GetSize() == 4);

	vec1.Add(5);
	vec1.Add(6);
	vec1.Add(7);
	vec1.Add(8);
	vec1.Add(9);

	TEST_CHECK(vec1.GetSize() == 9);

	vec2 = vec1;

	TEST_CHECK(vec2.GetSize() == 9);
	TEST_CHECK(vec2[0] == 1);
	TEST_CHECK(vec2[1] == 2);

	vec1.Remove(1);
	vec1.Remove(4);

	TEST_CHECK(vec1.GetSize() == 7);
	TEST_CHECK(vec1[0] == 2);
	TEST_CHECK(vec1[1] == 3);
	TEST_CHECK(vec1[2] == 5);
	TEST_CHECK(vec1[3] == 6);

	TEST_CHECK(vec2.GetSize() == 9);
	TEST_CHECK(vec2[0] == 1);
	TEST_CHECK(vec2[1] == 2);
}


void TestXMLParts()
{
	Text text("I am a man");
	TEST_CHECK(text == (Text)"I am a man");
	TEST_CHECK(!(text == (Text)"I am a ma"));
	TEST_CHECK(text.TypeOfData() == "Text");
	TEST_CHECK(text.CheckValidity());



	XMLPart* text2 = text.Clone();
	TEST_CHECK(*text2 == (String)"I am a man");
	TEST_CHECK(!(*text2 == (String)"I am a ma"));
	TEST_CHECK(text2->TypeOfData() == "Text");
	TEST_CHECK(text2->CheckValidity());



	Text text_wrong("< opeen");
	TEST_CHECK(!(text_wrong.CheckValidity()));
	Text text_wrong2("ope>en");
	TEST_CHECK(!(text_wrong2.CheckValidity()));



	OpeningTag open_tag("<opening id=\"1\" font=\"magenta\" size=\"big\" >");
	TEST_CHECK(open_tag.GetName() == "opening");
	TEST_CHECK(!(open_tag.GetName() == "opening "));
	TEST_CHECK(open_tag.GetId() == "1");
	TEST_CHECK(open_tag.GetSize() == 2);
	TEST_CHECK(open_tag.GetAttribute(0).first == "font");
	TEST_CHECK(open_tag.GetAttribute(0).second == "magenta");
	TEST_CHECK(open_tag.GetAttribute(1).first == "size");
	TEST_CHECK(open_tag.GetAttribute(1).second == "big");
	TEST_CHECK(open_tag.CheckValidity());



	OpeningTag open_tag2("<opening>");
	TEST_CHECK(open_tag2.GetName() == "opening");
	TEST_CHECK(!(open_tag2.GetName() == "opening "));
	TEST_CHECK(open_tag2.GetId() == "");




	String line("<opening id=\"1\" font=\"magenta\" size=\"big\" >Opening Tag</opening>");
	Vector<String> tags;
	line.GetTags(tags);
	OpeningTag tag1(tags[0]);
	ClosingTag tag2(tags[2]);
	Text text3(tags[1]);
	TEST_CHECK(tag1.GetName() == "opening");
	TEST_CHECK(tag2.GetName() == "opening");
	TEST_CHECK(tag1.GetId() == "1");
	TEST_CHECK(tag1.CheckValidity());
	TEST_CHECK(tag2.CheckValidity());
	TEST_CHECK(tag1.GetAttribute(0).first == "font");
	TEST_CHECK(tag1.GetAttribute(0).second == "magenta");
	TEST_CHECK(tag1.GetAttribute(1).first == "size");
	TEST_CHECK(tag1.GetAttribute(1).second == "big");
	TEST_CHECK(tag1.CheckValidity());
	TEST_CHECK(text3 == (Text)"Opening Tag");


}



void TestXMLContainer()
{
	String line("<opening id=\"1\" font=\"magenta\" size=\"big\" >Opening Tag</opening>");
	Vector<String> tags;
	line.GetTags(tags);
	XMLContainer test_container;

	test_container.Add(tags[0]);
	test_container.Add(tags[1]);
	test_container.Add(tags[2]);

	TEST_CHECK(test_container[0].CheckValidity());
	TEST_CHECK(test_container[1].CheckValidity());
	TEST_CHECK(test_container[2].CheckValidity());


	TEST_CHECK(test_container[0] == "opening");
	TEST_CHECK(test_container[2] == "opening");

	TEST_CHECK(test_container[0].IsOpeningTag());
	TEST_CHECK(!(test_container[1].IsClosingTag() || test_container[1].IsOpeningTag()));
	TEST_CHECK(test_container[2].IsClosingTag());

	test_container.Remove(1, 1);

	TEST_CHECK(test_container[0] == "opening");
	TEST_CHECK(test_container[1] == "opening");

	TEST_CHECK(test_container[0].IsOpeningTag());
	TEST_CHECK(test_container[1].IsClosingTag());
}
void TestCommandPrompt()
{	
	String command_line("\topen that.xml ");
	Vector<String> command;
	command = GetCommand(command_line);

	TEST_CHECK(command[0] == "open");
	TEST_CHECK(command[1] == "that.xml");
	command_line = "\topen     ";
	command = GetCommand(command_line);
	TEST_CHECK(command[0] == "open");
	TEST_CHECK(command[1] == "");
}

TEST_LIST = {
	{"String", TestString},
	{"Vector", TestVector},
	{"XMLParts", TestXMLParts},
	{"XMLContainer",TestXMLContainer},
	{"CommandPrompt", TestCommandPrompt},
	{NULL, NULL} };*/