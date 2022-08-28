#ifndef MarsStation_
#define MarsStation_

#include"Mission.h"

#include"UI.h"

class MarsStation
{
private:

	int Mode;
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
	int Counter_Cancellation_Events;
	//
	int Waiting_Days_Total_Emergency;
	int Waiting_Days_Total_Mountainous;
	int Waiting_Days_Total_Polar;
	int Execution_Days_Total_Emergency ;
	int Execution_Days_Total_Mountainous;
	int Execution_Days_Total_Polar;
	//
	int Counter_wait_EmergencyMissions;
	int Counter_wait_MountainousMissions;
	int Counter_wait_PolarMissions;
	int Counter_wait_missions;
	int Counter_Inec_MountainousRovers;
	int Counter_Inec_EmergencyRovers;
	int Counter_Inec_PolarRovers;
	int Counter_Inec_rovers;
	int Counter_Inec_EmergencyMissions;    //counters on In_Executions missions
	int Counter_Inec_MountainousMissions;
	int Counter_Inec_PolarMissions;
	int Conter_Inec_Missions;
	int Counter_check_MountainousRovers;
	int Counter_check_EmergencyRovers;
	int Counter_check_PolarRovers;
	int Counter_check_rovers;

	int Total_Emergency_Missions;   //total of each type from all lists and total of all types of both missions and rovers
	int Total_Mountainous_Missions;
	int Total_Polar_Missions;
	int all_Missions;
	int Total_Emergency_Rovers;
	int Total_Mountainous_Rovers;
	int Total_Polar_Rovers;
	int all_Rovers;
	//
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
	LinkedPriorityQueue <Mission> Completed_Missions_Total;   //Karim


	LinkedQueue<FormulationEvent> F_Events;
	LinkedQueue<CancellationEvent> C_Events;
	LinkedQueue<PromotionEvent> P_Events;


	UI  data;       // it should not be template 

	void Assign_Missions_To_Rovers(EmergencyMission* em, PolarMission* pm,
		MountainousMission* mm, EmergencyRover* er,
		PolarRover* pr, MountainousRover* mr
	);
public:
	MarsStation() {
		 Count_Days=0;
		 Count_Total_Missions = 0;
		 Count_EmergencyMissions = 0;
		 Count_MountainousMissions = 0;
		 Count_PolarMissions = 0;
		 Counter_Rovers = 0;
		 Counter_MountainousRovers = 0;
		 Counter_EmergencyRovers = 0;
		 Counter_PolarRovers = 0;
		 Waiting_Avg = 0;
		 Execution_Avg = 0;
		 Auto_Promoted = 0;
		 modeOfDisplay = 0;
		 Counter_Cancellation_Events = 0;
		//
		 Counter_wait_EmergencyMissions = 0;
		 Counter_wait_MountainousMissions = 0;
		 Counter_wait_PolarMissions = 0;
		 Counter_wait_missions = 0;
		 Counter_Inec_MountainousRovers = 0;
		 Counter_Inec_EmergencyRovers = 0;
		 Counter_Inec_PolarRovers = 0;
		 Counter_Inec_rovers = 0;
		 Counter_check_MountainousRovers = 0;
		 Counter_check_EmergencyRovers = 0;
		 Counter_check_PolarRovers = 0;
		 Counter_check_rovers = 0;

		 Counter_Inec_EmergencyMissions = 0;
		 Counter_Inec_MountainousMissions = 0;
		 Counter_Inec_PolarMissions = 0;
		 Conter_Inec_Missions = 0;

		 Counter_Inec_EmergencyRovers = 0;
		 Counter_Inec_MountainousRovers = 0;
		 Counter_Inec_PolarRovers = 0;
		 Counter_Inec_rovers = 0;
		 //
		 Waiting_Days_Total_Emergency = 0;
		 Waiting_Days_Total_Mountainous = 0;
		 Waiting_Days_Total_Polar = 0;
		 Execution_Days_Total_Emergency = 0;
		 Execution_Days_Total_Mountainous = 0;
		 Execution_Days_Total_Polar = 0;
		 //
		 Total_Emergency_Missions = 0;
		 Total_Mountainous_Missions = 0;
		 Total_Polar_Missions = 0;
		 all_Missions = 0;
		 Total_Emergency_Rovers = 0;
		 Total_Mountainous_Rovers = 0;
		 Total_Polar_Rovers = 0;
		 all_Rovers = 0;
	}        // Initialize all counters to 0 ( MUSTAFA )
	void getInput();

	void Get_Data_Into_PQ_Q();

	void assignMissions();

	//void Completed_Missions(EmergencyMission* em, PolarMission* pm, MountainousMission* mm);
	void Complete_Missions();
	//void CheckUp_Duration(EmergencyRover* er, PolarRover* pr, MountainousRover* mr);
	int Get_Count_Days() const;
	void Set_Count_Days(int cd);
	//void Statistics(EmergencyMission* em, PolarMission* pm, MountainousMission* mm, EmergencyRover* er, PolarRover* pr, MountainousRover* mr);
	void Statistics( );
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
	//void diplay();
	void outputdata(int Mode);
	virtual ~MarsStation() {}

	void decrementCheckUpDuration(); // decrement duration of the rovers in checkup by 1 each day
	void outfile();    //for calling ui output file
	void incrementDays();


};

#endif