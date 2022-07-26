#include "UI.h"
#include<iostream>
#include<fstream>
#include<string>
#include"MountainousMission.h"
#include"PolarMission.h"
#include"EmergencyMission.h"
using namespace std;

template<class T>
UI<T>::UI() : MAX_EVENTS_COUNT(100)
{
	F_Event_arr = new FormulationEvent<T>(MAX_EVENTS_COUNT);
	C_Event_arr = new CancellationEvent<T>(MAX_EVENTS_COUNT);
	P_Event_arr = new PromotionEvent<T>(MAX_EVENTS_COUNT);

	FormulationCount = CancellationCount = PromotionCount = 0;
}

template<class T>
void UI <T>::input()
{
	ifstream infile("input.file.txt");
	if (infile.fail())
	{
		cout << "input file does not open";
	}
	else
	{
		char input;
		while (!infile.eof())
		{
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
					F_Event_arr[FormulationCount++].Set_Mission_Type(mission_type);
					F_Event_arr[FormulationCount++].Set_Formulation_Day(Formulation_Day);
					F_Event_arr[FormulationCount++].Set_ID(ID);
					F_Event_arr[FormulationCount++].Set_Target_Location(Target_Location);
					F_Event_arr[FormulationCount++].Set_Mission_Duration(Mision_Duration);
					F_Event_arr[FormulationCount++].Set_Signature(Signature);
					break;
				case 'X':
					infile >> Formulation_Day >> ID;
					C_Event_arr[CancellationCount++].Set_Formulation_Day(Formulation_Day);
					C_Event_arr[CancellationCount++].Set_ID(ID);
					break;
				case 'P':
					infile >> mission_type >> Formulation_Day >> ID;
					P_Event_arr[PromotionCount++].Set_Mission_Type(mission_type);
					P_Event_arr[PromotionCount++].Set_Formulation_Day(Formulation_Day);
					P_Event_arr[PromotionCount++].Set_ID(ID);
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


			}




		}
		infile.close();


	}



}

