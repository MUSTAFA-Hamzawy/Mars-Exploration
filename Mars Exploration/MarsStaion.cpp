#include"MarsStation.h"


#include "MountainousRover.h"
#include "PolarRover.h"
#include "EmergencyRover.h"

#include"PolarMission.h"
#include"MountainousMission.h"
#include"EmergencyMission.h"

//#include"UI.h"
template < class T>
int  MarsStation < T> ::Get_Count_Days() const
{
	return Count_Days;
}

template < class T>
void  MarsStation < T> ::Set_Count_Days(int cd)
{
	Count_Days = (cd > 0) ? cd : -1;
}


template < class T>
void  MarsStation < T> ::Get_Data_Into_PQ_Q()
{
	// fill mountainous rovers data
	for (int i = 0; i < data.Get_Mountinous_Num(); i++)
	{
		ptr_mr->setAllData(data.Get_Mountinous_CheckupDuration(), data.Get_Missions_Count(), data.Get_Mountinous_Speed());
		MountainousRovers.enqueue(ptr_mr, data.Get_Mountinous_Speed());
	}
	// fill emergeny rovers data
	for (int i = 0; i < data.Get_Emergency_Num(); i++)
	{
		ptr_er->setAllData(data.Get_Emergency_CheckupDuration(), data.Get_Missions_Count(), data.Get_Emergency_Speed());
		EmergencyRovers.enqueue(ptr_er, data.Get_Emergency_Speed());
	}
	// fill polar rovers data
	for (int i = 0; i < data.Get_Polar_Num(); i++)
	{
		ptr_er->setAllData(data.Get_Polar_CheckupDuration(), data.Get_Missions_Count(), data.Get_Polar_Speed());
		PolarRovers.enqueue(ptr_pr, data.Get_Polar_Speed());
	}

	// fill Events

	data.fillEvents(F_Events, C_Events, P_Events);

}

template<class T>
void MarsStation<T>::assignMissions()
{
	EmergencyRover rover_1;
	EmergencyRovers.peek(rover_1);
	ptr_er = &rover_1;

	PolarRover rover_2;
	PolarRovers.peek(rover_2);
	ptr_pr = &rover_2;

	MountainousRover rover_3;
	MountainousRovers.peek(rover_3);
	ptr_mr = &rover_3;


	EmergencyMission mission_1;
	WaitingEmergency.peek(mission_1);
	ptr_em = &mission_1;

	PolarMission mission_2;
	waitingPolar.peek(mission_2);
	ptr_pm = &mission_2;

	MountainousMission mission_3;
	waitingMountainous.peek(mission_3);
	ptr_mm = &mission_3;


	Assign_Missions_To_Rovers(
		mission_1, mission_2, mission_3,
		rover_1, rover_2, rover_3
	);
}

template<class T>
void MarsStation<T>::excute_Events()
{
	if (!F_Events.isEmpty())
	{
		FormulationEvent event;
		F_Events.peek(event);
		if (event.Get_Formulation_Day() == Count_Days)
		{
			event.Excute(WaitingEmergency, waitingPolar, waitingMountainous);
			F_Events.dequeue(event);
		}
	}
	if (!C_Events.isEmpty())
	{
		CancellationEvent event;
		C_Events.peek(event);
		if (event.Get_Cancellation_Day() == Count_Days)
		{
			event.Execute(waitingMountainous);
			C_Events.dequeue(event);
		}
	}
	if (!P_Events.isEmpty())
	{
		PromotionEvent event;
		P_Events.peek(event);
		if (event.Get_Promotion_Day() == Count_Days)
		{
			event.Execute(waitingMountainous, WaitingEmergency);
			P_Events.dequeue(event);
		}
	}

}

