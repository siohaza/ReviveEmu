#pragma once

class CInitCriticalSection
{
private:
	LPCRITICAL_SECTION m_pCriticalSection;
public:
	CInitCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
	~CInitCriticalSection();
};

class CEnterCriticalSection
{
private:
	LPCRITICAL_SECTION m_pCriticalSection;
public:
	CEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
	~CEnterCriticalSection();
};
