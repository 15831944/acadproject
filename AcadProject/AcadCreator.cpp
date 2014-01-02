#include "AcadCreator.h"

//AcadShape class
AcadShape::AcadShape()
{
   currentDatabase = acdbHostApplicationServices()->workingDatabase();
}


void AcadShape::changeLayer(ACHAR *layer)
{
  AcDbLayerTable *layerTable;
  currentDatabase->getSymbolTable(layerTable, AcDb::kForWrite);
  if(!layerTable->has(layer)) {
	AcDbLayerTableRecord *layerTableRecord = new AcDbLayerTableRecord;
	layerTableRecord->setName(layer);
	layerTable->add(layerTableRecord);	
	layerTableRecord->close();
  }
  layerTable->close();
  shapeEntity->setLayer(layer);
}

void AcadShape::draw()
{  
  AcDbBlockTable *currentBlockTable;
  currentDatabase->getSymbolTable(currentBlockTable, AcDb::kForRead);
  AcDbBlockTableRecord *currentBlockTableRecord;
  currentBlockTable->getAt(ACDB_MODEL_SPACE, currentBlockTableRecord, AcDb::kForWrite);
  currentBlockTable->close();
  currentBlockTableRecord->appendAcDbEntity(shapeEntity);
  currentBlockTableRecord->close();
  shapeEntity->close();
}





//AcadLine class
AcadLine::AcadLine(AcadPoint startAcadPoint, AcadPoint endAcadPoint)
{
  AcGePoint3d startPoint(startAcadPoint.x, startAcadPoint.y, startAcadPoint.z);
  AcGePoint3d endPoint(endAcadPoint.x, endAcadPoint.y, endAcadPoint.z);
  shapeEntity = new AcDbLine(startPoint, endPoint);
}



//AcadCircle class
AcadCircle::AcadCircle(AcadPoint center, double radius)
{
  AcGePoint3d centerPoint(center.x, center.y, center.z);
  AcGeVector3d normal(0.0, 0.0, 1);
  shapeEntity = new AcDbCircle(centerPoint, normal, radius);
}