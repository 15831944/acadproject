#include<rxregsvc.h>
#include <string.h>
#include <aced.h>
#include <dbents.h>
#include <dbsymtb.h>
#include <dbgroup.h>
#include <dbapserv.h>
#include "tchar.h"

void initApp(); 
void unloadApp();

void createLine();
AcDbObjectId createLayer();

void initApp() 
{ 
    // register a command with the AutoCAD command mechanism 
    acedRegCmds->addCommand(_T("G_commands"), 
                            _T("createline"), 
                            _T("createline"), 
                            ACRX_CMD_TRANSPARENT, 
                            createLine); 
	
}

void unloadApp() 
{	
    acedRegCmds->removeGroup(_T("G_commands")); 
	acedArxUnload(_T("AcadMain"));
}


void createLine()
{
  AcDbObjectId layerId  = createLayer();
  AcGePoint3d startPoint(0.0, 0.0, 0.0);
  AcGePoint3d endPoint(100.0, 100.0, 0.0);
  AcDbLine *acLine = new AcDbLine(startPoint, endPoint);
  AcDbBlockTable *pBlockTable;
  acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pBlockTable, AcDb::kForRead);
  AcDbBlockTableRecord *pBlockTableRecord;
  pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForWrite);
  pBlockTable->close();
  AcDbObjectId pLineId;
  acLine->setLayer(layerId);
  pBlockTableRecord->appendAcDbEntity(pLineId, acLine);
  pBlockTableRecord->close();
  acLine->close();

  ads_name lastEntity;
  ads_entlast(lastEntity);
  struct resbuf *lastResbuf = ads_entget(lastEntity);
  struct resbuf *tempBuf = NULL;
  for(tempBuf = lastResbuf; tempBuf != NULL; tempBuf = tempBuf->rbnext) {
	if(tempBuf->restype == 8) {
	  acutPrintf(_T("Layer:%s"), tempBuf->resval.rstring);
	}
  }

  ads_relrb(lastResbuf);
}

AcDbObjectId createLayer()
{
  AcDbObjectId layerId;
  AcDbLayerTable *layerTable;
  acdbHostApplicationServices()->workingDatabase()->getSymbolTable(layerTable, AcDb::kForWrite);
  AcDbLayerTableRecord *layerTableRecord = new AcDbLayerTableRecord();
  layerTableRecord->setName(_T("Line_Layer"));
  layerTable->add(layerId, layerTableRecord);
  layerTable->close();
  layerTableRecord->close();
  return layerId;
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