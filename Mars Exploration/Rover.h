#ifndef Rover_
#define Rover_

#include"EmergencyMission.h"
#include"MountainousMission.h"
#include"PolarMission.h"



class Rover
{
protected:
	int Default_MissionsCount;
	int Current_MissionsCount;
private:
//	double Speed;
	//int	CheckupDuration;
//	int	MissionsCount;		// Number of missions before the checkup, ex : if it is = 3
	int ID;
	char MissionType;
public:
	Rover(double speed = -1, int checkDuration = -1, int missionsCount = -1, int id=-1);
	virtual bool available();     // check if the rover is available to be assigned a mission or in checkup
	virtual void Set_Speed(double speed) ;
	virtual void Set_CheckupDuration(int checkDuration);
	void Set_MissionsCount(int missionsCount);
	virtual void Set_MissionType(char w);
	virtual double Get_Speed()const;
	int Get_MissionsCount()const;
	virtual int Get_CheckupDuration() const;
	virtual void Set_ID(int id);
	virtual int Get_ID()const;
	virtual char Get_MissionType() const;
	virtual ~Rover();

	void reset_MissionCout();   // reset the number of missions to default after finishing the checkUp duration


};

#endif