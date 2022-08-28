#include"Rover.h"


Rover :: Rover(double speed , int checkDuration , int missionsCount, int id)
{
	Set_Speed(speed);
	Set_CheckupDuration(checkDuration);
	Set_MissionsCount(missionsCount);
	Set_ID(id);
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
	Default_MissionsCount = (missionsCount > 0) ? missionsCount : -1;
	Current_MissionsCount = Default_MissionsCount;
	
}

double  Rover::Get_Speed()const
{
	return -1;
}

int Rover::Get_MissionsCount()const
{
	return Current_MissionsCount;
}

int  Rover::Get_CheckupDuration() const
{
	return -1;
}

Rover :: ~Rover()
{
	return;
}

void Rover::reset_MissionCout()
{
	Current_MissionsCount = Default_MissionsCount;
}

void Rover::Set_ID(int id)
{
	return;
}

int Rover::Get_ID() const
{
	return -1;
}

void Rover::Set_MissionType(char w)
{
	MissionType = w;
}
char Rover::Get_MissionType() const
{
	return MissionType;
}