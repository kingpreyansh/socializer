#define __testing
#define MAT_SIZE 4
#include "graffit.c"

int main() { 
	User* a = create_user("a");
    User* b = create_user("b");
    User* c = create_user("c");
    User* d = create_user("d");
    User* e = create_user("e");
    User* f = create_user("f");
    //User* h = create_user("h");
    //User* i = create_user("i");
    populate_brand_matrix("sushi_brandz.txt");
    connect_similar_brands("A", "C");
    
    add_friend(a, b);
    add_friend(b, c);
    add_friend(c, d);
    add_friend(d, e);
    add_friend(e, a);
    add_friend(a, c);
    
    follow_brand(a, "A");
    follow_brand(a, "B");
    
    follow_brand(b, "A");
    follow_brand(b, "B");
    
    follow_brand(d, "A");
    follow_brand(d, "B");
    
    follow_brand(e, "A");
    follow_brand(e, "B"); 
    
    int n = get_degrees_of_connection(a, d);
    printf("degree(a, d) = expected 2, got %d\n", n); //2
    n = get_degrees_of_connection(d, d);
    printf("degree(d, d) = expected 0, got %d\n", n); //0
    
    print_brand_data("A"); //similar to B,C
	printf("^Should be C,B\n");
    print_brand_data("B"); //similar to A,C
	printf("^Should be A,C\n");
    print_brand_data("C"); //similar to A,B
	printf("^Should be A,B\n");
    print_brand_data("D"); //no one :(
	printf("^Should be no one\n");
    
    User* x = get_suggested_friend(a);
    printf("expected d, got suggested %s\n", x->name); //should be d.
    x = get_suggested_friend(b);
    printf("expected e, got suggested %s\n", x->name);   //should be e
    
    add_friend(f, a);
    follow_brand(f, "D");
    x = get_suggested_friend(f);
    printf("expected e, got suggested %s\n", x->name);   //should be e
    
    add_friend(f, e);
    x = get_suggested_friend(f);
    printf("expected d, got suggested %s\n", x->name);   //should be d
    
    follow_brand(f, "A");
    x = get_suggested_friend(f);
    printf("expected d, got suggested %s\n", x->name);   //should be d
    
    follow_brand(b, "D");
    x = get_suggested_friend(f);
    printf("expected b, got suggested %s\n", x->name);   //should be b
    
    n = get_degrees_of_connection(f, c);
    printf("degree(f, c) = expected 2, got %d\n", n); //2
    
    n = get_degrees_of_connection(b, d);
    printf("degree(b, d) = expected 2, got %d\n", n); //2
    
    User* g = create_user("g");
    
    n = get_degrees_of_connection(b, g);
    printf("degree(b, g) = expected -1, got %d\n", n); //-1
    
    n = get_degrees_of_connection(g, g);
    printf("degree(g, g) = expected 0, got %d\n", n); //0
    
    add_friend(g, a);
    
    n = delete_user(g);
    printf("Deleted user g. Result: expected 0, got %d\n", n); //should give 0
    
    n = delete_user(g);
    printf("Tried deleting user g again. Result: expected -1, got %d\n", n); //should give -1
    
    
    print_user_data(a); //a should not have g as a friend.
	printf("^Should NOT have g as friend\n");
    
    n = remove_friend(b, c);
    
    n = add_suggested_friends(b, 0);
    printf("Added this many new people: expected 0, got %d\n", n); //should be 0
    
    n = add_suggested_friends(b, -1);
    printf("Added this many new people: expected 0, got %d\n", n); //should be 0
    
    n = add_suggested_friends(b, 1);
    printf("Added this many new people: expected 1, got %d\n", n); //should be 1
    
    n = add_suggested_friends(b, 3);
    printf("Added this many new people: expected 3, got %d\n", n); //should be 3
    
    n = add_suggested_friends(b, 69);
    printf("Added this many new people: expected 0, got %d\n", n); //should be 0
    
    n = follow_suggested_brands(b, -1);
    printf("followed %d brands (should be 0)\n", n); //should be 0
    print_user_data(b); //b should follow A, B, D brands
	printf("^Should be A,B,D\n");
    
    n = follow_suggested_brands(b, 0);
    printf("followed %d brands (should be 0)\n", n); //should be 0
    print_user_data(b); //b should now follow A, B, D brands
	printf("^Should be A,B,D\n");
    
    printf("this case calls follow_suggested_brands with null user\n");
    n = follow_suggested_brands(NULL, 46);
    printf("followed %d brands (should be 0)\n", n); //should be 0

    printf("****************DEBUG**************\n");
    n = follow_suggested_brands(b, 2);
    printf("followed %d brands (should be 1)\n", n); //should be 1
    print_user_data(b); //b should now follow A, B, C, D brands
	printf("^Should be A,B,C,D\n");
    
    n = follow_suggested_brands(f, 1);
    printf("followed %d brands (should be 1)\n", n); //should be 1
    print_user_data(f); //f should follow A, C, D now
	printf("^Should be A,C,D\n");
    
    n = delete_user(NULL);
    printf("tried to delete a null person, expected -1 and got: %d\n", n);
    
    printf("\nprinting allUsers:\n");
    FriendNode* w = allUsers;
    while(w != NULL) {
		printf("%s ", w->user->name);
		w = w->next;
	}
	printf("\n");
	printf("^Should be a, b, c, d, e, f\n");
	
	delete_user(a);
	delete_user(b);
	delete_user(c);
	delete_user(d);
	delete_user(f);
	w = allUsers;
	printf("\nprinting allUsers:\n");
    while(w != NULL) {
		printf("%s ", w->user->name);
		w = w->next;
	}
	printf("\n");
	printf("^Should be e\n\n");
	
	print_user_data(e); //should have no friends now. sad
	printf("^Should have no friends (tragic) %d\n", n);
}
