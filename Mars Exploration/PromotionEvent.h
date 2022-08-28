#ifndef PromotionEvent_
#define PromotionEvent_

#include"Event.h"


class PromotionEvent : public Event
{
private:
	int Promotion_Day;
	int ID;
	int Counter_Num_Promotion_Events;
public:
	
	PromotionEvent( );
	virtual void Set_Event_Day(int PD);
	virtual void Set_ID(int ID);
	virtual int Get_Event_Day() ;
	virtual int Get_ID() ;
	virtual bool Execute(	LinkedQueue<MountainousMission>& waitingMountainous,
							LinkedPriorityQueue<EmergencyMission>& WaitingEmergency,
							LinkedQueue<PolarMission>& waitingPolar);

	~PromotionEvent();
	int Get_Counter_Num_Promotion_Events()const;
	char getType();

	PromotionEvent(const PromotionEvent& obj);
	void operator=(const PromotionEvent& obj);

};

#endif


/*{
	if (waitingMountainous.isEmpty()) return false;

	MountainousMission poppedMission;      // Note : Missions should not be template

	LinkedQueue< MountainousMission> temp;

	// search for this mission and dequeue it if found
	while (!waitingMountainous.isEmpty())
	{
		waitingMountainous.dequeue(poppedMission);
		if (poppedMission.Get_ID() != this->Get_ID())
		{
			temp.enqueue(poppedMission);
		}
		else
		{
			EmergencyMission mission
			(
				poppedMission.Get_Formulation_Day(),
				poppedMission.Get_Mission_Type(),
				poppedMission.Get_Target_Location(),
				poppedMission.Get_Mission_Duration(),
				poppedMission.Get_Signature(),
				Get_ID()
			);
			waitingEmergency.enqueue(mission, mission.getPriority());
			Counter_Num_Promotion_Events++;
		}
	}

	// now the waiting list is empty, so we will fill it again

	while (!temp.isEmpty())
	{
		temp.dequeue(poppedMission);
		waitingMountainous.enqueue(poppedMission);
	}
	return true;
}
*/


/*
PromotionEvent(int PD, int ID)
{
	Set_Promotion_Day(PD);
	Set_ID(ID);
}

//ALL Setters with Validations


void Set_Promotion_Day(int PD)
{
	Promotion_Day = (PD > 0) ? PD : -1;
}


void Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

//ALL Getters


int Get_Promotion_Day() const
{
	return Promotion_Day;
}


int Get_ID() const
{
	return ID;
}


bool Execute(LinkedQueue<MountainousMission>& waitingMountainous, LinkedPriorityQueue<EmergencyMission>& waitingEmergency)
{
	if (waitingMountainous.isEmpty()) return false;

	MountainousMission poppedMission;      // Note : Missions should not be template

	LinkedQueue< MountainousMission> temp;

	// search for this mission and dequeue it if found
	while (!waitingMountainous.isEmpty())
	{
		waitingMountainous.dequeue(poppedMission);
		if (poppedMission.Get_ID() != this->Get_ID())
		{
			temp.enqueue(poppedMission);
		}
		else
		{
			EmergencyMission mission
			(
				poppedMission.Get_Formulation_Day(),
				poppedMission.Get_Mission_Type(),
				poppedMission.Get_Target_Location(),
				poppedMission.Get_Mission_Duration(),
				poppedMission.Get_Signature(),
				Get_ID()
			);
			waitingEmergency.enqueue(mission, mission.getPriority());
			Counter_Num_Promotion_Events++;
		}
	}

	// now the waiting list is empty, so we will fill it again

	while (!temp.isEmpty())
	{
		temp.dequeue(poppedMission);
		waitingMountainous.enqueue(poppedMission);
	}
	return true;
}

//Destructor


~PromotionEvent()
{

}


char getType()
{
	return 'P';
}



int Get_Counter_Num_Promotion_Events() const
{
	return Counter_Num_Promotion_Events;
}
*/