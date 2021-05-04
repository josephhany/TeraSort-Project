#ifndef QUICKSORT_CPP_
#define QUICKSORT_CPP_

#include "QuickSort.h"

template <class T>
QuickSort<T>::QuickSort(T ** p_teraSortItem)
{
    teraSortItem = p_teraSortItem;
}
template <class T>
int64_t QuickSort<T>::partition( int64_t l, int64_t r) {
	int center =(l+r)/2;
if ( teraSortItem[center] < teraSortItem[l] ) 
std::swap(teraSortItem[l],teraSortItem[center]);
if ( teraSortItem[r] < teraSortItem[l] ) 
std::swap(teraSortItem[l],teraSortItem[r]);
if ( teraSortItem[r] < teraSortItem[center] ) 
std::swap(teraSortItem[center],teraSortItem[r]);
std::swap(teraSortItem[center],teraSortItem[r-1]);
return r-1;
}
template <class T>
void QuickSort<T>::quickSort( int64_t l, int64_t r){
if ( l+50 <= r) {
	T  *pivot = teraSortItem[partition(l,r)];
	//const T & pivot = teraSortItem[partition(l,r)];
int i = l,j=r-1;
for (;;) {
//while (teraSortItem[++i]->getKeyValue() < pivot);
while (teraSortItem[++i]->getKeyValue() < pivot->getKeyValue());
while ( pivot->getKeyValue() < teraSortItem[--j]->getKeyValue());
if ( i < j ) 
std::swap(teraSortItem[i], teraSortItem[j]); 
else break;    
}
std::swap(teraSortItem[i],teraSortItem[r-1]);
quickSort(l,i-1);
quickSort(i+1,r);
}
else{
	int list_size = r-l+1 ;
	if(list_size<=1)
		return;
	for(int i=1;i<list_size;i++){
		T* tmp=teraSortItem[i+l];
		int j=i+l;
		for(  ;j>l&&tmp<teraSortItem[l+j-1] ;j-- )
		teraSortItem[l+j] =teraSortItem[l+j-1];
	teraSortItem[l+j]=tmp;
	}
}
}
template <class T>
QuickSort<T>::~QuickSort()
{
    
}
template class QuickSort <TeraSortItem>;
#endif
