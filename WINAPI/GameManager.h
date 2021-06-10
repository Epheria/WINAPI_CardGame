#pragma once
#include<Windows.h>
#include <string>

class GameManager
{
private:

	static GameManager* m_hThis;
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}
	GameManager();
	~GameManager();


};

