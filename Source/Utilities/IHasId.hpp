#ifndef _IHASID_HPP_
    #define _IHASID_HPP_
    
template <typename T>
class IHasId {
public:	

	virtual T Id(void) = 0;
	
}; // end class.
	
#endif _IHASID_HPP_