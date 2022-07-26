#include"Rover.h"




Rover :: Rover(double speed , int checkDuration , int missionsCount )
{
	Set_Speed(speed);
	Set_CheckupDuration(checkDuration);
	Set_MissionsCount(missionsCount);
}
bool Rover::available()
{
	return false;
}

void Rover::Set_Speed(double speed)
{
	return;
}

void Rover::Set_CheckupDuration(int checkDuration)
{
	return;
}

void  Rover::Set_MissionsCount(int missionsCount)
{
	return;
}

double  Rover::Get_Speed()const
{
	return -1;
}

int Rover::Get_MissionsCount()const
{
	return -1;
}

int  Rover::Get_CheckupDuration() const
{
	return -1;
}

Rover :: ~Rover()
{
	return;
}

void Rover::Set_ID(int id)
{
	return;
}

int Rover::Get_ID() const
{
	return -1;
}