template<class T>
void UI<T>::output(
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

template<class T>
void UI<T>::Display_waitingOfCurrentDay(LinkedPriorityQueue<EmergencyMission> WaitingEmergency, LinkedQueue<PolarMission> waitingPolar, LinkedQueue<MountainousMission>waitingMountainous)
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

template<class T>
void UI<T>::Display_inExecutionOfCurrentDay(LinkedPriorityQueue<EmergencyRover> In_ExcutionEmergency, LinkedPriorityQueue<PolarRover> In_ExcutionPolar, LinkedPriorityQueue<MountainousRover> In_ExcutionMountainous )
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

template<class T>
void UI<T>::Display_AvailableRoversCurrentDay(LinkedPriorityQueue<EmergencyRover> EmergencyRovers, LinkedPriorityQueue<PolarRover> PolarRovers, LinkedPriorityQueue<MountainousRover> MountainousRovers)
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

template<class T>
void UI<T>::Display_checkUpRoversCurrentDay(LinkedPriorityQueue<EmergencyRover> EmergencyCheckup, LinkedPriorityQueue<PolarRover> PolarCheckup, LinkedPriorityQueue<MountainousRover> MountainousCheckup)
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

template<class T>
void UI<T>::Display_CompletedOfCurrentDay(LinkedQueue<EmergencyMission> Completed_Missions_Emergency, LinkedQueue<PolarMission> Completed_Missions_Polar, LinkedQueue<MountainousMission> Completed_Missions_Mountainous)
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

template<class T>
UI<T>::~UI()
{
	delete F_Event_arr;
	delete C_Event_arr;
	delete P_Event_arr;
}

template<class T>
void UI<T>:: Set_Mountinous_Num(int MN)
{
	Mountinous_Num = (MN > 0) ? MN : -1;
}

template<class T>
void UI<T>::Set_Polar_Num(int PN)
{
	Polar_Num = (PN > 0) ? PN : -1;
}

template<class T>
void UI<T>::Set_Emergency_Num(int EN)
{
	Emergency_Num = (EN > 0) ? EN : -1;
}

template<class T>
void UI<T>::Set_Mountinous_Speed(double MS)
{
	Mountinous_Speed = (MS > 0) ? MS : -1;
}

template<class T>
void UI<T>::Set_Polar_Speed(double PS)
{
	Polar_Speed = (PS > 0) ? PS : -1;
}

template<class T>
void  UI<T>::Set_Emergency_Speed(double ES)
{
	Emergency_Speed = (ES > 0) ? ES : -1;
}

template<class T>
void UI<T>::Set_Missions_Count(int MC)
{
	Missions_Count = MC > 0 ? MC : -1;
}

template<class T>
void UI<T>::Set_Mountinous_CheckupDuration(int MCD)
{
	Mountinous_CheckupDuration = (MCD > 0) ? MCD : -1;
}

template<class T>
void UI<T>::Set_Polar_CheckupDuration(int PCD)
{
	Polar_CheckupDuration = (PCD > 0) ? PCD : -1;
}

template<class T>
void  UI<T>::Set_Emergency_CheckupDuration(int ECD)
{
	Emergency_CheckupDuration = (ECD > 0) ? ECD : -1;
}

template<class T>
void UI<T>::Set_Auto_Promotion(int AP)
{
	Auto_Promotion = (AP > 0) ? AP : -1;
}

template<class T>
void UI<T>::Set_Events_Num(int EN)
{
	Events_Num = (EN > 0) ? EN : -1;
}

template<class T>
void  UI<T>::Set_TYPE(char T)
{
	mission_type = T;
}

template<class T>
void UI<T>::Set_FormulationDay(int FD)
{
	Formulation_Day = (FD > 0) ? FD : -1;
}

template<class T>
void UI<T>::Set_ID(int ID)
{
	ID = (ID > 0) ? ID : -1;
}

template<class T>
void  UI<T>::Set_Target_Location(int TL)
{
	Target_Location = (TL > 0) ? TL : -1;
}

template<class T>
void UI<T>::Set_Mision_Duration(int MD)
{
	Mision_Duration = (MD > 0) ? MD : -1;
}

template<class T>
void  UI<T>::Set_Signature(int S)
{
	Signature = (S > 0) ? S : -1;
}

template<class T>
int UI<T>::Get_Mountinous_Num()const
{
	return Mountinous_Num;
}

template<class T>
int UI<T>::Get_Polar_Num()const
{
	return Polar_Num;
}

template<class T>
int UI<T>::Get_Emergency_Num()const
{
	return Emergency_Num;
}

template<class T>
double UI<T>::Get_Mountinous_Speed()const
{
	return Mountinous_Speed;
}

template<class T>
double UI<T>::Get_Polar_Speed()const
{
	return Polar_Speed;
}

template<class T>
double UI<T>::Get_Emergency_Speed()const
{
	return Emergency_Speed;
}

template<class T>
int UI<T>::Get_Missions_Count()const
{
	return Missions_Count;
}

template<class T>
int  UI<T>::Get_Mountinous_CheckupDuration()const
{
	return Mountinous_CheckupDuration;
}

template<class T>
int UI<T>::Get_Polar_CheckupDuration()const
{
	return Polar_CheckupDuration;
}

template<class T>
int UI<T>::Get_Emergency_CheckupDuration()const
{
	return Emergency_CheckupDuration;
}

template<class T>
int UI<T>::Get_Auto_Promotion()const
{
	return Auto_Promotion;
}

template<class T>
int  UI<T>::Get_Events_Num()const
{
	return Events_Num;
}

template<class T>
char UI<T>::Get_TYPE()const
{
	return mission_type;
}

template<class T>
int UI<T>::Get_FormulationDay()const
{
	return Formulation_Day;
}

template<class T>
int UI<T>::Get_ID()const
{
	return ID;

}

template<class T>
int  UI<T>::Get_Target_Location()const
{
	return Target_Location;
}

template<class T>
int UI<T>::Get_Mision_Duration()const
{
	return Mision_Duration;
}

template<class T>
int  UI<T>::Get_Signature() const
{
	return Signature;
}

template<class T>
int UI<T>::getFormulationCount()
{
	return FormulationCount;
}

template<class T>
int UI<T>::getCancellationCount()
{
	return CancellationCount;
}

template<class T>
int UI<T>::getPromotionCount()
{
	return PromotionCount;
}
template<class T>
void UI<T>::fillEvents(LinkedQueue<FormulationEvent>& F_Events, LinkedQueue<CancellationEvent>& C_Events, LinkedQueue<PromotionEvent>& P_Events)
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
/*
template<class T>
void UI<T>::fillData(LinkedPriorityQueue<T, T2>& EmergencyMissions, LinkedQueue<T>& PolarMissions, LinkedQueue<T>& MountainousMissions, LinkedQueue<T>& Events)
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


