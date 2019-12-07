#include <stdio.h> /* printf, puts, sprintf */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcpy, strcat */

#define UNUSED(x) ((void)(x))
#define ARR_LEN(x) (sizeof(x) / sizeof(x[0]))


typedef void *(*virt_func_t)(void *);

/******************** TYPEDEFS *********************/
typedef struct Metadata Metadata_t;
typedef struct Object Object_t;
typedef struct Animal Animal_t;
typedef struct Dog Dog_t;
typedef struct Cat Cat_t;
typedef struct LegendaryAnimal LegendaryAnimal_t; 

/******************** STRUCTS *****************************/
struct Metadata {
    char *name;
    size_t size;
    virt_func_t *methods;
    Metadata_t *super_meta;
};

struct Object {
    Metadata_t *metadata;
};

int g_animal_counter = 0;

struct Animal {
    Object_t super;
	int ID;
    int num_legs;
	int num_masters;
};

struct Dog {
    Animal_t super;
    int num_legs;
};

struct Cat {
    Animal_t super;
    char *color;
    int num_masters;
};

struct LegendaryAnimal {
    Cat_t super;
};

/******************** Object function forward declarations and virtual table **/
void Object_def_ctor(Object_t *this);
char *ObjectToString(Object_t *this);
void ObjectFinalize(Object_t *this);

virt_func_t object_virt_table[] = {
    (virt_func_t)ObjectToString,
    (virt_func_t)ObjectFinalize
};

/******************** FORWARD DECLARATIONS AND VIRTUAL TABLES *****************/
/* ANIMAL */
void Animal_def_ctor(Animal_t *this);
void AnimalInitBlock(Animal_t *this);
void AnimalStaticInit();
char *AnimalToString(Animal_t *this);
void AnimalFinalize(Animal_t *this);
void AnimalSayHello(Animal_t *this);
void AnimalShowCounter(Animal_t *this);
int AnimalGetNumMasters(Animal_t *this);

virt_func_t animal_virt_table[] = {
    (virt_func_t)AnimalToString,
    (virt_func_t)AnimalFinalize,
    (virt_func_t)AnimalSayHello,
    (virt_func_t)AnimalShowCounter,
    (virt_func_t)AnimalGetNumMasters
};

/* DOG */
void Dog_def_ctor(Dog_t *this);
void DogInitBlock(Dog_t *this);
void DogStaticInit();
char *DogToString(Dog_t *this);
void DogFinalize(Dog_t *this);
void DogSayHello(Dog_t *this);

virt_func_t dog_virt_table[] = {
    (virt_func_t)DogToString,
    (virt_func_t)DogFinalize,
    (virt_func_t)DogSayHello,
    (virt_func_t)AnimalShowCounter,
    (virt_func_t)AnimalGetNumMasters
};

/* CAT */
void Cat_def_ctor(Cat_t *this);
void CatColorCtor(Cat_t *this, char *color);
void CatInitBlock(Cat_t *this);
void CatStaticInit();
char *CatToString(Cat_t *this);
void CatFinalize(Cat_t *this);

virt_func_t cat_virt_table[] = {
    (virt_func_t)CatToString,
    (virt_func_t)CatFinalize,
    (virt_func_t)AnimalSayHello,
    (virt_func_t)AnimalShowCounter,
    (virt_func_t)AnimalGetNumMasters
};

/* LEGENDARY */
void LegendaryAnimal_def_ctor(LegendaryAnimal_t *this);
void LegendaryAnimalStaticInit();
char *LegendaryAnimalToString(LegendaryAnimal_t *this);
void LegendaryAnimalFinalize(LegendaryAnimal_t *this);
void LegendaryAnimalSayHello(LegendaryAnimal_t *this);

virt_func_t legendary_animal_virt_table[] = {
    (virt_func_t)LegendaryAnimalToString,
    (virt_func_t)LegendaryAnimalFinalize,
    (virt_func_t)LegendaryAnimalSayHello,
    (virt_func_t)AnimalShowCounter,
    (virt_func_t)AnimalGetNumMasters
};

enum {TO_STRING, FINALIZE, SAY_HELLO, SHOW_COUNTER, GET_NUM_MASTERS};

/******************** METADATA *****************************************/
Metadata_t object_metadata = { "Object", sizeof(Object_t), (virt_func_t *)object_virt_table, NULL };

Metadata_t animal_metadata = { "Animal", sizeof(Animal_t), (virt_func_t *)animal_virt_table, &object_metadata };

Metadata_t cat_metadata = { "Cat", sizeof(Cat_t), (virt_func_t *)cat_virt_table, &animal_metadata };

