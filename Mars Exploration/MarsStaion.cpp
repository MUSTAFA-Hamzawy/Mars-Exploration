#include"MarsStation.h"


int  MarsStation  ::Get_Count_Days() const
{
	return Count_Days;
}


void  MarsStation  ::Set_Count_Days(int cd)
{
	Count_Days = (cd > 0) ? cd : -1;
}



void MarsStation::getInput()
{
	data.input();
}

void  MarsStation  ::Get_Data_Into_PQ_Q()
{
	// fill mountainous rovers data
	for (int i = 0; i < data.Get_Mountinous_Num(); i++)
	{
		MountainousRover M_rover
		(
			data.Get_Mountinous_Speed(), data.Get_Mountinous_CheckupDuration(), data.Get_Missions_Count(), i + 1
		);
		//M_rover.setAllData(data.Get_Mountinous_CheckupDuration(), data.Get_Missions_Count(), data.Get_Mountinous_Speed(), i + 1);
		//ptr_mr->setAllData(data.Get_Mountinous_CheckupDuration(), data.Get_Missions_Count(), data.Get_Mountinous_Speed(), i + 1);
		MountainousRovers.enqueue(M_rover, M_rover.Get_Speed());
		Counter_Rovers++;
	}
	// fill emergeny rovers data
	for (int i = 0; i < data.Get_Emergency_Num(); i++)
	{
		EmergencyRover E_rover
		(
			data.Get_Emergency_Speed(), data.Get_Emergency_CheckupDuration(), data.Get_Missions_Count(), i + 15
		);
		//E_rover.setAllData(data.Get_Mountinous_CheckupDuration(), data.Get_Missions_Count(), data.Get_Mountinous_Speed(), i + 1);
		//ptr_mr->setAllData(data.Get_Mountinous_CheckupDuration(), data.Get_Missions_Count(), data.Get_Mountinous_Speed(), i + 1);
		EmergencyRovers.enqueue(E_rover, E_rover.Get_Speed());
		Counter_Rovers++;

	}
	// fill polar rovers data
	for (int i = 0; i < data.Get_Polar_Num(); i++)
	{
		PolarRover P_rover
		(
			data.Get_Polar_Speed(), data.Get_Polar_CheckupDuration(), data.Get_Missions_Count(), i + 30
		);
		//P_rover.setAllData(data.Get_Mountinous_CheckupDuration(), data.Get_Missions_Count(), data.Get_Mountinous_Speed(), i + 1);
		//ptr_mr->setAllData(data.Get_Mountinous_CheckupDuration(), data.Get_Missions_Count(), data.Get_Mountinous_Speed(), i + 1);
		PolarRovers.enqueue(P_rover, P_rover.Get_Speed());
		Counter_Rovers++;

	}

	// fill Events

	data.fillEvents(F_Events, C_Events, P_Events);

}


