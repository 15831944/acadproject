#include<iostream>
#include<rxregsvc.h>
#include <string.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <dbgroup.h>
#include <dbapserv.h>
#include<math.h>
#include "tchar.h"
using namespace std;

#define PI 3.14159265

//Abstract shape class
class AcadShape
{
  AcDbDatabase* currentDatabase;
protected:
  AcDbEntity *shapeEntity;
public:
  //virtual draw function for acad shapes
  AcadShape();
  void draw();
  void changeLayer(ACHAR *);
};


//Point class
class AcadPoint
{
public:
  double x;
  double y;
  double z;  
  //AcadPoint class
  AcadPoint(double x, double y, double z) : x(x), y(y), z(z)  {}
};

//Line class
class AcadLine : public AcadShape
{

public:
  AcadLine(AcadPoint, AcadPoint);
  //void moveLine(AcadPoint);

};


//Circle class
class AcadCircle : public AcadShape
{

public:
  AcadCircle(AcadPoint, double);

};


