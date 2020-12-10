#ifndef LINKED_LIST_H
#define	LINKED_LIST_H

#include <windows.h>
#include <utility>
#include <memory>

template<typename T = void *>
class CLink_
{

public:

	T  		    m_pData;
				// Data referenced by this link.

	std::unique_ptr<CLink_<T> >	m_pNextLink;
				// Link that follow the current one (NULL for the
				// last link in a list.
};  /* class CLink_ */


template<typename T = void *>
class CLinkedList_
{
	std::unique_ptr<CLink_<T> > m_pFirstLink;
					// First link in the list (NULL when list is empty).

	CLink_<T> *		m_pLastLink = nullptr;
					// Last link in the list (NULL when list is empty).

public:
    template<typename U>
	void Append (U p_pData)
	{
	    if (!m_pLastLink)
	        m_pFirstLink.reset(m_pLastLink = new CLink_<T>);
	    else
	    {
	        m_pLastLink-> m_pNextLink.reset(new CLink_<T>);
	        m_pLastLink = m_pLastLink-> m_pNextLink.get();
	    }
	    
	    m_pLastLink-> m_pData = std::move(p_pData);
	}  /* CLinkedList_ :: Append () */

	T Dequeue ()
	{
	    CLink_<T> *		pOutLink;
	    // Link to be removed.
	    
	    T			    pData;
	    // Data to be returned.
	    
	    if (!m_pFirstLink)
	        return T();
	    
	    pOutLink = m_pFirstLink.get();
	    
	    /*
	     * Remove the link from the list.
	     */
	    pData = std::move(pOutLink-> m_pData);
	    m_pFirstLink.reset(pOutLink-> m_pNextLink.release());
	    if (m_pFirstLink == NULL)
	        m_pLastLink = NULL;
	    
	    return pData;
	}  /* CLinkedList_ :: Dequeue () */

	DWORD Length ()
	{
	    CLink_<T> *	pLink;
	    DWORD		Length = 0;
	    
	    pLink = m_pFirstLink.get();
	    
	    while (pLink)
	    {
	        Length++;
	        pLink = pLink-> m_pNextLink.get();
	    }
	    return Length;
	}  /* CLinkedList_ :: Length () */
};  /* class CLinkedList_ */

#endif // LINKED_LIST
