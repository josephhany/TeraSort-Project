#ifndef MAPPER_CPP
#define MAPPER_CPP

#include "Mapper.h"
#include "QuickSort.h"


template <class T, typename S>
void Mapper<T,S>::phase1()
{
    dataWrapper = (T **) calloc (read_count,sizeof(T *));
    sample = (T **) calloc (sample_size,sizeof(T *));
    for ( uint64_t i = 0  ; i < read_count ; i ++){
        dataWrapper[i] = new T (&data[i]);
    }
    
    for (uint64_t i = 0; i < sample_size; i++)
        sample[i] = dataWrapper[i];

    srand(time(NULL));
    for (uint64_t i=sample_size; i < read_count; i++)
    {
        
        uint64_t random_index = rand() % (i+1);
        if (random_index < sample_size)
        sample[random_index] = dataWrapper[i];
    }

    QuickSort <T> quickSort (sample);
    quickSort.quickSort(0,sample_size-1);
    
}
template <class T, typename S>
T * Mapper<T,S>::getSample(int index){
    return sample[index];

}

template <class T, typename S>
void Mapper<T,S>::phase2()
{
    printf ("Start Shuffling .....\n");
    for ( uint64_t i = 0 ; i  < read_count ; i ++){
        partitioner->addItem(dataWrapper[i]);
    }
    printf ("Finished Shuffling .....\n");
}



template <class T, typename S>
Mapper<T,S>::Mapper (FILE * f, 
                uint64_t p_start,
                uint64_t p_count,
                uint64_t p_sample_size,
                Partitioner<T,S> * p_partitioner)
{
    input = f;
    read_count = p_count;
    read_start = p_start;
    sample_size = p_sample_size;
    dataWrapper = NULL;
    data = (S *) calloc (read_count,sizeof(S));
    fseek(input,read_start*sizeof(S),SEEK_SET);
    uint64_t read_items = fread(data,sizeof(S),read_count,input);
    
    partitioner = p_partitioner;
    phase = PHASE1;
}


template <class T, typename S>
void Mapper<T,S>::execute ()
{
    if ( phase == PHASE1) 
    {
        phase1();
        phase = PHASE2;
    }
    else if(phase == PHASE2) phase2();
}

template <class T, typename S>
void Mapper<T,S>::start (Mapper<T,S> * me)
{
    me->execute();
}

template <class T, typename S>
void Mapper<T,S>::setThread(std::thread * p_th)
{
    th = p_th;
}

template <class T, typename S>
void Mapper<T,S>::waitForRunToFinish()
{
    th->join();
}

template <class T, typename S>
Mapper<T,S>::~Mapper()
{
    if (dataWrapper != NULL)
    {
        for ( uint64_t i = 0  ; i < read_count ; i ++) delete (dataWrapper[i]);
        free(dataWrapper);
    }
    free(data);
    delete(th);
}
template class Mapper <TeraSortItem,teraitem_r>;
#endif
