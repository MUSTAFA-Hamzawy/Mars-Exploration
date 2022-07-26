#ifndef PolarRover_
#define PolarRover_

#include"Rover.h"

class PolarMission;
class EmergencyMission;

class PolarRover : public Rover
{
	EmergencyMission* emergencyMission;
	PolarMission* polarMission;
	int CheckupDuration;
	int MissionsCount;
	double Speed;
	int ID;

public:
	PolarRover(double speed = -1, int checkDuration = -1, int missionsCount = -1);
	virtual bool available();     // check if the rover is available to be assigned a mission or in checkup
	virtual void Set_Speed(double speed);
	virtual void Set_CheckupDuration(int checkDuration);
	virtual void Set_MissionsCount(int missionsCount);
	void setAllData(int CheckupDuration, int MissionsCount, double Speed);
	virtual double Get_Speed()const;
	virtual int Get_MissionsCount()const;
	virtual int Get_CheckupDuration()const;
	bool assign_EmergencyMission(EmergencyMission* mission);
	bool assign_PolarMission(PolarMission* mission);
	virtual ~PolarRover();
	virtual void Set_ID(int id);
	virtual int Get_ID() const;
	EmergencyMission* get_EmergencyMission();
	PolarMission* get_PolarMission();
};
#endif