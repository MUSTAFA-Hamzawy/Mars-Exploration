#include"EmergencyMission.h"
#include<cmath>

EmergencyMission::EmergencyMission(int fd , char mt , double tl , int md , double sg , int id , int wd )
{
	Set_Formulation_Day(fd);
	Set_Mission_Type(mt);
	Set_Target_Location(tl);
	Set_Mission_Duration(md);
	Set_Signature(sg);
	Set_ID(id);
	Set_Waiting_Duration(wd);
}


void EmergencyMission::Set_Formulation_Day(int fd)
{
	Formulation_Day = (fd > 0) ? fd : -1;
}


void EmergencyMission::Set_Mission_Type(char mt)
{
	Mission_Type = mt;
}


void EmergencyMission::Set_Target_Location(double tl)
{
	Target_Location = (tl > 0) ? tl : -1;
}


void EmergencyMission::Set_Mission_Duration(int md)
{
	Mission_Duration = (md > 0) ? md : -1;
}


void EmergencyMission::Set_Signature(double sg)
{
	Signature = (sg > 0) ? sg : -1;
}


void EmergencyMission::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}


void EmergencyMission::Set_Waiting_Duration(int wd)
{
	Waiting_Duration = (wd > 0) ? wd : -1;
}
 
void EmergencyMission::Set_Inexecution_Days(int speed)
{
	if (speed > 0)                                                   //EXPLAIN YA NADA
		Inexecution_Days = ceil(Mission_Duration + ((static_cast<double>(speed) / static_cast<double>(Target_Location)) * 2));
}

int  EmergencyMission::Get_Formulation_Day()const
{
	return Formulation_Day;
}


char EmergencyMission::Get_Mission_Type()const
{
	return Mission_Type;
}


double EmergencyMission::Get_Target_Location()const
{
	return Target_Location;
}


int  EmergencyMission::Get_Mission_Duration()const
{
	return Mission_Duration;
}


double EmergencyMission::Get_Signature()const
{
	return Signature;
}


int EmergencyMission::Get_ID()const
{
	return ID;
}


int EmergencyMission::Get_Waiting_Duration() const
{
	return Waiting_Duration;
}


EmergencyMission::~EmergencyMission()
{

}

void EmergencyMission::set_AllData(int fd, char mt, double tl, int md, double sg, int id)
{
	Set_Formulation_Day(fd);
	Set_Mission_Type(mt);
	Set_Target_Location(tl);
	Set_Mission_Duration(md);
	Set_Signature(sg);
	Set_ID(id);
}

float EmergencyMission::getPriority()
{
	return Signature / (Formulation_Day * Mission_Duration * Target_Location);
}

EmergencyMission::EmergencyMission(const EmergencyMission& obj)
{
	Formulation_Day = obj.Formulation_Day;
	Mission_Type = obj.Mission_Type;
	Target_Location = obj.Target_Location;
	Mission_Duration = obj.Mission_Duration;
	Signature = obj.Signature;
	ID = obj.ID;
	Waiting_Duration = obj.Waiting_Duration;
	Inexecution_Days = obj.Inexecution_Days;
}

void EmergencyMission::operator=(const EmergencyMission& obj)
{
	Formulation_Day = obj.Formulation_Day;
	Mission_Type = obj.Mission_Type;
	Target_Location = obj.Target_Location;
	Mission_Duration = obj.Mission_Duration;
	Signature = obj.Signature;
	ID = obj.ID;
	Waiting_Duration = obj.Waiting_Duration;
	Inexecution_Days = obj.Inexecution_Days;
}

double EmergencyMission::Get_Inexecution_Days() const
{
	return Inexecution_Days;
}
double EmergencyMission::Get_Completion_Days() const
{
	return (Waiting_Duration + Formulation_Day + Inexecution_Days);
}
