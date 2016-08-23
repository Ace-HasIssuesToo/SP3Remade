#include "Player.h"
#include "Input_PI.h"
#include "Render_PI.h"
#include "Texture_PI.h"
#include "Enemy_Poison.h"
#include "Enemy_Ghost.h"
#include "GameState.h"

PlayerClass* PlayerClass::m_pointer = new PlayerClass();

PlayerClass::PlayerClass()
	:movementSpeed(0)
	, PlayerPos(0, 0, 0)
	, PlayerPosOffSet(0, 0, 0)
	, PokeballPos(0,0,0)
	, playerShadow(0,0,0)
	, pokeballShadow(0,0,0)
	, sc(0,0,0)
	, LightOn(false)
	, LightRange(1)
{
}

PlayerClass::~PlayerClass()
{
}

void PlayerClass::Init()
{
	movementSpeed = 20;
	Runtime = 30;
	LightPower = 10.f;
	PlayerPosOffSet = PlayerPos = Render_PI::Window_Scale()*0.5;
	PlayerPos = Render_PI::Window_Scale() * 0.5;
	sc.Set(10.f, 10.f, 10.f);

	setPlayerMesh(Top);
	SpriteAnimation *saL, *saR, *saF, *saB;
	//Left Texture
	playerMeshLeft = MeshBuilder::GenerateSpriteAnimation("playerMeshLeft", 1, 4);
	playerMeshLeft->textureArray[0] = LoadTGA("Data//Texture//playerLeft.tga");		
	saL = dynamic_cast<SpriteAnimation*>(playerMeshLeft);
	if (saL)
	{
		saL->m_anim = new Animation();
		saL->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Down Texture
	playerMeshDownward = MeshBuilder::GenerateSpriteAnimation("playerMeshDown", 1, 4);
	playerMeshDownward->textureArray[0] = LoadTGA("Data//Texture//playerDown.tga");
	saB = dynamic_cast<SpriteAnimation*>(playerMeshDownward);
	if (saB)
	{
		saB->m_anim = new Animation();
		saB->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Top Texture
	playerMeshForward = MeshBuilder::GenerateSpriteAnimation("playerMeshTop", 1, 4);
	playerMeshForward->textureArray[0] = LoadTGA("Data//Texture//playerTop.tga");
	saF = dynamic_cast<SpriteAnimation*>(playerMeshForward);
	if (saF)
	{
		saF->m_anim = new Animation();
		saF->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//Right Texture
	playerMeshRight = MeshBuilder::GenerateSpriteAnimation("playerMeshRight", 1, 4);
	playerMeshRight->textureArray[0] = LoadTGA("Data//Texture//PlayerRight.tga");
	saR = dynamic_cast<SpriteAnimation*>(playerMeshRight);
	if (saR)
	{
		saR->m_anim = new Animation();
		saR->m_anim->Set(0, 3, 0, 1.f, true);
	}
	//playerMesh = nullptr;
	RunBar = MeshBuilder::GenerateQuad("Runbar", Color(0, 1, 0));
	LightBar = MeshBuilder::GenerateQuad("Lightbar", Color(1, 1, 1));

}
float PlayerClass::GetLightRange()
{
	if (LightOn == true)
	{
		LightRange = 3.f;
	}
	else if (LightOn == false)
	{
		LightRange = 1.f;
	}
	return LightRange;
}
void PlayerClass::Update(double dt, Map* map)
{
	playerShadow = PlayerPos;
	PlayerPos.z = 0;
	Vector3 Movement = Vector3();
	movementSpeed = 20;
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::Run])
	{
		if (Runtime > 0.f)
		{
			Runtime -= dt;
			movementSpeed *= Math::Max(1.f, Runtime);
		}
	}
	else
	{
		if (Runtime <= Max_Speed)
		{
			Runtime += 0.5 * dt;
		}
	}
	if (Runtime > Max_Speed)
	{
		Runtime = Max_Speed;
	}
	else if (Runtime < 0.f)
	{
		Runtime = 0;
	}

	if (Input_PI::pointer()->IsBeingPressed[Input_PI::Forward] == true)
	{
		Movement.y += movementSpeed * dt;
	}
	else if (Input_PI::pointer()->IsBeingPressed[Input_PI::Backward] == true)
	{
		Movement.y -= movementSpeed * dt;
	}
	if (Input_PI::pointer()->IsBeingPressed[Input_PI::Leftward] == true)
	{
		Movement.x -= movementSpeed * dt;
	}
	else if (Input_PI::pointer()->IsBeingPressed[Input_PI::Rightward] == true)
	{
		Movement.x += movementSpeed * dt;
	}

	if (Input_PI::pointer()->IsBeingPressed[Input_PI::OffLight] == true)
	{
		LightOn = false;
	}
	else if (Input_PI::pointer()->IsBeingPressed[Input_PI::OnLight] == true)
	{
		LightOn = true;
	}

	if (LightOn == true)
	{
		if (LightPower > 0.f)
		{
			LightPower -= 0.25 * dt;
		}
		else if (LightPower <= 0.f)
		{
			LightPower = 0.f;
			LightOn = false;
		}
	}

	if (getPlayerMesh2() == playerMeshForward)
	{
		SpriteAnimation *saT = dynamic_cast<SpriteAnimation*>(playerMeshForward);
		if (saT)
		{
			saT->Update(dt);
			saT->m_anim->animActive = true;
		}
	}
	else if (getPlayerMesh2() == playerMeshDownward)
	{
		SpriteAnimation *saD = dynamic_cast<SpriteAnimation*>(playerMeshDownward);
		if (saD)
		{
			saD->Update(dt);
			saD->m_anim->animActive = true;
		}
	}
	else if (getPlayerMesh2() == playerMeshLeft)
	{
		SpriteAnimation *saL = dynamic_cast<SpriteAnimation*>(playerMeshLeft);
		if (saL)
		{
			saL->Update(dt);
			saL->m_anim->animActive = true;
		}
	}
	else if (getPlayerMesh2() == playerMeshRight)
	{
		SpriteAnimation *saR = dynamic_cast<SpriteAnimation*>(playerMeshRight);
		if (saR)
		{
			saR->Update(dt);
			saR->m_anim->animActive = true;
		}
	}

	Movement = Enemy_Poison::pointer()->Poison(Movement);
	Movement = Enemy_Ghost::pointer()->Freeze(Movement);

	if (Movement.y > 0)
	{
		setPlayerMesh(Top);
	}
	else if (Movement.y < 0)
	{
		setPlayerMesh(Down);
	}
	if (Movement.x < 0)
	{
		setPlayerMesh(Left);
	}
	else if (Movement.x > 0)
	{
		setPlayerMesh(Right);
	}
	playerShadow += Movement;
	//Kind of Collision
	cout << movementSpeed<<" / "<< Movement.x << " / " << Movement.y << endl;
	if (map->Get_Type(playerShadow + PlayerPosOffSet) == "Wall")
	{

	}
	else if (map->Get_Type(playerShadow + PlayerPosOffSet) == "Floor")
	{
		PlayerPos = playerShadow;
	}
	else if (map->Get_Type(playerShadow + PlayerPosOffSet) == "VendingMachine")
	{
		Runtime += 5 * dt;
		if (Runtime > Max_Speed)
		{
			Runtime = Max_Speed;
		}
	}
	else if (map->Get_Type(playerShadow + PlayerPosOffSet) == "Treasure")
	{
		LightPower = 10.f;
	}
	//Keep Player in window
	float Limitation_size = 30;
	if (PlayerPos.x > (Render_PI::Window_Scale().x - Limitation_size))
	{
		double difference = PlayerPos.x - (Render_PI::Window_Scale().x - Limitation_size);
		PlayerPosOffSet.x += difference;
		PlayerPos.x = (Render_PI::Window_Scale().x - Limitation_size);
	}
	else if (PlayerPos.x < Limitation_size)
	{
		double difference = PlayerPos.x - (Limitation_size);
		PlayerPosOffSet.x += difference;
		PlayerPos.x = (Limitation_size);
	}
	if (PlayerPos.y >(Render_PI::Window_Scale().y - Limitation_size))
	{
		double difference = PlayerPos.y - (Render_PI::Window_Scale().y - Limitation_size);
		PlayerPosOffSet.y += difference;
		PlayerPos.y = (Render_PI::Window_Scale().y - Limitation_size);
	}
	else if (PlayerPos.y < Limitation_size)
	{
		double difference = PlayerPos.y - (Limitation_size);
		PlayerPosOffSet.y += difference;
		PlayerPos.y = (Limitation_size);
	}
}

void PlayerClass::clearPlayer()
{
	movementSpeed = 20;
	Runtime = 30;
	PlayerPosOffSet = PlayerPos = Render_PI::Window_Scale()*0.5;
	PlayerPos = Render_PI::Window_Scale() * 0.5;
	sc.Set(10.f, 10.f, 10.f);
	LightOn = false;
	LightPower = 10.f;
	LightRange = 1.f;
}

void PlayerClass::Exit()
{
	if (playerMeshLeft != nullptr)
	{
		delete playerMeshLeft;
		playerMeshLeft = nullptr;
	};
	if (playerMeshRight != nullptr)
	{
		delete playerMeshRight;
		playerMeshRight = nullptr;
	};
	if (playerMeshForward != nullptr)
	{
		delete playerMeshForward;
		playerMeshForward = nullptr;
	};
	if (playerMeshDownward != nullptr)
	{
		delete playerMeshDownward;
		playerMeshDownward = nullptr;
	};
	if (RunBar != nullptr)
	{
		delete RunBar;
		RunBar = nullptr;
	};
	if (LightBar != nullptr)
	{
		delete LightBar;
		LightBar = nullptr;
	}
	if (m_pointer != nullptr)
	{
		delete m_pointer;
		m_pointer = nullptr;
	};
}

Vector3 PlayerClass::getPlayerPos()
{
	return PlayerPos;
}
Vector3 PlayerClass::getPlayerPosOffSet()
{
	return PlayerPosOffSet;
}
Vector3 PlayerClass::getPlayerScale()
{
	sc.z = 0;
	return sc;
}

void PlayerClass::setPlayerMesh(PlayerClass::PlayerMeshes mesh)
{
	this->playerMesh = mesh;
}

Mesh* PlayerClass::getPlayerMesh2()
{
	switch (playerMesh)
	{
	case Left:
		return playerMeshLeft;
		break;
	case Right:
		return playerMeshRight;
		break;
	case Top:
		return playerMeshForward;
		break;
	case Down:
		return playerMeshDownward;
		break;
	}
}

void PlayerClass::Renderplayer()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(PlayerClass::getPlayerMesh2(), false, Vector3(PlayerPos), Vector3(getPlayerScale()));
	Render_PI::pointer()->modelStack_Set(false);

	Render_PI::pointer()->modelStack_Set(true);
	Vector3 Pos = (Vector3(5, 5, 0) + Vector3(Runtime * 10, 10, 0))*0.5f;
	Render_PI::pointer()->RenderMeshIn2D(RunBar, false, Pos, Vector3(Runtime * 10, 10, 5));
	Render_PI::pointer()->modelStack_Set(false);

	Render_PI::pointer()->modelStack_Set(true);
	Vector3 Pos2 = (Vector3(5, 5, 0) + Vector3(LightPower * 10, 180, 0))*0.5f;
	Render_PI::pointer()->RenderMeshIn2D(LightBar, false, Pos2, Vector3(LightPower * 10, 10, 5));
	Render_PI::pointer()->modelStack_Set(false);

	std::ostringstream ss;
	ss.precision(5);
	ss << "Balls Left: " << PokeballInfo::pointer()->getNumOfBalls();
	Render_PI::pointer()->RenderTextOnScreen(GameState::pointer()->GetText(), ss.str(), Color(1, 0.25f, 0), (Render_PI::Window_Scale() * 0.3, 10, 1), Vector3(5, 5, 1));
}