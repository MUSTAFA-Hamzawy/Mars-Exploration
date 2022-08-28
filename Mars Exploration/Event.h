#ifndef Event_
#define Event_

#include"LinkedQueue.h"
#include"LinkedPriorityQueue.h"
#include"PolarMission.h"
#include"MountainousMission.h"
#include"EmergencyMission.h"

//class MountainousMission;
//class PolarMission;
//class EmergencyMission;

class Event
{
private:
	int ID;
	int Event_Day;

public:
	Event() {}
	virtual void Set_ID(int id)=0 ;
	virtual void Set_Event_Day(int event_day)=0;
	virtual int Get_ID() =0;
	virtual int Get_Event_Day()=0;
	virtual bool  Execute(	LinkedQueue<MountainousMission>& waitingMountainous,
							LinkedPriorityQueue<EmergencyMission>& WaitingEmergency,
							LinkedQueue<PolarMission>& waitingPolar ) = 0;
	virtual ~Event() {}
};

#endif