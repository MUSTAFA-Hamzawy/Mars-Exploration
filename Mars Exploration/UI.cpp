#include "UI.h"
#include<iostream>
#include<fstream>
#include<string>
#include"MountainousMission.h"
#include"PolarMission.h"
#include"EmergencyMission.h"

#include <chrono>		 // related to the delay in output mode 2
#include <thread>		// related to the delay in output mode 2
using namespace std;


UI :: UI() : MAX_EVENTS_COUNT(100)
{
	F_Event_arr = new FormulationEvent [MAX_EVENTS_COUNT];
	C_Event_arr = new CancellationEvent [MAX_EVENTS_COUNT];
	P_Event_arr = new PromotionEvent [MAX_EVENTS_COUNT];

	FormulationCount = CancellationCount = PromotionCount = 0;
}


void UI ::input()
{
	ifstream infile("input.txt");
	if (infile.fail())
	{
		cout << "input file does not open";
	}
	else
	{
		char input;
	//	while (!infile.eof() && input != 'e')
	//	{
			infile >> Mountinous_Num >> Polar_Num >> Emergency_Num;
			//cout << M << " " << P << " " << EE << endl;
			infile >> Mountinous_Speed >> Polar_Speed >> Emergency_Speed;
			// cout << SM << " " << SP << " " << SE << endl;
			infile >> Missions_Count >> Mountinous_CheckupDuration >> Polar_CheckupDuration >> Emergency_CheckupDuration;
			// cout << N << " " << CM << " " << CP << " " << CE << endl;
			infile >> Auto_Promotion;
			//cout << AutoP << endl;
			infile >> Events_Num;
			//cout << E << endl;

			for (int i = 0; i < Events_Num; i++)
			{
				infile >> input;
				switch (input)
				{
				case 'F':
					infile >> mission_type >> Formulation_Day >> ID >> Target_Location >> Mision_Duration >> Signature;
					F_Event_arr[FormulationCount].Set_Mission_Type(mission_type);
					F_Event_arr[FormulationCount].Set_Event_Day(Formulation_Day);
					F_Event_arr[FormulationCount].Set_ID(ID);
					F_Event_arr[FormulationCount].Set_Target_Location(Target_Location);
					F_Event_arr[FormulationCount].Set_Mission_Duration(Mision_Duration);
					F_Event_arr[FormulationCount].Set_Signature(Signature);
					FormulationCount++;
					break;
				case 'X':
					infile >> Formulation_Day >> ID;
					C_Event_arr[CancellationCount].Set_Event_Day(Formulation_Day);
					C_Event_arr[CancellationCount].Set_ID(ID);
					CancellationCount++;
					break;
				case 'P':
					infile >> Formulation_Day >> ID;
					P_Event_arr[PromotionCount].Set_Event_Day(Formulation_Day);
					P_Event_arr[PromotionCount].Set_ID(ID);
					PromotionCount++;
					break;
				default:
					break;
				}

				//if (charr == 'F')
				//{
				//	F = charr;
				//	infile >> TYPE >> Formulation_Day >> ID >> Target_Location >> Mision_Duration >> Signature;
				//	// crreate array
				//	//cout << F<< " " << TYP << " " << ED << " " << ID << " " << TLOC << " " << MDUR<< " " << SIG << endl;
				//}
				//else if (charr == 'X')
				//{
				//	X = charr;
				//	infile >> Formulation_Day >> ID;
				//	// crreate array
				//	//cout <<X << " " << ED << " " << ID << endl;
				//}
				//else if (charr == 'P')
				//{
				//	PP = charr;
				//	infile >> Formulation_Day >> ID;
				//	// crreate array
				//	//cout << PP << " " << ED << " " << ID << endl;
				//}


	//		}




		}
		infile.close();


	}



}

