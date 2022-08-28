#include"Mission.h"

Mission::Mission(int fd , char mt , double tl , int md , double sg , int id , int wd )
{

}

void Mission::Set_Formulation_Day(int fd)
{
	return;
}

void Mission::Set_Mission_Type(char mt)
{
	return;
}

void Mission::Set_Target_Location(double tl)
{
	return;
}

void Mission::Set_Mission_Duration(int md)
{
	return;
}

void Mission::Set_Signature(double sg)
{
	return;
}

void Mission::Set_ID(int id)
{
	return;
}

void Mission::Set_Waiting_Duration(int wd)
{
	return;
}

int Mission::Get_Formulation_Day() const
{
	return -1 ;
}

char Mission::Get_Mission_Type()const
{
	return '-1';
}

double Mission::Get_Target_Location()const
{
	return -1;
}

int Mission::Get_Mission_Duration()const
{
	return -1;
}

double Mission::Get_Signature()const
{
	return -1;
}

int Mission::Get_ID()const
{
	return -1;
}

int Mission::Get_Waiting_Duration()const
{
	return -1;
}
/*
Mission :: ~Mission()
{

}
*/
/////////////////////////////////////////////////////
double Mission::Get_Inexecution_Days()const
{
	return Inexecution_Days;
}
double Mission::Get_Completion_Days() const
{
	return(Waiting_Duration + Formulation_Day + Inexecution_Days);
}
void Mission::Set_Inexecution_Days(int speed)
{
	if (speed > 0)
		Inexecution_Days = Mission_Duration + ((static_cast<double>(speed) / static_cast<double>(Target_Location)) * 2);
}
