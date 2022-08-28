#ifndef Formulation_Event_
#define Formulation_Event_

#include"Event.h"
//#include"LinkedPriorityQueue.h"
//#include"LinkedQueue.h"
//#include"EmergencyMission.h"
//#include"MountainousMission.h"
//#include"PolarMission.h"

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
	virtual void Set_Event_Day(int FD);
	void Set_Target_Location(double TL);
	void Set_Mission_Duration(int MD);
	void Set_Signature(double S);
	virtual void Set_ID(int id);
	void Set_Mission_Type(char MT);
	virtual int Get_Event_Day() ;
	double Get_Target_Location() const;
	int Get_Mission_Duration() const;
	double Get_Signature() const;
	virtual int Get_ID() ;
	char Get_Mission_Type() const;


	virtual bool Execute
	(
		LinkedQueue<MountainousMission>& waitingMountainous,
		LinkedPriorityQueue<EmergencyMission>& WaitingEmergency,
		LinkedQueue<PolarMission>& waitingPolar
	);

	//bool Execute();
	int Get_Num_Of_Emergency_Missions() const;
	int Get_Num_Of_Mountainous_Missions() const;
	int Get_Num_Of_Polar_Missions() const;
	
	~FormulationEvent();
	char getType();
	
	FormulationEvent(const FormulationEvent& obj);
	void operator=(const FormulationEvent& obj);
};

#endif

/*
FormulationEvent(int FD, double TL, int MD, double S, int id, char MT)
{
	Set_Formulation_Day(FD);
	Set_Target_Location(TL);
	Set_Mission_Duration(MD);
	Set_Signature(S);
	Set_ID(id);
	Set_Mission_Type(MT);
	Num_Of_Emergency_Missions = Num_Of_Mountainous_Missions = Num_Of_Polar_Missions = 0;

}

//ALL Setters with Validations

void Set_Formulation_Day(int FD)
{
	Formulation_Day = (FD > 0) ? FD : -1;
}


void Set_Target_Location(double TL)
{
	Target_Location = (TL > 0) ? TL : -1;
}


void Set_Mission_Duration(int MD)
{
	Mission_Duration = (MD > 0) ? MD : -1;
}


void Set_Signature(double S)
{
	Signature = (S > 0) ? S : -1;
}


void Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}


void Set_Mission_Type(char MT)
{
	if (MT == 'M' || MT == 'P' || MT == 'E')
		Mission_Type = MT;
	else
		Mission_Type = '-1';
}

//ALL Getters


int Get_Formulation_Day()  const
{
	return Formulation_Day;
}


double Get_Target_Location()  const
{
	return Target_Location;
}


int Get_Mission_Duration()  const
{
	return Mission_Duration;
}


double Get_Signature()  const
{
	return Signature;
}


int Get_ID()  const
{
	return ID;
}


char Get_Mission_Type()  const
{
	return Mission_Type;
}



//Destructor

bool Excute(LinkedPriorityQueue<EmergencyMission>& WaitingEmergency, LinkedQueue<PolarMission>& waitingPolar, LinkedQueue<MountainousMission>& waitingMountainous)
{
	{
		char type = this->Get_Mission_Type();
		if (type == 'E')
		{
			EmergencyMission e_mission
			(
				Get_Formulation_Day(),
				Get_Mission_Type(),
				Get_Target_Location(),
				Get_Mission_Duration(),
				Get_Signature(),
				Get_ID()
			);
			WaitingEmergency.enqueue(e_mission, e_mission.getPriority());
			return true;
		}
		if (type == 'P')
		{
			PolarMission p_mission
			(
				Get_Formulation_Day(),
				Get_Mission_Type(),
				Get_Target_Location(),
				Get_Mission_Duration(),
				Get_Signature(),
				Get_ID()
			);
			waitingPolar.enqueue(p_mission);
			return true;
		}
		if (type == 'M')
		{
			MountainousMission m_mission
			(
				Get_Formulation_Day(),
				Get_Mission_Type(),
				Get_Target_Location(),
				Get_Mission_Duration(),
				Get_Signature(),
				Get_ID()
			);
			waitingMountainous.enqueue(m_mission);
			return true;
		}

	}
}



~FormulationEvent()
{

}


char getType()
{
	return 'F';
}


int Get_Num_Of_Emergency_Missions() const
{
	return Num_Of_Emergency_Missions;
}


int Get_Num_Of_Polar_Missions() const
{
	return Num_Of_Polar_Missions;
}


int Get_Num_Of_Mountainous_Missions() const
{
	return Num_Of_Mountainous_Missions;
}
*/
