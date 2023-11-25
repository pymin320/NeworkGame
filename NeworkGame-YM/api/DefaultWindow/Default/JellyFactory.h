#pragma once
#include "Item.h"
#include "Jelly.h"


class CJellyFactory
{
public:
	CJellyFactory() {};
	~CJellyFactory() {};

public:
	static CObj* Create_Jelly()
	{
		CObj* Temp = new CJelly;
		Temp->Initialize();
		return Temp;
	}
	static CObj* Create_Jelly(float _fX, float _fY)
	{
		CObj* Temp = new CJelly(_fX, _fY);
		Temp->Initialize();
		return Temp;
	}

};