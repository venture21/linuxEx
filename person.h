#define NAME_MAX 10
#define AGE_MAX 2
#define ID_MAX 10

#define STRING "/home/pi"
#define PROJ_ID 'S'

struct person
{
	long msg_type;
	char name[NAME_MAX];
	int age;
	int id;
};

