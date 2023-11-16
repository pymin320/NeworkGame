#include "Include.h"
#include "Jelly.h"

class CJellyMgr
{
public:
	CJellyMgr();
	~CJellyMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC hDC);
	void		Release(void);


	list<CJelly*>	Get_Jelly_List() { return m_JellyList; }

	static		CJellyMgr*&		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CJellyMgr;
		}

		return m_pInstance;
	}

	static	void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CJellyMgr*	m_pInstance;
	list<CJelly*>	m_JellyList;
};