#pragma once
#include <malloc.h>

#ifndef DYNARRAY_H
#define DYNARRAY_H
#endif

// CDynArray <type, grow_size = 128> array.
template <class T, size_t GROW_SIZE = 128>
class CDynArray
{
protected:
	unsigned int	*m_aPtr;		// Storage Pointer.
	unsigned int	m_uCount;		// Count of elemts.
	unsigned int	m_uGrow;		// Block count (Block * GROW_SIZE).

public:
	CDynArray(void);
	~CDynArray(void);

private:
	// Check for available array space.
	void			CheckAllocation();
	// Used by inserting an element in the middle of the array.
	void			CheckAllocation(unsigned int uInsertPosition);

public:
	// Copy constructor to fill array.
	CDynArray<T, GROW_SIZE>& operator=( const CDynArray<T, GROW_SIZE> &copy );

	// Array functions.
	unsigned int	Add( T tAddition );
	unsigned int	Insert( T tAddition, unsigned int uInsertPosition );
	unsigned int	Remove( unsigned int uIndex );				// Remove a Index and reorder the index.
	bool			IsValidIndex( unsigned int uIndex );		// Validate a Index number.
	unsigned int	Count() const;								// Will return the count of array.
	void			Clear();									// Clear the complete array.
	unsigned int	Purge(unsigned int uIndex);					// Remove specified element and use delete on it.
	void			PurgeAll();									// Removes all elements and use delete on it.

	// Accessibility.
	const T&		operator[]( int uIndex ) const;
	T&				operator[]( int uIndex );
	T&				LastElement();								// Returns the last element.
	T&				FirstElement();								// Returns the first element.
	void *			GetArrayBuffer();							// Will return pointer to allocated memory.

protected:
	// Copy Constructor for this class.
	CDynArray( CDynArray const& dynarray ) {}
};

template< typename T, size_t GROW_SIZE >
inline CDynArray<T, GROW_SIZE>::CDynArray(void)
{
	// Allocate (1 * GROW_SIZE) to make the array accessible.
	m_aPtr = (unsigned int*)malloc( (sizeof(unsigned int) * GROW_SIZE) );

	// Default values.
	m_uCount = 0;	// 0 Entrys
	m_uGrow = 1;	// Array is GROW_SIZE
}

template< typename T, size_t GROW_SIZE >
inline CDynArray<T, GROW_SIZE>::~CDynArray(void)
{
	// Cleanup.
	free(m_aPtr);
}

template< typename T, size_t GROW_SIZE >
inline CDynArray<T, GROW_SIZE>& CDynArray<T, GROW_SIZE>::operator=( const CDynArray<T, GROW_SIZE> &copy )
{
	unsigned int uCount = copy.Count();

	// Make sure we release the old buffer.
	(*this).Clear();

	// Copy Data.
	for(unsigned int i = 0; i < uCount; i++)
	{
		(*this).Add(copy[i]);
	}

	// Return new data.
	return *this;
}

template< typename T, size_t GROW_SIZE >
inline const T& CDynArray<T, GROW_SIZE>::operator[]( int uIndex ) const
{
	// Only way to prevent the warning.
	const T & tRet = (T)m_aPtr[uIndex];
	// Return element.
	return tRet;
}

template< typename T, size_t GROW_SIZE >
inline T& CDynArray<T, GROW_SIZE>::operator[]( int uIndex )
{
	// Only way to prevent the warning.
	const T& tRet = (T)m_aPtr[uIndex];
	// Return element.
	return (T)tRet;
}

template< typename T, size_t GROW_SIZE >
inline T& CDynArray<T, GROW_SIZE>::LastElement()
{
	// Only way to prevent the warning.
	const T& tRet = (T)m_aPtr[m_uCount];
	// Return last element.
	return (T)tRet;
}

template< typename T, size_t GROW_SIZE >
inline T& CDynArray<T, GROW_SIZE>::FirstElement()
{
	// Only way to prevent the warning.
	const T& tRet = (T)m_aPtr[0];
	// Return first element.
	return (T)tRet;
}

template< typename T, size_t GROW_SIZE >
inline void * CDynArray<T, GROW_SIZE>::GetArrayBuffer()
{
	// This function should be only touched when you know what you do.
	// Its meant to directly modify Data if necessary.
	return (void*)m_aPtr;
}