void MarsStation :: assignMissions()
{
	//if (WaitingEmergency.isEmpty() && waitingMountainous.isEmpty() && waitingPolar.isEmpty()) return;
	EmergencyRover er;
	EmergencyRovers.peek(er);
	ptr_er = new EmergencyRover(er);


	PolarRover pr;
	PolarRovers.peek(pr);
	ptr_pr = new PolarRover(pr);


	MountainousRover mr;
	MountainousRovers.peek(mr);
	ptr_mr = new MountainousRover(mr);


	EmergencyMission em;
	WaitingEmergency.peek(em);
	ptr_em = new EmergencyMission(em);

	PolarMission pm;
	waitingPolar.peek(pm);
	ptr_pm = new PolarMission(pm);

	MountainousMission mm;
	waitingMountainous.peek(mm);
	ptr_mm = new MountainousMission(mm);


	if (!er.available() && !mr.available() && !mr.available()) return;


	// assign emergency mission first
	if (!WaitingEmergency.isEmpty())
	{

		if (ptr_er->assign_EmergencyMission(ptr_em))
		{
			WaitingEmergency.dequeue(*ptr_em);
			ptr_em->Set_Inexecution_Days(ptr_er->Get_Speed());  //to be able to calculate in_execution days
			ptr_er->Set_MissionType('E');
			In_ExcutionEmergency.enqueue(*ptr_er, ptr_em->Get_Inexecution_Days());  // Note :
			EmergencyRovers.dequeue(er);
			Counter_Inec_EmergencyRovers++;////Don't forget to intialize it to zero && and redue it by 1 when dequeue it to completed missions
			Counter_Inec_EmergencyMissions++;
			Counter_Rovers--;

		}
		else if (ptr_mr->assign_EmergencyMission(ptr_em))
		{
			WaitingEmergency.dequeue(*ptr_em);
			ptr_em->Set_Inexecution_Days(ptr_er->Get_Speed());
			ptr_mr->Set_MissionType('E'); //////
			In_ExcutionMountainous.enqueue(*ptr_mr, ptr_em->Get_Inexecution_Days());
			MountainousRovers.dequeue(mr);
			Counter_Inec_MountainousRovers++;////Don't forget to intialize it to zero && and redue it by 1 when dequeue it to completed missions
			Counter_Inec_EmergencyMissions++;
			Counter_Rovers--;

		}
		else  // polar is available, no need to check
		{
			ptr_pr->assign_EmergencyMission(ptr_em);
			WaitingEmergency.dequeue(*ptr_em);
			ptr_em->Set_Inexecution_Days(ptr_pr->Get_Speed());  ////
			ptr_pr->Set_MissionType('E'); //// 
			In_ExcutionPolar.enqueue(*ptr_pr, ptr_em->Get_Inexecution_Days());
			PolarRovers.dequeue(pr);
			Counter_Inec_PolarRovers++;////Don't forget to intialize it to zero && and redue it by 1 when dequeue it to completed missions
			Counter_Inec_EmergencyMissions++;
			Counter_Rovers--;

		}
	}

	// assign polar missions using the available polar rovers only
	if (!waitingPolar.isEmpty())
	{
		if (ptr_pr->assign_PolarMission(ptr_pm))
		{
			waitingPolar.dequeue(*ptr_pm);
			ptr_pm->Set_Inexecution_Days(ptr_pr->Get_Speed());  /////
			ptr_pr->Set_MissionType('P'); ////
			In_ExcutionPolar.enqueue(*ptr_pr, ptr_pm->Get_Inexecution_Days());
			PolarRovers.dequeue(pr);
			Counter_Inec_PolarRovers++;
			Counter_Inec_PolarMissions++;
			Counter_Rovers--;

		}

	}

	// assign mountainous mission

	if (!waitingMountainous.isEmpty())
	{
		if (ptr_mr->assign_MountainousMission(ptr_mm))
		{
			waitingMountainous.dequeue(*ptr_mm);
			ptr_mm->Set_Inexecution_Days(ptr_mr->Get_Speed());
			ptr_mr->Set_MissionType('M');
			In_ExcutionMountainous.enqueue(*ptr_mr, ptr_mm->Get_Inexecution_Days());
			MountainousRovers.dequeue(mr);
			Counter_Inec_MountainousRovers++;
			Counter_Inec_MountainousMissions++;
			Counter_Rovers--;

		}
		else if (ptr_er->assign_MountainousMission(ptr_mm))
		{

			waitingMountainous.dequeue(*ptr_mm);
			ptr_mm->Set_Inexecution_Days(er.Get_Speed());
			ptr_er->Set_MissionType('M');
			In_ExcutionEmergency.enqueue(*ptr_er, ptr_mm->Get_Inexecution_Days());
			EmergencyRovers.dequeue(er);
			Counter_Inec_EmergencyRovers++; ////Don't forget to intialize it to zero && and reduce it by 1 when dequeue it to completed missions
			Counter_Inec_MountainousMissions++;
			Counter_Rovers--;

		}
	}

	//total rovers in the In_execution list
	Counter_Inec_rovers = Counter_Inec_EmergencyRovers + Counter_Inec_MountainousRovers + Counter_Inec_PolarRovers;



	//Assign_Missions_To_Rovers(
	//	ptr_em, ptr_pm , ptr_mm,
	//	ptr_er, ptr_pr, ptr_mr
	//);





}


void MarsStation::excute_Events()
{
	if (!F_Events.isEmpty())
	{                                                 // Make All Events Objects
		FormulationEvent event;
		F_Events.peek(event);
		if (event.Get_Event_Day() == Count_Days)
		{
			event.Execute(waitingMountainous, WaitingEmergency, waitingPolar);
			F_Events.dequeue(event);
		}
	}
	if (!C_Events.isEmpty())
	{
		CancellationEvent event;
		C_Events.peek(event);
		if (event.Get_Event_Day() == Count_Days)
		{
			event.Execute(waitingMountainous, WaitingEmergency, waitingPolar);
			C_Events.dequeue(event);
			Counter_Cancellation_Events++;
		}
	}
	if (!P_Events.isEmpty())
	{
		PromotionEvent event;
		P_Events.peek(event);
		if (event.Get_Event_Day() == Count_Days)
		{
			event.Execute(waitingMountainous, WaitingEmergency , waitingPolar);
			P_Events.dequeue(event);
		}
	}

}