Metadata_t dog_metadata = { "Dog", sizeof(Dog_t), (virt_func_t *)dog_virt_table, &animal_metadata };

Metadata_t legendary_animal_metadata = { "Legendary Animal", sizeof(LegendaryAnimal_t), (virt_func_t *)legendary_animal_virt_table, &cat_metadata };

/******************** Init function implementations *************************/
Object_t *Init(Metadata_t *metadata) {
    Object_t *object = (Object_t *)malloc(metadata->size);
    object->metadata = metadata;
    
    return object;
}

/******************** Object function implementations *************************/
void Object_def_ctor(Object_t *object) {
    UNUSED(object);
}

char *ObjectToString(Object_t *this) {
    return this->metadata->name;
}

void ObjectFinalize(Object_t *this) {
    printf("%sFinalize\n", this->metadata->name);
}

/******************** IMPLEMENTATIONS *************************/
void Animal_def_ctor(Animal_t *this) {
    AnimalInitBlock(this);
    puts("Animal Ctor");
    this->ID = ++g_animal_counter;
    this->super.metadata->methods[SAY_HELLO](this);
    this->super.metadata->methods[SHOW_COUNTER](this);
    puts(this->super.metadata->methods[TO_STRING](this));
    puts(ObjectToString(&(this->super)));
}

void Animal_nondef_ctor(Animal_t *this, int num_masters) {
    AnimalInitBlock(this);
    puts("Animal Ctor int");
	this->ID = ++g_animal_counter;
	this->num_masters = num_masters;
}

void AnimalInitBlock(Animal_t *this) {
    puts("Instance initialization block Animal");
    this->num_legs = 5;
    this->num_masters = 1;
}

void AnimalStaticInit() {
    static int is_static_called = 0;
    if (!is_static_called) {
        puts("Static block Animal 1");
        puts("Static block Animal 2");
        is_static_called = 1;
    }
}

void AnimalSayHello(Animal_t *this) {
    puts("Animal Hello!");
    printf("I have %d legs\n", this->num_legs);
}

void AnimalShowCounter(Animal_t *this) {
    UNUSED(this);
    printf("%d\n", g_animal_counter);
}

int AnimalGetNumMasters(Animal_t *this) {
    return this->num_masters;
}

char *AnimalToString(Animal_t *this) {
    const char *to_string = "Animal with ID: ";
    char num[12] = {0};
    size_t malloc_size = sizeof(char) * (strlen(to_string) + ARR_LEN(num));
    char *generated_string = (char *)malloc(malloc_size);

    strcpy(generated_string, to_string);
    sprintf(num, "%d", this->ID);
    strcat(generated_string, num);
    
    return generated_string;
}

void AnimalFinalize(Animal_t *this) {
    printf("finalize Animal with ID: %d\n", this->ID);
    this->super.metadata->super_meta->methods[FINALIZE](this);
}

void Dog_def_ctor(Dog_t *this) {
    Animal_nondef_ctor(&(this->super), 2);
    DogInitBlock(this);
    puts("Dog Ctor");
}

void DogInitBlock(Dog_t *this) {
    puts("Instance initialization block Dog");
    this->num_legs = 4;
}

void DogStaticInit() {
    static int is_static_called = 0;
    if (!is_static_called) {
        AnimalStaticInit();
        puts("Static block Dog");
        is_static_called = 1;
    }
}

void DogSayHello(Dog_t *this) {
    puts("Dog Hello!");
    printf("I have %d legs\n", this->num_legs);
}

char *DogToString(Dog_t *this) {
    const char *to_string = "Dog with ID: ";
    char num[12] = {0};
    size_t malloc_size = sizeof(char) * (strlen(to_string) + ARR_LEN(num));
    char *generated_string = (char *)malloc(malloc_size);

    strcpy(generated_string, to_string);
    sprintf(num, "%d", this->super.ID);
    strcat(generated_string, num);
    
    return generated_string;
}

void DogFinalize(Dog_t *this) {
    printf("finalize Dog with ID: %d\n", this->super.ID);
}

int g_is_cat_ctor_called = 0;

void Cat_def_ctor(Cat_t *this) {
    CatInitBlock(this);
    Animal_def_ctor(&(this->super));

    g_is_cat_ctor_called = 1;
    CatColorCtor(this, "black");
    g_is_cat_ctor_called = 0;
    
    puts("Cat Ctor");
    this->num_masters = 2;
}