template< typename T, size_t GROW_SIZE >
inline void CDynArray<T, GROW_SIZE>::CheckAllocation()
{
	if( (m_uCount + 1) > (GROW_SIZE * m_uGrow))
	{
		// We require new available space for the array.
		m_uGrow++;
		m_aPtr = (unsigned int*)realloc( m_aPtr, sizeof(unsigned int) * (m_uGrow * GROW_SIZE) );
	}
	else if( m_uCount < (GROW_SIZE * (m_uGrow - 1)))
	{
		// We have more than (1 * GROW_SIZE) unnecessary space.
		m_uGrow--;
		m_aPtr = (unsigned int*)realloc( m_aPtr, sizeof(unsigned int) * (m_uGrow * GROW_SIZE) );
	}
}

template< typename T, size_t GROW_SIZE >
inline void CDynArray<T, GROW_SIZE>::CheckAllocation(unsigned int uInsertPosition)
{
	// Only used by inserting in the middle of the array.
	if( (uInsertPosition + 1) > (GROW_SIZE * m_uGrow))
	{
		// We require new available space for the array.
		m_uGrow++;
		m_aPtr = (unsigned int*)realloc( m_aPtr, sizeof(unsigned int) * (m_uGrow * GROW_SIZE) );
	}
}

template< typename T, size_t GROW_SIZE >
inline unsigned int CDynArray<T, GROW_SIZE>::Add(T tAddition)
{
	// Check if more space is required to store the new entry.
	CheckAllocation();

	// Insert
	m_aPtr[m_uCount] = (unsigned int)tAddition;
	m_uCount++;

	// Return insert position.
	return m_uCount - 1;
}

template< typename T, size_t GROW_SIZE >
inline unsigned int CDynArray<T, GROW_SIZE>::Insert(T tAddition, unsigned int uInsertPosition)
{
	// We have to check this time if we don't go out of space via Index.
	CheckAllocation(uInsertPosition);

	// Move memory + sizeof(int), we insert it at the given position.
	memmove( &m_aPtr[uInsertPosition + 1], &m_aPtr[uInsertPosition], 
		sizeof(unsigned int) * (m_uCount - uInsertPosition) );

	// Insert
	m_aPtr[uInsertPosition] = (unsigned int)tAddition;
	m_uCount++;

	// Return insert position.
	return uInsertPosition;
}

template< typename T, size_t GROW_SIZE >
inline unsigned int CDynArray<T, GROW_SIZE>::Remove(unsigned int uIndex)
{
	// Move Index down.
	if( (uIndex + 1) < m_uCount )
	{
		// We had to make sure we are not moving the latest down.
		// This would cause going outside our area.
		memmove(
			&m_aPtr[uIndex], 
			&m_aPtr[uIndex + 1],
			sizeof(unsigned int) * (m_uCount - (uIndex - 1))
			);
	}

	// Decrease count.
	m_uCount--;

	// Check if we have too much unnecessary space.
	CheckAllocation();

	// Return new count.
	return m_uCount;
}

template< typename T, size_t GROW_SIZE >
inline void CDynArray<T, GROW_SIZE>::Clear()
{
	// We will keep looping while the Count is 0.
	while(m_uCount > 0)
		Remove(0);
}

template< typename T, size_t GROW_SIZE >
inline unsigned int CDynArray<T, GROW_SIZE>::Purge(unsigned int uIndex)
{
	// NOTE: Only call this if you know that the pointer is still valid.
	delete m_aPtr[uIndex];
	Remove(uIndex);
}

template< typename T, size_t GROW_SIZE >
inline void CDynArray<T, GROW_SIZE>::PurgeAll()
{
	// NOTE: Only call this if you know that the pointer is still valid.

	// We will keep looping while the Count is 0.
	while(m_uCount > 0)
	{
		delete m_aPtr[uIndex]; 
		Remove(0);
	}
}

template< typename T, size_t GROW_SIZE >
inline unsigned int CDynArray<T, GROW_SIZE>::Count() const
{
	// Return the actual count.
	return m_uCount;
}

template< typename T, size_t GROW_SIZE >
inline bool CDynArray<T, GROW_SIZE>::IsValidIndex( unsigned int uIndex )
{
	// This is an easy way to validate an existing/valid index.
	// TODO: Check for valid pointer.
	return (uIndex < 0) && (uIndex > m_uCount);
}