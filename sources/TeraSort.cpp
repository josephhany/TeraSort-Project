#ifndef TERASORT_CPP
#define TERASORT_CPP

#include "TeraSort.h"
#include<thread>

template <class T, typename S>
TeraSort<T,S>::TeraSort (char * p_input_file_name,char * p_output_file_name,
                            uint16_t p_mappers, uint16_t p_reducers,uint64_t p_sample_size)
{
    input = fopen (p_input_file_name,"rb");
    output = fopen (p_output_file_name,"wb");
    file_byte_size = 0 ;
    file_record_size = 0 ;
    mappers = p_mappers;
    reducers = p_reducers;
    sample_size = p_sample_size;
    map_engines = NULL;
    partitioner=NULL;
    if ( input != NULL && output != NULL)
    {
    	fseek(input,0,SEEK_END);
    	file_byte_size=ftell(input);
        printf("file byte size: %ld\n",(long)file_byte_size);
    	rewind(input);
    	uint64_t p_partition_expected_size=0;//(file_byte_size/file_record_size)/mappers;
    	partitioner= new Partitioner<T,S> (output,reducers,p_partition_expected_size);
    	file_record_size=sizeof(S);
    	map_engines= new Mapper<T,S>*[mappers];
    	uint64_t p_start= (file_byte_size/file_record_size)/mappers;
    	for(int i=0;i<mappers;i++){
            uint64_t p_count=p_start;//(p_start*(i+1))-(p_start*i);
            if(i==mappers-1){
                p_count=(file_byte_size/file_record_size)-(p_start*i);
            }
           //printf("start: %ld\n",(long)p_start*i);
           //printf("count: %ld\n",(long)p_count);
    		map_engines[i]=new Mapper<T,S> (input,p_start*i, p_count, sample_size,partitioner);
    	}
    	for(int i=0;i<reducers;i++){
    		reduce_engines[i]= new Reducer<T,S>  (partitioner->getPartition(i));
    	}
    }
}

template <class T, typename S>
void TeraSort<T,S>::execute()
{
    printf ("Terasort Start Execute\n");
    for ( uint16_t i = 0 ; i  < mappers; i++)
    {
        std::thread * th = new std::thread(&Mapper<T,S>::start, map_engines[i]);
        map_engines[i]->setThread(th);


    }
	for(uint16_t i=0;i<mappers;i++){
        map_engines[i]->waitForRunToFinish();
    }

    int leap=(sample_size-reducers+1)/(reducers);
    for(uint16_t i=0;i<mappers;i++){
    	for(uint16_t j=0;j<reducers-1;j++){
     	   partitioner->addCutpoint(j,map_engines[i]->getSample(j*(leap+1)+leap));
    	}
    }

    partitioner->calcCutpointsAverage(mappers);
    for ( uint16_t i = 0 ; i  < mappers; i++)
    {
        std::thread * thb = new std::thread(&Mapper<T,S>::start, map_engines[i]);
        map_engines[i]->setThread(thb);
    }
    
    for(uint16_t i=0;i<mappers;i++){
        map_engines[i]->waitForRunToFinish();
    }

    for ( uint16_t i = 0 ; i  < reducers; i++)
    {
        std::thread * tha = new std::thread(&Reducer<T,S>::start, reduce_engines[i]);    
        reduce_engines[i]->setThread(tha);
    }

    for(uint16_t i=0;i<reducers;i++){
        reduce_engines[i]->waitForRunToFinish();
    }
    for ( uint16_t i = 0 ; i  < reducers; i++)
        partitioner->getPartition(i)->dump();

}
template <class T, typename S>
TeraSort<T,S>::~TeraSort()
{
    if ( input != NULL) fclose (input);
    if ( output != NULL) fclose (output);
    if ( map_engines != NULL)
    {
        for ( uint16_t i = 0 ; i  < mappers; i++)
            delete (map_engines[i]);
        free(map_engines);
    }
    if ( partitioner != NULL ) delete(partitioner);
}
template class TeraSort <TeraSortItem,teraitem_r>;
#endif
