#include "EmergencyRover.h"


EmergencyRover::EmergencyRover(double speed, int checkDuration, int missionsCount)
{
	Set_Speed(speed);
	Set_CheckupDuration(checkDuration);
	Set_MissionsCount(missionsCount);
	emergencyMission = nullptr;
	mountainousMission = nullptr;
}


bool EmergencyRover::available()
{
	return MissionsCount > 0;
}


void EmergencyRover::Set_Speed(double speed)
{
	Speed = (speed > 0) ? speed : -1;
}


void EmergencyRover::Set_CheckupDuration(int checkDuration)
{
	CheckupDuration = (CheckupDuration > 0) ? CheckupDuration : -1;
}


void  EmergencyRover::Set_MissionsCount(int missionsCount)
{
	MissionsCount = (MissionsCount > 0) ? MissionsCount : -1;
}


void EmergencyRover::setAllData(int CheckupDuration, int MissionsCount, double Speed)
{
	Set_Speed(Speed);
	Set_CheckupDuration(CheckupDuration);
	Set_MissionsCount(MissionsCount);
}


double  EmergencyRover::Get_Speed()
{
	return Speed;
}


int  EmergencyRover::Get_MissionsCount()
{
	return MissionsCount;
}


int  EmergencyRover::Get_CheckupDuration()
{
	return CheckupDuration;
}


bool EmergencyRover::assign_EmergencyMission(EmergencyMission* mission)
{
	if (this->available() && emergencyMission == nullptr)
	{
		emergencyMission = mission;
		MissionsCount--;
		return true;
	}
	return false;
}


bool EmergencyRover::assign_MountainousMission(MountainousMission* mission)
{
	if (this->available() && mountainousMission == nullptr)
	{
		mountainousMission = mission;
		MissionsCount--;
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
	emergencyMission = nullptr;
	mountainousMission = nullptr;

}

void EmergencyRover::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

int EmergencyRover::Get_ID() const
{
	return ID;
}