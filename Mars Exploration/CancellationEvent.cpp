#include"CancellationEvent.h"
#include"LinkedPriorityQueue.h"
#include"LinkedQueue.h"
#include"MountainousMission.h"

/*Constructor*/


CancellationEvent  :: CancellationEvent(int CD , int ID )
{
	Set_Cancellation_Day( CD );
	Set_ID( ID );
	Num_Of_Mountainous_Missions = 0;
}

/*ALL Setters with Validations*/


void CancellationEvent  ::Set_Cancellation_Day(int CD)
{
	Cancellation_Day = (CD > 0) ? CD : -1;
}


void CancellationEvent  ::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

/*ALL Getters*/


int CancellationEvent  ::Get_Cancellation_Day() const
{
	return Cancellation_Day;
}


int CancellationEvent  ::Get_ID() const
{
	return ID;
}


bool CancellationEvent::Execute(LinkedQueue<MountainousMission>& waitingMountainous)
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


/*Destructor*/

CancellationEvent  :: ~CancellationEvent()
{

}


char CancellationEvent::getType()
{
	return 'C';
}


int CancellationEvent::Get_Num_Of_Mountainous_Missions() const
{
	return Num_Of_Mountainous_Missions;
}