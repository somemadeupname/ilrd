
#include <stddef.h> /* size_t */
#include <stdio.h> 

/********************************* GLOBALS *******************************/

/********************************* METHODS  *******************************/


static int counter = 0;

/** metas **/

Metadata_t *


/********************************* STRUCTS *******************************/

typedef struct Object
{
	Metadata_t *metadata;
}

typedef struct Animal
{
	Object_t super;
	int ID;
	int num_masters;
	int num_legs;
	
} Animal_t;

typedef struct Dog
{
	Animal_t super;
	int num legs;
} Dog_t;

typedef struct Cat
{
	Animal_t super;
	char *colors;
} Dog_t;

typedef void (*v_func_t)(void *);

typedef struct Metadata
{
	char *name;
	size_t size;
	Metadata_t *super;
	v_func_t (*methods)[];
} Metadata_t;

typedef struct LegendaryAnimal
{
	Animal_t animal;
}

/* INIT */
void *InitMetadata(Metadata_t *metadata)
{
	(Object_t *)this = ((Object_t *))malloc(sizeof(metadata->size));
	this->metadata = metadata;
	
	return this;
}

/********************************* CONSTRUCTORS *******************************/

void obj_ctor(Object_t *this)
{
	
}


void Animal_default_ctor(Animal_t *this, )
{
	obj_ctor((Object_t) this);
}

void Animal_ctor(Animal_t *this, int num_masters)
{
	obj_ctor((Object_t) this);
	this->num_masters = num_masters;
}

/********************************* METHODS *******************************/

/* ANIMAL METHODS */

void AnimalSayHello(void *this)
{
	printf("Animal Hello!\n");
	printf("I have %d legs\n",((Animal_t *) this)->num_legs);
}

int AnimalGetNumMasters(void *this)
{
	return ((Animal_t *) this)->num_masters;
}

void showCounter() {
	printf("counter: %d\n", counter);
}

char *AnimalToString(Animal_t *this) {
	char *str = (char *)malloc(sizeof(char) * 30);
	strcpy(str, "Animal with ID: ");
	
	sprintf(str, "%d", this->ID);
	
	return str;
}

/* DOG METHODS */

/* CAT METHODS */

/* LEGENDARY METHODS */