/*
void UI :: output(
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
	LinkedQueue<MountainousMission> Completed_Missions_Mountainous)

{
	ofstream outfile("finalresults.txt");
	if (mode == 1)
	{
		cout << "Current Day:" << countDays << endl;

		char input;

		cin >> input;
		if (int(input) == 10) // enter key is pressed
		{
			Display_waitingOfCurrentDay(WaitingEmergency, waitingPolar, waitingMountainous);
		}

		cin >> input;
		if (int(input) == 10) // enter key is pressed
		{
			Display_inExecutionOfCurrentDay(In_ExcutionEmergency, In_ExcutionPolar, In_ExcutionMountainous);
		}

		cin >> input;
		if (int(input) == 10) // enter key is pressed
		{
			Display_AvailableRoversCurrentDay(EmergencyRovers, PolarRovers, MountainousRovers);
		}

		cin >> input;
		if (int(input) == 10) // enter key is pressed
		{
			Display_checkUpRoversCurrentDay(EmergencyCheckup, PolarCheckup, MountainousCheckup);
		}

		cin >> input;
		if (int(input) == 10) // enter key is pressed
		{
			Display_CompletedOfCurrentDay(Completed_Missions_Emergency, Completed_Missions_Polar, Completed_Missions_Mountainous);
		}

	}
	else if (mode == 2)
	{
		
	}
	else if (mode == 3)
	{
		cout << "Silent Mode \nSimulation Starts... \nSimulation ends, Output file created\n";
	}

	// outputFile here

}


void UI :: Display_waitingOfCurrentDay(LinkedPriorityQueue<EmergencyMission> WaitingEmergency, LinkedQueue<PolarMission> waitingPolar, LinkedQueue<MountainousMission>waitingMountainous)
{
	cout << "Waiting Missions: ";
	if (!WaitingEmergency.isEmpty())
	{
		cout << '[';
		while (!WaitingEmergency.isEmpty())
		{
			EmergencyMission popped;
			WaitingEmergency.dequeue(popped);
			cout << popped.Get_ID() << ',';
		}
		cout << ']';
	}

	if (!waitingPolar.isEmpty())
	{
		cout << '(';
			while (!waitingPolar.isEmpty())
			{
				PolarMission popped;
				waitingPolar.dequeue(popped);
				cout << popped.Get_ID() << ',';

			}
		cout << ')';
	}
	if (!waitingMountainous.isEmpty())
	{
		cout << '{';
			while (!waitingMountainous.isEmpty())
			{
				MountainousMission popped;
				waitingMountainous.dequeue(popped);
				cout << popped.Get_ID() << ',';

			}
		cout << '}';
	}
	cout << endl;
}


void UI :: Display_inExecutionOfCurrentDay(LinkedPriorityQueue<EmergencyRover> In_ExcutionEmergency, LinkedPriorityQueue<PolarRover> In_ExcutionPolar, LinkedPriorityQueue<MountainousRover> In_ExcutionMountainous )
{
	cout << "In-Execution Missions/Rovers: ";
	if (!In_ExcutionEmergency.isEmpty())
	{
		cout << '[';
		while (!In_ExcutionEmergency.isEmpty())
		{
			EmergencyRover popped;
			In_ExcutionEmergency.dequeue(popped);
			if (popped.get_EmergencyMission())
				cout << popped.get_EmergencyMission()->Get_ID() << '/';
			else
				cout << popped.get_MountainousMission()->Get_ID() << '/';

			cout << popped.Get_ID() << ',';
		}
		cout << ']';
	}

	if (!In_ExcutionPolar.isEmpty())
	{
		cout << '(';
		while (!In_ExcutionPolar.isEmpty())
		{
			PolarRover popped;
			In_ExcutionPolar.dequeue(popped);
			if (popped.get_EmergencyMission())
				cout << popped.get_EmergencyMission()->Get_ID() << '/';
			else
				cout << popped.get_PolarMission()->Get_ID() << '/';

			cout << popped.Get_ID() << ',';
		}
		cout << ')';
	}

	if (!In_ExcutionMountainous.isEmpty())
	{
		cout << '{';
		while (!In_ExcutionMountainous.isEmpty())
		{
			MountainousRover popped;
			In_ExcutionEmergency.dequeue(popped);
			if (popped.get_EmergencyMission())
				cout << popped.get_EmergencyMission()->Get_ID() << '/';
			else
				cout << popped.get_MountainousMission()->Get_ID() << '/';

			cout << popped.Get_ID() << ',';
		}
		cout << '}';
	}
	cout << endl;
}


void UI :: Display_AvailableRoversCurrentDay(LinkedPriorityQueue<EmergencyRover> EmergencyRovers, LinkedPriorityQueue<PolarRover> PolarRovers, LinkedPriorityQueue<MountainousRover> MountainousRovers)
{
	cout << "Available Rovers: ";
	if (!EmergencyRovers.isEmpty())
	{
		cout << '[';
		while (!EmergencyRovers.isEmpty())
		{
			EmergencyRover popped;
			EmergencyRovers.dequeue(popped);
			cout << popped.Get_ID() << ',';
		}
		cout << ']';
	}

	if (!PolarRovers.isEmpty())
	{
		cout << '(';
		while (!PolarRovers.isEmpty())
		{
			PolarRover popped;
			PolarRovers.dequeue(popped);
			cout << popped.Get_ID() << ',';

		}
		cout << ')';
	}

	if (!MountainousRovers.isEmpty())
	{
		cout << '{';
		while (!MountainousRovers.isEmpty())
		{
			MountainousRover popped;
			MountainousRovers.dequeue(popped);
			cout << popped.Get_ID() << ',';

		}
		cout << '}';
	}
	cout << endl;
}


void UI :: Display_checkUpRoversCurrentDay(LinkedPriorityQueue<EmergencyRover> EmergencyCheckup, LinkedPriorityQueue<PolarRover> PolarCheckup, LinkedPriorityQueue<MountainousRover> MountainousCheckup)
{
	cout << "In-Checkup Rovers: ";
	if (!EmergencyCheckup.isEmpty())
	{
		cout << '[';
		while (!EmergencyCheckup.isEmpty())
		{
			EmergencyRover popped;
			EmergencyCheckup.dequeue(popped);
			cout << popped.Get_ID() << ',';
		}
		cout << ']';
	}

	if (!PolarCheckup.isEmpty())
	{
		cout << '(';
		while (!PolarCheckup.isEmpty())
		{
			PolarRover popped;
			PolarCheckup.dequeue(popped);
			cout << popped.Get_ID() << ',';

		}
		cout << ')';
	}

	if (!MountainousCheckup.isEmpty())
	{
		cout << '{';
		while (!MountainousCheckup.isEmpty())
		{
			MountainousRover popped;
			MountainousCheckup.dequeue(popped);
			cout << popped.Get_ID() << ',';

		}
		cout << '}';
	}

	cout << endl;
}


void UI :: Display_CompletedOfCurrentDay(LinkedQueue<EmergencyMission> Completed_Missions_Emergency, LinkedQueue<PolarMission> Completed_Missions_Polar, LinkedQueue<MountainousMission> Completed_Missions_Mountainous)
{
	cout << "Completed Missions: ";
	if (!Completed_Missions_Emergency.isEmpty())
	{
		cout << '[';
		while (!Completed_Missions_Emergency.isEmpty())
		{
			EmergencyMission popped;
			Completed_Missions_Emergency.dequeue(popped);
			cout << popped.Get_ID() << ',';
		}
		cout << ']';
	}

	if (!Completed_Missions_Polar.isEmpty())
	{
		cout << '(';
		while (!Completed_Missions_Polar.isEmpty())
		{
			PolarMission popped;
			Completed_Missions_Polar.dequeue(popped);
			cout << popped.Get_ID() << ',';

		}
		cout << ')';
	}

	if (!Completed_Missions_Mountainous.isEmpty())
	{
		cout << '{';
		while (!Completed_Missions_Mountainous.isEmpty())
		{
			MountainousMission popped;
			Completed_Missions_Mountainous.dequeue(popped);
			cout << popped.Get_ID() << ',';

		}
		cout << '}';
	}
	cout << endl;
}
*/

