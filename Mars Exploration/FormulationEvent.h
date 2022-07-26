

#include"Event.h"
#include"LinkedPriorityQueue.h"
#include"LinkedQueue.h"


class EmergencyMission;
class MountainousMission;
class PolarMission;

template<class T>
class LinkedQueue;
template<class T>
class LinkedPriorityQueue;

class FormulationEvent : public Event
{
private:
	int Formulation_Day;
	double Target_Location;
	int Mission_Duration;
	double Signature;
	int ID;
	char Mission_Type;
	int Num_Of_Emergency_Missions;
	int Num_Of_Mountainous_Missions;
	int Num_Of_Polar_Missions;
public:
	FormulationEvent(int FD = -1, double TL = -1, int MD = -1, double S = -1, int id = -1, char MT = -1);
	virtual void Set_Formulation_Day(int FD);
	virtual void Set_Target_Location(double TL);
	virtual void Set_Mission_Duration(int MD);
	virtual void Set_Signature(double S);
	virtual void Set_ID(int id);
	virtual void Set_Mission_Type(char MT);
	virtual int Get_Formulation_Day() const;
	virtual double Get_Target_Location() const;
	virtual int Get_Mission_Duration() const;
	virtual double Get_Signature() const;
	virtual int Get_ID() const;
	virtual char Get_Mission_Type() const;


	virtual bool Excute
	(
		LinkedPriorityQueue<EmergencyMission>& WaitingEmergency,
		LinkedQueue<PolarMission>& waitingPolar,
		LinkedQueue<MountainousMission>& waitingMountainous
	);

	//bool Execute();
	int Get_Num_Of_Emergency_Missions() const;
	int Get_Num_Of_Mountainous_Missions() const;
	int Get_Num_Of_Polar_Missions() const;
	
	virtual ~FormulationEvent();
	char getType();
};


