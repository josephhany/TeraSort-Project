#ifndef PARTITIONER_CPP_
#define PARTITIONER_CPP_

#include "Partitioner.h"

template <class T, typename S>
Partitioner<T,S>::Partitioner (FILE * f,uint16_t p_partitions_count,uint64_t p_partition_expected_size)
{
    partitions_count = p_partitions_count;
    partitions = (Partition<T,S> **) calloc (partitions_count,sizeof(Partition<T,S> *));
    for ( uint16_t i = 0 ; i < partitions_count ; i++)
        partitions[i] = new Partition <T,S> (f,p_partition_expected_size,100);
    cutpoints = (T **) calloc (partitions_count-1,sizeof(T *));
    for ( uint16_t i = 0 ; i < partitions_count-1 ; i++)
        cutpoints[i] = new T();
}
template <class T, typename S>
void Partitioner<T,S>::addCutpoint(uint16_t index,T * t)
{
    if(index<partitions_count-1){
    cutpoints[index]->addToKeyValue(t->key());
    }
}

template <class T, typename S>
void Partitioner<T,S>::calcCutpointsAverage(uint16_t p_mappers_count)
{
    for(int i=0;i<partitions_count-1;i++){
        cutpoints[i]->keyValueAverage( p_mappers_count);
    }
}

template <class T, typename S>
void Partitioner<T,S>::addItem(T * t)
{
    bool partition_set = false;
    for ( uint16_t i = 0 ; i < partitions_count-1 ; i++)
    {
        if (cutpoints[i]->getKeyValue() > t->key())
        {
            partition_set = true;
            partitions[i]->addItem(t->getTeraItem());
            break;
        }
    }
    if ( !partition_set) partitions[partitions_count-1]->addItem(t->getTeraItem());
    //partitions[0]->addItem(t->getTeraItem());
}

template <class T, typename S>
uint16_t Partitioner<T,S>::getPartitionsCount()
{
    return partitions_count;
}

template <class T, typename S>
Partition<T,S> * Partitioner<T,S>::getPartition (uint16_t index)
{
    if ( index < partitions_count) return partitions[index];
    else return NULL;
}

template <class T, typename S>
Partitioner<T,S>::~Partitioner ()
{
    for ( uint16_t i = 0 ; i < partitions_count ; i++)
        delete(partitions[i]);
    for ( uint16_t i = 0 ; i < partitions_count-1 ; i++)
        delete(cutpoints[i]);
    free(partitions);
    free(cutpoints);
}
template class Partitioner <TeraSortItem,teraitem_r>;
#endif