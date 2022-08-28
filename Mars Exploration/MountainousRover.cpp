#include "MountainousRover.h"



MountainousRover  ::MountainousRover(double speed, int checkDuration, int missionsCount, int id)
{
	Set_Speed(speed);
	Set_CheckupDuration(checkDuration);
	Set_MissionsCount(missionsCount);
	Set_ID(id);
}



bool MountainousRover ::available()
{
	return Current_MissionsCount > 0;
}


void MountainousRover  ::Set_Speed(double speed)
{
	this->Speed = speed;
}


void MountainousRover  ::Set_CheckupDuration(int checkDuration)
{
	CheckupDuration = (checkDuration > 0) ? checkDuration : -1;
}

/*
void  MountainousRover  ::Set_MissionsCount(int missionsCount)
{
	MissionsCount = (MissionsCount > 0) ? MissionsCount : -1;
}
*/

void MountainousRover::setAllData(int CheckupDuration, int MissionsCount, double Speed, int id)
{
	Set_Speed(Speed);
	Set_CheckupDuration(CheckupDuration);
	Set_MissionsCount(MissionsCount);
	Set_ID(id);
}


double  MountainousRover  ::Get_Speed()const
{
	return Speed;
}

/*
int  MountainousRover  ::Get_MissionsCount()const
{
	return MissionsCount;
}
*/

int  MountainousRover  ::Get_CheckupDuration()const
{
	return CheckupDuration;
}


bool MountainousRover::assign_EmergencyMission(EmergencyMission* mission)
{
	if (this->available() && emergencyMission == nullptr)
	{
		emergencyMission = mission;
		Current_MissionsCount--;
		return true;
	}
	return false;
}


bool MountainousRover::assign_MountainousMission(MountainousMission* mission)
{
	if (this->available() && mountainousMission == nullptr)
	{
		mountainousMission = mission;
		Current_MissionsCount--;
		return true;
	}
	return false;
}



MountainousRover  :: ~MountainousRover()
{

}

EmergencyMission* MountainousRover::get_EmergencyMission()
{
	return emergencyMission;
}

MountainousMission* MountainousRover::get_MountainousMission()
{
	return mountainousMission;
}

void MountainousRover::set_Missions(EmergencyMission* e, MountainousMission* m)
{
	emergencyMission = e;
	mountainousMission = m;
}

MountainousRover::MountainousRover(const MountainousRover& obj)
{
	emergencyMission = obj.emergencyMission;
	mountainousMission = obj.mountainousMission;
	CheckupDuration = obj.CheckupDuration;
	Speed = obj.Speed;
	ID = obj.ID;
	MissionType = obj.MissionType;
	Default_MissionsCount = obj.Default_MissionsCount;
	Current_MissionsCount = obj.Current_MissionsCount;
}

void MountainousRover::operator=(const MountainousRover& obj)
{
	emergencyMission = obj.emergencyMission;
	mountainousMission = obj.mountainousMission;
	CheckupDuration = obj.CheckupDuration;
	Speed = obj.Speed;
	ID = obj.ID;
	MissionType = obj.MissionType;
	Default_MissionsCount = obj.Default_MissionsCount;
	Current_MissionsCount = obj.Current_MissionsCount;
}

void MountainousRover::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

int MountainousRover::Get_ID() const
{
	return ID;
}

void MountainousRover::Set_MissionType(char w)
{
	MissionType = w;
}
char MountainousRover::Get_MissionType() const
{
	return MissionType;
}