UI :: ~UI()
{
	delete[] F_Event_arr;
	delete[] C_Event_arr;
	delete[] P_Event_arr;
}


void UI ::  Set_Mountinous_Num(int MN)
{
	Mountinous_Num = (MN > 0) ? MN : -1;
}


void UI :: Set_Polar_Num(int PN)
{
	Polar_Num = (PN > 0) ? PN : -1;
}


void UI :: Set_Emergency_Num(int EN)
{
	Emergency_Num = (EN > 0) ? EN : -1;
}


void UI :: Set_Mountinous_Speed(double MS)
{
	Mountinous_Speed = (MS > 0) ? MS : -1;
}


void UI :: Set_Polar_Speed(double PS)
{
	Polar_Speed = (PS > 0) ? PS : -1;
}


void  UI :: Set_Emergency_Speed(double ES)
{
	Emergency_Speed = (ES > 0) ? ES : -1;
}


void UI :: Set_Missions_Count(int MC)
{
	Missions_Count = MC > 0 ? MC : -1;
}


void UI :: Set_Mountinous_CheckupDuration(int MCD)
{
	Mountinous_CheckupDuration = (MCD > 0) ? MCD : -1;
}


void UI :: Set_Polar_CheckupDuration(int PCD)
{
	Polar_CheckupDuration = (PCD > 0) ? PCD : -1;
}


