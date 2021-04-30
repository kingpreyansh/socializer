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
    struct friend_node_struct* friends;
    struct brand_node_struct* brands;
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
  for (FriendNode *cur = head; cur != NULL; cur = cur->next) {
    if (strcmp(cur->user->name, node->name) == 0) {
      return true;
    }
  }
  return false;
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
  if (node == NULL) return head;

  if (in_friend_list(head, node)) {
    printf("User already in list\n");
    return head;
  }
  FriendNode *fn = calloc(1, sizeof(FriendNode));
  fn->user = node;
  fn->next = NULL;

  if (head == NULL)
    return fn;
    
  if (strcmp(head->user->name, node->name) > 0) {
    fn->next = head;
    return fn;
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
User* create_user(char* name) { //fail if cannot get memory for node, fail if username exists already, fail if empty username, fail if username too big
	//calloc new user, then check for fail conditions, then initialize user, then check fail condition, then return user or delete them
	if (name == NULL) {
		return NULL;
	}
	User *new_user = (User *)calloc(1, sizeof(User));
	if (!new_user) {
		return NULL;
	}
	if (strcmp(name, "") == 0 || strlen(name) >= MAX_STR_LEN) {
		free(new_user);
		return NULL;
	}
	strcpy(new_user -> name, name);
	new_user -> friends = NULL;
	new_user -> brands = NULL;
	new_user -> visited = false;
	if (!in_friend_list(allUsers, new_user)) {
		allUsers = insert_into_friend_list(allUsers, new_user);
		return new_user;
	}
	free(new_user);
	return NULL;
}

/**TODO: Complete this function
 * Deletes a given user. 
 * Returns 0 on success, -1 on failure.
 **/
int delete_user(User* user) { //fail if user not in allUsers
	//check fail condition, then remove user from allUsers friends lists, then remove from allUsers, then delete user
	if (user != NULL && in_friend_list(allUsers, user)) {
		for (FriendNode *cur = allUsers; cur != NULL; cur = cur -> next) {
			if (in_friend_list(cur -> user -> friends, user)) {
				cur -> user -> friends = delete_from_friend_list(cur -> user -> friends, user);
			}
		}
		allUsers = delete_from_friend_list(allUsers, user);
		free(user);
	}
	return -1;
}

/**TODO: Complete this function
 * Create a friendship between user and friend.
 * Returns 0 on success, -1 on failure.
 **/
int add_friend(User* user, User* friend) { //fail if user or friend are not in allUsers or if already friends or trying to friend self
	//insert_into_friend_list friend on user, then insert_into_friend_list user on friend (sort alphabetically)
	if (user == NULL || friend == NULL || !in_friend_list(allUsers, user) || !in_friend_list(allUsers, friend) || in_friend_list(user -> friends, friend) || in_friend_list(friend -> friends, user) || strcmp(user -> name, friend -> name) == 0) {
		return -1;
	}
	user -> friends = insert_into_friend_list(user -> friends, friend);
	friend -> friends = insert_into_friend_list(friend -> friends, user);
	return 0;
}

/**TODO: Complete this function
 * Removes a friendship between user and friend.
 * Returns 0 on success, -1 on faliure.
 **/
int remove_friend(User* user, User* friend) { //fail if user or friend not in other one's friend list, or not in allUsers or if trying to unfriend self
	//check fail conditions, then delete_from_friend_list friend on user and user on friend
	if (user == NULL || friend == NULL || !in_friend_list(allUsers, user) || !in_friend_list(allUsers, friend) || !in_friend_list(friend -> friends, user) || !in_friend_list(user -> friends, friend) || strcmp(user -> name, friend -> name) == 0) {
		return -1;
	}
	user -> friends = delete_from_friend_list(user -> friends, friend);
	friend -> friends = delete_from_friend_list(friend -> friends, user);
	return 0;
}

/**TODO: Complete this function
 * Creates a follow relationship, the user follows the brand.
 * Returns 0 on success, -1 on faliure.
 **/
int follow_brand(User* user, char* brand_name) { //fail if user not in allUsers or brand not in brand_names or user already following brand
	//check fail condition, check other fail condition, then insert_into_brand_list brand_name
	if (user != NULL && brand_name != NULL && in_friend_list(allUsers, user) && !(in_brand_list(user -> brands, brand_name))) {
		for (int i = 0; i < MAT_SIZE; i++) {
			if (strcmp(brand_names[i], brand_name) == 0) {
				user -> brands = insert_into_brand_list(user -> brands, brand_name);
				return 0;
			}
		}
	}
	return -1;
}

/**TODO: Complete this function
 * Removes a follow relationship, the user unfollows the brand.
 * Returns 0 on success, -1 on faliure.
 **/
int unfollow_brand(User* user, char* brand_name) { //fail if not following brand, or user not in allUsers, or brand not in brand_names
	//check fail conditions, then delete_from_brand_list brand on user
	if (user != NULL && brand_name != NULL && in_friend_list(allUsers, user) && in_brand_list(user -> brands, brand_name)) {
		for (int i = 0; i < MAT_SIZE; i++) {
			if (strcmp(brand_names[i], brand_name) == 0) {
				user -> brands = delete_from_brand_list(user -> brands, brand_name);
				return 0;
			}
		}
	}
	return -1;
}

/**TODO: Complete this function
 * Return the number of mutual friends between two users.
 **/
int get_mutual_friends(User* a, User* b) { //return 0 if either user not in allUsers
	//iterate through friends list of a and check if each friend in b, increase by 1 if so and return
	int mutuals = 0;
	if (a != NULL && b != NULL && in_friend_list(allUsers, a) && in_friend_list(allUsers, b)) {
		for (FriendNode *cur = a -> friends; cur != NULL; cur = cur -> next) {
			if (in_friend_list(b -> friends, cur -> user)) {
				mutuals++;
			}
		}
	}
	return mutuals;
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
void get_degree(User *a, User *b, int* degree, int current) { //helper for below. recursively goes through friends to find degree of connection between original input
	current++;
	if (in_friend_list(a -> friends, b) && (*degree <= 0 || *degree > current)) {
		*degree = current;
	}
	if (!(a -> visited)) {
		a -> visited = true;
		for (FriendNode *cur = a -> friends; cur != NULL; cur = cur -> next) {
			get_degree(cur -> user, b, degree, current);
		}
	}
}

int get_degrees_of_connection(User* a, User* b) { //fail either user not in allUsers, or not connected
	//check fail conditions then iterate through friends of a recursively until find b, if cannot find at end, return -1
	if (a != NULL && b!= NULL && in_friend_list(allUsers, a) && in_friend_list(allUsers, b)) {
		if (strcmp(a -> name, b -> name) == 0) {
			return 0;
		}
		int degree = 0;
		get_degree(a, b, &degree, 0);
		for (FriendNode *cur = allUsers; cur != NULL; cur = cur -> next) {
			cur -> user -> visited = false;
		}
		if (degree == 0) {
			return -1;
		}
		return degree;
	}
	return -1;
}


// Brands
/**TODO: Complete this function
 * Marks two brands as similar.
 **/
void connect_similar_brands(char* brandNameA, char* brandNameB) {
	if (!(brandNameA == NULL) && !(brandNameB == NULL) && !(get_brand_index(brandNameA) == -1) && !(get_brand_index(brandNameB) == -1)) {
		brand_adjacency_matrix[get_brand_index(brandNameA)][get_brand_index(brandNameB)] = 1;
		brand_adjacency_matrix[get_brand_index(brandNameB)][get_brand_index(brandNameA)] = 1;
	}
}

/**TODO: Complete this function
 * Marks two brands as not similar.
 **/
void remove_similar_brands(char* brandNameA, char* brandNameB) {
	if (!(brandNameA == NULL) && !(brandNameB == NULL) && !(get_brand_index(brandNameA) == -1) && !(get_brand_index(brandNameB) == -1)) {
		brand_adjacency_matrix[get_brand_index(brandNameA)][get_brand_index(brandNameB)] = 0;
		brand_adjacency_matrix[get_brand_index(brandNameB)][get_brand_index(brandNameA)] = 0;
	}
}


// Harder ones
/**TODO: Complete this function
 * Returns a suggested friend for the given user, returns NULL on failure.
 * See the handout for how we define a suggested friend.
 **/
User* get_suggested_friend(User* user) { //fail if no suggested user in allUsers, user not in allUsers
  //compare most commons and return last one alphabetically
  if (user != NULL && in_friend_list(allUsers, user)) {
    User *suggested = NULL;
    int most = 0;
    int commonness = 0;
    for (FriendNode *cur = allUsers; cur != NULL; cur = cur -> next) {
      if (user != cur -> user && !in_friend_list(user -> friends, cur -> user)) {
        commonness = 0;
        for (BrandNode *current = user -> brands; current != NULL; current = current -> next) {
          if (in_brand_list(cur -> user -> brands, current -> brand_name)) {
            commonness++;
          }
        }
        if (commonness > most) {
          most = commonness;
          suggested = cur -> user;
        }
        else if (commonness == most && (suggested == NULL || strcmp(cur -> user -> name, suggested -> name) > 0)) {
          suggested = cur -> user;
        }
      }
    }
    return suggested;
  }
  return NULL;
}

/**TODO: Complete this function
 * Friends n suggested friends for the given user.
 * See the handout for how we define a suggested friend.
 * Returns how many friends were successfully followed.
 **/
int add_suggested_friends(User* user, int n) {
  //start at 0, add if able to get suggested and add as friend
  int adds = 0;
  if (user == NULL) {
    return 0;
  }
  for (int r = 0; r < n; r++) {
    if (add_friend(user, get_suggested_friend(user)) == 0) {
      adds++;
    }
  }
  return adds;
}

/**TODO: Complete this function
 * Follows n suggested brands for the given user.
 * See the handout for how we define a suggested brand.     
 * Returns how many brands were successfully followed.      
 **/
int follow_suggested_brands(User* user, int n) {
  //similar process as above but with brands
  int adds = 0;
  int connectedness = 0;
  int most = 0;
  char suggested[MAX_STR_LEN];
  if (user == NULL) {
    return 0;
  }
  for (int r = 0; r < n; r++) {
    strcpy(suggested, "");
    for (int i = 0; i < MAT_SIZE; i++) {
      if (!in_brand_list(user -> brands, brand_names[i]) && get_brand_index(brand_names[i]) != -1) {
        connectedness = 0;
        for (BrandNode *b = user -> brands; b != NULL; b = b -> next) {
          if (get_brand_index(b -> brand_name) != -1) {
            connectedness += brand_adjacency_matrix[get_brand_index(brand_names[i])][get_brand_index(b -> brand_name)];
          }
        }
        if (connectedness > most) {
          most = connectedness;
          strcpy(suggested, brand_names[i]);
        }
        else if (connectedness == most && (strcmp(suggested, "") == 0 || strcmp(brand_names[i], suggested) > 0)) {
          strcpy(suggested, brand_names[i]);
        }
      }
    }
    if (follow_brand(user, suggested) == 0) {
      adds++;
    }
  }
  return adds;
}