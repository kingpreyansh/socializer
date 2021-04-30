/**
 * CSC A48 - Intro to Computer Science II, Summer 2020
 * 
 * Assignment 3 - Graffit
 * 
 * Graphs &
 * Recursion
 * Assignment
 * For
 * Freshmen
 * In
 * Toronto
 *
 * (I am so proud of that initialism.)
 * 
 * This is the program file where you will implement your solution for
 * assignment 3. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will also need to have read the handout carefully. 
 * 
 * Parts where you have to implement functionality are clearly labeled TODO
 * 
 * Be sure to test your work thoroughly, our testing will be extensive
 * and will check that your solution is *correct*, not only that it
 * provides functionality.
 * 
 * (c) 2020 William Song, Mustafa Quraish
 **/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024
#ifndef __testing
#define MAT_SIZE 3	// A small graph
#endif

typedef struct user_struct {
    char name[MAX_STR_LEN];
    struct friend_node_struct* friends; // which contains a user (root/head) and a next pointer
    struct brand_node_struct* brands; // which contains a brand_name (root/head) and a next pointer
    bool visited;
} User;

typedef struct friend_node_struct {
    User* user;
    struct friend_node_struct* next;
} FriendNode;

typedef struct brand_node_struct {
    char brand_name[MAX_STR_LEN];
    struct brand_node_struct* next;
} BrandNode;

/** Note: We are reusing the FriendNode here as a Linked List for allUsers.
  * This is usually bad coding practice but it will allow us to reuse the
  * helper functions.
  **/
FriendNode* allUsers; 

int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];

/**
 * Checks if a user is inside a FriendNode LL.
 **/
bool in_friend_list(FriendNode *head, User *node) {
  for (FriendNode *cur = head; cur != NULL; cur = cur->next) { // current pointer points to head and while the pointer is not null go to the next pointer
    if (strcmp(cur->user->name, node->name) == 0) { // if the current pointer's username is equal to the name of the node's username
      return true; // then the user is in the friendlist so return true
    }
  }
  return false; // the item is not in the friend list return false
}

/**
 * Checks if a brand is inside a BrandNode LL.
 **/
bool in_brand_list(BrandNode *head, char *name) {
  for (BrandNode *cur = head; cur != NULL; cur = cur->next) {
    if (strcmp(cur->brand_name, name) == 0) {
      return true;
    }
  }
  return false;
}

/**
 * Inserts a User into a FriendNode LL in sorted position. If the user 
 * already exists, nothing is done. Returns the new head of the LL.
 **/
FriendNode *insert_into_friend_list(FriendNode *head, User *node) {
  if (node == NULL) return head; // if the user node is null then return the head 

  if (in_friend_list(head, node)) { // if node is in the friend list of friend node then the user is already in the list and do nothing
    printf("User already in list\n");
    return head;
  }

  // else case
  FriendNode *fn = calloc(1, sizeof(FriendNode)); // allocates memory for the fn node 
  fn->user = node; // new friend is the new node
  fn->next = NULL; // next node of the frield is null - this is the new friend

  if (head == NULL) // if the head is NULL i.e. the user has no friends then return fn as in add the first friend
    return fn;
    
  if (strcmp(head->user->name, node->name) > 0) {
    fn->next = head;
    return fn;
    // if the name of the friend is greater than the name of the new friend then insert at head  
  } 

  FriendNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
       cur = cur->next)
    ;
  fn->next = cur->next;
  cur->next = fn;
  return head;
}

/**
 * Inserts a brand into a BrandNode LL in sorted position. If the brand 
 * already exists, nothing is done. Returns the new head of the LL.
 **/
BrandNode *insert_into_brand_list(BrandNode *head, char *node) {
  if (node == NULL) return head;

  if (in_brand_list(head, node)) {
    printf("Brand already in list\n");
    return head;
  }
  BrandNode *fn = calloc(1, sizeof(BrandNode));
  strcpy(fn->brand_name, node);
  fn->next = NULL;

  if (head == NULL)
    return fn;
    
  if (strcmp(head->brand_name, node) > 0) {
    fn->next = head;
    return fn;
  } 

  BrandNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
       cur = cur->next)
    ;
  fn->next = cur->next;
  cur->next = fn;
  return head;
}

/**
 * Deletes a User from FriendNode LL. If the user doesn't exist, nothing is 
 * done. Returns the new head of the LL.
 **/
