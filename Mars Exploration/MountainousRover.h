#ifndef MountainousRover_
#define MountainousRover_

#include "Rover.h"

class EmergencyMission;
class MountainousMission;

class MountainousRover : public Rover
{
	EmergencyMission* emergencyMission;
	MountainousMission* mountainousMission;
	int CheckupDuration;
	int MissionsCount;
	double Speed;
	int ID;

public:
	MountainousRover(double speed = -1, int checkDuration = -1, int missionsCount = -1);
	virtual bool available();     // check if the rover is available to be assigned a mission or in checkup
	virtual void Set_Speed(double speed);
	virtual void Set_CheckupDuration(int checkDuration);
	virtual void Set_MissionsCount(int missionsCount);
	void setAllData(int CheckupDuration,int MissionsCount, double Speed);
	virtual double Get_Speed()const;
	virtual int Get_MissionsCount()const;
	virtual int Get_CheckupDuration()const;
	bool assign_EmergencyMission(EmergencyMission* mission);
	bool assign_MountainousMission(MountainousMission* mission);
	virtual ~MountainousRover();
	virtual void Set_ID(int id);
	virtual int Get_ID() const;
	EmergencyMission* get_EmergencyMission();
	MountainousMission* get_MountainousMission();
};

/*
#pragma once
#include "Rover.h"
class MountainousRover : public Rover
{
	// pointer of emergencyMission
	// pointer of mountainousMission
public:
	bool assignEmergency(// pointer of emergencyMission);
	bool assignMountainous(// pointer of mountainousMission);
	bool assign();
};

*/

#endif