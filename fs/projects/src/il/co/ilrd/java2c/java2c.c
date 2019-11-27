
#include <stddef.h> /* size_t */
#include <stdio.h> 
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy */

/********************************* GLOBALS *******************************/

enum v_funcs {SAY_HELLO, SHOW_COUNTER, GET_NUM_MASTERS, TO_STRING, FINALIZE, NUM_FUNCS};

static int counter = 0;


/********************************* STRUCTS *******************************/

typedef struct Metadata Metadata_t;

struct Metadata
{
	char *name;
	size_t size;
	Metadata_t *super;
	v_func_t (*methods)[];
};

typedef struct Object
{
	Metadata_t *metadata;
} Object_t;

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
	int num_legs;
} Dog_t;

typedef struct Cat
{
	Animal_t super;
	char *colors;
} Cat_t;

typedef void *(*v_func_t)(void *);


typedef struct LegendaryAnimal
{
	Cat_t cat;
} Legendary_t;

/* INIT */
void *InitMetadata(Metadata_t *metadata)
{
	Object_t *obj = (Object_t *)malloc(sizeof(metadata->size));
	obj->metadata = metadata;
	
	return obj;
}


/********************************* METHODS *******************************/

/* ANIMAL METHODS */

void AnimalSayHello(Animal_t *this)
{
	printf("Animal Hello!\n");
	printf("I have %d legs\n",((Animal_t *) this)->num_legs);
}

int AnimalGetNumMasters(Animal_t *this)
{
	return ((Animal_t *) this)->num_masters;
}

void showCounter() {
	printf("counter: %d\n", counter);
}

char *AnimalToString(Animal_t *this)
{
	char *str = (char *)malloc(sizeof(char) * 30);
	strcpy(str, "Animal with ID: ");
	
	sprintf(str, "%d", this->ID);
	
	return str;
}

void AnimalFinalize(Animal_t *this)
{
	printf("finalize Animal with ID: %d\n", this->ID);
	/*this->super->v_*/ /*TODO */
}

/* DOG METHODS */

void DogSayHello(Dog_t *this)
{
	printf("Dog Hello!\n");
	printf("I have %d legs\n", this->num_legs);
}

int DogGetNumMasters(Dog_t *this)
{
	return ((Animal_t *)this->super)->num_masters;
}

char *DogToString(Dog_t *this)
{
	char *str = (char *)malloc(sizeof(char) * 30);
	strcpy(str, "Dog with ID: ");
	
	sprintf(str, "%d", ((Animal_t *)this->super)->ID);
	
	return str;
}

void CatFinalize(Cat_t *this)
{
	printf("finalize Cat with ID: %d\n", ((Animal_t *)this->super)->ID);
	/*this->super->v_*/ /*TODO */
}

/* CAT METHODS */

char *CatToString(Dog_t *this)
{
	char *str = (char *)malloc(sizeof(char) * 30);
	strcpy(str, "Cat with ID: ");
	
	sprintf(str, "%d", ((Animal_t *)this->super)->ID);
	
	return str;
}

void CatFinalize(Cat_t *this)
{
	printf("finalize Cat with ID: %d\n", ((Animal_t *)this->super)->ID);
	/* this->super->v_ */ /*TODO */
}

/* LEGENDARY METHODS */

void LegendarySayHello(Legendary_t *this)
{
	printf("Legendary Hello!\n");
	printf("I have %d legs\n", this->num_legs);
}

void LegendaryFinalize(Legendary_t *this)
{
	printf("finalize LegendaryAnimal with ID: %d\n", ((Animal_t *)this->super)->ID);
	/* this->super->v_ */ /*TODO */
}

/************************* METHODS ARRAYS INIT *******************************/

v_func_t animal_v_funcs[]	 =  { &AnimalSayHello, &showCounter,	&AnimalGetNumMasters,
							 	  &AnimalToString, &AnimalFinalize};
v_func_t dog_v_funcs[]		 = 	{ &DogSayHello,    &showCounter, 	&DogGetNumMasters,
						   	 	  &DogToString,    &DogFinalize};
v_func_t cat_v_funcs[] 		 = 	{ &AnimalSayHello, &showCounter, 	&AnimalGetNumMasters,
						   	   	  &CatToString, &CatFinalize};
v_func_t legendary_v_funcs[] = 	{ &LegendarySayHello, &showCounter, &AnimalGetNumMasters,
						   	  	  &LegendaryToString, &LegendaryFinalize};				 						   	  						   	  
/******************** STATIC BLOCKS INITs *****************************/

void ClassLoadAnimal()
{
	printf("Static block Animal 1\n");
	printf("Instance initialization block Animal\n");
}

void ClassLoadDog()
{
	printf("Static block Dog\n");
}

void ClassLoadCat()
{
	printf("Static block Cat\n");
}

void ClassLoadLegendary()
{
	printf("Static block Legendary Animal\n");
}

/**************************** META INITS *************************************/

Metadata_t animal_meta  = 	{"Animal", sizeof(Animal_t), NULL, animal_v_funcs};
Metadata_t dog_meta  = 		{"Dog", sizeof(Dog_t), animal_meta, dog_v_funcs};
Metadata_t cat_meta  = 		{"Cat", sizeof(Cat_t), animal_meta, cat_v_funcs};
Metadata_t legendary_meta  ={"Legendary", sizeof(Legendary_t), animal_meta,
							 legendary_v_funcs};

/********************************* CONSTRUCTORS *******************************/

void obj_ctor(Object_t *this)
{
	
}


void Animal_default_ctor(Animal_t *this)
{
	obj_ctor((Object_t) this);
	printf("Animal Ctor\n");
	this->ID = ++counter;
	this->methods[SAY_HELLO](this);
	this->methods[SHOW_COUNTER]();
	printf("%s\n", (char *) this->methods[TO_STRING](this));
	printf("%s\n", (char *) this->super->methods[TO_STRING](this));
}

void Animal_nondef_ctor(Animal_t *this, int num_masters)
{
	obj_ctor((Object_t) this);
	printf("Animal Ctor int\n");
	this->ID = ++counter;
	this->num_masters = num_masters;
}

void Dog_default_ctor(Dog_t *this)
{
	
}