FriendNode *delete_from_friend_list(FriendNode *head, User *node) {
  if (node == NULL) return head;

  if (!in_friend_list(head, node)) {
    printf("User not in list\n");
    return head;
  }

  if (strcmp(head->user->name, node->name) == 0) {
    FriendNode *temp = head->next;
    free(head);
    return temp;
  }

  FriendNode *cur;
  for (cur = head; cur->next->user != node; cur = cur->next)
    ;

  FriendNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);
  return head;
}

/**
 * Deletes a brand from BrandNode LL. If the user doesn't exist, nothing is 
 * done. Returns the new head of the LL.
 **/
BrandNode *delete_from_brand_list(BrandNode *head, char *node) {
  if (node == NULL) return head;

  if (!in_brand_list(head, node)) {
    printf("Brand not in list\n");
    return head;
  }

  if (strcmp(head->brand_name, node) == 0) {
    BrandNode *temp = head->next;
    free(head);
    return temp;
  }

  BrandNode *cur;
  for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
    ;

  BrandNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);
  return head;
}

/**
 * Prints out the user data.
 **/
void print_user_data(User *user) {
  printf("User name: %s\n", user->name);
  printf("Friends:\n");
  for (FriendNode *f = user->friends; f != NULL; f = f->next) {
    printf("   %s\n", f->user->name);
  }
  printf("Brands:\n");
  for (BrandNode *b = user->brands; b != NULL; b = b->next) {
    printf("   %s\n", b->brand_name);
  }
}

/**
 * Get the index into brand_names for the given brand name. If it doesn't
 * exist in the array, return -1
 **/
int get_brand_index(char *name) {
  for (int i = 0; i < MAT_SIZE; i++) {
    if (strcmp(brand_names[i], name) == 0) {
      return i;
    }
  }
  printf("brand '%s' not found\n", name);
  return -1; // Not found
}

/**
 * Print out brand name, index and similar brands.
 **/
void print_brand_data(char *brand_name) {
  int idx = get_brand_index(brand_name);
  if (idx < 0) {
    printf("Brand '%s' not in the list.\n", brand_name);
    return;
  }
  printf("Brand name: %s\n", brand_name);
  printf("Brand idx: %d\n", idx);
  printf("Similar brands:\n");
  for (int i = 0; i < MAT_SIZE; i++) {
    if (brand_adjacency_matrix[idx][i] == 1 && strcmp(brand_names[i], "") != 0) {
      printf("   %s\n", brand_names[i]);
    }
  }
}

/**
 * Read from a given file and populate a the brand list and brand matrix.
 **/
void populate_brand_matrix(char* file_name) {
    // Read the file
    char buff[MAX_STR_LEN];
    FILE* f = fopen(file_name, "r");
    fscanf(f, "%s", buff);
    char* line = buff;
    // Load up the brand_names matrix
    for (int i = 0; i < MAT_SIZE; i++) {
        if (i == MAT_SIZE - 1) {
            strcpy(brand_names[i], line);
            break;
        }
        int index = strchr(line, ',') - line;
        strncpy(brand_names[i], line, index);
        line = strchr(line, ',') + sizeof(char);
    }
    // Load up the brand_adjacency_matrix
    for (int x = 0; x < MAT_SIZE; x++) {
        fscanf(f, "%s", buff);
        for (int y = 0; y < MAT_SIZE; y++) {
            int value = (int) buff[y*2];
            if (value == 48) { value = 0; }
            else {value = 1;}
            brand_adjacency_matrix[x][y] = value;
        }
    }
}


// Users
/**TODO: Complete this function
 * Creates and returns a user. Returns NULL on failure.
 **/


User* create_user(char* name){
  // if the name is not unique
  if(name != NULL){
  for (FriendNode *cur = allUsers; cur != NULL; cur = cur->next) {
    if (strcmp(cur->user->name, name) == 0) { 
      return NULL; 
    }
  }
  // if the name is empty or exceeds the max
  User *new_user = (User *)calloc(1, sizeof(User));
  if(strcmp(name, "") == 0 || strlen(name) > MAX_STR_LEN || name == NULL){
    new_user = NULL;
  } else{
      strcpy(new_user->name, name);
      new_user->friends = NULL;
      new_user->brands = NULL;
      new_user->visited = false;
      allUsers = insert_into_friend_list(allUsers, new_user);
    }
    return new_user;
  }
  return NULL;
}

/**TODO: Complete this function
 * Deletes a given user. 
 * Returns 0 on success, -1 on failure.
 **/
