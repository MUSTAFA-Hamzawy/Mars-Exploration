#include"Event.h"
class MountainousMission;
class MountainousLinkedQueueMission;

template<class T>
class LinkedQueue;



class CancellationEvent : public Event
{
private:
	int Cancellation_Day;
	int ID;
	int Num_Of_Mountainous_Missions;
public:
	CancellationEvent( int CD = -1 , int ID  = -1);
	virtual void Set_Cancellation_Day( int CD );
	virtual void Set_ID ( int ID );
	virtual int Get_Cancellation_Day() const;
	virtual int Get_ID() const;
	virtual bool Execute(LinkedQueue<MountainousMission>& waitingMountainous);
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
	//bool Execute();

	int Get_Num_Of_Mountainous_Missions() const;
	virtual ~CancellationEvent();
	char getType();
};