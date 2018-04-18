#ifndef WRAPPER_GEN_RAND
#define WRAPPER_GEN_RAND

unsigned int gen_rand_seed = 1;

void gen_srand(unsigned int a)
{
	gen_rand_seed = a;
}

unsigned int gen_rand()
{
	gen_rand_seed = (1103515245*gen_rand_seed + 12345)%4294967296;
	return gen_rand_seed;
}

#endif
