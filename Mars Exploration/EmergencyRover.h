#ifndef Emergency_Rover_
#define Emergency_Rover_

#include "Rover.h"

class EmergencyRover : public Rover
{

	EmergencyMission* emergencyMission;
	MountainousMission* mountainousMission;
	int CheckupDuration;
//	int MissionsCount;
	double Speed;
	int ID;
	char MissionType;
public:
	EmergencyRover(double speed = -1, int checkDuration = -1, int missionsCount = -1, int id = -1);
	virtual bool available();
	virtual void Set_Speed(double speed);
	virtual void Set_CheckupDuration(int checkDuration);
	//virtual void Set_MissionsCount(int missionsCount);
	void setAllData(int CheckupDuration, int MissionsCount, double Speed, int id);
	virtual double Get_Speed();
	//virtual int Get_MissionsCount();
	virtual int Get_CheckupDuration();
	bool assign_EmergencyMission(EmergencyMission* mission);
	bool assign_MountainousMission(MountainousMission* mission);
	// setter for priority of mission for emergency only
	virtual void Set_ID(int id);
	virtual int Get_ID() const;
	EmergencyMission* get_EmergencyMission();
	MountainousMission* get_MountainousMission();
	virtual void Set_MissionType(char w);
	virtual char Get_MissionType();
	virtual ~EmergencyRover();

	void set_Missions(EmergencyMission* e, MountainousMission* m);

	EmergencyRover(const EmergencyRover& obj);
	void  operator=(const EmergencyRover & obj);
};

/*
#pragma once
#include "Rover.h"
class EmergencyRover : public Rover
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