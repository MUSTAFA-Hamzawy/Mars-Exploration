#include"FormulationEvent.h"
#include"MountainousMission.h"
#include "EmergencyMission.h"
#include "PolarMission.h"
/*Constructor*/



FormulationEvent::FormulationEvent(int FD, double TL, int MD, double S, int id, char MT)
{
	Set_Formulation_Day(FD);
	Set_Target_Location(TL);
	Set_Mission_Duration(MD);
	Set_Signature(S);
	Set_ID(id);
	Set_Mission_Type(MT);
	Num_Of_Emergency_Missions = Num_Of_Mountainous_Missions = Num_Of_Polar_Missions = 0;

}

/*ALL Setters with Validations*/

void FormulationEvent::Set_Formulation_Day(int FD)
{
	Formulation_Day = (FD > 0) ? FD : -1;
}


void FormulationEvent::Set_Target_Location(double TL)
{
	Target_Location = (TL > 0) ? TL : -1;
}


void FormulationEvent::Set_Mission_Duration(int MD)
{
	Mission_Duration = (MD > 0) ? MD : -1;
}


void FormulationEvent::Set_Signature(double S)
{
	Signature = (S > 0) ? S : -1;
}


void FormulationEvent::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}


void FormulationEvent::Set_Mission_Type(char MT)
{
	if (MT == 'M' || MT == 'P' || MT == 'E')
		Mission_Type = MT;
	else
		Mission_Type = '-1';
}

/*ALL Getters*/


int FormulationEvent::Get_Formulation_Day()  const
{
	return Formulation_Day;
}


double FormulationEvent::Get_Target_Location()  const
{
	return Target_Location;
}


int FormulationEvent::Get_Mission_Duration()  const
{
	return Mission_Duration;
}


double FormulationEvent::Get_Signature()  const
{
	return Signature;
}


int FormulationEvent::Get_ID()  const
{
	return ID;
}


char FormulationEvent::Get_Mission_Type()  const
{
	return Mission_Type;
}



/*Destructor*/

bool FormulationEvent::Excute(LinkedPriorityQueue<EmergencyMission>& WaitingEmergency, LinkedQueue<PolarMission>& waitingPolar, LinkedQueue<MountainousMission>& waitingMountainous)
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
		/*switch (type)
		{
		case 'E':
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
			break;
		case 'M':
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
			break;
		case 'P':
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
			break;
		default:
			return false;
			break;
		}*/
	}
}



FormulationEvent ::  ~FormulationEvent()
{

}


char FormulationEvent::getType()
{
	return 'F';
}


int FormulationEvent::Get_Num_Of_Emergency_Missions() const
{
	return Num_Of_Emergency_Missions;
}


int FormulationEvent::Get_Num_Of_Polar_Missions() const
{
	return Num_Of_Polar_Missions;
}


int FormulationEvent::Get_Num_Of_Mountainous_Missions() const
{
	return Num_Of_Mountainous_Missions;
}

/*
bool FormulationEvent::Excute(LinkedPriorityQueue<EmergencyMission>& WaitingEmergency, LinkedQueue<PolarMission>& waitingPolar, LinkedQueue<MountainousMission>& waitingMountainous)
{
	switch (this->Get_Mission_Type())
	{
	case 'E':
		EmergencyMission mission = new EmergencyMission
			(
			Get_Formulation_Day(),
			Get_Mission_Type(),
			Get_Target_Location(),
			Get_Mission_Duration,
			Get_Signature(),
			Get_ID()
			);

		WaitingEmergency.enqueue(mission, mission.getPriority());
		return true;
		break;
	case 'M':
		MountainousMission mission = new MountainousMission
			(
			Get_Formulation_Day(),
			Get_Mission_Type(),
			Get_Target_Location(),
			Get_Mission_Duration,
			Get_Signature(),
			Get_ID()
			);
		waitingMountainous.enqueue(mission);
		return true;
		break;
	case 'P':
		PolarMission mission = new PolarMission
			(
			Get_Formulation_Day(),
			Get_Mission_Type(),
			Get_Target_Location(),
			Get_Mission_Duration,
			Get_Signature(),
			Get_ID()
			);
		waitingPolar.enqueue(mission);
		return true;
		break;
	default:
		return false;
		break;
	}
}
*/