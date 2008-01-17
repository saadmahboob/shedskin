#ifndef __RANDOM_HPP
#define __RANDOM_HPP

#include "builtin.hpp"
#include "math.hpp"
#include "time.hpp"

using namespace __shedskin__;
namespace __random__ {

class Random;
class WichmannHill;

extern class_ *cl_Random;
class Random : public pyobj {
/**
Random number generator base class used by bound module functions.

    Used to instantiate instances of Random to get generators that don't
    share state.  Especially useful for multi-threaded programs, creating
    a different instance of Random for each thread, and using the jumpahead()
    method to ensure that the generated sequences seen by each thread don't
    overlap.

    Class Random can also be subclassed if you want to use a different basic
    generator of your own devising: in that case, override the following
    methods:  random(), seed(), getstate(), setstate() and jumpahead().
*/
public:
    int gauss_switch;
    int VERSION;
    double gauss_next;
    list<int> *mt;
    int mti;

    virtual double random();
    double paretovariate(double alpha);
    int randrange(int start, int stop);
    int randrange(int start, int stop, int step);
    double betavariate(double alpha, double beta);
    double normalvariate(double mu, double sigma);
    double _genrand_res53();
    int seed();
    int seed(int a);
    double weibullvariate(double alpha, double beta);
    Random();
    Random(int a);
    int _init_by_array(list<int> *init_key);
    int randint(int a, int b);
    double vonmisesvariate(double mu, double kappa);
    double gammavariate(double alpha, double beta);
    double uniform(double a, double b);
    double stdgamma(double alpha, double ainv, double bbb, double ccc);
    double expovariate(double lambd);
    int getrandbits(int k);
    virtual int setstate(list<double> *state);
    double lognormvariate(double mu, double sigma);
    int _init_genrand(int s);
    double gauss(double mu, double sigma);
    template <class A> A choice(pyseq<A> *seq);
    template <class A> int shuffle(pyseq<A> *x);
    template <class A> list<A> *sample(pyseq<A> *population, int k);
    int _genrand_int32();
    virtual list<double> *getstate();
    double cunifvariate(double mean, double arc);
};

extern class_ *cl_WichmannHill;
class WichmannHill : public Random {
public:
    tuple2<int, int> *_seed;

    int __whseed(int x, int y, int z);
    double random();
    int seed();
    int seed(int a);
    WichmannHill();
    WichmannHill(int a);
    int whseed();
    int whseed(int a);
    int setstate(list<double> *state);
    int jumpahead(int n);
    list<double> *getstate();
};


extern int  UPPER;
extern double  LOG4;
extern double  SG_MAGICCONST;
extern list<str *> * __all__;
extern int  BPF;
extern Random * _inst;
extern int  MATRIX_A;
extern int  M;
extern int  LOWER;
extern int  N;
extern int  MAXWIDTH;
extern int  MAXINT;
extern str * __name__;
extern double  NV_MAGICCONST;
extern int  MAXBITS;
void __init();
int seed();
int seed(int a);
double random();
list<double> *getstate();
int setstate(list<double> *state);
int randrange(int start, int stop);
int randrange(int start, int stop, int step);
int randint(int a, int b);
template <class A> A choice(pyseq<A> *seq);
template <class A> int shuffle(pyseq<A> *x);
template <class A> list<A> *sample(pyseq<A> *population, int k);
double uniform(double a, double b);
double normalvariate(double mu, double sigma);
double lognormvariate(double mu, double sigma);
double cunifvariate(double mean, double arc);
double expovariate(double lambd);
double vonmisesvariate(double mu, double kappa);
double gammavariate(double alpha, double beta);
double stdgamma(double alpha, double ainv, double bbb, double ccc);
double gauss(double mu, double sigma);
double betavariate(double alpha, double beta);
double paretovariate(double alpha);
double weibullvariate(double alpha, double beta);
int getrandbits(int k);

template <class A> A choice(pyseq<A> *seq) {
    
    return _inst->choice(seq);
}

template <class A> int shuffle(pyseq<A> *x) {
    
    return _inst->shuffle(x);
}

template <class A> list<A> *sample(pyseq<A> *population, int k) {
    
    return _inst->sample(population, k);
}

template <class A> int Random::shuffle(pyseq<A> *x) {
    /**
    x, random=random.random -> shuffle list x in place; return None.
    
            Note that for even rather small len(x), the total number of
            permutations of x is larger than the period of most random number
            generators; this implies that "most" permutations of a long
            sequence can never be generated.
    */
    A __31, __32;
    int __29, __30, i, j;


    FAST_FOR_NEG(i,(len(x)-1),0,-1,29,30)
        j = __int((this->random()*(i+1)));
        __31 = x->__getitem__(j);
        __32 = x->__getitem__(i);
        ELEM((x),i) = __31;
        ELEM((x),j) = __32;
    END_FOR

    return 0;
}


template <class A> list<A> *Random::sample(pyseq<A> *population, int k) {
    /**
    Chooses k unique random elements from a population sequence.
    
            Returns a new list containing elements from the population while
            leaving the original population unchanged.  The resulting list is
            in selection order so that all sub-slices will also be valid random
            samples.  This allows raffle winners (the sample) to be partitioned
            into grand prize and second place winners (the subslices).
    
            Members of the population need not be hashable or unique.  If the
            population contains repeats, then each occurrence is a possible
            selection in the sample.
    */
    str *const_5, *const_6;
    const_5 = new str("sample larger than population");
    const_6 = new str("population to sample has no members");
    A __39;
    dict<int, A> *selected;
    int __33, __34, __37, __38, i, j, n;
    list<A> *pool, *result;

    n = len(population);
    if ((!((0<=k)&&(k<=n)))) {
        throw (new ValueError(const_5));
    }
    if ((n==0)) {
        throw (new ValueError(const_6));
    }
    result = ((new list<A>(1, population->__getitem__(0))))->__mul__(k);
    if ((n<(6*k))) {
        pool = __list(population);

        FAST_FOR(i,0,k,1,33,34)
            j = __int((this->random()*(n-i)));
            ELEM((result),i) = pool->__getfast__(j);
            ELEM((pool),j) = pool->__getfast__(((n-i)-1));
        END_FOR

    }
    else {
        try {
            ((n>0) && __bool((new tuple2<A, A>(3, population->__getitem__(0), population->__getitem__(__floordiv(n, 2)), population->__getitem__((n-1))))));
        } catch (TypeError *) {
            population = __tuple(population);
        } catch (KeyError *) {
            population = __tuple(population);
        }
        selected = (new dict<int, A>());

        FAST_FOR(i,0,k,1,37,38)
            j = __int((this->random()*n));

            while(selected->__contains__(j)) {
                j = __int((this->random()*n));
            }
            __39 = population->__getitem__(j);
            ELEM((result),i) = __39;
            selected->__setitem__(j, __39);
        END_FOR

    }
    return result;
}

template <class A> A Random::choice(pyseq<A> *seq) {
    /**
    Choose a random element from a non-empty sequence.
    */
    
    return seq->__getitem__(__int((this->random()*len(seq))));
}

} // module namespace
#endif