void MarsStation ::Assign_Missions_To_Rovers(EmergencyMission* em, PolarMission* pm, MountainousMission* mm, EmergencyRover* er, PolarRover* pr, MountainousRover* mr)
{
	// if no rover is availabe, return

	if (!er->available() && !mr->available() && !mr->available()) return;


	// assign emergency mission first
	if (em)
	{

		if (er->assign_EmergencyMission(em))
		{
			WaitingEmergency.dequeue(*em);
			em->Set_Inexecution_Days(er->Get_Speed());  //to be able to calculate in_execution days
			er->Set_MissionType('E'); 
			In_ExcutionEmergency.enqueue(*er, em->Get_Inexecution_Days());  // Note : 
			Counter_Rovers--;
			Counter_Inec_EmergencyRovers++;////Don't forget to intialize it to zero && and redue it by 1 when dequeue it to completed missions
			Counter_Inec_EmergencyMissions++;
		}
		else if (mr->assign_EmergencyMission(em))
		{
			WaitingEmergency.dequeue(*em);
			em->Set_Inexecution_Days(mr->Get_Speed());
			mr->Set_MissionType('E'); //////
			In_ExcutionMountainous.enqueue(*mr, em->Get_Inexecution_Days());
			Counter_Rovers--;
			Counter_Inec_MountainousRovers++;////Don't forget to intialize it to zero && and redue it by 1 when dequeue it to completed missions
			Counter_Inec_EmergencyMissions++;
		}
		else  // polar is available, no need to check
		{
			pr->assign_EmergencyMission(em);
			WaitingEmergency.dequeue(*em);
			em->Set_Inexecution_Days(pr->Get_Speed());  ////
			pr->Set_MissionType('E'); //// 
			In_ExcutionPolar.enqueue(*pr, em->Get_Inexecution_Days());
			Counter_Rovers--;
			Counter_Inec_PolarRovers++;////Don't forget to intialize it to zero && and redue it by 1 when dequeue it to completed missions
			Counter_Inec_EmergencyMissions++;
		}
	}

	// assign polar missions using the available polar rovers only
	if (pm && pr->assign_PolarMission(pm))
	{
		waitingPolar.dequeue(*pm);
		pm->Set_Inexecution_Days(pr->Get_Speed());  /////
		pr->Set_MissionType('P'); ////
		In_ExcutionPolar.enqueue(*pr , pm->Get_Inexecution_Days());
		Counter_Rovers--;
		Counter_Inec_PolarRovers++;
		Counter_Inec_PolarMissions++;
	}

	// assign mountainous mission

	if (mm)
	{
		if (mr->assign_MountainousMission(mm))
		{
			waitingMountainous.dequeue(*mm);
			mm->Set_Inexecution_Days(mr->Get_Speed());
			mr->Set_MissionType('M');
			In_ExcutionMountainous.enqueue(*mr , mm->Get_Inexecution_Days());
			Counter_Rovers--;
			Counter_Inec_MountainousRovers++;
			Counter_Inec_MountainousMissions++;
		}
		else if (er->assign_MountainousMission(mm))
		{

			waitingMountainous.dequeue(*mm);
			mm->Set_Inexecution_Days(er->Get_Speed());
			er->Set_MissionType('M');
			Counter_Inec_EmergencyRovers++; ////Don't forget to intialize it to zero && and redue it by 1 when dequeue it to completed missions
			Counter_Inec_MountainousMissions++;
			In_ExcutionEmergency.enqueue(*er , mm->Get_Inexecution_Days());
			Counter_Rovers--;
		}
	}

	//total rovers in the In_execution list
	Counter_Inec_rovers = Counter_Inec_EmergencyRovers + Counter_Inec_MountainousRovers + Counter_Inec_PolarRovers;
}


