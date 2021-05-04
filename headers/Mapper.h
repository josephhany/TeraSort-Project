#ifndef MAPPER_H
#define MAPPER_H

#include "defines.h"
#include "includes.h"
#include "/home/jhb/Pictures/terasort_project/sources/Partitioner.cpp"

template <class T, typename S>
class Mapper
{
    private:
        S * data;
        T ** dataWrapper;
        T ** sample;
        FILE * input;
        uint8_t phase;
        uint64_t read_start;
        uint64_t read_count;
        uint64_t sample_size;
        std::thread * th;
        Partitioner<T,S> * partitioner;
        void phase1();
        void phase2();
    public:
        Mapper (FILE * f, 
                uint64_t p_start,
                uint64_t p_count,
                uint64_t p_sample_size,
                Partitioner<T,S> * p_partitioner);
        void execute ();
        T * getSample(int index);
        static void start(Mapper<T,S> * me);
        void setThread(std::thread * p_th);
        void waitForRunToFinish();
//        std::thread* spawn(Mapper<T,S> * me);
        ~Mapper ();
};

#endif
