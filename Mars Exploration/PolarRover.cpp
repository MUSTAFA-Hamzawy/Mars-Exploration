#include "PolarRover.h"


PolarRover  ::PolarRover(double speed, int checkDuration, int missionsCount)
{
	Set_Speed(speed);
	Set_CheckupDuration(checkDuration);
	Set_MissionsCount(missionsCount);
	emergencyMission = nullptr;
	polarMission = nullptr;
}



bool PolarRover  ::available()
{
	return MissionsCount > 0;
}


void PolarRover  ::Set_Speed(double speed)
{
	Speed = (speed > 0) ? speed : -1;
}


void PolarRover  ::Set_CheckupDuration(int checkDuration)
{
	CheckupDuration = (CheckupDuration > 0) ? CheckupDuration : -1;
}


void  PolarRover  ::Set_MissionsCount(int missionsCount)
{
	MissionsCount = (MissionsCount > 0) ? MissionsCount : -1;
}


void PolarRover::setAllData(int CheckupDuration, int MissionsCount, double Speed)
{
	Set_Speed(Speed);
	Set_CheckupDuration(CheckupDuration);
	Set_MissionsCount(MissionsCount);
}


double  PolarRover  ::Get_Speed()const
{
	return Speed;
}


int  PolarRover  ::Get_MissionsCount()const
{
	return MissionsCount;
}


int  PolarRover  ::Get_CheckupDuration()const
{
	return CheckupDuration;
}


bool PolarRover::assign_EmergencyMission(EmergencyMission* mission)
{
	if (this->available() && emergencyMission == nullptr)
	{
		emergencyMission = mission;
		MissionsCount--;
		return true;
	}
	return false;
}


bool PolarRover::assign_PolarMission(PolarMission* mission)
{
	if (this->available() && polarMission == nullptr)
	{
		polarMission = mission;
		MissionsCount--;
		return true;
	}
	return false;
}


PolarRover  :: ~PolarRover()
{
	emergencyMission = nullptr;
	polarMission = nullptr;
}

EmergencyMission* PolarRover::get_EmergencyMission()
{
	return emergencyMission;
}

PolarMission* PolarRover::get_PolarMission()
{
	return polarMission;
}

void PolarRover::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

int PolarRover::Get_ID() const
{
	return ID;
}