void MarsStation::Complete_Missions()
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
			Completed_Days = peekedRover.get_EmergencyMission()->Get_Completion_Days();

			if (Completed_Days == Count_Days)    //Counter_Days
			{
				// add this mission to completed
				ptr_er = new EmergencyRover(peekedRover);
				Completed_Missions_Emergency.enqueue(*ptr_er->get_EmergencyMission());
				Count_Total_Missions++;
				Counter_Inec_EmergencyRovers--;
				Counter_Inec_EmergencyMissions--;
				Counter_Inec_rovers--;
				// make this mission inside this rover to be nullptr (DONE)
				ptr_er->set_Missions(nullptr, nullptr);

				// if need check up, go to it else go to the original list
				In_ExcutionEmergency.dequeue(poppedRover);
				ptr_er = new EmergencyRover(poppedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					EmergencyCheckup.enqueue(*ptr_er, poppedRover.Get_CheckupDuration());
					Counter_check_EmergencyRovers++;
				}
				else
				{
					EmergencyRovers.enqueue(*ptr_er, poppedRover.Get_Speed());
					Counter_Rovers++;
				}
			}
		}
		else if (peekedRover.get_MountainousMission())
		{
			Completed_Days = peekedRover.get_MountainousMission()->Get_Completion_Days();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				ptr_er = new EmergencyRover(peekedRover);
				Completed_Missions_Mountainous.enqueue(*ptr_er->get_MountainousMission());
				Count_Total_Missions++;
				Counter_Inec_EmergencyRovers--;
				Counter_Inec_MountainousMissions--;
				Counter_Inec_rovers--;
				// make this mission inside this rover to be nullptr
				ptr_er->set_Missions(nullptr, nullptr);

				// if need check up, go to it else go to the original list
				In_ExcutionEmergency.dequeue(*ptr_er);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					EmergencyCheckup.enqueue(*ptr_er, poppedRover.Get_CheckupDuration());
					Counter_check_EmergencyRovers++;
				}
				else
				{
					EmergencyRovers.enqueue(*ptr_er, poppedRover.Get_Speed());
					Counter_Rovers++;
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
			Completed_Days = peekedRover.get_EmergencyMission()->Get_Completion_Days();
			

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				ptr_pr = new PolarRover(peekedRover);
				Completed_Missions_Emergency.enqueue(*ptr_pr->get_EmergencyMission());
				Count_Total_Missions++;
				Counter_Inec_PolarRovers--;
				Counter_Inec_EmergencyMissions--;
				Counter_Inec_rovers--;
				// make this mission inside this rover to be nullptr
				peekedRover.set_Missions(nullptr, nullptr);

				// if need check up, go to it else go to the original list
				In_ExcutionPolar.dequeue(poppedRover); 
				ptr_pr = new PolarRover(peekedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					PolarCheckup.enqueue(*ptr_pr, poppedRover.Get_CheckupDuration());
					Counter_check_PolarRovers++;
				}
				else
				{
					PolarRovers.enqueue(*ptr_pr, poppedRover.Get_Speed());
					Counter_Rovers++;
				}
			}
		}
		else if (peekedRover.get_PolarMission())
		{
			Completed_Days = peekedRover.get_PolarMission()->Get_Completion_Days();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				Completed_Missions_Polar.enqueue(*peekedRover.get_PolarMission());
				Count_Total_Missions++;
				Counter_Inec_PolarRovers--;
				Counter_Inec_PolarMissions--;
				Counter_Inec_rovers--;
				// make this mission inside this rover to be nullptr
				peekedRover.set_Missions(nullptr, nullptr);

				// if need check up, go to it else go to the original list
				In_ExcutionPolar.dequeue(poppedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					PolarCheckup.enqueue(poppedRover, poppedRover.Get_CheckupDuration());
					Counter_check_PolarRovers++;
				}
				else
				{
					PolarRovers.enqueue(poppedRover, poppedRover.Get_Speed());
					Counter_Rovers++;
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
			Completed_Days = peekedRover.get_EmergencyMission()->Get_Completion_Days();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				ptr_mr = new MountainousRover(peekedRover);
				Completed_Missions_Emergency.enqueue(*ptr_mr->get_EmergencyMission());
				Count_Total_Missions++;
				Counter_Inec_MountainousRovers--;
				Counter_Inec_EmergencyMissions--;
				Counter_Inec_rovers--;
				// make this mission inside this rover to be nullptr
				ptr_mr->set_Missions(nullptr, nullptr);

				// if need check up, go to it else go to the original list
				In_ExcutionMountainous.dequeue(poppedRover);
				ptr_mr = new MountainousRover(poppedRover);
				Completed_Missions_Emergency.enqueue(*ptr_mr->get_EmergencyMission());
				if (poppedRover.Get_MissionsCount() == 0)
				{
					MountainousCheckup.enqueue(*ptr_mr, poppedRover.Get_CheckupDuration());
					Counter_check_MountainousRovers++;
				}
				else
				{
					MountainousRovers.enqueue(*ptr_mr, poppedRover.Get_Speed());
					Counter_Rovers++;
				}

			}
		}
		else if (peekedRover.get_MountainousMission())
		{
			Completed_Days = peekedRover.get_MountainousMission()->Get_Completion_Days();

			if (Completed_Days == Count_Days)
			{
				// add this mission to completed
				ptr_mr = new MountainousRover(peekedRover);
				ptr_mm = new MountainousMission(*ptr_mr->get_MountainousMission());
				Count_Total_Missions++;
				Completed_Missions_Mountainous.enqueue(*ptr_mm);
				Counter_Inec_MountainousRovers--;
				Counter_Inec_MountainousMissions--;
				Counter_Inec_rovers--;
				// make this mission inside this rover to be nullptr
				ptr_mr->set_Missions(nullptr, nullptr);

				// if need check up, go to it else go to the original list
				In_ExcutionMountainous.dequeue(poppedRover);
				ptr_mr = new MountainousRover(poppedRover);
				if (poppedRover.Get_MissionsCount() == 0)
				{
					MountainousCheckup.enqueue(*ptr_mr, poppedRover.Get_CheckupDuration());
					Counter_check_MountainousRovers++;
				}
				else
				{
					MountainousRovers.enqueue(*ptr_mr, poppedRover.Get_Speed());
					Counter_Rovers++;
				}

			}

		}

	}
	/*
	EmergencyMission pp;
	MountainousMission ppp;
	PolarMission pppp;
	while (!Completed_Missions_Emergency.isEmpty())
	{
		Completed_Missions_Emergency.dequeue(pp);
		ptr_em = new EmergencyMission(pp);
		Completed_Missions_Total.enqueue( *ptr_em, pp.Get_Completion_Days());   // total must be sent to the output function not each type alone
	}
	while (!Completed_Missions_Mountainous.isEmpty())
	{
		Completed_Missions_Mountainous.dequeue(ppp);
		ptr_mm = new MountainousMission(ppp);
		Completed_Missions_Total.enqueue(*ptr_mm, ppp.Get_Completion_Days());// total must be sent to the output function not each type alone
	}
	while (!Completed_Missions_Polar.isEmpty())
	{
		Completed_Missions_Polar.dequeue(pppp);
		ptr_pm = new PolarMission(pppp);
		Completed_Missions_Total.enqueue(*ptr_pm, pppp.Get_Completion_Days());// total must be sent to the output function not each type alone
	}
	*/
	Counter_check_rovers = Counter_check_EmergencyRovers + Counter_check_MountainousRovers + Counter_check_PolarRovers;
}

void MarsStation::outfile()
{

	data.printfile(Completed_Missions_Total, Count_Total_Missions, Total_Emergency_Missions, Total_Mountainous_Missions, Total_Polar_Missions, all_Missions, Total_Emergency_Rovers, Total_Mountainous_Rovers, Total_Polar_Rovers, all_Rovers, Waiting_Avg, Execution_Avg, Auto_Promoted);
}


