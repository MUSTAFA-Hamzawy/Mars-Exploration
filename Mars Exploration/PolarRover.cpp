#include "PolarRover.h"


PolarRover  ::PolarRover(double speed, int checkDuration, int missionsCount ,int id)
{
	Set_Speed(speed);
	Set_CheckupDuration(checkDuration);
	Set_MissionsCount(missionsCount);
	Set_ID(id);
}



bool PolarRover  ::available()
{
	return Current_MissionsCount > 0;
}


void PolarRover  ::Set_Speed(double speed)
{
	Speed = (speed > 0) ? speed : -1;
}


void PolarRover  ::Set_CheckupDuration(int checkDuration)
{
	CheckupDuration = (checkDuration > 0) ? checkDuration : -1;
}

/*
void  PolarRover  ::Set_MissionsCount(int missionsCount)
{
	MissionsCount = (MissionsCount > 0) ? MissionsCount : -1;
}
*/

void PolarRover::setAllData(int CheckupDuration, int MissionsCount, double Speed , int id)
{
	Set_Speed(Speed);
	Set_CheckupDuration(CheckupDuration);
	Set_MissionsCount(MissionsCount);
	Set_ID(id);
}


double  PolarRover  ::Get_Speed()const
{
	return Speed;
}

/*
int  PolarRover  ::Get_MissionsCount()const
{
	return MissionsCount;
}
*/

int  PolarRover  ::Get_CheckupDuration()const
{
	return CheckupDuration;
}


bool PolarRover::assign_EmergencyMission(EmergencyMission* mission)
{
	if (this->available() && emergencyMission == nullptr)
	{
		emergencyMission = mission;
		Current_MissionsCount--;
		return true;
	}
	return false;
}


bool PolarRover::assign_PolarMission(PolarMission* mission)
{
	if (this->available() && polarMission == nullptr)
	{
		polarMission = mission;
		Current_MissionsCount--;
		return true;
	}
	return false;
}


PolarRover  :: ~PolarRover()
{

}

EmergencyMission* PolarRover::get_EmergencyMission()
{
	return emergencyMission;
}

PolarMission* PolarRover::get_PolarMission()
{
	return polarMission;
}

void PolarRover::set_Missions(EmergencyMission* emergencyMission, PolarMission* polarMission)
{
	this->emergencyMission = emergencyMission;
	this->polarMission = polarMission;
}

PolarRover::PolarRover(const PolarRover& obj)
{
	emergencyMission = obj.emergencyMission;
	polarMission = obj.polarMission;
	CheckupDuration = obj.CheckupDuration;
	Speed = obj.Speed;
	ID = obj.ID;
	MissionType = obj.MissionType;
	Default_MissionsCount = obj.Default_MissionsCount;
	Current_MissionsCount = obj.Current_MissionsCount;
}

void PolarRover::operator=(const PolarRover& obj)
{
	emergencyMission = obj.emergencyMission;
	polarMission = obj.polarMission;
	CheckupDuration = obj.CheckupDuration;
	Speed = obj.Speed;
	ID = obj.ID;
	MissionType = obj.MissionType;
	Default_MissionsCount = obj.Default_MissionsCount;
	Current_MissionsCount = obj.Current_MissionsCount;
}

void PolarRover::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

int PolarRover::Get_ID() const
{
	return ID;
}

void PolarRover::Set_MissionType(char w)
{
	MissionType = w;
}
char PolarRover::Get_MissionType() const
{
	return MissionType;
}

