/*
 * CSC A48 - Intro to Computer Science II, Summer 2020
 *
 * This file provides an interactive test driver to help you check your
 * work as you work on A2.
 *
 * This is provided *only* with the intent of helping you test. It's up
 * to you to use this to thoroughly check that everything works in your
 * code.
 *
 * Remember: You are expected to test for *correctness*, that means
 * it's not enough for your functions to produce the right result,
 * they have to do so by manipulating all the relevant data correctly.
 * You should check for structure and correctness at every step.
 *
 * (c) 2020 Mustafa Quraish
 */

#define __testing
#define MAT_SIZE 100
#include "graffit.c"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>
void getInt(char *prompt, int *var) {
  printf("%s = ", prompt);
  scanf("%d", var);
  getchar();
}

void getStr(char *prompt, char *var) {
  printf("%s = ", prompt);
  fgets(&var[0], 1024, stdin);
  int i = strlen(&var[0]);
  if (var[i - 1] == '\n')
    var[i - 1] = '\0';
}
void print_matrix(int arr[MAT_SIZE][MAT_SIZE]){
  for(int i = 0; i < MAT_SIZE; i++){
    for(int j = 0; j < MAT_SIZE; j++){
      printf("%d ", arr[i][j]);
    }
    printf("\n");
  }
}
void print_friend_list(User *user){
  printf("%s | ", user->name);
  for(FriendNode *f = user->friends; f != NULL; f = f->next){
    printf("%s -> ", f->user->name);
  }
  printf("\n");
}
User *get_user_by_name(char *a){
  for(FriendNode *f = allUsers; f != NULL; f=f->next){
    if(strcmp(f->user->name,a) == 0) return f->user;
  }
  return NULL;
}
int main() {
  int tx, ty, w, h, wsplit, choice, i;
  int sx = 512, threshold, mode;
  char name[1024], name2[1024];
  choice = 0;


  srand(time(NULL));
  while (choice != 15) {
    printf("Please select from among the following options:\n");
    printf("0 - Create new User\n");
    printf("1 - Add friends\n");
    printf("2 - Follow brand\n");
    printf("3 - Print Adjacency matrix for users\n");
    printf("4 - Print Adjacency list for users\n");
    printf("5 - Mark brands as similar\n");
    printf("6 - Get degree of connections\n");
    printf("7 - Add suggested friends\n");
    printf("8 - Add suggested brands\n");
    printf("9 - Load custom brand matrix\n");
    printf("10 - Remove friends\n");
    printf("11 - Delete User\n");
    printf("12 - Unfollow brand\n");
    printf("13 - Mark brands as unsimilar\n");
    printf("14 - Get number of mutual friends\n");
    printf("15 - Exit (Delete everything yourself though I ain't your maid)\n");
    printf("69 - Load test graph\n");
    printf("420 - Static tests\n");
    getInt("Enter choice", &choice);
    printf("------------------------------------------------\n");
    name[0] = '\0', name2[0] = '\0';
    if (choice == 0) {//create new user
      getStr("Name of user: ", name);
      create_user(name);
    }

    if (choice == 1) {//add friend
      getStr("Name of first user", name);
      getStr("Name of second user", name2);
      if(add_friend(get_user_by_name(name), get_user_by_name(name2)) == 0){
        printf("%s and %s are now friends\n", name, name2);
      }
      else{
        printf("An error occurred, friends not added\n");
      }
    }

    if (choice == 2) {//follow brand
      getStr("Name of user", name);
      getStr("Name of brand", name2);
      if(follow_brand(get_user_by_name(name), name2) == 0){
        printf("%s is now following brand %s\n", name, name2);
      }
      else{
        printf("An error occurred, brand not followed\n");
      }
    }

    if (choice == 3) {//adjacency matrix for users
      //structure(root, 0);
      //if(validate_bst(root, -1, sx*sx,0))printf("BST is valid\n");
      //else printf("BST is invalid :(\n");
      int i = 0;
      for(FriendNode *f = allUsers; f != NULL; f = f->next){
        printf("%d : %s\n", i++, f->user->name);
      }
      for(FriendNode *V = allUsers; V != NULL; V=V->next){
        for(FriendNode *E = allUsers; E != NULL; E = E->next){
          if(in_friend_list(V->user->friends,E->user)){
            if(E->next != NULL) printf("1,");
            else printf("1");
          }
          else{
            if(E->next != NULL) printf("0,");
            else printf("0");
          }
        }
        printf("\n");
      }
    }

    if (choice == 4) {//adjacency list for users
      for(FriendNode *f = allUsers; f != NULL; f = f->next){
        print_friend_list(f->user);
      }
    }

    if (choice == 5) {//mark 2 brands as similar
      getStr("Name of first brand", name);
      getStr("Name of second brand", name2);
      connect_similar_brands(name, name2);
      printf("%s and %s are now connected\n", name, name2);
    }

    if (choice == 6) {//degree of connection
      getStr("Name of first user", name);
      getStr("Name of second user", name2);
      printf("Degree of connection between %s and %s is: %d\n", name, name2, get_degrees_of_connection(get_user_by_name(name), get_user_by_name(name2)));
    }

    if (choice == 7) {//add n suggested friends
      getStr("Name of user", name);
      int amount = 0;
      getInt("Number of friends to add", &amount);
      printf("User before----------------------\n");
      print_user_data(get_user_by_name(name));

      
      printf("Added %d friends\n", add_suggested_friends(get_user_by_name(name), amount));

      printf("User after----------------------\n");
      print_user_data(get_user_by_name(name));
    }

    if (choice == 8) {//fpllow n suggested brands
      getStr("Name of user", name);
      int amount = 0;
      getInt("Number of friends to add", &amount);
      printf("User before----------------------\n");
      print_user_data(get_user_by_name(name));

      
      printf("Added %d brands\n", follow_suggested_brands(get_user_by_name(name), amount));

      printf("User after----------------------\n");
      print_user_data(get_user_by_name(name));
    }
    if (choice == 9) {//load brand matrix from file
      getStr("Name of brand file", name);

      populate_brand_matrix(name);
      printf("brands populated");
    }
    if (choice == 10) {//remove friend
      getStr("Name of first user", name);
      getStr("Name of second user", name2);
      if(remove_friend(get_user_by_name(name), get_user_by_name(name2)) == 0){
        printf("%s and %s are now not friends", name, name2);
      }
      else{
        printf("An error occurred, friends not removed");
      }
    }

    if (choice == 11) {//delete user
      getStr("Name of user", name);
      if(delete_user(get_user_by_name(name)) == 0){
        printf("successfully deleted\n");
      }
      else{
        printf("An error occurred while deleting the user");
      }
    }
    if (choice == 12) {//unfollow brand
      getStr("Name of user", name);
      getStr("Name of brand", name2);
      if(unfollow_brand(get_user_by_name(name),name2 )){
        printf("successfully unfollowed\n");
      }
      else{
        printf("An error occurred while unfollowing the brand");
      }
    }
    if (choice == 13) {//mark 2 brands as unsimilar
      getStr("Name of first brand", name);
      getStr("Name of second brand", name2);
      remove_similar_brands(name,name2);
    }
    if (choice == 14) {//get number of mutual friends
      getStr("Name of first user", name);
      getStr("Name of second user", name2);
      printf("%s and %s have %d mutuals\n", name, name2, get_mutual_friends(get_user_by_name(name),get_user_by_name(name2)));
    }
    if (choice == 69) {
      User* A = create_user("A");
      User* B = create_user("B");
      User* C = create_user("C");
      User* D = create_user("D");
      User* E = create_user("E");
      User* F = create_user("F");
      User* loner = create_user("loner");//friends with no one
      add_friend(A,B);
      add_friend(A,D);
      add_friend(A,F);
      add_friend(B,E);
      add_friend(B,D);
      add_friend(F,C);
      printf("Default graph loaded\n");
    }
    if (choice == 420){
      
    }
    
    printf("------------------------------------------------\n");
  } // Enf while (choice!=9)

  return 0;
}