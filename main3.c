#define __testing
#define MAT_SIZE 100
#include "graffit.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	User* angela = create_user("Angela");
	User* brian = create_user("Brian");
	User* harry = create_user("harry");
	User* messi = create_user("messi");
	User* ronaldo = create_user("ronaldo");
	User* neymar = create_user("neymar");
	User* xavi = create_user("Xavi");
	User* iniesta = create_user("Iniesta");
	User* pele = create_user("Pele");
	add_friend(angela, brian);
	add_friend(angela,messi);
	add_friend(messi, neymar);
	add_friend(brian, harry);
	add_friend(brian, messi);
	add_friend(neymar, harry);
	add_friend(harry, ronaldo);
	add_friend(neymar, xavi);
	add_friend(ronaldo, xavi);
	add_friend(ronaldo, iniesta);
	add_friend(iniesta, pele);
	add_friend(xavi, pele);
	int n = get_degrees_of_connection(angela, pele);
	printf("%d\n", n);
	
	User* angela1 = create_user("Angela1");
	User* brian1 = create_user("Brian1");
	User* harry1 = create_user("harry1");
	User* messi1 = create_user("messi1");
	User* ronaldo1 = create_user("ronaldo1");
	User* neymar1 = create_user("neymar1");
	User* xavi1 = create_user("Xavi1");
	User* iniesta1 = create_user("Iniesta1");
	User* pele1 = create_user("Pele1");
	User* penis1 = create_user("penis1");
	User* penis21 = create_user("penis21");
	User* penis31 = create_user("penis31");
	add_friend(angela1, brian1);
	add_friend(angela1,messi1);
	add_friend(messi1, neymar1);
	add_friend(brian1, harry1);
	add_friend(brian1, messi1);
	add_friend(harry1, ronaldo1);
	add_friend(neymar1, xavi1);
	add_friend(ronaldo1, xavi1);
	add_friend(ronaldo1, iniesta1);
	add_friend(iniesta1, pele1);
	add_friend(harry1, penis21);
	add_friend(iniesta1, penis21);
	add_friend(iniesta1, penis31);
	add_friend(penis21, penis1);
	add_friend(penis31, penis1);
	add_friend(xavi1, pele);
	add_friend(pele1, penis1);
	n = get_degrees_of_connection(angela1, penis1);
	printf("%d\n", n);
}