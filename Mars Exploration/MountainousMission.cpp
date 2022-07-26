#include"MountainousMission.h"


MountainousMission::MountainousMission(int fd, char mt, double tl, int md, double sg, int id, int wd)
{
	Set_Formulation_Day(fd);
	Set_Mission_Type(mt);
	Set_Target_Location(tl);
	Set_Mission_Duration(md);
	Set_Signature(sg);
	Set_ID(id);
	Set_Waiting_Duration(wd);
}


void MountainousMission::Set_Formulation_Day(int fd)
{
	Formulation_Day = (fd > 0) ? fd : -1;
}


void MountainousMission::Set_Mission_Type(char mt)
{
	Mission_Type = mt;
}


void MountainousMission::Set_Target_Location(double tl)
{
	Target_Location = (tl > 0) ? tl : -1;
}


void MountainousMission::Set_Mission_Duration(int md)
{
	Mission_Duration = (md > 0) ? md : -1;
}


void MountainousMission::Set_Signature(double sg)
{
	Signature = (sg > 0) ? sg : -1;
}


void MountainousMission::Set_ID(int id)
{
	ID = (id > 0) ? id : -1;
}


void MountainousMission::Set_Waiting_Duration(int wd)
{
	Waiting_Duration = (wd > 0) ? wd : -1;
}


int  MountainousMission::Get_Formulation_Day()
{
	return Formulation_Day;
}


char MountainousMission::Get_Mission_Type()
{
	return Mission_Type;
}


double MountainousMission::Get_Target_Location()
{
	return Target_Location;
}


int  MountainousMission::Get_Mission_Duration()
{
	return Mission_Duration;
}


double MountainousMission::Get_Signature()
{
	return Signature;
}


int MountainousMission::Get_ID()
{
	return ID;
}


int MountainousMission::Get_Waiting_Duration()
{
	return Waiting_Duration;
}


MountainousMission::~MountainousMission()
{

}