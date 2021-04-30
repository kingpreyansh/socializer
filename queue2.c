typedef struct QueueNode{
  char name[MAX_STR_LEN];
  struct QueueNode *next;
  int index; //relative to all users
}q_node;

typedef struct Queue{
    q_node *head;
    q_node *tail;
}Queue;

int get_index_from_all_users(char *name){
  FriendNode *curr = allUsers;
  if (curr == NULL){
    return -1;
  }
  int i = 0;
  while (curr != NULL){
    if (strcmp(curr->user->name, name) == 0){
      return i;
    }
    i++;
    curr = curr->next;
  }
  return -1;
  
}

void enqueue(Queue *myQueue, char *name){
    //first in first out
    //insert at tail
    q_node *new_node = (q_node *) calloc(1, sizeof(q_node));
    strcpy(new_node -> name, name);
    new_node->index = get_index_from_all_users(name);
    new_node->next = NULL;
    if (myQueue -> head == NULL){
        myQueue -> head = new_node;
        myQueue -> tail = new_node;
    }
    else {
        myQueue -> tail -> next = new_node;
        myQueue -> tail = new_node;
    }

    
}
FriendNode *get_user(char *name){
  FriendNode *curr = allUsers;
  if (curr == NULL){
    return NULL;
  }
  while (curr != NULL){
    if (strcmp(curr->user->name,name) == 0){
      return curr;
    }
    curr = curr -> next;
  }
  return NULL;
}
FriendNode *dequeue (Queue *myQueue){
    //first in first out, remove head and arrange for linked list to still be linked
    q_node *temp = NULL;
    temp = myQueue -> head;
    FriendNode *return_me = get_user(temp->name);
    myQueue -> head = myQueue -> head -> next;
    free (temp);
    return return_me;
}
bool is_queue_empty(Queue *MyQueue){
  return MyQueue->head == NULL;
}

void set_visited_false(){
  FriendNode *curr = allUsers;
  if(curr == NULL){
    return;
  }
  while(curr != NULL){
    curr->user->visited = false;
    curr = curr -> next;
  }
  return;
}
int len_all_users(){
  FriendNode *curr = allUsers;
  int result;
  if (curr == NULL){
    result = 0;
  }
  int i = 0;
  while (curr != NULL){
    i++;
    curr = curr -> next;
  }
  result = i;
  return i;
}

void fill_arr(int *arr, int arr_len){
  for (int i = 0; i < arr_len; i++){
    *(arr + i) = -1;
  }
  return;
}

int get_degrees_of_connection(User* a, User* b){
  // int degree = 0;
  int result;
  if (a == NULL || b == NULL || !in_friend_list(allUsers, a) || !in_friend_list(allUsers,b)){
     return -1;
  }

  int distances[len_all_users()];

  fill_arr(distances, len_all_users());

  Queue *unchecked_nodes = (Queue *) calloc(1, sizeof(Queue));
  unchecked_nodes->head = NULL;
  unchecked_nodes->tail = NULL;
  enqueue(unchecked_nodes, a->name);

  int start_id = get_index_from_all_users(a->name);
  distances[start_id] = 0;

  while (!is_queue_empty(unchecked_nodes)){
    FriendNode *curr_node = dequeue(unchecked_nodes);
    FriendNode *curr_friend = curr_node->user->friends;
    while(curr_friend != NULL){
      if (distances[get_index_from_all_users(curr_friend->user->name)] == -1 && curr_friend->user->visited == false){
        distances[get_index_from_all_users(curr_friend->user->name)] = distances[get_index_from_all_users(curr_node->user->name)] + 1;
        curr_node->user->visited = true;
        enqueue(unchecked_nodes, curr_friend->user->name);
      }
      curr_friend = curr_friend->next;
    }
  }
  result = distances[get_index_from_all_users(b->name)];
  free(unchecked_nodes);
  set_visited_false();
  return result;
}