template < class T>
void MarsStation < T > ::Assign_Missions_To_Rovers(EmergencyMission* em, PolarMission* pm, MountainousMission* mm, EmergencyRover* er, PolarRover* pr, MountainousRover* mr)
{
	// if no rover is availabe, return

	if (er->available() || mr->available() || mr->available() == false) return;


	// assign emergency first
	if (em)
	{

		if (er->assign_EmergencyMission(em))
		{
			WaitingEmergency.dequeue(em);
			In_ExcutionEmergency.enqueue(em, em->getPriority());
		}
		else if (mr->assign_EmergencyMission(em))
		{
			WaitingEmergency.dequeue(em);
			In_ExcutionEmergency.enqueue(em, em->getPriority());
		}
		else  // polar is available, no need to check
		{
			pr->assign_EmergencyMission(em);
			WaitingEmergency.dequeue(em);
			In_ExcutionEmergency.enqueue(em, em->getPriority());
		}
	}

	// assign polar missions using the available polar rovers only
	if (pm && pr->assign_PolarMission(pm))
	{
		waitingPolar.dequeue(pm);
		In_ExcutionPolar.enqueue(em);
	}

	// assign mountainous mission

	if (mm)
	{
		if (mr->assign_MountainousMission(mm))
		{
			waitingMountainous.dequeue(mm);
			In_ExcutionMountainous.enqueue(em);
		}
		else if (er->assign_MountainousMission())
		{

			waitingMountainous.dequeue(mm);
			In_ExcutionMountainous.enqueue(em);
		}
	}
}

template<class T>
void MarsStation<T>::Complete_Missions()
{

	// check the list of emergency rovers (in-excution)
	if (!In_ExcutionEmergency.isEmpty())
	{
		EmergencyRover peekedRover;
		EmergencyRover poppedRover;
		In_ExcutionEmergency.peek(peekedRover);
		int Completed_Days;
		if (peekedRover.get_EmergencyMission())
		{
			Completed_Days =
				peekedRover.get_EmergencyMission()->Get_Mission_Duration() +
				peekedRover.get_EmergencyMission()->Get_Formulation_Day() +
				peekedRover.get_EmergencyMission()->Get_Waiting_Duration();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				Completed_Missions_Emergency.enqueue(*peekedRover.get_EmergencyMission());

				// make this mission inside this rover to be nullptr

				// if need check up, go to it else go to the original list
				In_ExcutionEmergency.dequeue(poppedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					EmergencyCheckup.enqueue(poppedRover, poppedRover.Get_CheckupDuration());
				}
				else
				{
					EmergencyRovers.enqueue(poppedRover);
				}
			}
		}
		else if (peekedRover.get_MountainousMission())
		{
			Completed_Days =
				peekedRover.get_MountainousMission()->Get_Mission_Duration() +
				peekedRover.get_MountainousMission()->Get_Formulation_Day() +
				peekedRover.get_MountainousMission()->Get_Waiting_Duration();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				Completed_Missions_Emergency.enqueue(*peekedRover.get_MountainousMission());

				// make this mission inside this rover to be nullptr

				// if need check up, go to it else go to the original list
				In_ExcutionEmergency.dequeue(poppedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					EmergencyCheckup.enqueue(poppedRover, poppedRover.Get_CheckupDuration());
				}
				else
				{
					EmergencyRovers.enqueue(poppedRover, poppedRover.Get_Speed());
				}
			}
		}
	}

	// check the list of polar rovers (in-excution)
	if (!In_ExcutionPolar.isEmpty())
	{
		PolarRover peekedRover;
		PolarRover poppedRover;
		In_ExcutionPolar.peek(peekedRover);
		int Completed_Days;
		if (peekedRover.get_EmergencyMission())
		{
			Completed_Days =
				peekedRover.get_EmergencyMission()->Get_Mission_Duration() +
				peekedRover.get_EmergencyMission()->Get_Formulation_Day() +
				peekedRover.get_EmergencyMission()->Get_Waiting_Duration();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				Completed_Missions_Emergency.enqueue(*peekedRover.get_EmergencyMission());

				// make this mission inside this rover to be nullptr

				// if need check up, go to it else go to the original list
				In_ExcutionPolar.dequeue(poppedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					PolarCheckup.enqueue(poppedRover, poppedRover.Get_CheckupDuration());
				}
				else
				{
					PolarRovers.enqueue(poppedRover, poppedRover.Get_Speed());
				}
			}
		}
		else if (peekedRover.get_PolarMission())
		{
			Completed_Days =
				peekedRover.get_PolarMission()->Get_Mission_Duration() +
				peekedRover.get_PolarMission()->Get_Formulation_Day() +
				peekedRover.get_PolarMission()->Get_Waiting_Duration();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				Completed_Missions_Polar.enqueue(*peekedRover.get_PolarMission());

				// make this mission inside this rover to be nullptr

				// if need check up, go to it else go to the original list
				In_ExcutionPolar.dequeue(poppedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					PolarCheckup.enqueue(poppedRover, poppedRover.Get_CheckupDuration());
				}
				else
				{
					PolarRovers.enqueue(poppedRover, poppedRover.Get_Speed());
				}
			}
		}
	}
	
	// check the list of mountainous rovers (in-excution)

	if (!In_ExcutionMountainous.isEmpty())
	{
		MountainousRover peekedRover;
		MountainousRover poppedRover;
		In_ExcutionMountainous.peek(peekedRover);
		int Completed_Days;
		if (peekedRover.get_EmergencyMission())
		{
			Completed_Days =
				peekedRover.get_EmergencyMission()->Get_Mission_Duration() +
				peekedRover.get_EmergencyMission()->Get_Formulation_Day() +
				peekedRover.get_EmergencyMission()->Get_Waiting_Duration();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				Completed_Missions_Emergency.enqueue(*peekedRover.get_EmergencyMission());

				// make this mission inside this rover to be nullptr

				// if need check up, go to it else go to the original list
				In_ExcutionMountainous.dequeue(poppedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					MountainousCheckup.enqueue(poppedRover, poppedRover.Get_CheckupDuration());
				}
				else
				{
					MountainousRovers.enqueue(poppedRover, poppedRover.Get_Speed());
				}
			}
		}
		else if (peekedRover.get_MountainousMission())
		{
			Completed_Days =
				peekedRover.get_MountainousMission()->Get_Mission_Duration() +
				peekedRover.get_MountainousMission()->Get_Formulation_Day() +
				peekedRover.get_MountainousMission()->Get_Waiting_Duration();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				Completed_Missions_Mountainous.enqueue(*peekedRover.get_MountainousMission());

				// make this mission inside this rover to be nullptr

				// if need check up, go to it else go to the original list
				In_ExcutionMountainous.dequeue(poppedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					MountainousCheckup.enqueue(poppedRover, poppedRover.Get_CheckupDuration());
				}
				else
				{
					MountainousRovers.enqueue(poppedRover, poppedRover.Get_Speed());
				}
			}
		}
	}



}