int delete_user(User* user) { 
  int return_val = -1;
  // if user is in all users and its not null
  if(user != NULL && in_friend_list(allUsers, user)){
    // go through the list of allUsers and the user is in the friend list of some other user then delete it from their friend list
    
    for(BrandNode *brand = user->brands; brand != NULL; brand = brand->next){
        user->brands = delete_from_brand_list(user->brands, brand->brand_name);
    }

    FriendNode *currUser = allUsers;
    while(currUser!= NULL){

      if(in_friend_list(currUser->user->friends, user)){
        currUser->user->friends = delete_from_friend_list(currUser->user->friends, user);
      }
      currUser = currUser->next;
    }
    allUsers = delete_from_friend_list(allUsers, user);
    free(user);
    return_val = 0;
  }
  return return_val;
}
/**TODO: Complete this function
 * Create a friendship between user and friend.
 * Returns 0 on success, -1 on failure.
 **/
int add_friend(User* user, User* friend){
  // if both user && friend exists
  if(user == NULL || friend == NULL || !(in_friend_list(allUsers, user)) || !(in_friend_list(allUsers, friend)) || (in_friend_list(friend->friends, user)) || (in_friend_list(user->friends, friend)) || user == friend){
  // fails when the user or the friend does not exist
  // fails if the user already is a friend of friend or friend is already a friend of user
    return -1;
  } else{
    user->friends = insert_into_friend_list(user->friends, friend);
    friend->friends = insert_into_friend_list(friend->friends, user);
  }
  return 0; // fails when either user does not exist or friend does not exist
}

/**TODO: Complete this function
 * Removes a friendship between user and friend.
 * Returns 0 on success, -1 on faliure.
 **/
int remove_friend(User* user, User* friend){
  if(user == NULL || friend == NULL || !in_friend_list(allUsers, user) || !in_friend_list(allUsers, friend) || user == friend || !(in_friend_list(friend->friends, user)) || !(in_friend_list(user->friends, friend))){
    return -1;
  }
  user->friends = delete_from_friend_list(user->friends, friend);
  friend->friends = delete_from_friend_list(friend->friends, user);
  return 0;
}

/**TODO: Complete this function
 * Creates a follow relationship, the user follows the brand.
 * Returns 0 on success, -1 on faliure.
 **/
int follow_brand(User* user, char* brand_name){
  // brand name already in user's brand list or the user not in AllUsers
  int ret_val = -1;
  if(user == NULL || brand_name == NULL || in_brand_list(user->brands, brand_name) || !(in_friend_list(allUsers, user))){
    ret_val = -1;
  } else{
    // if the brand name exists in the list of brands only then follow the brand
    for (int i = 0; i < MAT_SIZE; ++i){
      if(strcmp(brand_names[i], brand_name) == 0){
        user->brands = insert_into_brand_list(user->brands, brand_name);
        ret_val = 0; 
      }
    }
  }
  return ret_val; 
}

/**TODO: Complete this function
 * Removes a follow relationship, the user unfollows the brand.
 * Returns 0 on success, -1 on faliure.
 **/
int unfollow_brand(User* user, char* brand_name){
  // fail cases
  int ret_val;
  if(!(in_friend_list(allUsers, user)) || !(in_brand_list(user->brands, brand_name))){
    ret_val = -1;
  } else{
    for(int i = 0; i < MAT_SIZE; i++){
      if(strcmp(brand_names[i], brand_name) == 0){
        // the brand is in the brands_name
        user->brands = delete_from_brand_list(user->brands, brand_name);
        ret_val = 0;
      }
    }
  }
  return ret_val; // there was no brand to delete hence 0 was not returned
}

/**TODO: Complete this function
 * Return the number of mutual friends between two users.
 **/
int get_mutual_friends(User* a, User* b){
  int count = 0; 
  if(a == NULL || b == NULL || !in_friend_list(allUsers, a) || !(in_friend_list(allUsers, b))){
    return 0;
  } else{
    // iterate through all of a's friends
    for(FriendNode *node = a -> friends; node != NULL; node = node -> next){
      // if b's friendlist contains a's friends then the counter will go up
        if(in_friend_list(b->friends, node->user)){
          count++;
        }
    }
  }
  return count; // fails when either user does not exist
}

/**TODO: Complete this function
 * A degree of connection is the number of steps it takes to get from
 * one user to another.
 * 
 * For example, if X & Y are friends, then we expect to recieve 1 when calling
 * this on (X,Y). Continuing on, if Y & Z are friends, then we expect to
 * recieve 2 when calling this on (X,Z).
 * 
 * Returns a non-negative integer representing the degrees of connection
 * between two users, -1 on failure.
 **/

