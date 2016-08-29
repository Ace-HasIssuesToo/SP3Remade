#include "DecoText.h"

DecoText* DecoText::m_pointer = new DecoText();

void DecoText::Init()
{
	m_pointer->Deco_Data.insert(std::pair<std::string, std::string>("Default", "1010111010101110101010"));
	if (Set("Data\\Texture\\DecoText.csv") == false)
	{
	}
}

void DecoText::Exit()
{
	std::map<std::string, std::string>::iterator it;
	for (it = m_pointer->Deco_Data.begin(); it != m_pointer->Deco_Data.end(); ++it)
	{
	}
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	}

}

string DecoText::Get(std::string Deco_Name)
{
	std::map < std::string, std::string > ::iterator it;
	it = m_pointer->Deco_Data.find(Deco_Name);
	if (it == m_pointer->Deco_Data.end())
	{
		it = m_pointer->Deco_Data.find("Default");
	}
	return it->second;
}

bool DecoText::Set(std::string FileName)
{
	std::ifstream file(FileName);	 // declare file stream: 
	std::string Raw_Data;	//the entire line WITH commas
	std::stringstream Datas;//Datas to process
	std::string Porcessed_Data; //individual values
	std::string Deco_Name;
	std::string Deco_interact;
	if (file.is_open())
	{
		while (getline(file, Raw_Data)) //read entire line
		{
			Deco_Name = "";
			Deco_interact = "";
			Datas << Raw_Data;    //create istringstream for parsing
			while (getline(Datas, Porcessed_Data, ',')) //parse for commas
			{
				if (Deco_Name.size() == 0)
				{
					Deco_Name = Porcessed_Data;
				}
				else if (Deco_interact.size() == 0)
				{
					Deco_interact = Porcessed_Data;
				}
				else
				{
					cout << Deco_Name << " texture array have error" << endl;
					return false;
				}
			}
			if (Deco_interact.size() == 0)
			{
				cout << Deco_Name << " texture array have error" << endl;
				return false;
			}
			else if (Deco_Name.size() == 0)
			{
				cout << Deco_Name << " have error" << endl;
				return false;
			}
			else
			{
				m_pointer->Deco_Data.insert(std::pair<std::string, std::string>(Deco_Name, Deco_interact));
			}
			Datas.clear();
		}
	}
	return true;
}