template<class T>
void MarsStation < T > ::Statistics(EmergencyMission* em, PolarMission* pm, MountainousMission* mm, EmergencyRover* er, PolarRover* pr, MountainousRover* mr)
{
	LinkedPriorityQueue <EmergencyMission> temp_e;
	LinkedQueue<PolarMission> temp_p;
	LinkedQueue<MountainousMission> temp_m;
	int Waiting_Days_Total_Emergency = 0;
	int Waiting_Days_Total_Mountainous = 0;
	int Waiting_Days_Total_Polar = 0;
	int Execution_Days_Total_Emergency = 0;
	int Execution_Days_Total_Mountainous = 0;
	int Execution_Days_Total_Polar = 0;

	//Count Emergency Missions

	while (!Completed_Missions_Emergency.isEmpty())
	{
		Completed_Missions_Emergency.dequeue(em);
		Waiting_Days_Total_Emergency += em->Get_Waiting_Duration();
		Execution_Days_Total_Emergency += em->Get_Mission_Duration();
		temp_e.enqueue(em);
		Count_EmergencyMissions++;
	}

	while (!temp_e.isEmpty())
	{
		temp_e.dequeue(em);
		Completed_Missions_Emergency.enqueue(em);
	}

	//Count Mountainous Missions

	while (!Completed_Missions_Mountainous.isEmpty())
	{
		Completed_Missions_Mountainous.dequeue(mm);
		Waiting_Days_Total_Mountainous += mm->Get_Waiting_Duration();
		Execution_Days_Total_Mountainous += mm->Get_Mission_Duration();
		temp_m.enqueue(mm);
		Count_MountainousMissions++;
	}

	while (!temp_m.isEmpty())
	{
		temp_m.dequeue(mm);
		Completed_Missions_Mountainous.enqueue(mm);
	}

	//Count Polar Missions

	while (!Completed_Missions_Polar.isEmpty())
	{
		Completed_Missions_Polar.dequeue(pm);
		Waiting_Days_Total_Polar += pm->Get_Waiting_Duration();
		Execution_Days_Total_Polar += pm->Get_Mission_Duration();
		temp_p.enqueue(pm);
		Count_PolarMissions++;
	}

	while (!temp_p.isEmpty())
	{
		temp_p.dequeue(pm);
		Completed_Missions_Polar.enqueue(pm);
	}

	//Total Number of Missions
	Count_Total_Missions = Count_PolarMissions + Count_MountainousMissions + Count_EmergencyMissions;

	//Total Number of each type of Rovers
	Counter_MountainousRovers = data.Get_Mountinous_Num();;
	Counter_EmergencyRovers = data.Get_Emergency_Num();
	Counter_PolarRovers = data.Get_Polar_Num();

	//Total Number of Rovers
	Counter_Rovers = data.Get_Emergency_Num() + data.Get_Polar_Num() + data.Get_Mountinous_Num();

	//Calculate Waiting Avg
	Waiting_Avg = (Waiting_Days_Total_Emergency + Waiting_Days_Total_Mountainous + Waiting_Days_Total_Polar) / float(Count_Total_Missions);

	//Calculate Execution Avg
	Execution_Avg = (Execution_Days_Total_Emergency + Execution_Days_Total_Mountainous + Execution_Days_Total_Polar) / float(Count_Total_Missions);

	//Calculate Percentage of automatically-promoted missions (relative to the total number of mountainous missions)
	Auto_Promoted = (pe->Get_Counter_Num_Promotion_Events() / Count_MountainousMissions) * 100;
}

