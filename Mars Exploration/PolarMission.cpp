#include"PolarMission.h"
#include<cmath>

PolarMission ::PolarMission(int fd, char mt, double tl, int md, double sg, int id, int wd)
{
	Set_Formulation_Day(fd);
	Set_Mission_Type(mt);
	Set_Target_Location(tl);
	Set_Mission_Duration(md);
	Set_Signature(sg);
	Set_ID(id);
	Set_Waiting_Duration(wd);
}


void PolarMission ::Set_Formulation_Day(int fd)
{
	Formulation_Day = (fd > 0) ? fd : -1;
}


void PolarMission ::Set_Mission_Type(char mt)
{
	Mission_Type = mt;
}


void PolarMission ::Set_Target_Location(double tl)
{
	Target_Location = (tl > 0) ? tl : -1;
}


void PolarMission ::Set_Mission_Duration(int md)
{
	Mission_Duration = (md > 0) ? md : -1;
}


void PolarMission ::Set_Signature(double sg)
{
	Signature = (sg > 0) ? sg : -1;
}


void PolarMission ::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}


void PolarMission ::Set_Waiting_Duration(int wd)
{
	Waiting_Duration = (wd > 0) ? wd : -1;
}

void PolarMission::Set_Inexecution_Days(int speed)
{
	if (speed > 0)
		Inexecution_Days = ceil(Mission_Duration + ((static_cast<double>(speed) / static_cast<double>(Target_Location)) * 2));
}

int  PolarMission ::Get_Formulation_Day()const
{
	return Formulation_Day;
}


char PolarMission ::Get_Mission_Type()const
{
	return Mission_Type;
}


double PolarMission ::Get_Target_Location()const
{
	return Target_Location;
}


int  PolarMission ::Get_Mission_Duration()const
{
	return Mission_Duration;
}


double PolarMission ::Get_Signature()const
{
	return Signature;
}


int PolarMission ::Get_ID()const
{
	return ID;
}


int PolarMission ::Get_Waiting_Duration()const
{
	return Waiting_Duration;
}


PolarMission ::~PolarMission()
{

}

PolarMission::PolarMission(const PolarMission& obj)
{
	Formulation_Day = obj.Formulation_Day;
	Mission_Type = obj.Mission_Type;
	Target_Location = obj.Target_Location;
	Mission_Duration = obj.Mission_Duration;
	Signature = obj.Signature;
	ID = obj.ID;
	Waiting_Duration = obj.Waiting_Duration;
	MissionsCount = obj.MissionsCount;
	Inexecution_Days = obj.Inexecution_Days;
}

void PolarMission::operator=(const PolarMission& obj)
{
	Formulation_Day = obj.Formulation_Day;
	Mission_Type = obj.Mission_Type;
	Target_Location = obj.Target_Location;
	Mission_Duration = obj.Mission_Duration;
	Signature = obj.Signature;
	ID = obj.ID;
	Waiting_Duration = obj.Waiting_Duration;
	MissionsCount = obj.MissionsCount;
	Inexecution_Days = obj.Inexecution_Days;
}

double PolarMission::Get_Inexecution_Days() const
{
	return Inexecution_Days;
}
double PolarMission::Get_Completion_Days()  const
{
	return (Waiting_Duration + Formulation_Day + Inexecution_Days);
}
