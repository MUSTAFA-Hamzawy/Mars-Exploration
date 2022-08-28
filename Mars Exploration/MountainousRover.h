#ifndef MountainousRover_
#define MountainousRover_

#include "Rover.h"

class MountainousRover : public Rover
{
	EmergencyMission* emergencyMission;
	MountainousMission* mountainousMission;
	int CheckupDuration;
//	int MissionsCount;
	double Speed;
	int ID;
	char MissionType;
public:
	MountainousRover(double speed = -1, int checkDuration = -1, int missionsCount = -1, int id = -1);
	virtual bool available();     // check if the rover is available to be assigned a mission or in checkup
	virtual void Set_Speed(double speed);
	virtual void Set_CheckupDuration(int checkDuration);
	//virtual void Set_MissionsCount(int missionsCount);
	virtual void Set_MissionType(char w);
	void setAllData(int CheckupDuration,int MissionsCount, double Speed, int id);
	virtual double Get_Speed()const;
	//virtual int Get_MissionsCount()const;
	virtual int Get_CheckupDuration()const;
	virtual char Get_MissionType() const;
	bool assign_EmergencyMission(EmergencyMission* mission);
	bool assign_MountainousMission(MountainousMission* mission);
	virtual ~MountainousRover();
	virtual void Set_ID(int id);
	virtual int Get_ID() const;
	EmergencyMission* get_EmergencyMission();
	MountainousMission* get_MountainousMission();

	void set_Missions(EmergencyMission* e, MountainousMission* m);

	MountainousRover(const MountainousRover& obj);
	void operator=(const MountainousRover& obj);
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