//************************************NEED MODIFICATIONS************************************
template<class T>
bool MarsStation<T>::finished()
{
	bool temp = In_ExcutionEmergency.isEmpty() && In_ExcutionMountainous.isEmpty() && In_ExcutionPolar.isEmpty();
	bool test = WaitingEmergency.isEmpty() && waitingMountainous.isEmpty() && waitingPolar.isEmpty();
	int Counter = fe->Get_Num_Of_Emergency_Missions() + fe->Num_Of_Montinous_Missions() + fe->Get_Num_Of_Polar_Missions();
	if (temp && test)
		if (ce->Get_Num_Of_Mountainous_Missions() != 0) // Check for cancellation Missions
			Counter -= ce->Get_Num_Of_Mountainous_Missions();
	if (Count_Total_Missions == Counter)
		return true;
	else
		return false;
}

template<class T>
void MarsStation<T>::diplay()
{
	data.output
	(
		modeOfDisplay, Count_Days,
		WaitingEmergency, waitingPolar, waitingMountainous,
		In_ExcutionEmergency, In_ExcutionPolar, In_ExcutionMountainous,
		EmergencyRovers, PolarRovers, MountainousRovers,
		EmergencyCheckup, PolarCheckup, MountainousCheckup,
		Completed_Missions_Emergency, Completed_Missions_Polar, Completed_Missions_Mountainous
	);
}




template<class T>
int  MarsStation < T > ::Get_Count_Total_Missions()const
{
	return Count_Total_Missions;
}

template<class T>
int  MarsStation < T > ::Get_Count_EmergencyMissions()const
{
	return Count_EmergencyMissions;
}

template<class T>
int MarsStation < T > ::Get_Count_MountainousMissions()const
{
	return Count_MountainousMissions;
}

template<class T>
int MarsStation < T > ::Get_Count_PolarMissions()const
{
	return Count_PolarMissions;
}

template<class T>
int  MarsStation < T > ::Get_Counter_MountainousRovers()const
{
	return Counter_MountainousRovers;

}

template<class T>
int MarsStation < T > ::Get_Counter_EmergencyRovers()const
{
	return Counter_EmergencyRovers;
}

template<class T>
int  MarsStation < T > ::Get_Counter_PolarRovers()const
{
	return Counter_PolarRovers;

}

template<class T>
int MarsStation < T > ::Get_Counter_Rovers()const
{
	return Counter_Rovers;
}

template<class T>
float  MarsStation < T > ::Get_Waiting_Avg() const
{
	return Waiting_Avg;
}

template<class T>
float  MarsStation < T > ::Get_Execution_Avg()const
{
	return Execution_Avg;
}

