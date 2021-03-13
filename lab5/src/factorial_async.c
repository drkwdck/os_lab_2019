#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>


long result = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


struct FactArgs
{
    int begin;
    int end;
    int mod;
};


int Factorial(const struct FactArgs *args)
{
    int fact = 1;

    for(int i = args->begin; i <= args->end; ++i)
    {

        fact *= i;
        fact %= args->mod;
    }

    pthread_mutex_lock(&mutex);
    result *= fact;
    result %= args->mod;
    pthread_mutex_unlock(&mutex);    
    printf("result %d\n", result);
    return fact;
}


void *ThreadFact(void *args)
{
  struct FactArgs *fact_args = (struct FactArgs*)args;
  return (void *)(size_t)Factorial(fact_args);
}


int main(int argc, char **argv)
{
    int thread_count = -1;
    int mod = -1;
    int k = -1;
    int current_optind = optind ? optind : 1;

    while(true)
    {
        static struct option options[] = {{"pnum", required_argument, 0, 0},
                                        {"mod", required_argument, 0, 0},
                                        {0, 0, 0, 0}};
                    
        int option_index = 0;
        int c = getopt_long(argc, argv, "k:", options, &option_index);

        if (c == -1)
        {
            break;
        }

        switch (c)
        {
            case 0:
                switch (option_index)
                {
                    case 0:
                        thread_count = atoi(optarg);
                        break;
                    case 1:
                        mod = atoi(optarg);
                        break;
                    default:
                        printf("Index %d is out of options\n", option_index);
                }

                break;
            case 'k':
                k = atoi(optarg);

                if(k < 0)
                {
                    printf("k must be positive \n");
                    return 1;
                }

                break;

            case '?':
                break;
            default:
                printf("getopt returned character code 0%o?\n", c);
        }
    }   

    if (optind < argc)
    {
        printf("Has at least one no option argument\n");
        return 1;
    }

    if (mod == -1 || k == -1 || thread_count == -1) 
    {
        printf("Usage: %s -k \"num\" --pnum \"num\" --mod \"num\" \n",
            argv[0]);
        return 1;
    }

    pthread_t threads_array[thread_count];

    int step =  k / thread_count;
    
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    if (step > 2 && thread_count > 1)
    {
        struct FactArgs args[thread_count];

        for (int i = 0; i < thread_count; ++i)
        {
            int begin = step * i + 1;
            int end = thread_count - 1 == i ? k : step * (i + 1);
            args[i].begin = begin;
            args[i].end = end;
            args[i].mod = mod;

            if (pthread_create(&threads_array[i], NULL, ThreadFact, (void *)&args[i]))
            {
                printf("Error: pthread_create failed!\n");
                return 1;
            }
        }

        for (int i = 0; i < thread_count; ++i)
        {
            int part_of_factorial = 0;
            pthread_join(threads_array[i], (void **)&part_of_factorial);
        }
    }
    else
    {
        struct FactArgs args = { .begin = 1, .end = k, .mod = mod };
        Factorial(&args);

    }

    struct timeval finish_time;
    gettimeofday(&finish_time, NULL);

    double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
    elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

    printf("Total: %lld\n", result);
    printf("Elapsed time: %fms\n", elapsed_time);
    return 0;

}