////////////////// HELPER FUNCTIONS /////////////

int user_index(User *a){
  int i = 0;
  for(FriendNode *curr = allUsers; curr != NULL; curr = curr->next){
    if(curr->user == a) return i;
    i++;
  }
  return -1;
}

int get_user_len(FriendNode *friend){
  int i = 0;
  for(FriendNode *curr = allUsers; curr != NULL; curr = curr->next){
    i++;
  }
  return i;
}

FriendNode *get_friend(User *user){
  for(FriendNode *curr = allUsers; curr != NULL; curr = curr->next){
    if(curr->user == user) return curr;
  }
  return NULL;
}

//////////////////// QUEUE //////////////////////

typedef struct Queue{
  //A FIFI queue of friends
  User *user[MAX_STR_LEN];
  int size;
}Queue;

void initialize_queue(Queue *my_queue){
  //set up a new queue
  //(must be called on all newly created queues)
  my_queue->size = 0;
}

void enqueue(Queue *my_queue, User *a){
  //add new_data to the end of the queue
  my_queue->user[my_queue->size] = a;
  my_queue->size += 1;
}

User *dequeue(Queue *my_queue){
  //remove and return the first item in the queue
  User *ret_item = my_queue->user[0];
  for(int i = 0; i < (my_queue->size -1); i++){
    my_queue->user[i] = my_queue->user[i + 1];
  }
  my_queue->size -= 1;
  return ret_item;
}

bool is_queue_empty(Queue *my_queue){
  //return true iff the queue is empty
  return my_queue->size == 0;
}

void initialize_array(int distances[get_user_len(allUsers)]){
  for(int i = 0; i < get_user_len(allUsers); i++){
    distances[i] = -1;
  }
}

void user_false(){
  for(FriendNode *curr = allUsers; curr != NULL; curr = curr->next){
    curr->user->visited = false;
  }
}
/////////////////////////////////////////////////

int get_degrees_of_connection(User* a, User* b){
  int result;
  // this is the degree that i will be returning
  if (a == NULL || b == NULL || !in_friend_list(allUsers, a) || !in_friend_list(allUsers,b)){
    // making sure that the input is valid - if it's not valid then return -1 or if it is valid then return 0
    return -1;
  } else if(a == b){
    return 0;
  }else{

  // store the distances from user a to every single possible node
  int dis_arr[get_user_len(allUsers)];
  // initialize means set the distance array all to -1's.
  initialize_array(dis_arr);

  // make a queue with array of pointers to Users
  Queue my_queue;
  // initialize the queue by making the size to be 0
  initialize_queue(&my_queue);
  // add a to the queue
  enqueue(&my_queue, a);

  // get the index of a (in the allUsers linked list)
  int a_index = user_index(a);
  // the the distance array's position where a is located i.e. the index will be now set.
  dis_arr[a_index] = 0;

  // the queue initially has the 'a' user in it and while the queue is not empty
  while (!is_queue_empty(&my_queue)){
    // set the current user to be the first user in the queue i.e. dequeue from the queue
    User *current_user = dequeue(&my_queue);
    // for that user's friends
    for(FriendNode *current_friend = current_user->friends; current_friend != NULL; current_friend = current_friend->next){
      // if the distance array at that specific index is -1 i.e. the distance array does not have information about how far it is from the current user
      if (dis_arr[user_index(current_friend->user)] == -1 && !(current_friend->user->visited)){ // and the current user's first friend is not visited
        dis_arr[user_index(current_friend->user)] = dis_arr[user_index(current_user)] + 1;
        // the distance array is now incremented by 1 - basically the distance from the current user + 1
        current_user->visited = true;
        enqueue(&my_queue, current_friend->user); // add the friend of the user to the queue now
      }
    }
  }
  result = dis_arr[user_index(b)]; // once the distance array is filled the result is simply the appropriate index of the distance array
  user_false(); // then to reuse the distance array we must set all of the users->visited to be false
  }
  return result;
}

// Brands
/**TODO: Complete this function
 * Marks two brands as similar.
 **/
void connect_similar_brands(char* brandNameA, char* brandNameB){
  if(brandNameA != NULL && brandNameB != NULL && strcmp(brandNameA, brandNameB) != 0){
     // if brandNameA and brandNameB is inside the list of brands
    if(get_brand_index(brandNameA) != -1 && get_brand_index(brandNameB) != -1){
      int brandA = get_brand_index(brandNameA);
      int brandB = get_brand_index(brandNameB);
      brand_adjacency_matrix[brandA][brandB] = 1;
      brand_adjacency_matrix[brandB][brandA] = 1;
    }
  }
}

