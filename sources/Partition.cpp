#ifndef PARTITION_CPP_
#define PARTITION_CPP_

#include "Partition.h"
#include "QuickSort.h"

template <class T, typename S>
bool Partition<T,S>::resize ()
{
    if ( current == partition_size)
    {
        partition_size += increment;
        data = (S *) realloc (data,partition_size*sizeof(S));
        dataWrapper = (T **) realloc (dataWrapper,partition_size*sizeof(T *));
        memset (((char*) data)+(current*sizeof(S)),0,increment*sizeof(S));
        memset (((char*) dataWrapper)+(current*sizeof(T*)),0,increment*sizeof(T*));
        return true;
    }
    return false;
}
template <class T, typename S>
Partition<T,S>::Partition (FILE * f,uint64_t p_partition_size,uint64_t p_increment)
{
    partition_size = p_partition_size;
    increment = p_increment;
    current = 0;
    output = f;
    data = (S *) calloc (partition_size,sizeof(S));
    dataWrapper = (T **) calloc (partition_size,sizeof(T *));
}
template <class T, typename S>
void Partition<T,S>::addItem(S * s)
{
    mtx.lock();
    /*if(!resize()){
        printf("FAILURE!!!\n");
    }
    else{
        printf("SUCCESS!!\n");
    }*/
    resize();
    memcpy(&data[current],s,sizeof(teraitem_r));
    current++;
    mtx.unlock();
}
template <class T, typename S>
void Partition<T,S>::sort()
{
    for ( uint64_t i = 0  ; i < partition_size ; i ++){
        dataWrapper[i] = new T (&data[i]);
    }
    QuickSort <T> quickSort (dataWrapper);
    quickSort.quickSort(0,current-1);
    //memset(data,0,current);
    for(uint64_t i=0;i<current;i++){
        //printf("keys: %ld\n",(long)dataWrapper[i]->getKeyValue());
        memcpy(&data[i],dataWrapper[i]->getTeraItem(),sizeof(S));
    }
}
template <class T, typename S>
void Partition<T,S>::dump()
{
    //printf("current: %ld\n",(long)current);
    fwrite(data,sizeof(S),current,output);
}
template <class T, typename S>
Partition<T,S>::~Partition ()
{
    if ( data != NULL ) free(data);
    for ( uint64_t i = 0  ; i < partition_size ; i ++) delete (dataWrapper[i]);
    free(dataWrapper);
}
template class Partition <TeraSortItem,teraitem_r>;
#endif