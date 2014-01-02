#include "AcadCreator.h"

void initApp(); 
void unloadApp();

//void createLine();
//AcDbObjectId createLayer();
void createAcadLine();
void createAcadCircle();

void initApp() 
{ 
    // register a command with the AutoCAD command mechanism 
    acedRegCmds->addCommand(_T("G_commands"), 
                            _T("createline"), 
                            _T("createline"), 
                            ACRX_CMD_TRANSPARENT, 
                            createAcadLine); 

	 acedRegCmds->addCommand(_T("G_commands"), 
                            _T("createcircle"), 
                            _T("createcircle"), 
                            ACRX_CMD_TRANSPARENT, 
                            createAcadCircle); 
	
	
}

void unloadApp() 
{	
    acedRegCmds->removeGroup(_T("G_commands")); 
	acedArxUnload(_T("AcadMain"));
}


void createAcadLine()
{
  double radius = 100;
  double angle = 0.0;
  acedGetReal(_T("\nRadius:"), &radius);
  //spokes from lines
  for(int i = 0 ; i < 100; i++) {
	double two_pi = 2 * PI;
	angle = (i * two_pi / 100);
	double x = radius * cos(angle);
	double y = radius * sin(angle);	
	AcadPoint startPoint(x, y, 0.0);
	angle = ((i+1) * two_pi / 100);
	x = radius * cos(angle);
	y = radius * sin(angle);	
	AcadPoint endPoint(x, y, 0.0);
	AcadLine line(startPoint, endPoint);
	line.draw();
  }  
}

void createAcadCircle() 
{
  AcadPoint center(0.0, 0.0, 0.0);
  AcadCircle circle(center, 50);  
  circle.changeLayer(_T("Circle_Layer"));
  circle.draw();
}


extern "C" AcRx::AppRetCode 
acrxEntryPoint(AcRx::AppMsgCode msg, void* pkt) 
{ 
    switch (msg) 
    { 
        case AcRx::kInitAppMsg: 
            acrxDynamicLinker->unlockApplication(pkt); 
            acrxRegisterAppMDIAware(pkt); 
            initApp(); 
            break; 
        case AcRx::kUnloadAppMsg: 
            unloadApp(); 
            break; 
        default: 
            break; 
    } 
    return AcRx::kRetOK; 
}