template<class T>
float MarsStation < T > ::Get_Auto_Promoted()const
{
	return Auto_Promoted;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Check for all Missions if any of them is completed 
/*
template < class T>
void MarsStation < T > ::Completed_Missions(EmergencyMission* em, PolarMission* pm, MountainousMission* mm)
{
	LinkedPriorityQueue <EmergencyMission> temp_e;
	LinkedQueue <PolarMission> temp_p;
	LinkedQueue< MountainousMission> temp_m;
	int Completed_Days;

	// check for completed Emergency Missions
	while (!In_ExcutionEmergency.isEmpty())
	{
		Completed_Days = em->Get_Mission_Duration() + em->Get_Formulation_Day() + em->Get_Waiting_Duration();
		In_ExcutionEmergency.dequeue(em);
		if (Completed_Days == Count_Days)
		{
			Completed_Missions_Emergency.enqueue(em, em->getPriority());
			// Get Rover that done this Mission (Create Function Get Rover in Mission ) and check for its count if 0 enter it in checkup
			//  ( DO THIS FOR ALL ROvers )
		}
		else
			temp_e.enqueue(em);
	}

	//Fill In_Excution Emergency again
	while (!temp_e.isEmpty())
	{
		temp_e.dequeue(em);
		In_ExcutionEmergency.enqueue(em, em->getPriority());
	}


	// check for completed Mountainous Mission
	while (!In_ExcutionMountainous.isEmpty())
	{
		Completed_Days = mm->Get_Mission_Duration() + mm->Get_Formulation_Day() + mm->Get_Waiting_Duration();
		In_ExcutionMountainous.dequeue(mm);
		if (Completed_Days == Count_Days)
			Completed_Missions_Mountainous.enqueue(mm);
		else
			temp_m.enqueue(mm);
	}

	//Fill In_Excution Mountainous again
	while (!temp_m.isEmpty())
	{
		temp_m.dequeue(mm);
		In_ExcutionMountainous.enqueue(mm);
	}

	// check for completed Polar Mission
	while (!In_ExcutionPolar.isEmpty())
	{
		Completed_Days = pm->Get_Mission_Duration() + pm->Get_Formulation_Day() + pm->Get_Waiting_Duration();
		In_ExcutionPolar.dequeue(pm);
		if (Completed_Days == Count_Days)
			Completed_Missions_Polar.enqueue(pm);
		else
			temp_p.enqueue(pm);
	}

	//Fill In_Excution Mountainous again
	while (!temp_p.isEmpty())
	{
		temp_p.dequeue(pm);
		In_ExcutionPolar.enqueue(pm);
	}
}
*/



//Check for all Rovers if there is one of them need to enter CheckUp

/*
template<class T>
void MarsStation < T > ::CheckUp_Duration(EmergencyRover* er, PolarRover* pr, MountainousRover* mr)
{

	LinkedPriorityQueue <EmergencyRover> temp_e;
	LinkedPriorityQueue <PolarRover> temp_p;
	LinkedPriorityQueue <MountainousRover> temp_m;

	//Check for Emrgency Rovers if there is one of them need to enter CheckUp
	while (!EmergencyRovers.isEmpty())
	{
		EmergencyRovers.dequeue(er);
		if (er->Get_MissionsCount() == 0)
			EmergencyCheckup.enqueue(er);
		else
			temp_e.enqueue(er);
	}

	//Fill Emrgency Rovers that didn't need CheckUp
	while (!temp_e.isEmpty())
	{
		temp_e.dequeue(er);
		EmergencyRovers.enqueue(er);
	}

	//Check for Mountinous Rovers if there is one of them need to enter CheckUp
	while (!MountainousRovers.isEmpty())
	{
		MountainousRovers.dequeue(mr);
		if (mr->Get_MissionsCount() == 0)
			MountainousCheckup.enqueue(mr);
		else
			temp_m.enqueue(mr);
	}

	//Fill Mountinous Rovers that didn't need CheckUp
	while (!temp_m.isEmpty())
	{
		temp_m.dequeue(mr);
		MountainousRovers.enqueue(mr);
	}

	//Check for Polar Rovers if there is one of them need to enter CheckUp
	while (!EmergencyRovers.isEmpty())
	{
		PolarRovers.dequeue(pr);
		if (pr->Get_MissionsCount() == 0)
			PolarCheckup.enqueue(pr);
		else
			temp_p.enqueue(pr);
	}

	//Fill Polar Rovers that didn't need CheckUp
	while (!temp_p.isEmpty())
	{
		temp_p.dequeue(pr);
		PolarRovers.enqueue(pr);
	}

}
*/


//check for which rover need checkup
	/*
	if (er->Get_MissionsCount() == 0)
		Under_Checkup->enqueue(er, er->Get_CheckupDuration());

	if (mr->Get_MissionsCount() == 0)
		Under_Checkup->enqueue(mr, mr->Get_CheckupDuration());

	if (pr->Get_MissionsCount() == 0)
		Under_Checkup->enqueue(pr, pr->Get_CheckupDuration());
	*/