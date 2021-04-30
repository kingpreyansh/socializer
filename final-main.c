#define __testing
#define MAT_SIZE 4
#include "graffit.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * Questions
 * - Can users have empty string as name?
 *
 */

int main()
{
	printf("Test 1: create_user():\n");

	printf("  Test 1.1 - sanity check: creating a normal user - ");
	User *test1_1 = create_user("jimmyjohn");
	if (!test1_1) {
		printf("Failed\n  Test 1.1: failure to create new user\n");
		return -1;
	} else if (strcmp(test1_1->name, "jimmyjohn")) {
		printf("Failed\n  Test 1.1: name does not match\n");
		printf("  Exp: jimmyjohn  Got: %s\n", test1_1->name);
		return -1;
	} else if (test1_1->brands) {
		printf("Failed\n  Test 1.1: brands isnt null\n");
		return -1;
	} else if (test1_1->friends) {
		printf("Failed\n  Test 1.1: friends isnt null\n");
		return -1;
	} else if (test1_1->visited) {
		printf("Failed\n  Test 1.1: visited isnt false\n");
		return -1;
	} else if (!in_friend_list(allUsers, test1_1)) {
		printf("Failed\n  Test 1.1: not in allUsers\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 1.2 - null string - ");
	User *test1 = create_user(NULL);
	if (test1) {
		printf("Failed\n  Test 1.2: NULL is not a valid username\n");
		return -1;
	} else printf("Passed\n");

	/* CAUTION ABOUT THIS TEST CASE */
	printf("  Test 1.3 - empty string - ");
	test1 = create_user("");
	if (test1) {
		printf("Failed\n  Test 1.3: "" is not a valid username\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 1.4 - already existing user - ");
	User *test1_4 = create_user("willy");
	test1 = create_user("willy");
	if (test1) {
		printf("Failed\n  Test 1.4: not checking existing users\n");
		return -1;
	} else printf("Passed\n");

	printf("Test 1: create_user() passed!\n\n");

	printf("Test 2 - Part 1: delete_user():\n");

	printf("  Test 2.1 - sanity check: deleting a user - ");
	FriendNode *test2_1_f = test1_1->friends;
	BrandNode *test2_1_b = test1_1->brands;
	int res2_1 = delete_user(test1_1);
	if (in_friend_list(allUsers, test1_1)) {
		printf("Failed\n  Test 2.1: did not remove from allUsers\n");
		return -1;
	// } else if (test2_1_b) {
	// 	printf("Failed\n  Test 2.1: brands wasn't deleted\n");
	// 	return -1;
	// } else if (test2_1_f) {
	// 	printf("Failed\n  Test 2.1: friends wasn't deleted\n");
	// 	return -1;
	} else if (res2_1) {
		printf("Failed\n  Test 2.1: did not return properly\n");
		return -1;
	} else printf("Passed\n");
	delete_user(test1_4);
	delete_user(test1);

	printf("  Test 2.2 - deleting null / nonuser - ");
	int res2_2 = delete_user(NULL);
	if (!res2_2){
		printf("Failed\n  Test 2.2: did not return properly\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 2.3 - deleting user not in allUsers - TODO\n");

	printf("Test 2 - Part 1 passed!\n\n");

	printf("Test 3: add_friend():\n");

	printf("  Test 3.1 - sanity check: adding friends - ");
	User *test3_richard = create_user("richard");
	User *test3_johnny = create_user("johnny");
	int res3_1 = add_friend(test3_richard, test3_johnny);
	if (!in_friend_list(test3_richard->friends, test3_johnny) ||
	    !in_friend_list(test3_johnny->friends, test3_richard)) {
		printf("Failed\n  Test 3.1: connection not established\n");
		return -1;
	} else if (res3_1) {
		printf("Failed\n  Test 3.1: bad return value\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 3.2 - adding existing friends - ");
	int res3_2 = add_friend(test3_richard, test3_johnny);
	if (!in_friend_list(test3_richard->friends, test3_johnny) ||
	    !in_friend_list(test3_johnny->friends, test3_richard)) {
		printf("Failed\n  Test 3.2: connection was screwed up\n");
		return -1;
	} else if (!res3_2) {
		/* CAUTION ABOUT THIS TEST CASE */
		printf("Failed\n  Test 3.2: bad return value\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 3.3 - when the friendship is... complicated - ");
	test3_johnny->friends = delete_from_friend_list(test3_johnny->friends, test3_richard);
	int res3_3 = add_friend(test3_johnny, test3_richard);
	if (!res3_3) {
		/* CAUTION ABOUT THIS TEST CASE */
		printf("Failed (maybe...)\n trying to repair friendship?\n");
		return -1;
	} else if (in_friend_list(test3_johnny->friends, test3_richard)) {
		printf("Failed (maybe...)\n trying to repair friendship?\n");
		return -1;
	} else printf("Passed (CAUTION)\n");

	printf("  Test 3.4 - lol you can't have imaginary friends - ");
	int res3_4 = add_friend(test3_johnny, NULL);
	if (!res3_4) {
		printf("Failed\n Imaginary friends aren't a thing\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 3.5 - you can't be friends with the shadow people - ");
	int res3_5 = add_friend(NULL, test3_johnny);
	if (!res3_5) {
		printf("Failed\n you can't befriend the shadow people\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 3.6 - Adding a friend that isn't in allUsers - ");
	User *test3_6 = (User*) calloc(1, sizeof(User));
	int res3_6 = add_friend(test3_johnny, test3_6);
	if (!res3_6) {
		printf("Failed\n  Tried to add user that is not in allUsers\n");
		return -1;
	} else printf("Passed\n");
	free(test3_6);

	printf("  Test 3.7 - lonelyyyy I am so lonelyyyy I have nobodyyy - ");
	int res3_7 = add_friend(test3_johnny, test3_johnny);
	if (!res3_6) {
		printf("Failed\n  Are you ok? You can't be your own friend\n");
		return -1;
	} else if (in_friend_list(test3_johnny->friends, test3_johnny)) {
		printf("Failed\n  You're trying to friend yourself still...\n");
		return -1;
	} else printf("Passed\n");

	delete_user(test3_richard);
	delete_user(test3_johnny);

	printf("Test 3: add_friend() passed!\n\n");

	/*
	 * - when the friendship is... complicated pt. 2
	 */

	printf("Test 4: remove_friend():\n");

	printf("  Test 4.1 - sanity check: removing friends - ");
	User *test4_donald = create_user("donald");
	User *test4_dong = create_user("dong");
	add_friend(test4_donald, test4_dong);
	int res4_1 = remove_friend(test4_dong, test4_donald);
	if (in_friend_list(test4_donald->friends, test4_dong) ||
	    in_friend_list(test4_dong->friends, test4_donald)) {
		printf("Failed\n  Test 4.1: connection not severed\n");
		return -1;
	} else if (res4_1) {
		printf("Failed\n  Test 4.1: bad return value: %d\n", res4_1);
		return -1;
	} else printf("Passed\n");

	printf("  Test 4.2 - not friends - ");
	int res4_2 = remove_friend(test4_donald, test4_dong);
	if (in_friend_list(test4_donald->friends, test4_dong) ||
	    in_friend_list(test4_dong->friends, test4_donald)) {
		printf("Failed\n  Test 4.2: connection was screwed up\n");
		return -1;
	} else if (!res4_2) {
		printf("Failed\n  Test 4.2: bad return value\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 4.3 - unfriending the shadow people - ");
	int res4_3 = remove_friend(test4_donald, NULL);
	if (!res4_3) {
		printf("Failed\n  Test 4.3: you can't unfriend nothing\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 4.4 - getting unfriended by the shadow people - ");
	int res4_4 = remove_friend(NULL, test4_dong);
	if (!res4_4) {
		printf("Failed\n  Test 4.4: NULL can't have friends anyways\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 4.5 - self loathing - ");
	int res4_5 = remove_friend(test4_dong, test4_dong);
	if (!res4_5) {
		printf("Failed\n  Test 4.5: you can't unfriend yourself...\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 4.6 - when the friendship is... complicated pt. 2 - ");
	add_friend(test4_dong, test4_donald);
	test4_donald->friends = delete_from_friend_list(test4_donald->friends,
							test4_dong);
	int res4_6 = remove_friend(test4_dong, test4_dong);
	if (!in_friend_list(test4_dong->friends, test4_donald)) {
		printf("Failed\n  Test 4.6: tried to end friendship further\n");
		return -1;
	} else if (!res4_6) {
		printf("Failed\n  Test 4.6: returning wrong result\n");
		return -1;
	} else printf("Passed\n");

	printf("  Test 4.7 - unfriending someone not in allUsers - ");
	User *test4_7 = (User*) malloc(sizeof(User));
	int res4_7 = remove_friend(test4_dong, test4_7);
	if (!res4_7) {
		printf("Failed\n  Test 4.7: handling user not in allUsers\n");
		return -1;
	} else printf("Passed\n");
	free(test4_7);

	delete_user(test4_dong);
	delete_user(test4_donald);

	printf("Test 4: remove_friend() passed!\n\n");

	populate_brand_matrix("sushi_brandz.txt");

	printf("Test 5: follow_brand():\n");
	printf("  Test 5.1 - NULL trying to follow a brand - ");
	int test5_1 = follow_brand(NULL, "A");
	if (test5_1 != -1){
		printf("Failed\n  Test 5.1: NULL trying to follow brand\n");
		return -1;
	} else printf("Passed\n");
	
	printf("  Test 5.2 - Valid user trying to follow NULL - ");
	User *user5_2 = create_user("A");
	int test5_2 = follow_brand(user5_2, NULL);
	if (test5_2 != -1){
		printf("Failed\n  Test 5.2: User trying to follow NULL\n");
		return -1;
	} else printf("Passed\n");
	delete_user(user5_2);
	
	printf("  Test 5.3 - Valid user trying to follow brand not in matrix - ");
	User *user5_3 = create_user("A");
	int test5_3 = follow_brand(user5_3, "E");
	if (test5_3 != -1){
		printf("Failed\n  Test 5.3: User trying to follow 2.718281828...\n");
		return -1;
	} else printf("  Passed (and hopefully this is properly indented)!\n");
	delete_user(user5_3);
	
	printf("  Test 5.4 - Valid user trying to follow brand\n  they're already following (also a sanity check) - ");
	User *user5_4 = create_user("A");
	int a5_4 = follow_brand(user5_4, "A");
	int b5_4 = follow_brand(user5_4, "A");
	if (a5_4 != 0){
		printf("Failed\n  Test 5.4: User did not follow brand A\n");
		return -1;
	}else if (b5_4 != -1){
		printf("Failed\n  Test 5.4: User trying to follow brand A again\n");
		return -1;
	} else printf("Passed\n");
	delete_user(user5_4);
	
	printf("  Test 5.5 - Invalid user trying to follow valid brand - ");
	User *user5_5 = calloc(1, sizeof(User));
	int a5_5 = follow_brand(user5_5, "A");
	if (a5_5 != -1){
		printf("Failed (maybe)\n  Test 5.5: User followed brand\n");
		return -1;
	} else printf("Passed\n");
	free(user5_5);
	
	printf("Test 5: follow_brand() passed!\n\n");
	
	//TODO
	//test 1: user == NULL
	//test 2: user not in all user
	//invalid brand?
	
	
	printf("Test 6: unfollow_brand():\n");
	printf("  Test 6.1 - NULL trying to unfollow a brand - ");
	int test6_1 = unfollow_brand(NULL, "A");
	if (test6_1 != -1){
		printf("Failed\n  Test 6.1: NULL trying to unfollow brand\n");
		return -1;
	} else printf("Passed\n");
	
	printf("  Test 6.2 - Valid user trying to follow NULL - ");
	User *user6_2 = create_user("A");
	int test6_2 = unfollow_brand(user6_2, NULL);
	if (test6_2 != -1){
		printf("Failed\n  Test 6.2: User trying to unfollow NULL\n");
		return -1;
	} else printf("Passed\n");
	delete_user(user6_2);
	
	printf("  Test 6.3 - Valid user trying to unfollow brand not in matrix - ");
	User *user6_3 = create_user("A");
	int test6_3 = unfollow_brand(user5_3, "E");
	if (test6_3 != -1){
		printf("Failed\n  Test 6.3: User trying to follow 2.718281828...\n");
		return -1;
	} else printf("Passed\n");
	delete_user(user6_3);
	
	printf("  Test 6.4 - Valid user trying to unfollow brand\n  they've already unfollowed (also a sanity check) - ");
	User *user6_4 = create_user("A");
	int a6_4 = follow_brand(user6_4, "A");
	int b6_4 = unfollow_brand(user6_4, "A");
	int c6_4 = unfollow_brand(user6_4, "A");
	if (a6_4 != 0){
		printf("Failed\n  Test 6.4: User did not follow brand A to begin with\n");
		return -1;
	}else if (b6_4 != 0){
		printf("Failed\n  Test 6.4: User did not unfollow brand A\n");
		return -1;
	}else if (c6_4 != -1){
		printf("Failed\n  Test 6.4: User trying to unfollow brand A again\n");
		return -1;
	} else printf("Passed\n");
	delete_user(user6_4);
	
	
	printf("  Test 6.5 - Invalid user trying to unfollow valid brand - ");
	User *user6_5 = calloc(1, sizeof(User));
	int a6_5 = follow_brand(user6_5, "A");
	int b6_5 = unfollow_brand(user6_5, "A");
	if (a6_5 != -1){
		printf("Failed \n  Test 6.5: User followed brand\n");
		return -1;
	} else if (b6_5 != -1){
		printf("Failed \n  Test 6.5: User unfollowed brand\n");
		return -1;
	} else printf("Passed\n");
	free(user6_5);
	
	
	
	printf("Test 6: unfollow_brand() passed!\n\n");
	
	//TODO
	//test 1: user == NULL
	//test 2: user not in all user


	printf("Test 7: get_mutual_friends():\n");
	printf("  Test 7.1 - sanity check: get_mutual_friends - ");
	User *test7_a = create_user("aa");
	User *test7_b = create_user("bb");
	User *test7_c = create_user("cc");
	User *test7_e = create_user("ee");
	User *test7_f = create_user("ff");
	User *test7_g = create_user("gg");
	User *test7_d = (User *) calloc(1, sizeof(User));
	strcpy(test7_d->name, "dd");
	add_friend(test7_a,test7_b);
	add_friend(test7_a,test7_c);
	add_friend(test7_c,test7_b);
	// add_friend(test7_b,d);
	add_friend(test7_b,test7_g);
	int res7_1 = get_mutual_friends(test7_a,test7_b);
	if(res7_1 != 1){
		printf("Failed\n  Test 7.1: Expected = 1 - Received  = %d\n", res7_1);
		return 1;
	}else printf("Passed\n");

	printf("  Test 7.2 - NULL Case - ");

	int res7_2 = get_mutual_friends(NULL, test7_a);
	if(res7_2 != 0){
		printf("Failed\n  Test 7.2:  Expected = 0 - Received  = %d\n", res7_2);
		return 1;
	}else printf("Passed\n");

	printf("  Test 7.3 - Another NULL Case - ");
	int res7_3 = get_mutual_friends(test7_a, NULL);
	if(res7_3 != 0){
		printf("Failed\n  Test 7.3:  Expected = 0 - Received  = %d\n", res7_3);
		return 1;
	}else printf("Passed\n");

	printf("  Test 7.4 - User not in allUsers - ");
	int res7_4 = get_mutual_friends(test7_a, test7_d);
	if(res7_4 != 0){
		printf("Failed\n  Test 7.4:  Expected = 0 - Received  = %d\n", res7_4);
		return 1;
	}else printf("Passed\n");

	printf("  Test 7.5 - A Simple No Friends In Common - ");
	int res7_5 = get_mutual_friends(test7_a, test7_f);
	if(res7_5 != 0){
		printf("Failed\n  Test 7.5:  Expected = 0 - Received  = %d\n", res7_5);
		return 1;
	}else printf("Passed\n");

	printf("  Test 7.6 - User with User itself - ");
	int res7_6 = get_mutual_friends(test7_a, test7_a);
	if(res7_6 != 2){
		printf("Failed\n  Test 7.6:  Expected = 2 - Received  = %d\n", res7_6);
		return 1;
	}else printf("Passed\n");

	free(test7_d);
	delete_user(test7_a);
	delete_user(test7_b);
	delete_user(test7_c);
	delete_user(test7_e);
	delete_user(test7_f);
	delete_user(test7_g);

	printf("Test 7: get_mutual_friends() passed!\n\n");


	printf("Test 8: get_degrees_of_connection():\n");
	printf("  Test 8.1 - sanity check: get_degrees_of_connection - ");
	User *test8_a = create_user("aa");
	User *test8_b = create_user("bb");
	add_friend(test8_a,test8_b);
	User *test8_d = (User *) calloc(1, sizeof(User));
	strcpy(test8_d->name, "dd");


	int res8_1 = get_degrees_of_connection(test8_a,test8_b);
	if(res8_1 != 1){
	printf("Failed\n  Test 8.1:  Expected = 1 - Received  = %d\n", res8_1);
		return 1;
	}else printf("Passed\n");

	printf("  Test 8.2 - User with User itself - ");
	int res8_2 = get_degrees_of_connection(test8_a,test8_a);
	if(res8_2 != 0){
	printf("Failed\n  Test 8.2:  Expected = 0 - Received  = %d\n", res8_2);
		return 1;
	}else printf("Passed\n");

	printf("  Test 8.3 - NULL Case - ");
	int res8_3 = get_degrees_of_connection(test8_a,NULL);
	if(res8_3 != -1){
	printf("Failed\n  Test 8.3:  Expected = -1 - Received  = %d\n", res8_3);
		return 1;
	}else printf("Passed\n");

	printf("  Test 8.4 - Another NULL Case - ");
	int res8_4 = get_degrees_of_connection(NULL,test8_a);
	if(res8_4 != -1){
	printf("Failed\n  Test 8.4:  Expected = -1 - Received  = %d\n", res8_4);
		return 1;
	}else printf("Passed\n");

	printf("  Test 8.5 - User Not In allUsers - ");
	int res8_5 = get_degrees_of_connection(test8_a,test8_d);
	if(res8_5 != -1){
	printf("Failed\n  Test 8.5:  Expected = -1 - Received  = %d\n", res8_5 );
		return 1;
	}else printf("Passed\n");
	free(test8_d);
	delete_user(test8_a);
	delete_user(test8_b);

	printf("Test 8: get_degrees_of_connection() passed!\n\n");

	printf("Test 9: connect_similar_brands():\n");

	printf("  Test 9.1 - sanity check: connecting brands - ");
	connect_similar_brands("A","D");
	if (!brand_adjacency_matrix[0][1] || !brand_adjacency_matrix[1][0]){
		printf("Failed\n  Test 9.1: failed to update brand matrix\n");
		return 1;
	} else printf("Passed\n");

	printf("  Test 9.2 - connecting the same brand together - ");
	connect_similar_brands("A","A");
	if (brand_adjacency_matrix[0][0]){
		printf("Failed\n  Test 9.2: can't connect same brand\n");
		return 1;
	} else printf("Passed\n");

	printf("  Test 9.3 - connecting brands not in brandlist:\n");
	connect_similar_brands("A","X");
	connect_similar_brands("X","A");
	printf("    If you didn't segfault, congrats! you passed lol\n");

	printf("  Test 9.4 - connecting brands not in brandlist:\n");
	connect_similar_brands("A", NULL);
	connect_similar_brands(NULL, "A");
	printf("    If you didn't segfault, congrats! you passed lol\n");

	printf("Test 9: connect_similar_brands() passed!\n\n");

	printf("Test 10: remove_similar_brands():\n");

	printf("  Test 10.1 - sanity check: connecting brands - ");
	remove_similar_brands("A","D");
	if (brand_adjacency_matrix[0][1] || brand_adjacency_matrix[1][0]) {
		printf("Failed\n  Test 9.1: failed to update brand matrix\n");
		return 1;
	} else printf("Passed\n");

	printf("  Test 10.2 - removing brands not in brandlist:\n");
	remove_similar_brands("A","X");
	remove_similar_brands("X","A");
	printf("    If you didn't segfault, congrats! you passed lol\n");

	printf("  Test 10.3 - removing brands not in brandlist:\n");
	remove_similar_brands("A", NULL);
	remove_similar_brands(NULL, "A");
	printf("    If you didn't segfault, congrats! you passed lol\n");

	printf("Test 10: connect_similar_brands() passed!\n\n");

	printf("Test 11: get_suggested_friend():\n");
	printf("  Test 11.1 - sanity check: get_suggested_friend - ");
	User *test11_a = create_user("aa");
	User *test11_b = create_user("bb");
	add_friend(test11_a,test11_b);
	User *test11_d = (User *) calloc(1, sizeof(User));
	strcpy(test11_d->name, "dd");

	User *test11_v = get_suggested_friend(test11_a);
	if(test11_v != NULL){
	printf("Failed\n  Test 11.1:  Expected NULL\n");
		return 1;
	}else printf("Passed\n");

	printf("  Test 11.2 - User Not In allUsers - ");
	User *test11_n = get_suggested_friend(test11_d);
	if(test11_n){
	printf("Failed\n  Test 11.2:  Expected NULL\n");
		return 1;
	}else printf("Passed\n");


	printf("  Test 11.3 - User Is NULL - ");
	User *test11_c = get_suggested_friend(NULL);
	if(test11_c){
	printf("Failed\n  Test 11.3:  Expected NULL\n");
		return 1;
	}else printf("Passed\n");
	free(test11_d);

	delete_user(test11_a);
	delete_user(test11_b);

	printf("Test 11: connect_similar_brands() passed!\n\n");
	
	/*printf("Test 12: add_suggested_friend():\n");
	printf("  Test 12.1 - sanity check: add_suggested_friend - ");
	User *aaa = create_user("aa");
	User *bbb = create_user("bb");
	add_friend(aaa,bbb);
	User *ddd = (User *) calloc(1, sizeof(User));
	strcpy(ddd->name, "dd");



	test 1: user null
	test 2: n = 0
	test 3: user not in allUsers
	*/

	printf("Test 13: follow_suggested_brand():\n");
	printf("  Test 13.1 - sanity check: follow_suggested_brand - ");
	User *test13_a = create_user("aa");
	User *test13_b = create_user("bb");
	add_friend(test13_a,test13_b);
	User *test13_d = (User *) calloc(1, sizeof(User));
	strcpy(test13_d->name, "dd");


	int res13_1 = follow_suggested_brands(NULL, 10);
	if(res13_1 != 0){
		printf("Failed\n  Test 13.1:  Expected 0\n");
		return 1;
	}else printf("Passed\n");

	printf("  Test 13.2 - n = 0 - ");
	int res13_2 = follow_suggested_brands(test13_a, 0);
	if(res13_2 != 0){
		printf("Failed\n  Test 13.2:  Expected 0\n");
		return 1;
	}else printf("Passed\n");

	free(test13_d);

	delete_user(test13_a);
	delete_user(test13_b);


	printf("Completed. This test should result in leak-free programs.\n");
}