void  UI :: Set_Emergency_CheckupDuration(int ECD)
{
	Emergency_CheckupDuration = (ECD > 0) ? ECD : -1;
}


void UI :: Set_Auto_Promotion(int AP)
{
	Auto_Promotion = (AP > 0) ? AP : -1;
}


void UI :: Set_Events_Num(int EN)
{
	Events_Num = (EN > 0) ? EN : -1;
}


void  UI :: Set_TYPE(char T)
{
	mission_type = T;
}


void UI :: Set_FormulationDay(int FD)
{
	Formulation_Day = (FD > 0) ? FD : -1;
}


void UI :: Set_ID(int ID)
{
	ID = (ID > 0) ? ID : -1;
}


void  UI :: Set_Target_Location(int TL)
{
	Target_Location = (TL > 0) ? TL : -1;
}


void UI :: Set_Mision_Duration(int MD)
{
	Mision_Duration = (MD > 0) ? MD : -1;
}


void  UI :: Set_Signature(int S)
{
	Signature = (S > 0) ? S : -1;
}


int UI :: Get_Mountinous_Num()const
{
	return Mountinous_Num;
}


int UI :: Get_Polar_Num()const
{
	return Polar_Num;
}


int UI :: Get_Emergency_Num()const
{
	return Emergency_Num;
}


double UI :: Get_Mountinous_Speed()const
{
	return Mountinous_Speed;
}


double UI :: Get_Polar_Speed()const
{
	return Polar_Speed;
}


double UI :: Get_Emergency_Speed()const
{
	return Emergency_Speed;
}


int UI :: Get_Missions_Count()const
{
	return Missions_Count;
}


int  UI :: Get_Mountinous_CheckupDuration()const
{
	return this->Mountinous_CheckupDuration;
}


int UI :: Get_Polar_CheckupDuration()const
{
	return Polar_CheckupDuration;
}


int UI :: Get_Emergency_CheckupDuration()const
{
	return Emergency_CheckupDuration;
}


int UI :: Get_Auto_Promotion()const
{
	return Auto_Promotion;
}


int  UI :: Get_Events_Num()const
{
	return Events_Num;
}


char UI :: Get_TYPE()const
{
	return mission_type;
}


int UI :: Get_FormulationDay()const
{
	return Formulation_Day;
}


int UI :: Get_ID()const
{
	return ID;

}


int  UI :: Get_Target_Location()const
{
	return Target_Location;
}


int UI :: Get_Mision_Duration()const
{
	return Mision_Duration;
}


int  UI :: Get_Signature() const
{
	return Signature;
}


int UI :: getFormulationCount()
{
	return FormulationCount;
}


int UI :: getCancellationCount()
{
	return CancellationCount;
}


int UI :: getPromotionCount()
{
	return PromotionCount;
}

void UI :: fillEvents(LinkedQueue<FormulationEvent>& F_Events, LinkedQueue<CancellationEvent>& C_Events, LinkedQueue<PromotionEvent>& P_Events)
{
	for (int i = 0; i < FormulationCount; i++)
	{
		F_Events.enqueue(F_Event_arr[i]);
	}
	for (int i = 0; i < CancellationCount; i++)
	{
		C_Events.enqueue(C_Event_arr[i]);
	}
	for (int i = 0; i < PromotionCount; i++)
	{
		P_Events.enqueue(P_Event_arr[i]);
	}

}