void CatColorCtor(Cat_t *this, char *color) {
    if (!g_is_cat_ctor_called) {
        CatInitBlock(this);
        Animal_def_ctor(&(this->super));
    }
    this->color = color;
    printf("Cat Ctor with color: %s\n", this->color);
}

void CatInitBlock(Cat_t *this) {
    this->num_masters = 5;
}

void CatStaticInit() {
    static int is_static_called = 0;

    if (!is_static_called) {
        AnimalStaticInit();
        puts("Static block Cat");
        is_static_called = 1;
    }
}

char *CatToString(Cat_t *this) {
    const char *to_string = "Cat with ID: ";
    char num[12] = {0};
    size_t malloc_size = sizeof(char) * (strlen(to_string) + ARR_LEN(num));
    char *generated_string = (char *)malloc(malloc_size);

    strcpy(generated_string, to_string);
    sprintf(num, "%d", this->super.ID);
    strcat(generated_string, num);
    
    return generated_string;   
}

void CatFinalize(Cat_t *this) {
    printf("finalize Dog with ID: %d\n", this->super.ID);
}

void LegendaryAnimal_def_ctor(LegendaryAnimal_t *this) {
    Cat_def_ctor(&(this->super));
    puts("Legendary Ctor");
}

void LegendaryAnimalSayHello(LegendaryAnimal_t *this) {
    UNUSED(this);
    puts("Legendary Hello!");
}

void LegendaryAnimalStaticInit() {
    static int is_static_called = 0;

    if (!is_static_called) {
        CatStaticInit();
        puts("Static block Legendary Animal");
        is_static_called = 1;
    }
}

char *LegendaryAnimalToString(LegendaryAnimal_t *this) {
    const char *to_string = "LegendaryAnimal with ID: ";
    char num[12] = {0};
    size_t malloc_size = sizeof(char) * (strlen(to_string) + 12);
    char *generated_string = (char *)malloc(malloc_size);

    strcpy(generated_string, to_string);
    sprintf(num, "%d", this->super.super.ID);
    strcat(generated_string, num);
    
    return generated_string;
}

void LegendaryAnimalFinalize(LegendaryAnimal_t *this) {
    printf("finalize LegendaryAnimal with ID: %d\n", this->super.super.ID);
}

/******************** MAIN ****************************************************/
void foo(Animal_t *animal) {
    puts(animal->super.metadata->methods[TO_STRING](animal));
}

int main() {
    size_t i = 0;

    Animal_t *animal = NULL;
    Dog_t *dog = NULL;
    Cat_t *cat = NULL;
    Cat_t *cat_white = NULL;
    LegendaryAnimal_t *la = NULL;

    Animal_t *animals[5] = {NULL};

    AnimalStaticInit();
    animal = (Animal_t *)Init(&animal_metadata);
    Animal_def_ctor(animal);

    DogStaticInit();
    dog = (Dog_t *)Init(&dog_metadata);
    Dog_def_ctor(dog);

    CatStaticInit();
    cat = (Cat_t *)Init(&cat_metadata);
    Cat_def_ctor(cat);

    LegendaryAnimalStaticInit();
    la = (LegendaryAnimal_t *)Init(&legendary_animal_metadata);
    LegendaryAnimal_def_ctor(la);

    AnimalShowCounter(animal);

    printf("%d\n", animal->ID);
    printf("%d\n", ((Animal_t *)dog)->ID);
    printf("%d\n", ((Animal_t *)cat)->ID);
    printf("%d\n", ((Animal_t *)la)->ID);

    dog = (Dog_t *)Init(&dog_metadata);
    Dog_def_ctor(dog);

    cat = (Cat_t *)Init(&cat_metadata);
    Cat_def_ctor(cat);

    cat_white = (Cat_t *)Init(&cat_metadata);
    CatColorCtor(cat_white, "white");

    la = (LegendaryAnimal_t *)Init(&legendary_animal_metadata);
    LegendaryAnimal_def_ctor(la);

    animal = (Animal_t *)Init(&animal_metadata);
    Animal_def_ctor(animal);
    
    animals[0] = ((Animal_t *)dog);
    animals[1] = ((Animal_t *)cat);
    animals[2] = ((Animal_t *)cat_white);
    animals[3] = ((Animal_t *)la);
    animals[4] = animal;

    for (i = 0; i < 5; ++i) {
        animals[i]->super.metadata->methods[SAY_HELLO](animals[i]);
        printf("%d\n", animals[i]->super.metadata->methods[GET_NUM_MASTERS](animals[i]));
    }

    for (i = 0; i < 5; ++i) {
        foo(animals[i]);
    }

    return 0;
}
