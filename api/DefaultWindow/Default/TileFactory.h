#pragma once
#include "Obj.h"
#include "Tile.h"

class CTileFactory
{
public:
	CTileFactory() {};
	~CTileFactory() {};

	static CObj* Create_Tile(float _fX,float _fY)
	{
		CObj* Obj = new CTile;
		Obj->Initialize();
		Obj->Set_Pos(_fX, _fY);
		return Obj;
	}
};

