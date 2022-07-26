#include "Rover.h"

template <class T >
bool Rover < T > ::available()
{
	return MissionsCount == 0;
}

template <class T >
void Rover < T > ::Set_Speed(int speed)
{
	Speed = (speed > 0) ? speed : -1;
}

template <class T >
void Rover < T > ::Set_CheckupDuration(int checkDuration)
{
	CheckupDuration = (CheckupDuration > 0) ? CheckupDuration : -1;
}

template <class T >
void  Rover < T > ::Set_MissionsCount(int missionsCount)
{
	MissionsCount = (MissionsCount > 0) ? MissionsCount : -1;
}

template <class T >
int  Rover < T > ::Get_Speed()
{
	return Speed;
}

template <class T >
int  Rover < T > ::Get_MissionsCount()
{
	return MissionsCount;
}

template <class T >
int  Rover < T > ::Get_CheckupDuration()
{
	return CheckupDuration;
}

template <class T >
Rover < T > :: ~Rover()
{

}