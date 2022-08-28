#include "EmergencyRover.h"


EmergencyRover::EmergencyRover(double speed, int checkDuration, int missionsCount, int id)
{
	Set_Speed(speed);
	Set_CheckupDuration(checkDuration);
	Set_MissionsCount(missionsCount);
	Set_ID(id);
}


bool EmergencyRover::available()
{
	return Current_MissionsCount > 0;
}


void EmergencyRover::Set_Speed(double speed)
{
	Speed = (speed > 0) ? speed : -1;
}


void EmergencyRover::Set_CheckupDuration(int checkDuration)
{
	CheckupDuration = (checkDuration > 0) ? checkDuration : -1;
}

/*
void  EmergencyRover::Set_MissionsCount(int missionsCount)
{
	MissionsCount = (MissionsCount > 0) ? MissionsCount : -1;
}
*/

void EmergencyRover::setAllData(int CheckupDuration, int MissionsCount, double Speed, int id)
{
	Set_Speed(Speed);
	Set_CheckupDuration(CheckupDuration);
	Set_MissionsCount(MissionsCount);
	Set_ID(id);
}


double  EmergencyRover::Get_Speed()
{
	return Speed;
}

/*
int  EmergencyRover::Get_MissionsCount()
{
	return MissionsCount;
}
*/

int  EmergencyRover::Get_CheckupDuration()
{
	return CheckupDuration;
}


bool EmergencyRover::assign_EmergencyMission(EmergencyMission* mission)
{
	if (this->available() && emergencyMission == nullptr)
	{
		emergencyMission = mission;
		Current_MissionsCount--;
		return true;
	}
	return false;
}


bool EmergencyRover::assign_MountainousMission(MountainousMission* mission)
{
	if (this->available() && mountainousMission == nullptr)
	{
		mountainousMission = mission;
		Current_MissionsCount--;
		return true;
	}
	return false;
}

EmergencyMission* EmergencyRover::get_EmergencyMission()
{
	return emergencyMission;
}

MountainousMission* EmergencyRover::get_MountainousMission()
{
	return mountainousMission;
}


EmergencyRover:: ~EmergencyRover()
{


}

void EmergencyRover::set_Missions(EmergencyMission* e, MountainousMission* m)
{
	emergencyMission = e;
	mountainousMission = m;
}

EmergencyRover::EmergencyRover(const EmergencyRover& obj)
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

void EmergencyRover::operator=(const EmergencyRover& obj)
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

void EmergencyRover::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

int EmergencyRover::Get_ID() const
{
	return ID;
}

void EmergencyRover::Set_MissionType(char w)
{
	MissionType = w;
}

char EmergencyRover::Get_MissionType()
{
	return MissionType;
}