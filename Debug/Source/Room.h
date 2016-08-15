#ifndef ROOM
#define ROOM

class Room
{
public:
	void Set_Room(int x, int y, char input){ Map[x][y] = input; };
	char Get_Room(int x, int y){ return Map[x][y]; };
	void Clear_Room()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0;  j < 9; j++)
			{
				Map[i][j] = char(' ');
			}
		}
	};
private:
	char Map[10][10];
};
#endif