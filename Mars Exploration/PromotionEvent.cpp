#include"PromotionEvent.h"
#include"EmergencyMission.h"
#include"MountainousMission.h"
/*Constructor*/



PromotionEvent  ::PromotionEvent(int PD, int ID)
{
	Set_Promotion_Day(PD);
	Set_ID(ID);
}

/*ALL Setters with Validations*/


void PromotionEvent  ::Set_Promotion_Day(int PD)
{
	Promotion_Day = (PD > 0) ? PD : -1;
}


void PromotionEvent  ::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}

/*ALL Getters*/


int PromotionEvent  ::Get_Promotion_Day() const
{
	return Promotion_Day;
}


int PromotionEvent  ::Get_ID() const
{
	return ID;
}


bool PromotionEvent::Execute(LinkedQueue<MountainousMission>& waitingMountainous, LinkedPriorityQueue<EmergencyMission>& waitingEmergency)
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

/*Destructor*/


PromotionEvent  :: ~PromotionEvent()
{

}


char PromotionEvent::getType()
{
	return 'P';
}



int PromotionEvent ::Get_Counter_Num_Promotion_Events() const
{
	return Counter_Num_Promotion_Events;
}