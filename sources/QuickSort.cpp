#ifndef QUICKSORT_CPP_
#define QUICKSORT_CPP_

#include "QuickSort.h"
template <class T>
QuickSort<T>::QuickSort(T ** p_teraSortItem)
{
    teraSortItem = p_teraSortItem;
}
template <class T>
void QuickSort<T>::quickSort(int64_t low, int64_t high)
{
	if (low < high){
		int64_t pi = Partition(low, high);
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}

template <class T>
int64_t QuickSort<T>::Partition (int64_t low, int64_t high)
{
	uint128_t pivot = teraSortItem[high]->key();
	int64_t i = (low - 1);
	for (int64_t j = low; j <= high- 1; j++){
		if (teraSortItem[j]->key() <= pivot){
		//if (teraSortItem[j]->getKeyValue() < teraSortItem[high]->getKeyValue()){
		//if (teraSortItem[j] < teraSortItem[high]){
			i++;
			//printf("(%ld , %ld\n)",(long)teraSortItem[i],(long)teraSortItem[j]);
			teraSortItem[j]->swap(teraSortItem[i]);
			//std::swap(teraSortItem[i], teraSortItem[j]);
			//printf("(%ld , %ld\n)",(long)teraSortItem[i],(long)teraSortItem[j]);
		}
	}
	//std::swap(teraSortItem[i+1], teraSortItem[high]);
	teraSortItem[i+1]->swap(teraSortItem[high]);
	return (i + 1);
}
/*
template <class T>
void QuickSort<T>::insertionSort(int64_t l, int64_t n)
{
	for (int64_t i = l + 1; i <= n; i++) 
	{
		uint128_t value = teraSortItem[i]->getKeyValue();
		int64_t j = i;

		while (j > l && teraSortItem[j - 1]->getKeyValue() > value) 
		{
			teraSortItem[j] = teraSortItem[j - 1];/////////////////////
			j--;
		}		
		T *new_t=new T();
		new_t->addToKeyValue(value);
		teraSortItem[j] = new_t; ///////////////////
	}
}

template <class T>
int64_t QuickSort<T>::Partition (int64_t l, int64_t r)
{
	uint128_t pivot = teraSortItem[r]->getKeyValue();
	int64_t pIndex = l;	
	for (int64_t i = l; i < r; i++)
	{
		if (teraSortItem[i]->getKeyValue() <= pivot)
		{
			std::swap(teraSortItem[i], teraSortItem[pIndex]);
			pIndex++;
		}
	}
	std::swap (teraSortItem[pIndex], teraSortItem[r]);
	return pIndex;
}

template <class T>
QuickSort<T>::QuickSort(T ** p_teraSortItem,int64_t l, int64_t r)
{
	teraSortItem = p_teraSortItem;
	if(l < r){
	int64_t pivot = Partition(l, r);
	QuickSort(p_teraSortItem,l, pivot - 1);
	QuickSort(p_teraSortItem,pivot + 1, r);
}
}
template <class T>
void QuickSort<T>::optimizedQuickSort(int64_t l, int64_t r)
{
	while (l < r) 
	{
		if(r - l < 10)
		{
			insertionSort(l, r);
			break;
		}
		else 
		{
			int64_t pivot = Partition(l, r);
			
			if (pivot - l < r - pivot) {
				optimizedQuickSort(l, pivot - 1);
				l = pivot + 1;
			} else {
				optimizedQuickSort(pivot + 1, r);
				r = pivot - 1;
			}
		}
	}	
}*/
/*
template <class T>
QuickSort<T>::QuickSort(T ** p_teraSortItem)
{
    teraSortItem = p_teraSortItem;
}
template <class T>
int64_t QuickSort<T>::partition( int64_t l, int64_t r) {
	int64_t center =(l+r)/2;
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
	InsertionSort (l,r);
}
}
template <class T>
void QuickSort<T>::InsertionSort(int64_t l, int64_t r)
{
	int list_size = r-l ;
	if(list_size<=1)
		return;
	for(int64_t i=l+1;i<r;i++){
		T* tmp=teraSortItem[i];
	int64_t j=i;
	for(;j>l && tmp<teraSortItem[j-1] ;j-- ){
		teraSortItem[j] =teraSortItem[j-1];	
	}
	
	teraSortItem[j]=tmp;
	}
}*/
template <class T>
QuickSort<T>::~QuickSort()
{
    
}
template class QuickSort <TeraSortItem>;
#endif