void MarsStation  ::Statistics( )
{
	LinkedQueue<EmergencyMission> temp_e;
	LinkedQueue<PolarMission> temp_p;
	LinkedQueue<MountainousMission> temp_m;
	/////////
	LinkedPriorityQueue<EmergencyRover> temp_ER;
	LinkedPriorityQueue<PolarRover> temp_PR;
	LinkedPriorityQueue<MountainousRover> temp_MR;
	EmergencyRover er;
	MountainousRover mr;
	PolarRover pr;
	EmergencyMission em;
	PolarMission pm;
	MountainousMission mm;
	///////

	/*
	//calculate it (everyday) so i want it to start from begnning  for output file NADA
	Total_Emergency_Missions = 0;
	Total_Mountainous_Missions = 0;
	Total_Polar_Missions = 0;
	all_Missions = 0;
	Total_Emergency_Rovers = 0;
	Total_Mountainous_Rovers = 0;
	Total_Polar_Rovers = 0;
	all_Rovers = 0;
	//calculations for waiting missions and avaliable rovers (everday) same here  NADA
	Counter_wait_EmergencyMissions = 0;
	Counter_wait_MountainousMissions = 0;
	Counter_wait_PolarMissions = 0;
	Counter_wait_missions = 0;

	Counter_EmergencyRovers = 0;
	Counter_MountainousRovers = 0;
	Counter_Inec_PolarRovers = 0;
	Counter_Inec_rovers = 0;
	*/
	//Count Emergency Missions

	while (!Completed_Missions_Emergency.isEmpty())
	{
		Completed_Missions_Emergency.dequeue(em);
		Waiting_Days_Total_Emergency += em.Get_Waiting_Duration();
		Execution_Days_Total_Emergency += em.Get_Inexecution_Days();
		temp_e.enqueue(em);
		Count_EmergencyMissions++;
	}

	while (!temp_e.isEmpty())
	{
		temp_e.dequeue(em);
		ptr_em = new EmergencyMission(em);
		Completed_Missions_Emergency.enqueue(*ptr_em);
	}

	//Count Mountainous Missions

	while (!Completed_Missions_Mountainous.isEmpty())
	{
		Completed_Missions_Mountainous.dequeue(mm);
		Waiting_Days_Total_Mountainous += mm.Get_Waiting_Duration();
		Execution_Days_Total_Mountainous += mm.Get_Inexecution_Days();
		temp_m.enqueue(mm);
		Count_MountainousMissions++;
	}

	while (!temp_m.isEmpty())
	{
		temp_m.dequeue(mm);
		ptr_mm = new MountainousMission(mm);
		Completed_Missions_Mountainous.enqueue(*ptr_mm);
	}

	//Count Polar Missions

	while (!Completed_Missions_Polar.isEmpty())
	{
		Completed_Missions_Polar.dequeue(pm);
		Waiting_Days_Total_Polar += pm.Get_Waiting_Duration();
		Execution_Days_Total_Polar += pm.Get_Inexecution_Days(); 
		temp_p.enqueue(pm);
		Count_PolarMissions++;
	}

	while (!temp_p.isEmpty())
	{
		temp_p.dequeue(pm);
		ptr_pm = new PolarMission(pm);
		Completed_Missions_Polar.enqueue(*ptr_pm);
	}

	//Total Number of Missions
	//Count_Total_Missions = Count_PolarMissions + Count_MountainousMissions + Count_EmergencyMissions;

	//Total Number of each type of avaliable Rovers
	 //first avliable emergency rovers
	while (!EmergencyRovers.isEmpty())
	{
		EmergencyRovers.dequeue(er);
		temp_ER.enqueue( er , er.Get_Speed() );
		Counter_EmergencyRovers++;
	}
	while (!temp_ER.isEmpty())
	{
		temp_ER.dequeue(er);
		ptr_er = new EmergencyRover(er);
		EmergencyRovers.enqueue(*ptr_er, ptr_er->Get_Speed());
	}
	//second avaliable mountainous rovers
	while (!MountainousRovers.isEmpty())
	{
		MountainousRovers.dequeue(mr);
		temp_MR.enqueue(mr , mr.Get_Speed());
		Counter_MountainousRovers++;
	}
	while (!temp_MR.isEmpty())
	{
		temp_MR.dequeue(mr);
		ptr_mr = new MountainousRover(mr);
		MountainousRovers.enqueue(*ptr_mr, ptr_mr->Get_Speed());
	}

	//third avaliable polar rovers
	while (!PolarRovers.isEmpty())
	{
		PolarRovers.dequeue(pr);
		temp_PR.enqueue(pr,pr.Get_Speed());
		Counter_PolarRovers++;
	}
	while (!temp_PR.isEmpty())
	{
		temp_PR.dequeue(pr);
		ptr_pr = new PolarRover(pr);
		PolarRovers.enqueue(*ptr_pr, ptr_pr->Get_Speed());
	}
	//total avaliable rovers
	//Counter_Rovers = Counter_EmergencyRovers + Counter_MountainousRovers + Counter_PolarRovers;

	//calculate the total numbers of waiting missions
	//first waiting emergency missions

	while (!WaitingEmergency.isEmpty())
	{
		WaitingEmergency.dequeue(em);
		temp_e.enqueue(em);
		Counter_wait_EmergencyMissions++;
	}
	while (!temp_e.isEmpty())
	{
		temp_e.dequeue(em);
		ptr_em = new EmergencyMission(em);
		WaitingEmergency.enqueue(*ptr_em, ptr_em->getPriority());
	}
	//second waiting mountainous missions

	while (!waitingMountainous.isEmpty())
	{
		waitingMountainous.dequeue(mm);
		temp_m.enqueue(mm);
		Counter_wait_MountainousMissions++;
	}
	while (!temp_m.isEmpty())
	{
		temp_m.dequeue(mm);
		ptr_mm = new MountainousMission(mm);
		waitingMountainous.enqueue(*ptr_mm);
	}
	//third waiting polar misions

	while (!waitingPolar.isEmpty())
	{
		waitingPolar.dequeue(pm);
		temp_p.enqueue(pm);
		Counter_wait_PolarMissions++;
	}
	while (!temp_p.isEmpty())
	{
		temp_p.dequeue(pm);
		ptr_pm = new PolarMission(pm);
		waitingPolar.enqueue(*ptr_pm);
	}

	//calculate total waiting missions
	Counter_wait_missions = Counter_wait_EmergencyMissions + Counter_wait_MountainousMissions + Counter_wait_PolarMissions;

	//Calculate Waiting Avg
	Waiting_Avg = (Waiting_Days_Total_Emergency + Waiting_Days_Total_Mountainous + Waiting_Days_Total_Polar) / float(Count_Total_Missions);
	
	//Calculate Execution Avg
	Execution_Avg = (Execution_Days_Total_Emergency + Execution_Days_Total_Mountainous + Execution_Days_Total_Polar) / float(Count_Total_Missions);

	//Calculate Percentage of automatically-promoted missions (relative to the total number of mountainous missions)
	//Auto_Promoted = (pe->Get_Counter_Num_Promotion_Events() / Count_MountainousMissions) * 100;

	//total missions of each type from all lists
	Total_Emergency_Missions = Counter_Inec_EmergencyMissions + Counter_wait_EmergencyMissions + Count_EmergencyMissions;
	Total_Mountainous_Missions = Counter_Inec_MountainousMissions + Counter_wait_MountainousMissions + Count_MountainousMissions;
	Total_Polar_Missions = Counter_Inec_PolarMissions + Counter_wait_PolarMissions + Count_PolarMissions;

	//total missions of all lists
	all_Missions = Counter_wait_missions + Conter_Inec_Missions + Count_Total_Missions;

	//Total rovers of each type from all lists
	Total_Emergency_Rovers = Counter_Inec_EmergencyRovers + Counter_check_EmergencyRovers + Counter_EmergencyRovers;
	Total_Mountainous_Rovers = Counter_Inec_MountainousRovers + Counter_check_MountainousRovers + Counter_MountainousRovers;
	Total_Polar_Rovers = Counter_Inec_PolarRovers + Counter_check_PolarRovers + Counter_PolarRovers;

	//total rovers of all lists
	all_Rovers = Counter_check_rovers + Counter_Rovers + Counter_Inec_rovers;


	//Total Number of each type of Rovers
	//Counter_MountainousRovers = data.Get_Mountinous_Num();;
	//Counter_EmergencyRovers = data.Get_Emergency_Num();
	//Counter_PolarRovers = data.Get_Polar_Num();

	//Total Number of Rovers
	//Counter_Rovers = data.Get_Emergency_Num() + data.Get_Polar_Num() + data.Get_Mountinous_Num();
	
}

