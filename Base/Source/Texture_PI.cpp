#include "Texture_PI.h"

std::map<std::string, Mesh*> Texture::Textures_Data;

void Texture::Init()
{
	Mesh* X = MeshBuilder::GenerateQuad("Default",Color(1,1,1));
	X->textureArray[0] = LoadTGA("Data\\Default\\Default_Texture.tga");
	Textures_Data.insert(std::pair<std::string, Mesh*>(X->name, X));
	if (Set("Data\\Texture\\Texture.csv") == false)
	{
		cout << "Error" << endl;
	}
}

void Texture::Exit()
{
	for (auto& x : Textures_Data)
	{
		if (x.second != nullptr)
		{
			delete x.second;
			x.second = nullptr;
		}
	}
	Textures_Data.clear();
}

Mesh* Texture::Get(std::string Mesh_Name)
{
	std::map<std::string, Mesh*>::iterator it;
	it = Textures_Data.find(Mesh_Name);
	if (it == Textures_Data.end())
	{
		it = Textures_Data.find("Default");
	}
	Mesh* return_mesh = it->second;
	return return_mesh;
}

bool Texture::Set(Mesh* Mesh_)
{
	std::pair<std::map<std::string, Mesh*>::iterator, bool> ret;
	ret = Textures_Data.insert(std::pair<std::string, Mesh*>(Mesh_->name, Mesh_));
	if (ret.second == false) {
		return false;
	}
	return true;
}

bool Texture::Set(std::string FileName)
{
	std::ifstream file(FileName);	 // declare file stream: 
	std::string Raw_Data;	//the entire line WITH commas
	std::stringstream Datas;//Datas to process
	std::string Porcessed_Data; //individual values
	std::string TGA_File;
	std::string Mesh_Name;
	if (file.is_open())
	{
		while (getline(file, Raw_Data)) //read entire line
		{
			TGA_File = "";
			Mesh_Name = "";
			Datas << Raw_Data;    //create istringstream for parsing
			while (getline(Datas, Porcessed_Data, ',')) //parse for commas
			{
				if (Mesh_Name.size() == 0)
				{
					Mesh_Name = Porcessed_Data;
				}
				else if (TGA_File.size() == 0)
				{
					TGA_File = Porcessed_Data;
				}
				else
				{
					return false;
				}
			}
			Mesh* X = MeshBuilder::GenerateQuad(Mesh_Name, Color(1, 1, 1));
			X->textureArray[0] = LoadTGA(TGA_File.c_str());
			if (X->textureArray[0] == 0)
			{
				return false;
				cout << Mesh_Name << " texture array have error" << endl;
			}
			if (Set(X) == false)
			{
				cout << Mesh_Name << " have error" << endl;
			}
			Datas.clear();
		}
	}
		return true;
}
