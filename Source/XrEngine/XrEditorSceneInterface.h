#pragma once
#include "..\XrCDB\xrCDB.h"
class CObjectSpace;
class ENGINE_API XrEditorSceneInterface
{
public:
	XrEditorSceneInterface();
	virtual ~XrEditorSceneInterface();
	virtual void LoadSpawn(xr_vector<NET_Packet>& Ps) = 0;
	virtual	void LoadCFrom(CObjectSpace*Space, CDB::build_callback)=0;
	virtual struct NodeCompressed*	GetAINodes()=0;
	virtual struct hdrNODES*		GetAIHeader()=0;
	virtual void* GetGraphEdges() = 0;
	virtual void* GetGraphVertex() = 0;
	virtual void* GetGraphHeader() = 0;
	virtual void* GetCrossTableHeader() = 0;
	virtual void* GetCrossTableVertex() = 0;

};