//************************************NEED MODIFICATIONS************************************

bool MarsStation::finished()
{
	/*
	bool temp = In_ExcutionEmergency.isEmpty() && In_ExcutionMountainous.isEmpty() && In_ExcutionPolar.isEmpty();
	bool test = WaitingEmergency.isEmpty() && waitingMountainous.isEmpty() && waitingPolar.isEmpty();

	int Counter = Count_EmergencyMissions + Count_MountainousMissions + Count_PolarMissions;
	if (temp && test)
		if (ce->Get_Num_Of_Mountainous_Missions() != 0) // Check for cancellation Missions
			Counter -= ce->Get_Num_Of_Mountainous_Missions();
	if (Count_Total_Missions == Counter)
		return true;
	else
		return false;
		*/

	bool finished = In_ExcutionEmergency.isEmpty() && In_ExcutionMountainous.isEmpty() && In_ExcutionPolar.isEmpty()
		&& WaitingEmergency.isEmpty() && waitingMountainous.isEmpty() && waitingPolar.isEmpty()
		&& F_Events.isEmpty() && F_Events.isEmpty() && P_Events.isEmpty();

	return finished;
}


void MarsStation::outputdata(int Mode)
{
	data.outputmode(
		Count_Days, Mode,
		In_ExcutionEmergency,
		In_ExcutionMountainous,
		In_ExcutionPolar,
		WaitingEmergency,
		waitingMountainous,
		waitingPolar,
		EmergencyRovers,
		MountainousRovers,
		PolarRovers,
		EmergencyCheckup,
		MountainousCheckup,
		PolarCheckup,
		Completed_Missions_Emergency,
		Completed_Missions_Mountainous,
		Completed_Missions_Polar,
		Counter_wait_missions,
		Counter_Inec_rovers,
		Counter_Rovers,
		Counter_check_rovers,
		Count_Total_Missions
	);
}