void UI::outputmode
(
	int day, int M,
	LinkedPriorityQueue <EmergencyRover> ER,
	LinkedPriorityQueue<MountainousRover> MR,
	LinkedPriorityQueue<PolarRover> PR,
	LinkedPriorityQueue<EmergencyMission> EM,
	LinkedQueue <MountainousMission> MM,
	LinkedQueue<PolarMission> PM,
	LinkedPriorityQueue <EmergencyRover> er,
	LinkedPriorityQueue<MountainousRover> mr,
	LinkedPriorityQueue<PolarRover> pr,
	LinkedPriorityQueue <EmergencyRover> check_er,
	LinkedPriorityQueue<MountainousRover> check_mr,
	LinkedPriorityQueue<PolarRover> check_pr,
	LinkedQueue <EmergencyMission>comp_em,
	LinkedQueue<MountainousMission> comp_mm,
	LinkedQueue <PolarMission> comp_pm,
	int WM, int IM, int AR, int CHR, int CM
)
{
	//LinkedPriorityQueue <T> temp_1;
	//LinkedQueue <T> temp_2;
	EmergencyMission E_M;
	MountainousMission M_M;
	PolarMission P_M;
	EmergencyRover E_R;
	MountainousRover M_R;
	PolarRover P_R;
	char q;

	int delay_inMilliSeconds = 1000; // it means 1 second --> ( look at line No : 1040) (MUSTAFA)


	if (M == 1) //interactive mode or step by step mode
	{
		cout << "current day: " << day << endl;
		cout << WM << " waiting missions : ";
		if (!EM.isEmpty())
		{
			cout << WM << " [ ";
			while (!EM.isEmpty())
			{
				EM.dequeue(E_M);
				cout << E_M.Get_ID();
				if (!EM.isEmpty())                     // Don't print comme befor checking that the list is not empty
					cout << " , ";
			}
			cout << "] ";
		}

		if (!PM.isEmpty())
		{
			cout << " ( ";
			while (!PM.isEmpty())
			{
				PM.dequeue(P_M);
				cout << P_M.Get_ID();
				if (!PM.isEmpty())
					cout << " , ";
			}
			cout << " ) ";
		}

		if (!MM.isEmpty())
		{
			cout << " { ";
			while (!MM.isEmpty())
			{
				MM.dequeue(M_M);
				cout << M_M.Get_ID();
				if (!MM.isEmpty())
					cout << " , ";
			}
			cout << " } " << endl;
			//cout << "--------------------------------------------------------------" << endl;
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(delay_inMilliSeconds));   // wait 1 second, then excute the next line
			if(int(cin.get()) == 10)
		cout << IM << " In_excution Missions /Rovers : ";

		if (!ER.isEmpty())
		{
			cout << " [ ";
			while (!ER.isEmpty())
			{
				ER.dequeue(E_R);
				q = E_R.Get_MissionType();
				if (q == 'E')
					cout << E_R.get_EmergencyMission()->Get_ID() << "/" << E_R.Get_ID();
				else
					cout << E_R.get_MountainousMission()->Get_ID() << "/" << E_R.Get_ID();

				if (!ER.isEmpty())
					cout << " , ";

			}

			cout << " ] ";
		}

		if (!PR.isEmpty())
		{
			cout << " ( ";
			while (!PR.isEmpty())
			{
				PR.dequeue(P_R);
				q = P_R.Get_MissionType();
				if (q == 'E')
					cout << P_R.get_EmergencyMission()->Get_ID() << "/" << P_R.Get_ID();
				else
					cout << P_R.get_PolarMission()->Get_ID() << "/" << P_R.Get_ID();

				if (!PR.isEmpty())
					cout << " , ";

			}

			cout << " ) ";
		}

		if (!MR.isEmpty())
		{
			cout << " { ";
			while (!MR.isEmpty())
			{
				MR.dequeue(M_R);
				q = M_R.Get_MissionType();
				if (q == 'E')
					cout << M_R.get_EmergencyMission()->Get_ID() << "/" << M_R.Get_ID();
				else
					cout << M_R.get_MountainousMission()->Get_ID() << "/" << M_R.Get_ID();

				if (!MR.isEmpty())
					cout << " , ";

			}

			cout << " } ";
			//cout << "--------------------------------------------------------------" << endl;
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(delay_inMilliSeconds));
		if (int(cin.get()) == 10)
			cout << AR << " Avaliable Rovers : ";

		if (!er.isEmpty())
		{
			cout << " [ ";
			while (!er.isEmpty())
			{
				er.dequeue(E_R);
				cout << E_R.Get_ID();
				if (!er.isEmpty())
					cout << " , ";

			}
			cout << " ] ";
		}

		if (!pr.isEmpty())
		{
			cout << " ( ";
			while (!pr.isEmpty())
			{
				pr.dequeue(P_R);
				cout << P_R.Get_ID();
				if (!pr.isEmpty())
					cout << " , ";
				//temp_1.enqueue(P_R);
			}
			cout << " ) ";
		}

		if (!mr.isEmpty())
		{
			cout << " { ";
			while (!mr.isEmpty())
			{
				mr.dequeue(M_R);
				cout << M_R.Get_ID();

				if (!mr.isEmpty())
					cout << " , ";

				//temp_1.enqueue(M_R);
			}
			cout << " } ";
			//cout << "--------------------------------------------------------------" << endl;
		}

		//std::this_thread::sleep_for(std::chrono::milliseconds(delay_inMilliSeconds));
		if (int(cin.get()) == 10)
			cout << CHR << " In_check_up rovers : ";

		if (!check_er.isEmpty())
		{
			cout << " [ ";
			while (!check_er.isEmpty())
			{
				check_er.dequeue(E_R);
				cout << E_R.Get_ID();

				if (!check_er.isEmpty())
					cout << " , ";
				//temp_1.enqueue(E_R);
			}
			cout << "] ";
		}

		if (!check_pr.isEmpty())
		{
			cout << " ( ";
			while (!check_pr.isEmpty())
			{
				check_pr.dequeue(P_R);
				cout << P_R.Get_ID();

				if (!check_pr.isEmpty())
					cout << " , ";
				//temp_1.enqueue(P_R);
			}
			cout << " ) ";
		}

		if (!check_mr.isEmpty())
		{
			while (!check_mr.isEmpty())
			{
				check_mr.dequeue(M_R);
				cout << M_R.Get_ID();

				if (!check_mr.isEmpty())
					cout << " , ";
			}
			cout << " } ";
			//cout << "--------------------------------------------------------------" << endl;
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(delay_inMilliSeconds));
		if (int(cin.get()) == 10)
			cout << CM << " Completed Missions : ";

		if (!comp_em.isEmpty())
		{
			cout << " [ ";
			while (!comp_em.isEmpty())
			{
				comp_em.dequeue(E_M);
				cout << E_M.Get_ID();

				if (!comp_em.isEmpty())
					cout << " , ";
			}
			cout << " ] ";
		}

		if (!comp_pm.isEmpty())
		{
			cout << " ( ";
			while (!comp_pm.isEmpty())
			{
				comp_pm.dequeue(P_M);
				cout << E_M.Get_ID();

				if (!comp_em.isEmpty())
					cout << " , ";
			}
			cout << " ) ";
		}

		if (!comp_mm.isEmpty())
		{
			cout << " { ";
			while (!comp_mm.isEmpty())
			{
				comp_mm.dequeue(M_M);
				cout << M_M.Get_ID();

				if (!comp_mm.isEmpty())
					cout << " , ";
			}
			cout << "}";
		}
		cout << "\n-----------------------------------------------------------------------------------" << endl;
	}
	else if (M == 2)
	{

		cout << "current day: " << day << endl;
		cout << WM << " waiting missions : ";
		if (!EM.isEmpty())
		{
			cout << WM << " [ ";
			while (!EM.isEmpty())
			{
				EM.dequeue(E_M);
				cout << E_M.Get_ID();
				if (!EM.isEmpty())                     // Don't print comme befor checking that the list is not empty
					cout << " , ";
			}
			cout << "] ";
		}

		if (!PM.isEmpty())
		{
			cout << " ( ";
			while (!PM.isEmpty())
			{
				PM.dequeue(P_M);
				cout << P_M.Get_ID();
				if (!PM.isEmpty())
					cout << " , ";
			}
			cout << " ) ";
		}

		if (!MM.isEmpty())
		{
			cout << " { ";
			while (!MM.isEmpty())
			{
				MM.dequeue(M_M);
				cout << M_M.Get_ID();
				if (!MM.isEmpty())
					cout << " , ";
			}
			cout << " } " << endl;
			//cout << "--------------------------------------------------------------" << endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay_inMilliSeconds));   // wait 1 second, then excute the next line
		cout << endl << IM << " In_excution Missions /Rovers : ";

		if (!ER.isEmpty())
		{
			cout << " [ ";
			while (!ER.isEmpty())
			{
				ER.dequeue(E_R);
				q = E_R.Get_MissionType();
				if (q == 'E')
					cout << E_R.get_EmergencyMission()->Get_ID() << "/" << E_R.Get_ID();
				else
					cout << E_R.get_MountainousMission()->Get_ID() << "/" << E_R.Get_ID();

				if (!ER.isEmpty())
					cout << " , ";

			}

			cout << " ] ";
		}

		if (!PR.isEmpty())
		{
			cout << " ( ";
			while (!PR.isEmpty())
			{
				PR.dequeue(P_R);
				q = P_R.Get_MissionType();
				if (q == 'E')
					cout << P_R.get_EmergencyMission()->Get_ID() << "/" << P_R.Get_ID();
				else
					cout << P_R.get_PolarMission()->Get_ID() << "/" << P_R.Get_ID();

				if (!PR.isEmpty())
					cout << " , ";

			}

			cout << " ) ";
		}

		if (!MR.isEmpty())
		{
			cout << " { ";
			while (!MR.isEmpty())
			{
				MR.dequeue(M_R);
				q = M_R.Get_MissionType();
				if (q == 'E')   
					cout << M_R.get_EmergencyMission()->Get_ID() << "/" << M_R.Get_ID();
				else
					cout << M_R.get_MountainousMission()->Get_ID() << "/" << M_R.Get_ID();

				if (!MR.isEmpty())
					cout << " , ";

			}

			cout << " } ";
			//cout << "--------------------------------------------------------------" << endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay_inMilliSeconds));
		cout << endl << AR << " Avaliable Rovers : ";

		if (!er.isEmpty())
		{
			cout << " [ ";
			while (!er.isEmpty())
			{
				er.dequeue(E_R);
				cout << E_R.Get_ID();
				if (!er.isEmpty())
					cout << " , ";

			}
			cout << " ] ";
		}

		if (!pr.isEmpty())
		{
			cout << " ( ";
			while (!pr.isEmpty())
			{
				pr.dequeue(P_R);
				cout << P_R.Get_ID();
				if (!pr.isEmpty())
					cout << " , ";
				//temp_1.enqueue(P_R);
			}
			cout << " ) ";
		}

		if (!mr.isEmpty())
		{
			cout << " { ";
			while (!mr.isEmpty())
			{
				mr.dequeue(M_R);
				cout << M_R.Get_ID();

				if (!mr.isEmpty())
					cout << " , ";

				//temp_1.enqueue(M_R);
			}
			cout << " } ";
			//cout << "--------------------------------------------------------------" << endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(delay_inMilliSeconds));
		cout << endl << CHR << " In_check_up rovers : \n";

		if (!check_er.isEmpty())
		{
			cout << " [ ";
			while (!check_er.isEmpty())
			{
				check_er.dequeue(E_R);
				cout << E_R.Get_ID();

				if (!check_er.isEmpty())
					cout << " , ";
				//temp_1.enqueue(E_R);
			}
			cout << "] ";
		}

		if (!check_pr.isEmpty())
		{
			cout << " ( ";
			while (!check_pr.isEmpty())
			{
				check_pr.dequeue(P_R);
				cout << P_R.Get_ID();

				if (!check_pr.isEmpty())
					cout << " , ";
				//temp_1.enqueue(P_R);
			}
			cout << " ) ";
		}

		if (!check_mr.isEmpty())
		{
			while (!check_mr.isEmpty())
			{
				check_mr.dequeue(M_R);
				cout << M_R.Get_ID();

				if (!check_mr.isEmpty())
					cout << " , ";
			}
			cout << " } " << endl;
			//cout << "--------------------------------------------------------------" << endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay_inMilliSeconds));
		cout << CM << " Completed Missions : ";

		if (!comp_em.isEmpty())
		{
			cout << " [ ";
			while (!comp_em.isEmpty())
			{
				comp_em.dequeue(E_M);
				cout << E_M.Get_ID();

				if (!comp_em.isEmpty())
					cout << " , ";
			}
			cout << " ] ";
		}

		if (!comp_pm.isEmpty())
		{
			cout << " ( ";
			while (!comp_pm.isEmpty())
			{
				comp_pm.dequeue(P_M);
				cout << E_M.Get_ID();

				if (!comp_em.isEmpty())
					cout << " , ";
			}
			cout << " ) ";
		}

		if (!comp_mm.isEmpty())
		{
			cout << " { ";
			while (!comp_mm.isEmpty())
			{
				comp_mm.dequeue(M_M);
				cout << M_M.Get_ID();

				if (!comp_mm.isEmpty())
					cout << " , ";
			}
			cout << "}";
		}
		cout << "\n-----------------------------------------------------------------------------------" << endl;
	}
	else {
		cout << "silent mode" << endl;
		cout << "simulation starts ..." << endl;
		cout << "simulation end , outputfile created" << endl;
	}


}
void UI::printfile(LinkedPriorityQueue<Mission> t1, int T_C_M, int T_E_M, int T_M_M, int T_P_M, int T_M, int T_E_R, int T_M_R, int T_P_R, int T_R, float avg_W, float avg_Ex, float Aut)
{
	LinkedPriorityQueue<Mission> temp;
	int end1 = T_C_M;
	Mission M;

	ofstream outputfile;
	outputfile.open("output.txt");
	outputfile.clear();
	outputfile << "CD  ID  FD  WD  ED  " << endl;

	for (int i = 1; i <= T_C_M; i++)
	{

		for (int j = 1; j <= end1; j++)
		{
			t1.dequeue(M);
			if (j != end1)
				temp.enqueue(M, M.Get_Completion_Days());
		}

		end1--;

		outputfile << M.Get_Completion_Days() << "   " << M.Get_ID() << "   " << M.Get_Formulation_Day() << "   " << M.Get_Waiting_Duration() << "   " << M.Get_Inexecution_Days() << endl;

	//	M = nullptr;
		for (int k = 1; k <= end1; k++)
		{
			temp.dequeue(M);
			t1.enqueue(M, M.Get_Completion_Days());
		}
	}
	outputfile << "Missions: " << T_M << "[M:" << T_M_M << ", P:" << T_P_M << ", E:" << T_E_M << "]" << endl;
	outputfile << "Rovers: " << T_R << "[M:" << T_M_R << ", P:" << T_P_R << ", E:" << T_E_R << "]" << endl;
	outputfile << "Avg Wait = " << avg_W << ", Avg Exec = " << avg_Ex << endl;
	outputfile << "Auto-promoted: " << Aut << "%" << endl;

	outputfile.close();
}
/*

void UI :: fillData(LinkedPriorityQueue<T, T2>& EmergencyMissions, LinkedQueue<T>& PolarMissions, LinkedQueue<T>& MountainousMissions, LinkedQueue<T>& Events)
{

	char type;
	for (int i = 0; i < FormulationCount; i++)
	{
		Events.enqueue(F_Event_arr[i]);
		type = F_Event_arr[i].Get_Mission_Type();
		switch (type)
		{
		case 'E':
			EmergencyMission<T> mission = new EmergencyMission<T>(
				F_Event_arr[i].Get_Formulation_Day(),
				F_Event_arr[i].Get_Mission_Type(),
				F_Event_arr[i].Get_Target_Location(),
				F_Event_arr[i].Get_Mission_Duration,
				F_Event_arr[i].Get_Signature(),
				F_Event_arr[i].Get_ID(),				
																);
			
			EmergencyMissions.enqueue(mission, mission.getPriority());
			break;
		case 'M':
			MountainousMission<T> mission = new MountainousMission<T>(
				F_Event_arr[i].Get_Formulation_Day(),
				F_Event_arr[i].Get_Mission_Type(),
				F_Event_arr[i].Get_Target_Location(),
				F_Event_arr[i].Get_Mission_Duration,
				F_Event_arr[i].Get_Signature(),
				F_Event_arr[i].Get_ID(),
																	);
			MountainousMissions.enqueue(mission);
			break;
		case 'P':
			PolarMission<T> mission = new PolarMission<T>(
				F_Event_arr[i].Get_Formulation_Day(),
				F_Event_arr[i].Get_Mission_Type(),
				F_Event_arr[i].Get_Target_Location(),
				F_Event_arr[i].Get_Mission_Duration,
				F_Event_arr[i].Get_Signature(),
				F_Event_arr[i].Get_ID(),
														);
			PolarMissions.enqueue(mission);
			break;
		default:
			break;
		}
	}

	for (int i = 0; i < CancellationCount; i++)
	{
		type = C_Event_arr[i].Get_ID();
		// dequeue this mission from list of missions --> loop in  events list 
	}

	for (int i = 0; i < PromotionCount; i++)
	{
		type = P_Event_arr[i].Get_ID();
		// dequeue this mission from the list of mountainous missions
		// enqueu it in the list of emergency mission
		
	}
}
*/


