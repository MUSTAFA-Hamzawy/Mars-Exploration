#include "MountainousRover.h"



MountainousRover  ::MountainousRover(double speed, int checkDuration, int missionsCount)
{
	Set_Speed(speed);
	Set_CheckupDuration(checkDuration);
	Set_MissionsCount(missionsCount);
	emergencyMission  = nullptr;
	mountainousMission = nullptr;
}



bool MountainousRover ::available()
{
	return MissionsCount > 0;
}


void MountainousRover  ::Set_Speed(double speed)
{
	Speed = (speed > 0) ? speed : -1;
}


void MountainousRover  ::Set_CheckupDuration(int checkDuration)
{
	CheckupDuration = (CheckupDuration > 0) ? CheckupDuration : -1;
}


void  MountainousRover  ::Set_MissionsCount(int missionsCount)
{
	MissionsCount = (MissionsCount > 0) ? MissionsCount : -1;
}


void MountainousRover::setAllData(int CheckupDuration, int MissionsCount, double Speed)
{
	Set_Speed(Speed);
	Set_CheckupDuration(CheckupDuration);
	Set_MissionsCount(MissionsCount);
}


double  MountainousRover  ::Get_Speed()const
{
	return Speed;
}


int  MountainousRover  ::Get_MissionsCount()const
{
	return MissionsCount;
}


int  MountainousRover  ::Get_CheckupDuration()const
{
	return CheckupDuration;
}


bool MountainousRover::assign_EmergencyMission(EmergencyMission* mission)
{
	if (this->available() && emergencyMission == nullptr)
	{
		emergencyMission = mission;
		MissionsCount--;
		return true;
	}
	return false;
}


bool MountainousRover::assign_MountainousMission(MountainousMission* mission)
{
	if (this->available() && mountainousMission == nullptr)
	{
		mountainousMission = mission;
		MissionsCount--;
		return true;
	}
	return false;
}



MountainousRover  :: ~MountainousRover()
{
	emergencyMission = nullptr;
	mountainousMission = nullptr;
}

EmergencyMission* MountainousRover::get_EmergencyMission()
{
	return emergencyMission;
}

MountainousMission* MountainousRover::get_MountainousMission()
{
	return mountainousMission;
}

void MountainousRover::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

int MountainousRover::Get_ID() const
{
	return ID;
}