#include "EnemyGhost.h"
#include "Render_PI.h"
#include "Texture_PI.h"
EnemyGhost* EnemyGhost::c_enemyGhost = new EnemyGhost();

void EnemyGhost::Init()
{
	ghostPos = (Render_PI::Window_Scale() * 0.5);
}
void EnemyGhost::Update(double dt, Map map)
{
	ghostShadow = ghostPos;
	//ghost will move randomly until every 10 seconds
	ghostTimer += dt;
	ghostShadow.x += dirX * dt;
	ghostShadow.y += dirY * dt;
	if (map.Get_Type(ghostShadow) == "Wall")
	{
		dirX = -dirX;
		dirY = -dirY;
		dirX += Math::RandFloatMinMax(-5, 5);
		dirY += Math::RandFloatMinMax(-5, 5);
	}
	else if (map.Get_Type(ghostShadow) == "Floor")
	{
		ghostPos = ghostShadow;
	}
	if (ghostTimer > 10.f)
	{
		//teleport ghost to 1 tile before player position
		
		ghostStayTimer += dt;
		if (ghostStayTimer > 3.f)
		{
			//ghost will move away again
		}
		ghostTimer = 0.0f;
	}
}
void EnemyGhost::RenderGhost()
{
	Render_PI::pointer()->modelStack_Set(true);
	Render_PI::pointer()->RenderMeshIn2D(Texture::Get("gastly"), false, Vector3(ghostPos), Vector3(1, 1, 1));
	Render_PI::pointer()->modelStack_Set(false);
}
void EnemyGhost::Exit()
{

}