/**TODO: Complete this function
 * Marks two brands as not similar.
 **/
void remove_similar_brands(char* brandNameA, char* brandNameB){
if(brandNameA != NULL && brandNameB != NULL){
     // if brandNameA and brandNameB is inside the list of brands
    if(get_brand_index(brandNameA) != -1 && get_brand_index(brandNameB) != -1){
      int brandA = get_brand_index(brandNameA);
      int brandB = get_brand_index(brandNameB);
      brand_adjacency_matrix[brandA][brandB] = 0;
      brand_adjacency_matrix[brandB][brandA] = 0;
    }
  }
}

// Harder ones
/**TODO: Complete this function
 * Returns a suggested friend for the given user, returns NULL on failure.
 * See the handout for how we define a suggested friend.
 **/

int get_mutual_brands(User* a, User* b){
  int count = 0; 
  if(!in_friend_list(allUsers, a) || !(in_friend_list(allUsers, b)) || a == NULL || b == NULL){
    return 0;
  } else{
    for(BrandNode *a_brands = a->brands; a_brands != NULL; a_brands = a_brands->next){
      for(BrandNode *b_brands = b->brands; b_brands != NULL; b_brands = b_brands->next){
        if(strcmp(a->brands->brand_name, b->brands->brand_name) == 0){
          count++;
        }
      }
    }
  }
  return count; // fails when either user does not exist
}

User* get_suggested_friend(User* user) {
  // user has to exist
  int max_mutuals = 0;
  User *ret_user = NULL;
  if(user != NULL && in_friend_list(allUsers, user)){
    for(FriendNode *userfriend = allUsers; userfriend != NULL; userfriend = userfriend->next){
        if(!(in_friend_list(user->friends, userfriend->user)) && user != userfriend->user){
          if(max_mutuals < get_mutual_brands(user, userfriend->user)){            
            max_mutuals = get_mutual_brands(user, userfriend->user);
            ret_user = userfriend->user;
          } else if (max_mutuals == get_mutual_brands(user, userfriend->user)){
            if(ret_user != NULL && strcmp(userfriend->user->name, ret_user->name) > 0){
              ret_user = userfriend->user;
            } else{
              ret_user = userfriend->user;
            }
          }
        }
    }
  }
  return ret_user;
}

/**TODO: Complete this function
 * Friends n suggested friends for the given user.
 * See the handout for how we define a suggested friend.
 * Returns how many friends were successfully followed.
 **/
int add_suggested_friends(User* user, int n) {
  int count = 0;
  if(user == NULL){
    return 0;
  } else{
    for(int i = 0; i < n; i++){
      if(add_friend(user, get_suggested_friend(user)) == 0){
        count += 1;
      }
    }
  }
  return count;
}

/**TODO: Complete this function
 * Follows n suggested brands for the given user.
 * See the handout for how we define a suggested brand.     
 * Returns how many brands were successfully followed.      
 **/
int get_col_ones(int index, User *user){

  int count = 0;
  for(BrandNode *brand = user->brands; brand != NULL; brand = brand->next){
      if(brand_adjacency_matrix[index][get_brand_index(brand->brand_name)] == 1){
        count++;        
    }
  }
  return count;
}

char* get_suggested_brand(User* user) {
  int max_col = 0;
  char *ret_brand = "";
  for(BrandNode *brand = user->brands; brand != NULL; brand = brand->next){
    for(int i = 0; i < MAT_SIZE; i++){
      if(max_col < get_col_ones(i, user) && !(in_brand_list(user->brands, brand_names[i]))){
        max_col = get_col_ones(i, user);
        ret_brand = brand_names[i];        
      } else if(max_col == get_col_ones(i, user) && !(in_brand_list(user->brands, brand_names[i]))){
        if(strcmp(ret_brand, brand_names[i]) < 0){
          ret_brand = brand_names[i];
        }
      }
    }
  }
  return ret_brand;
}

int follow_suggested_brands(User* user, int n) {
  if(user != NULL){
  int count = 0;
  int i = 0;
  while(i < n){
    char *to_add = get_suggested_brand(user);
    if (follow_brand(user, to_add) == 0) {
      count++;
    }
    i++;
  }
  return count;
  }
  return 0;
}
