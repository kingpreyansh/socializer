#include "graffit.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	User* araka = create_user("Araka");
	User* leana = create_user("Leana");
	User* anika = create_user("Anika");
	User* sina = create_user("Sina");
	
	populate_brand_matrix("brands.txt");

	add_friend(araka,leana);
	add_friend(araka,anika);
	add_friend(anika,sina);
	
	print_user_data(araka); 
	print_user_data(leana); 
	print_user_data(anika); 
	print_user_data(sina);	
	
	int connection = get_degrees_of_connection(araka,sina);
	printf("The connection is %d \n", connection);
	
	populate_brand_matrix("brands.txt");
	follow_brand(araka, "brandonRufino");
	follow_brand(araka, "brandZero");
	print_user_data(araka);
	
	User* sayogana = create_user("Sayogana");
	User* sazuko = create_user("Sazuko");
	add_friend(sina,sayogana);
	
	connection = get_degrees_of_connection(araka,sayogana);
	printf("The connection between sayogana and araka is %d \n", connection);
	
	add_friend(sina,sazuko);
	//add_friend(leana,sazuko);
	connection = get_degrees_of_connection(araka,sazuko);//should stay the same
	printf("The connection is %d \n", connection);
	User* chitane = create_user("Chitane");
	add_friend(sazuko,chitane);
	//add_friend(leana,chitane);
	//add_friend(sina,chitane);
	add_friend(leana,anika);
	add_friend(sayogana,chitane);
	connection = get_degrees_of_connection(araka,chitane);
	printf("The connection between araka and chitane is %d \n", connection);//should see 3
	connection = get_degrees_of_connection(leana,chitane);
	printf("The connection between leana and chitane is %d \n", connection);//should see 3
	
	User* jun = create_user("Jun");
	add_friend(jun,leana);
	int mutuals_jun_araka = get_mutual_friends(jun,araka);
	printf("Jun and Araka has %d mutual friends\n", mutuals_jun_araka);
	
	User* kunonaya = create_user("Kunonaya");
	connection = get_degrees_of_connection(araka,kunonaya);
	printf("The connection is %d \n", connection);
	
	User* kosunawa = create_user("Kosunawa");
	User* padora = create_user("Padora");
	User* heiya = create_user("Heiya");
	User* araka2 = create_user("araka");
	User* padora2 = create_user("penipadora");
	
	follow_brand(padora,"brandonRufino");
	follow_brand(padora, "brandZero");
	follow_brand(chitane,"brandonRufino");
	follow_brand(heiya,"brandonRufino");
	follow_brand(jun,"brandonRufino");
	follow_brand(araka2 ,"brandonRufino");
	follow_brand(padora2 ,"brandonRufino");
	add_suggested_friends(araka,110);
	print_user_data(araka);
	
	add_friend(jun,padora);
	add_friend(araka,padora);
	mutuals_jun_araka = get_mutual_friends(jun,araka);
	printf("Jun and Araka has %d mutual friends\n", mutuals_jun_araka);

	for (int i = 0; i < 49; i++)
		printf("#");
	printf("\n");

	User *a = create_user("A");
	User *b = create_user("B");
	User *c = create_user("C");
	User *d = create_user("D");
	User *e = create_user("E");
	User *f = create_user("F");
	User *g = create_user("G");
	add_friend(a, b);
	add_friend(b, c);
	add_friend(c, d);
	add_friend(d, e);
	add_friend(e, f);
	int a_g = get_degrees_of_connection(a, g);
	printf("(a_g) want: -1, got %d\n", a_g);

	for (int i = 0; i < 49; i++)
		printf("#");
	printf("\n");

	delete_user(a);
	delete_user(b);
	delete_user(c);
	delete_user(d);
	delete_user(e);
	delete_user(f);
	delete_user(g);
	a = create_user("A");
	b = create_user("B");
	c = create_user("C");
	d = create_user("D");
	e = create_user("E");
	f = create_user("F");
	g = create_user("G");
	add_friend(a, b);
	add_friend(a, c);
	add_friend(a, d);
	add_friend(a, e);
	add_friend(a, f);
	add_friend(a, g);
	add_friend(b, c);
	add_friend(b, d);
	add_friend(b, e);
	add_friend(b, f);
	add_friend(b, g);
	add_friend(c, d);
	add_friend(c, e);
	add_friend(c, f);
	add_friend(c, g);
	add_friend(d, e);
	add_friend(d, f);
	add_friend(d, g);
	add_friend(e, f);
	add_friend(e, g);
	add_friend(f, g);
	printf("(a_d) want: 1, got %d, (a_e) want: 1, got %d\n", get_degrees_of_connection(a, d), get_degrees_of_connection(a, e));

	for (int i = 0; i < 49; i++)
		printf("#");
	printf("\n");

	delete_user(a);
	delete_user(b);
	delete_user(c);
	delete_user(d);
	delete_user(e);
	delete_user(f);
	delete_user(g);
	a = create_user("A");
	b = create_user("B");
	c = create_user("C");
	d = create_user("D");
	e = create_user("E");
	f = create_user("F");
	g = create_user("G");
	add_friend(a, b);
	add_friend(b, c);
	add_friend(c, d);
	add_friend(d, e);
	add_friend(e, f);
	add_friend(f, g);
	add_friend(g, a);
	int a_d = get_degrees_of_connection(a, d);
	int a_e = get_degrees_of_connection(a, e);
	printf("(a_d) want: 3, got %d, (a_e) want: 3, got %d\n", a_d, a_e);
}
