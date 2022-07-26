#ifndef UI_
#define UI_


class PolarRover;
class MountainousRover;
class EmergencyRover;

class FormulationEvent;
class CancellationEvent;
class PoPromotionEventlarRover;

template<class T>
class LinkedQueue;
template<class T>
class LinkedPriorityQueue;

template<class T>
class UI
{
private:
	int Mountinous_Num;
	int Polar_Num;
    int Emergency_Num;
	double Mountinous_Speed;
	double Polar_Speed;
	double Emergency_Speed;
	int Missions_Count;
	int Mountinous_CheckupDuration;
	int Polar_CheckupDuration;
	int Emergency_CheckupDuration;
	int Auto_Promotion;
	int Events_Num;
	char event_Type;
	char mission_type;
	int Formulation_Day;
	int ID;
	double Target_Location;
	int Mision_Duration;
	double Signature;
	//char X;
	//char PP;
	//int emergencyRover_MissionsCount, moutainousRover_MissionsCount, polarRover_MissionsCount;

	//create 3 arrays of events to store there data 
	const int MAX_EVENTS_COUNT;
	FormulationEvent* F_Event_arr;
	CancellationEvent* C_Event_arr;
	PromotionEvent* P_Event_arr;

	int FormulationCount, CancellationCount, PromotionCount;

public:
	UI();
	void input();
	void output(
		int mode, int countDays,
		LinkedPriorityQueue<EmergencyMission> WaitingEmergency,
		LinkedQueue<PolarMission> waitingPolar,
		LinkedQueue<MountainousMission> waitingMountainous,
		LinkedPriorityQueue<EmergencyRover> In_ExcutionEmergency,
		LinkedPriorityQueue<PolarRover> In_ExcutionPolar,
		LinkedPriorityQueue<MountainousRover> In_ExcutionMountainous,
		LinkedPriorityQueue<EmergencyRover> EmergencyRovers,
		LinkedPriorityQueue<PolarRover> PolarRovers,
		LinkedPriorityQueue<MountainousRover> MountainousRovers,
		LinkedPriorityQueue<EmergencyRover> EmergencyCheckup,
		LinkedPriorityQueue<PolarRover> PolarCheckup,
		LinkedPriorityQueue<MountainousRover> MountainousCheckup,
		LinkedQueue<EmergencyMission> Completed_Missions_Emergency,
		LinkedQueue<PolarMission> Completed_Missions_Polar,
		LinkedQueue<MountainousMission> Completed_Missions_Mountainous
		);

	void Display_waitingOfCurrentDay
	(
		LinkedPriorityQueue<EmergencyMission> WaitingEmergency,
		LinkedQueue<PolarMission> waitingPolar,
		LinkedQueue<MountainousMission> waitingMountainous
	);
	void Display_inExecutionOfCurrentDay
	(
		LinkedPriorityQueue<EmergencyRover> In_ExcutionEmergency,
		LinkedPriorityQueue<PolarRover> In_ExcutionPolar,
		LinkedPriorityQueue<MountainousRover> In_ExcutionMountainous
	);
	void Display_AvailableRoversCurrentDay
	(
		LinkedPriorityQueue<EmergencyRover> EmergencyRovers,
		LinkedPriorityQueue<PolarRover> PolarRovers,
		LinkedPriorityQueue<MountainousRover> MountainousRovers
	);
	void Display_checkUpRoversCurrentDay
	(
		LinkedPriorityQueue<EmergencyRover> EmergencyCheckup,
		LinkedPriorityQueue<PolarRover> PolarCheckup,
		LinkedPriorityQueue<MountainousRover> MountainousCheckup
	);
	void Display_CompletedOfCurrentDay
	(
		LinkedQueue<EmergencyMission> Completed_Missions_Emergency,
		LinkedQueue<PolarMission> Completed_Missions_Polar,
		LinkedQueue<MountainousMission> Completed_Missions_Mountainous
	);
	
	virtual~UI();

	void Set_Mountinous_Num( int MN);
	void Set_Polar_Num(int PN);
	void Set_Emergency_Num(int EN);
	void Set_Mountinous_Speed(double MS);
	void Set_Polar_Speed(double PS);
	void Set_Emergency_Speed(double ES);
	void Set_Missions_Count(int MC);
	void Set_Mountinous_CheckupDuration(int MCD);
	void Set_Polar_CheckupDuration(int PCD);
	void Set_Emergency_CheckupDuration(int ECD);
	void Set_Auto_Promotion(int AP);
	void Set_Events_Num(int EN);
	void Set_TYPE(char T);
	void Set_FormulationDay(int FD);
	void Set_ID(int ID);
	void Set_Target_Location(int TL);
	void Set_Mision_Duration(int MD);
	void Set_Signature(int S);

	int Get_Mountinous_Num()const;
	int Get_Polar_Num()const;
	int Get_Emergency_Num()const;
	double Get_Mountinous_Speed()const;
	double Get_Polar_Speed()const;
	double Get_Emergency_Speed()const;
	int Get_Missions_Count()const;
	int Get_Mountinous_CheckupDuration()const;
	int Get_Polar_CheckupDuration()const;
	int Get_Emergency_CheckupDuration()const;
	int Get_Auto_Promotion()const;
	int Get_Events_Num()const;
	char Get_TYPE()const;
	int Get_FormulationDay()const;
	int Get_ID()const;
	int Get_Target_Location()const;
	int Get_Mision_Duration()const;
	int Get_Signature()const;
	
	int getFormulationCount();
	int getCancellationCount();
	int getPromotionCount();

	void fillEvents(
		LinkedQueue<FormulationEvent>& F_Events,
		LinkedQueue<CancellationEvent>& C_Events,
		LinkedQueue<PromotionEvent>& P_Events
	);
};


#endif
