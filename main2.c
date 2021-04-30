#define __testing
#define MAT_SIZE 100
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

	printf("  Test 3.4 - Adding a friend that isn't in allUsers - TODO\n");

	delete_user(test3_richard);
	delete_user(test3_johnny);
	printf("Test 3: add_friend() passed!\n\n");

	printf("Completed. This test should result in leak-free programs.\n");
}
