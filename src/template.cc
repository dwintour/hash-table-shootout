#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <vector>
using std::vector;

double get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (tv.tv_usec / 1000000.0);
}

char * new_string_from_integer(int num)
{
    int ndigits = num == 0 ? 1 : (int)log10(num) + 1;
    char * str = (char *)malloc(ndigits + 1);
    sprintf(str, "%d", num);
    return str;
}

template <class T> 
void _fill(vector<T> &v)
{
    srand(1);   // for a fair/deterministic comparison 
    for (size_t i = 0, sz = v.size(); i < sz; ++i) 
        v[i] = (T)(i * 10 + rand() % 10);
}

template <class T> 
void _shuffle(vector<T> &v)
{
    for (size_t n = v.size(); n >= 2; --n)
        std::swap(v[n - 1], v[static_cast<unsigned>(rand()) % n]);
}

template <class T, class HT>
double _fill_random(vector<T> &v, HT &hash)
{
    _fill<T>(v);
    _shuffle<T>(v);
    
    double start_time = get_time();

    for (size_t i = 0, sz = v.size(); i < sz; ++i)
        hash.insert(typename HT::value_type(v[i], 0));
    return start_time;
}

template <class T, class HT>
double _lookup(vector<T> &v, HT &hash, size_t &num_present)
{
    _fill_random(v, hash);

    num_present = 0;
    size_t max_val = v.size() * 10;
    double start_time = get_time();

    for (size_t i = 0, sz = v.size(); i < sz; ++i)
    {
        num_present += (size_t)(hash.find(v[i]) != hash.end());
        num_present += (size_t)(hash.find((T)(rand() % max_val)) != hash.end());
    }
    return start_time;
}

template <class T, class HT>
double _delete(vector<T> &v, HT &hash)
{
    _fill_random(v, hash);
    _shuffle(v); // don't delete in insertion order

    double start_time = get_time();

    for(size_t i = 0, sz = v.size(); i < sz; ++i)
        hash.erase(v[i]);
    return start_time;
}


int main(int argc, char ** argv)
{
    int64_t num_keys = atoi(argv[1]);
    int64_t i, value = 0;

    if(argc <= 2)
        return 1;

    SETUP

    srand(1); // for a fair/deterministic comparison 
    double before = get_time();

    try 
    {
        if(!strcmp(argv[2], "sequential"))
        {
            for(i = 0; i < num_keys; i++)
                INSERT_INT_INTO_HASH(i, value);
        }

        else if(!strcmp(argv[2], "random"))
        {
            vector<int64_t> v(num_keys);
            before = _fill_random(v, hash);
        }

        else if(!strcmp(argv[2], "lookup"))
        {
#if 0
            // shows very weird slowdown with Google's sparsehash
            int64_t max_val = num_keys * 2;
            for(i = 0; i < max_val; i+=2)
                INSERT_INT_INTO_HASH(i + (rand() % 2), value);
            srand(1); // for a fair/deterministic comparison
            before = get_time();
            int64_t num_present = 0;
            for(i = 0; i < num_keys; i++)
                num_present += PRESENT((int64_t)(rand() % max_val));
            fprintf(stderr, "found %lu\n", num_present);
#else
            vector<int64_t> v(num_keys);
            size_t num_present;

            before = _lookup(v,  hash, num_present);
            fprintf(stderr, "found %lu\n", num_present);
#endif
        }

        else if(!strcmp(argv[2], "delete"))
        {
            vector<int64_t> v(num_keys);
            before = _delete(v,  hash);
        }

        else if(!strcmp(argv[2], "sequentialstring"))
        {
            for(i = 0; i < num_keys; i++)
                INSERT_STR_INTO_HASH(new_string_from_integer(i), value);
        }

        else if(!strcmp(argv[2], "randomstring"))
        {
            for(i = 0; i < num_keys; i++)
                INSERT_STR_INTO_HASH(new_string_from_integer((int)rand()), value);
        }

        else if(!strcmp(argv[2], "deletestring"))
        {
            for(i = 0; i < num_keys; i++)
                INSERT_STR_INTO_HASH(new_string_from_integer(i), value);
            before = get_time();
            for(i = 0; i < num_keys; i++)
                DELETE_STR_FROM_HASH(new_string_from_integer(i));
        }

        double after = get_time();
        printf("%f\n", after - before);
        fflush(stdout);
        sleep(1000000);
    }
    catch (...)
    {
    }
}
