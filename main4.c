 #define __testing
#define MAT_SIZE 10
#include "graffit.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
	populate_brand_matrix("bigbrands10.txt");
	
	
	//Test case 1, NULL case
	User *test_1 = get_suggested_friend(NULL);
	if (test_1 != NULL){
		printf("Failed test case 1, user should be NULL.\n");
		return -1;
	}
	else printf("Passed test case 1.\n");
	
	
	//Test case 2, user is the only person on allUsers, should add no one/return NULL
	User *userA_2 = create_user("A");
	User *test_2 = get_suggested_friend(userA_2);
	if (test_2 != NULL){
		printf("Failed test case 2, user should be NULL.\n");
		return -1;
	}
	else printf("Passed test case 2.\n");
	delete_user(userA_2);
	
	
	//Test case 3, only 2 users in allUsers, none following brands, returns B
	User *userA_3 = create_user("A");
	User *userB_3 = create_user("B");
	
	User *test_3 = get_suggested_friend(userA_3);
	if (test_3 != userB_3){
		printf("Failed test case 3, should return userB_3.\n");
		return -1;
	}
	else printf("Passed test case 3.\n");
	delete_user(userA_3);
	delete_user(userB_3);
	
	
	//Test case 4, only 2 users in allUsers, A following brands, returns B
	User *userA_4 = create_user("A");
	User *userB_4 = create_user("B");
	follow_brand(userA_4, "1");
	
	User *test_4 = get_suggested_friend(userA_4);
	if (test_4 != userB_4){
		printf("Failed test case 4, should return userB_4.\n");
		return -1;
	}
	else printf("Passed test case 4.\n");
	delete_user(userA_4);
	delete_user(userB_4);
	
	//Test case 5, 3 users in allUsers, B following brands, returns C
	User *userA_5 = create_user("A");
	User *userB_5 = create_user("B");
	User *userC_5 = create_user("C");
	follow_brand(userB_5, "1");
	
	User *test_5 = get_suggested_friend(userB_5);
	if (test_5 != userC_5){
		printf("Failed test case 5, should return userC_5.\n");
		return -1;
	}
	else printf("Passed test case 5.\n");
	delete_user(userA_5);
	delete_user(userB_5);
	delete_user(userC_5);
	
	
	//Test case 6, 3 users in allUsers, A and B following same brands, returns A
	User *userA_6 = create_user("A");
	User *userB_6 = create_user("B");
	User *userC_6 = create_user("C");
	follow_brand(userA_6, "1");
	follow_brand(userB_6, "1");
	follow_brand(userC_6, "3");
	
	User *test_6 = get_suggested_friend(userB_6);
	if (test_6 != userA_6){
		printf("Failed test case 6, should return userA_6.\n");
		return -1;
	}
	else printf("Passed test case 6.\n");
	delete_user(userA_6);
	delete_user(userB_6);
	delete_user(userC_6);
	
	
	//Test case 7, 4 users in allUsers, A and B following same brands, returns D
	User *userA_7 = create_user("A");
	User *userB_7 = create_user("B");
	User *userC_7 = create_user("C");
	User *userD_7 = create_user("D");
	follow_brand(userA_7, "1");
	follow_brand(userB_7, "1");
	follow_brand(userC_7, "3");
	follow_brand(userD_7, "0");
	
	User *test_7 = get_suggested_friend(userC_7);
	if (test_7 != userD_7){
		printf("Failed test case 7, should return userD_7.\n");
		return -1;
	}
	else printf("Passed test case 7.\n");
	delete_user(userA_7);
	delete_user(userB_7);
	delete_user(userC_7);
	delete_user(userD_7);
	
	
	
	
	//Test cases 8 to 14
	//Literally the same ones as above (well, almost) but with add_suggested_friends instead
	
	//Test case 8, NULL case
	int test_8 = add_suggested_friends(NULL, 10);
	if (test_8 != 0){
		printf("Failed test case 8, test should be 0.\n");
		return -1;
	}
	else printf("Passed test case 8.\n");
	
	
	//Test case 9, user is the only person on allUsers, should add no one/return 0
	User *userA_9 = create_user("A");
	int test_9 = add_suggested_friends(userA_9, 10);
	if (test_9 != 0){
		printf("Failed test case 9, test should be 0.\n");
		return -1;
	}
	else printf("Passed test case 9.\n");
	delete_user(userA_9);
	
	
	//Test case 10, only 2 users in allUsers, none following brands, returns 1
	User *userA_10 = create_user("A");
	User *userB_10 = create_user("B");
	
	int test_10 = add_suggested_friends(userA_10, 3);
	if (test_10 != 1){
		printf("Failed test case 10, should return 1.\n");
		return -1;
	}
	if (!in_friend_list(userA_10->friends, userB_10) || !in_friend_list(userB_10->friends, userA_10)){
		printf("Failed test case 10, users failed to add each other.\n");
		return -1;
	}
	else printf("Passed test case 10.\n");
	delete_user(userA_10);
	delete_user(userB_10);
	
	
	//Test case 11, only 2 users in allUsers, A following brands, returns 1
	User *userA_11 = create_user("A");
	User *userB_11 = create_user("B");
	follow_brand(userA_11, "1");
	
	int test_11 = add_suggested_friends(userA_11, 10);
	if (test_11 != 1){
		printf("Failed test case 11, should return 1.\n");
		return -1;
	}
	if (!in_friend_list(userA_11->friends, userB_11) || !in_friend_list(userB_11->friends, userA_11)){
		printf("Failed test case 11, users failed to add each other.\n");
		return -1;
	}
	else printf("Passed test case 11.\n");
	delete_user(userA_11);
	delete_user(userB_11);
	
	//Test case 12a, 3 users in allUsers, B following brands, returns 2
	User *userA_12a = create_user("A");
	User *userB_12a = create_user("B");
	User *userC_12a = create_user("C");
	follow_brand(userB_12a, "1");
	
	int test_12a = add_suggested_friends(userB_12a, 10);
	if (test_12a != 2){
		printf("Failed test case 12a, should return 2.\n");
		return -1;
	}
	if (!in_friend_list(userA_12a->friends, userB_12a) || !in_friend_list(userB_12a->friends, userA_12a)
		||!in_friend_list(userC_12a->friends, userB_12a) || !in_friend_list(userB_12a->friends, userC_12a)){
		printf("Failed test case 12a, users failed to add each other.\n");
		return -1;
	}
	else printf("Passed test case 12a.\n");
	delete_user(userA_12a);
	delete_user(userB_12a);
	delete_user(userC_12a);
	
	//Test case 12b, 3 users in allUsers, B following brands, returns 1
	User *userA_12b = create_user("A");
	User *userB_12b = create_user("B");
	User *userC_12b = create_user("C");
	follow_brand(userB_12b, "1");
	
	int test_12b = add_suggested_friends(userB_12b, 1);
	if (test_12b != 1){
		printf("Failed test case 12b, should return 1.\n");
		return -1;
	}
	if (!in_friend_list(userC_12b->friends, userB_12b) || !in_friend_list(userB_12b->friends, userC_12b)){
		printf("Failed test case 12b, users failed to add each other.\n");
		return -1;
	}
	else printf("Passed test case 12b.\n");
	delete_user(userA_12b);
	delete_user(userB_12b);
	delete_user(userC_12b);
	
	
	//Test case 13, 3 users in allUsers, A and B following same brands, returns 1
	User *userA_13 = create_user("A");
	User *userB_13 = create_user("B");
	User *userC_13 = create_user("C");
	follow_brand(userA_13, "1");
	follow_brand(userB_13, "1");
	follow_brand(userC_13, "3");
	
	int test_13 = add_suggested_friends(userB_13, 1);
	if (test_13 != 1){
		printf("Failed test case 13, should return 1.\n");
		return -1;
	}
	if (!in_friend_list(userA_13->friends, userB_13) || !in_friend_list(userB_13->friends, userA_13)){
		printf("Failed test case 13, users failed to add each other.\n");
		return -1;
	}
	else printf("Passed test case 13.\n");
	delete_user(userA_13);
	delete_user(userB_13);
	delete_user(userC_13);
	
	
	
	//Test case 14a, 4 users in allUsers, A and B following same brands, returns 1
	User *userA_14a = create_user("A");
	User *userB_14a = create_user("B");
	User *userC_14a = create_user("C");
	User *userD_14a = create_user("D");
	follow_brand(userA_14a, "1");
	follow_brand(userB_14a, "1");
	follow_brand(userC_14a, "3");
	follow_brand(userD_14a, "0");
	
	int test_14a = add_suggested_friends(userB_14a, 1);
	if (test_14a != 1){
		printf("Failed test case 14a, should return 1\n");
		return -1;
	}
	if (!in_friend_list(userA_14a->friends, userB_14a) || !in_friend_list(userB_14a->friends, userA_14a)){
		printf("Failed test case 14a, users failed to add each other.\n");
		return -1;
	}
	else printf("Passed test case 14a.\n");
	delete_user(userA_14a);
	delete_user(userB_14a);
	delete_user(userC_14a);
	delete_user(userD_14a);
	
	
	//Test case 14b, 4 users in allUsers, A and B following same brands, returns 2
	User *userA_14b = create_user("A");
	User *userB_14b = create_user("B");
	User *userC_14b = create_user("C");
	User *userD_14b = create_user("D");
	follow_brand(userA_14b, "1");
	follow_brand(userB_14b, "1");
	follow_brand(userC_14b, "3");
	follow_brand(userD_14b, "0");
	
	int test_14b = add_suggested_friends(userB_14b, 2);
	if (test_14b != 2){
		printf("Failed test case 14b, should return 1\n");
		return -1;
	}
	if (!in_friend_list(userA_14b->friends, userB_14b) || !in_friend_list(userB_14b->friends, userA_14b)
		||!in_friend_list(userD_14b->friends, userB_14b) || !in_friend_list(userB_14b->friends, userD_14b)){
		printf("Failed test case 14b, users failed to add each other.\n");
		return -1;
	}
	else printf("Passed test case 14b.\n");
	delete_user(userA_14b);
	delete_user(userB_14b);
	delete_user(userC_14b);
	delete_user(userD_14b);
	
	if (allUsers == NULL) printf("Are you happy now, Andrew?\n");
}