void MarsStation::decrementCheckUpDuration()
{

	
	if (!EmergencyCheckup.isEmpty())
	{
		LinkedPriorityQueue <EmergencyRover> E_temp;
		EmergencyRover poppedRover;

		while (!EmergencyCheckup.isEmpty())
		{
			EmergencyCheckup.dequeue(poppedRover);
			int Current_Duration = poppedRover.Get_CheckupDuration();
			if (Current_Duration > 0)
			{
				poppedRover.Set_CheckupDuration(Current_Duration - 1);
				E_temp.enqueue(poppedRover, Current_Duration - 1);
			}
			else
			{
				//reset it, enqueue it in the available rovers list

				poppedRover.reset_MissionCout();
				ptr_er = new EmergencyRover(poppedRover);
				EmergencyRovers.enqueue(*ptr_er, poppedRover.Get_Speed());
				Counter_Rovers++;
			}
		}

		while (!E_temp.isEmpty())
		{
			E_temp.dequeue(poppedRover);
			ptr_er = new EmergencyRover(poppedRover);
			EmergencyCheckup.enqueue(*ptr_er, poppedRover.Get_CheckupDuration());
		}

	}

	if (!MountainousCheckup.isEmpty())
	{
		LinkedPriorityQueue <MountainousRover> M_temp;
		MountainousRover poppedRover;

		while (!MountainousCheckup.isEmpty())
		{
			MountainousCheckup.dequeue(poppedRover);
			int Current_Duration = poppedRover.Get_CheckupDuration();
			if (Current_Duration > 0)
			{
				poppedRover.Set_CheckupDuration(Current_Duration - 1);
				M_temp.enqueue(poppedRover, Current_Duration - 1);
			}
			else
			{
				//reset it, enqueue it in the available rovers list

				poppedRover.reset_MissionCout();
				ptr_mr = new MountainousRover(poppedRover);
				MountainousRovers.enqueue(*ptr_mr, poppedRover.Get_Speed());
				Counter_Rovers++;

			}
		}

		while (!M_temp.isEmpty())
		{
			M_temp.dequeue(poppedRover);
			ptr_mr = new MountainousRover(poppedRover);
			MountainousCheckup.enqueue(*ptr_mr, poppedRover.Get_CheckupDuration());
		}

	}

	if (!PolarCheckup.isEmpty())
	{
		LinkedPriorityQueue <PolarRover> P_temp;
		PolarRover poppedRover;

		while (!PolarCheckup.isEmpty())
		{
			PolarCheckup.dequeue(poppedRover);
			int Current_Duration = poppedRover.Get_CheckupDuration();
			if (Current_Duration > 0)
			{
				poppedRover.Set_CheckupDuration(Current_Duration - 1);
				P_temp.enqueue(poppedRover, Current_Duration - 1);
			}
			else
			{
				//reset it, enqueue it in the available rovers list

				poppedRover.reset_MissionCout();
				ptr_pr = new PolarRover(poppedRover);
				PolarRovers.enqueue(*ptr_pr, poppedRover.Get_Speed());
				Counter_Rovers++;

			}
		}

		while (!P_temp.isEmpty())
		{
			P_temp.dequeue(poppedRover);
			ptr_pr = new PolarRover(poppedRover);
			PolarCheckup.enqueue(*ptr_pr, poppedRover.Get_CheckupDuration());
		}

	}


}

void MarsStation::incrementDays()
{
	Count_Days++;
}




/*
void MarsStation::diplay()
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
*/




int  MarsStation  ::Get_Count_Total_Missions()const
{
	return Count_Total_Missions;
}

int  MarsStation  ::Get_Count_EmergencyMissions()const
{
	return Count_EmergencyMissions;
}


int MarsStation ::Get_Count_MountainousMissions()const
{
	return Count_MountainousMissions;
}


int MarsStation ::Get_Count_PolarMissions()const
{
	return Count_PolarMissions;
}


int  MarsStation ::Get_Counter_MountainousRovers()const
{
	return Counter_MountainousRovers;

}


int MarsStation  ::Get_Counter_EmergencyRovers()const
{
	return Counter_EmergencyRovers;
}

int  MarsStation  ::Get_Counter_PolarRovers()const
{
	return Counter_PolarRovers;

}


int MarsStation ::Get_Counter_Rovers()const
{
	return Counter_Rovers;
}


float  MarsStation  ::Get_Waiting_Avg() const
{
	return Waiting_Avg;
}


float  MarsStation ::Get_Execution_Avg()const
{
	return Execution_Avg;
}


