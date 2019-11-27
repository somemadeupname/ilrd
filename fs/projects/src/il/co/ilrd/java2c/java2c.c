
static int counter = 0;

typedef struct Animal
{
	Object_t object;
	int ID;
	int num_masters;
	int num_legs;
	
} Animal_t;

typedef struct void (*v_func_t)(void *);

typedef struct Metadata {
	char *name;
	size_t size;
	Metadata_t *super;
	v_func_t (*methods)[];
} Metadata_t;
