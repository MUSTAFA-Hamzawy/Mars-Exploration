
class PromotionEvent;
class FormulationEvent;
class CancellationEvent;

class PolarRover;
class MountainousRover;
class EmergencyRover;

class PolarMission;
class MountainousMission;
class EmergencyMission;
template<class T>
class UI;

template<class T>
class LinkedQueue;

template<class T>
class LinkedPriorityQueue;






template < class T>
class MarsStation
{
private:
	// ////////////////////////////      need getters          ////////////////////////////////
	int Count_Days;
	int Count_Total_Missions;
	int Count_EmergencyMissions;
	int Count_MountainousMissions;
	int Count_PolarMissions;
	int Counter_Rovers;
	int Counter_MountainousRovers;
	int Counter_EmergencyRovers;
	int Counter_PolarRovers;
	float Waiting_Avg;
	float Execution_Avg;
	float Auto_Promoted;
	int modeOfDisplay;

	EmergencyMission* ptr_em;
	PolarMission* ptr_pm;
	MountainousMission* ptr_mm;
	EmergencyRover* ptr_er;
	PolarRover* ptr_pr;
	MountainousRover* ptr_mr;

	CancellationEvent* ce;
	PromotionEvent* pe;
	FormulationEvent* fe;
	//LinkedPriorityQueue <EmergencyMission> EmergencyMissions;
	//LinkedQueue < PolarMission > PolarMissions;
	//LinkedQueue < MountainousMission > MountainousMissions;

	LinkedPriorityQueue <EmergencyRover> EmergencyRovers;
	LinkedPriorityQueue <PolarRover> PolarRovers;
	LinkedPriorityQueue <MountainousRover> MountainousRovers;

	LinkedPriorityQueue <EmergencyMission>WaitingEmergency;
	LinkedQueue<PolarMission> waitingPolar;
	LinkedQueue<MountainousMission> waitingMountainous;

	LinkedPriorityQueue <EmergencyRover> In_ExcutionEmergency;
	LinkedPriorityQueue<PolarRover> In_ExcutionPolar;
	LinkedPriorityQueue<MountainousRover> In_ExcutionMountainous;

	LinkedPriorityQueue <EmergencyRover> EmergencyCheckup;
	LinkedPriorityQueue <PolarRover> PolarCheckup;
	LinkedPriorityQueue <MountainousRover> MountainousCheckup;

	LinkedQueue <EmergencyMission> Completed_Missions_Emergency;
	LinkedQueue<PolarMission> Completed_Missions_Polar;
	LinkedQueue<MountainousMission> Completed_Missions_Mountainous;


	LinkedQueue<FormulationEvent> F_Events;
	LinkedQueue<CancellationEvent> C_Events;
	LinkedQueue<PromotionEvent> P_Events;


	UI < T > data;       // it should not be template 

	void Assign_Missions_To_Rovers(EmergencyMission* em, PolarMission* pm,
		MountainousMission* mm, EmergencyRover* er,
		PolarRover* pr, MountainousRover* mr
	);
public:
	MarsStation();
	void Get_Data_Into_PQ_Q();

	void assignMissions();

	//void Completed_Missions(EmergencyMission* em, PolarMission* pm, MountainousMission* mm);
	void Complete_Missions();
	//void CheckUp_Duration(EmergencyRover* er, PolarRover* pr, MountainousRover* mr);
	int Get_Count_Days() const;
	void Set_Count_Days(int cd);
	void Statistics(EmergencyMission* em, PolarMission* pm, MountainousMission* mm, EmergencyRover* er, PolarRover* pr, MountainousRover* mr);
	int Get_Count_Total_Missions()const;
	int Get_Count_EmergencyMissions()const;
	int Get_Count_MountainousMissions()const;
	int Get_Count_PolarMissions()const;
	int Get_Counter_MountainousRovers()const;
	int Get_Counter_EmergencyRovers()const;
	int Get_Counter_PolarRovers()const;
	int Get_Counter_Rovers()const;
	float Get_Waiting_Avg()const;
	float Get_Execution_Avg()const;
	float Get_Auto_Promoted()const;
	void excute_Events();
	bool finished();
	void diplay();

	virtual ~MarsStation();
};