float MarsStation ::Get_Auto_Promoted()const
{
	return Auto_Promoted;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Check for all Missions if any of them is completed 
/*

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


/*

void MarsStation  ::Statistics(EmergencyMission* em, PolarMission* pm, MountainousMission* mm, EmergencyRover* er, PolarRover* pr, MountainousRover* mr)
{
	LinkedQueue<EmergencyMission> temp_e;
	LinkedQueue<PolarMission> temp_p;
	LinkedQueue<MountainousMission> temp_m;
	/////////
	LinkedPriorityQueue<EmergencyRover> temp_ER;
	LinkedPriorityQueue<PolarRover> temp_PR;
	LinkedPriorityQueue<MountainousRover> temp_MR;
	EmergencyRover* ER;
	MountainousRover* MR;
	PolarRover* PR;
	///////
	int Waiting_Days_Total_Emergency = 0;
	int Waiting_Days_Total_Mountainous = 0;
	int Waiting_Days_Total_Polar = 0;
	int Execution_Days_Total_Emergency = 0;
	int Execution_Days_Total_Mountainous = 0;
	int Execution_Days_Total_Polar = 0;

	//Count Emergency Missions

	while (!Completed_Missions_Emergency.isEmpty())
	{
		Completed_Missions_Emergency.dequeue(*em);
		Waiting_Days_Total_Emergency += em->Get_Waiting_Duration();
		Execution_Days_Total_Emergency += em->Get_Inexecution_Days();
		temp_e.enqueue(*em );
		Count_EmergencyMissions++;
	}

	while (!temp_e.isEmpty())
	{
		temp_e.dequeue(*em);
		Completed_Missions_Emergency.enqueue(*em);
	}

	//Count Mountainous Missions

	while (!Completed_Missions_Mountainous.isEmpty())
	{
		Completed_Missions_Mountainous.dequeue(*mm);
		Waiting_Days_Total_Mountainous += mm->Get_Waiting_Duration();
		Execution_Days_Total_Mountainous += mm->Get_Inexecution_Days();
		temp_m.enqueue(*mm);
		Count_MountainousMissions++;
	}

	while (!temp_m.isEmpty())
	{
		temp_m.dequeue(*mm);
		Completed_Missions_Mountainous.enqueue(*mm);
	}

	//Count Polar Missions

	while (!Completed_Missions_Polar.isEmpty())
	{
		Completed_Missions_Polar.dequeue(*pm);
		Waiting_Days_Total_Polar += pm->Get_Waiting_Duration();
		Execution_Days_Total_Polar += pm->Get_Inexecution_Days();  //the calculation was wrong and i modified it
		temp_p.enqueue(*pm);
		Count_PolarMissions++;
	}

	while (!temp_p.isEmpty())
	{
		temp_p.dequeue(*pm);
		Completed_Missions_Polar.enqueue(*pm);
	}

	//Total Number of Missions
	Count_Total_Missions = Count_PolarMissions + Count_MountainousMissions + Count_EmergencyMissions;

	//Total Number of each type of avaliable Rovers
	 //first avliable emergency rovers
	while (!EmergencyRovers.isEmpty())
	{
		EmergencyRovers.dequeue(ER);
		temp_ER.enqueue(ER);
		Counter_EmergencyRovers++;
	}
	while (!temp_ER.isEmpty())
	{
		temp_ER.dequeue(ER);
		EmergencyRovers.enqueue(ER);
	}
	//second avaliable mountainous rovers
	while (!MountainousRovers.isEmpty())
	{
		MountainousRovers.dequeue(MR);
		temp_MR.enqueue(MR);
		Counter_MountainousRovers++;
	}
	while (!temp_MR.isEmpty())
	{
		temp_MR.dequeue(MR);
		MountainousRovers.enqueue(MR);
	}

	//third avaliable polar rovers
	while (!PolarRovers.isEmpty())
	{
		PolarRovers.dequeue(PR);
		temp_PR.enqueue(PR);
		Counter_PolarRovers++;
	}
	while (!temp_PR.isEmpty())
	{
		temp_PR.dequeue(PR);
		PolarRovers.enqueue(PR);
	}
	//total avaliable rovers
	Counter_Rovers = Counter_EmergencyRovers + Counter_MountainousRovers + Counter_PolarRovers;

	//calculate the total numbers of waiting missions
	//first waiting emergency missions

	while (!WaitingEmergency.isEmpty())
	{
		WaitingEmergency.dequeue(em);
		temp_e.enqueue(em);
		Counter_wait_EmergencyMissions++;
	}
	while (!temp_e.isEmpty())
	{
		temp_e.dequeue(em);
		WaitingEmergency.enqueue(em);
	}
	//second waiting mountainous missions

	while (!WaitingMountainous.isEmpty())
	{
		WaitingMountainous.dequeue(mm);
		temp_m.enqueue(mm);
		Counter_wait_MountainousMissions++;
	}
	while (!temp_m.isEmpty())
	{
		temp_m.dequeue(mm);
		WaitingMountainous.enqueue(mm);
	}
	//third waiting polar misions

	while (!WaitingPolar.isEmpty())
	{
		WaitingPolar.dequeue(pm);
		temp_p.enqueue(pm);
		Counter_wait_PolarMissions++;
	}
	while (!temp_p.isEmpty())
	{
		temp_p.dequeue(pm);
		WaitingPolar.enqueue(pm);
	}

	//calculate total waiting missions
	Counter_wait_missions = Counter_wait_EmergencyMissions + Counter_wait_MountainousMissions + Counter_wait_PolarMissions;

	//Calculate Waiting Avg
	Waiting_Avg = (Waiting_Days_Total_Emergency + Waiting_Days_Total_Mountainous + Waiting_Days_Total_Polar) / float(Count_Total_Missions);

	//Calculate Execution Avg
	Execution_Avg = (Execution_Days_Total_Emergency + Execution_Days_Total_Mountainous + Execution_Days_Total_Polar) / float(Count_Total_Missions);

	//Calculate Percentage of automatically-promoted missions (relative to the total number of mountainous missions)
	Auto_Promoted = (pe->Get_Counter_Num_Promotion_Events() / Count_MountainousMissions) * 100;

	//Total Number of each type of Rovers
	//Counter_MountainousRovers = data.Get_Mountinous_Num();;
	//Counter_EmergencyRovers = data.Get_Emergency_Num();
	//Counter_PolarRovers = data.Get_Polar_Num();

	//Total Number of Rovers
	//Counter_Rovers = data.Get_Emergency_Num() + data.Get_Polar_Num() + data.Get_Mountinous_Num();




}


*/