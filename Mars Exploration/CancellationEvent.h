#ifndef Cancellation_Event_
#define Cancellation_Event_
#include"Event.h"


class CancellationEvent : public Event
{
private:
	int Cancellation_Day;
	int ID;
	int Num_Of_Mountainous_Missions;
public:
	
	CancellationEvent();
	virtual void Set_Event_Day( int CD );
	virtual void Set_ID ( int ID );
	virtual int Get_Event_Day() ;
	virtual int Get_ID() ;
	virtual bool Execute(	LinkedQueue<MountainousMission>& waitingMountainous,
							LinkedPriorityQueue<EmergencyMission>& WaitingEmergency,
							LinkedQueue<PolarMission>& waitingPolar);

	int Get_Num_Of_Mountainous_Missions() const;
	~CancellationEvent();
	char getType();


	CancellationEvent(const CancellationEvent& obj);
	void operator=(const CancellationEvent& obj);
	

};

#endif

/*
CancellationEvent(int CD, int ID)
{
	Set_Cancellation_Day(CD);
	Set_ID(ID);
	Num_Of_Mountainous_Missions = 0;
}

//ALL Setters with Validations


void Set_Cancellation_Day(int CD)
{
	Cancellation_Day = (CD > 0) ? CD : -1;
}


void Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

//ALL Getters


int Get_Cancellation_Day() const
{
	return Cancellation_Day;
}


int Get_ID() const
{
	return ID;
}


bool Execute(LinkedQueue<MountainousMission>& waitingMountainous)
{
	if (waitingMountainous.isEmpty()) return false;

	MountainousMission poppedMission;

	LinkedQueue<MountainousMission> temp;

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
			continue;
		}
	}

	// now the waiting list is empty, so we will fill it again

	while (!temp.isEmpty())
	{
		temp.dequeue(poppedMission);
		waitingMountainous.enqueue(poppedMission);
	}

	// Note : we won't return the Popped Mission as it is not required to print or used for anything
	return true;
}


//Destructor

 ~CancellationEvent()
{

}


char getType()
{
	return 'C';
}


int Get_Num_Of_Mountainous_Missions() const
{
	return Num_Of_Mountainous_Missions;
}
*/

/*{
	if (waitingMountainous.isEmpty()) return false;

	MountainousMission poppedMission;

	LinkedQueue<MountainousMission> temp;

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
			continue;
		}
	}

	// now the waiting list is empty, so we will fill it again

	while (!temp.isEmpty())
	{
		temp.dequeue(poppedMission);
		waitingMountainous.enqueue(poppedMission);
	}

	// Note : we won't return the Popped Mission as it is not required to print or used for anything
	return true;
}
*/