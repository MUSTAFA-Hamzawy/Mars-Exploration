#ifndef PromotionEvent_
#define PromotionEvent_

#include"Event.h"


class MountainousMission;
class EmergencyMission;

template<class T>
class LinkedQueue;
template<class T>
class LinkedPriorityQueue;



class PromotionEvent : public Event
{
private:
	int Promotion_Day;
	int ID;
	int Counter_Num_Promotion_Events;
public:
	PromotionEvent(int PD = -1 , int ID = -1 );
	virtual void Set_Promotion_Day(int PD);
	virtual void Set_ID(int ID);
	virtual int Get_Promotion_Day() const;
	virtual int Get_ID() const;
	virtual bool Execute(LinkedQueue<MountainousMission>& waitingMountainous, LinkedPriorityQueue<EmergencyMission>& waitingEmergency);
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
	}*/
	virtual ~PromotionEvent();
	int Get_Counter_Num_Promotion_Events()const;
	char getType();

	//bool Execute();
};

#endif