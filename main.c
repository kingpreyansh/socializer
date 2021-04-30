#include "graffit.c"

/** 
 * Here's some basic testing code. It's primarily intended to give you an idea of
 * how these functions are used.
 *
 * As always, you should add more tests.
 */
int main() { 
    // Users & Brands
    User* angela = create_user("Angela");
    User* brian = create_user("Brian");
    add_friend(angela, brian);
    int deg = get_degrees_of_connection(brian, angela);
    printf("DEGREE IS %d\n", deg);

    // test #1 - check if correct users are added to allUsers
    int has_angela = 0;
    int has_brian = 0;
    FriendNode *p = allUsers;
    while (p) {
        if (strcmp(p->user->name, "Angela") == 0) has_angela = 1;
        if (strcmp(p->user->name, "Brian") == 0) has_brian = 1;
        if (has_brian && has_angela) break;
        p = p->next;
    }
    if (has_brian && has_angela) printf("Test #1 passed.\n");
    else {
        printf("Test #1 failed. Angela or Brian was not inserted properly in allUsers\n");
        return 1;
    }

    // test #2 - check if angela and brian are friends
    add_friend(angela, brian);

    // Expect to see Angela with her friend Brian
    if (in_friend_list(angela->friends, brian) && in_friend_list(brian->friends, angela)) printf("Test #2 passed.\n");
    else {
        printf("Test #2 failed. Angela is not a friend of Brian or Brian is not a friend of Angela or both\n");
        return 1;
    }

    print_user_data(angela); 
    // Expect to see Brian with his friend Angela
    print_user_data(brian); 

    // test #3 - check the degree of angela and brian
    int angela_and_brian = get_degrees_of_connection(angela, brian);
    // Expect 1
    if (angela_and_brian == 1) printf("Test #3 passed.\n");
    else {
        printf("Test #3 failed. Expected Degree: 1, Recieved Degree: %d\n", angela_and_brian);
        return 1;
    }

    populate_brand_matrix("brands.txt");
    printf("Connections between Angela and Brian: %d\n", angela_and_brian);

    // test #4 - check if angela is following brandonRufino
    follow_brand(angela, "brandonRufino"); 
    // Angela should now follow brandonRufino.
    if (in_brand_list(angela->brands, "brandonRufino")) printf("Test #4 passed.\n");
    else {
        printf("Test #4 failed. Angela is not following brandonRufino.\n");
        return 1;
    }
	// Brandon was a TA for this course and there's a pun too good to give up.
    print_user_data(angela); 
    print_brand_data("brandZero"); // Similar to brandonRufino
    print_brand_data("brandonRufino"); // Similar to brandZero
    print_brand_data("brandTwo"); // Not similar to anything

    // test #5 - check if brandZero is similar to brandTwo
    connect_similar_brands("brandZero", "brandTwo");
    if (brand_adjacency_matrix[get_brand_index("brandZero")][get_brand_index("brandTwo")] \
        && brand_adjacency_matrix[get_brand_index("brandZero")][get_brand_index("brandTwo")]) printf("Test #5 passed.\n");
    else {
        printf("Test #5 failed. brandZero and brandTwo were not connected properly\n");
        return 1;
    }

    print_brand_data("brandZero"); // Similar to brandonRufino and brandTwo
    print_brand_data("brandonRufino"); // Similar to brandZero
    print_brand_data("brandTwo"); // Simlar to brandZero

    // test #6 - check if Will was created properly
	User* will = create_user("Will");
    int has_will = 0;
    p = allUsers;
    while (p) {
        if (strcmp(p->user->name, "Will") == 0) has_will = 1;
        if (has_will) break;
        p = p->next;
    }
    if (has_brian && has_angela) printf("Test #6 passed.\n");
    else {
        printf("Test #6 failed. Will was not inserted properly in allUsers\n");
        return 1;
    }

    // test #7 - check if angela and will are friends
    add_friend(angela, will);
    if (in_friend_list(angela->friends, will) && in_friend_list(will->friends, angela)) printf("Test #7 passed.\n");
    else {
        printf("Test #7 failed. Angela is not a friend of Will or Will is not a friend of Angela or both\n");
        return 1;
    }


	print_user_data(will); // Expect to see Will with his friend Angela

    // test #8 - check if there exists 1 mutual friend between brian and will
	int mutuals_brian_will = get_mutual_friends(brian, will); // Expect 1
    if (mutuals_brian_will) printf("Test #8 passed.\n");
    else {
        printf("Test #8 failed. Expected number of mutual friends: 1, Recieved number of mutual friends: %d\n", mutuals_brian_will);
        return 1;
    }
    // Last Part

    // test #9 - check if will is brian's suggested friend
    // This should return Will
    User* brianSuggested = get_suggested_friend(brian);
    if (strcmp(brianSuggested->name, "Will") == 0) printf("Test #9 passed.\n");
    else {
        printf("Test #9 failed. Expected name: Will, Recieved name: %s\n", brianSuggested->name);
        return 1;
    }
    print_user_data(brianSuggested); // We should see Will here again

    // test #10 - check if mustafa's suggested friends are angela brian and will and are friends with them
    User* mustafa = create_user("Mustafa");
    add_friend(angela, mustafa); // complete test
    add_suggested_friends(mustafa, 2);
    int count = 0;
    FriendNode *mustafa_friends_list_temp = mustafa->friends;
    while (mustafa_friends_list_temp) {
        count++;
        mustafa_friends_list_temp = mustafa_friends_list_temp->next;
    }
    // Expect to see Mustafa with friends Angela, Brian, and Will
    print_user_data(will); // Expect to see Will with his friend Angela
    print_user_data(mustafa); // Expect to see Will with his friend Angela
    print_user_data(angela); // Expect to see Will with his friend Angela
    print_user_data(brian); // Expect to see Will with his friend Angela

    if (count != 3) {
        printf("Test #10 failed. Mustafa has an incorrect number of friends. Expected number of friends: 3, Received number of friends: ");
    } 
    if (in_friend_list(mustafa->friends, brian) && in_friend_list(mustafa->friends, will)) {
        printf("Test #10 passed.\n");
    } else {
        printf("Test #10 failed. Brian and Will were not suggested\n");
        return 1;
    }
    print_user_data(mustafa);

    // printing current matrix
    for (int i=0; i<MAT_SIZE; i++) {
        for (int j=0; j<MAT_SIZE; j++) {
            printf("%d ", brand_adjacency_matrix[i][j]);
        }
        printf("\n");
    }

    // test #11 - check if mustafa was suggested brandonRufino
    follow_brand(will, "brandTwo");
    follow_brand(mustafa, "brandZero"); 
    follow_suggested_brands(mustafa, 1);
    print_user_data(mustafa); // Mustafa should now also follow brandonRufino
    if (in_brand_list(mustafa->brands, "brandonRufino")) {
        printf("Test #11 passed.\n");
    } else {
        printf("Mustafa was not suggested brandonRufino\n");
        return 1;
    }

    // Rigerous tests

    // check allUsers count and users in allUsers
    FriendNode *allUsers_temp = allUsers;
    count = 0;
    while (allUsers_temp) {
        count++;
        allUsers_temp = allUsers_temp->next;
    }

    if (count != 4) {
        printf("allUsers does not have the right amount of users. Expected 4 users, Recieved: %d\n", count);
        return 1;
    }
    printf("Specific test #1 passed.\n");

    if (!in_friend_list(allUsers, angela) && !in_friend_list(allUsers, angela) && !in_friend_list(allUsers, angela) && !in_friend_list(allUsers, angela)) {
        printf("Some or All users were not added properly to allUsers list.\n");
        return 1;
    }
    printf("Specific test #2 passed.\n");

    // check adjacency matarix
    int brandZero_index = get_brand_index("brandZero");
    int brandonRufino_index = get_brand_index("brandonRufino");
    int brandTwo_index = get_brand_index("brandTwo");

    if (brand_adjacency_matrix[brandZero_index][brandZero_index] != 0) printf("brand adjacency matrix incorrect.\n");
    if (brand_adjacency_matrix[brandZero_index][brandonRufino_index] != 1) printf("brand adjacency matrix incorrect.\n");
    if (brand_adjacency_matrix[brandZero_index][brandTwo_index] != 1) printf("brand adjacency matrix incorrect.\n");
    if (brand_adjacency_matrix[brandonRufino_index][brandZero_index] != 1) printf("brand adjacency matrix incorrect.\n");
    if (brand_adjacency_matrix[brandonRufino_index][brandonRufino_index] != 0) printf("brand adjacency matrix incorrect.\n");
    if (brand_adjacency_matrix[brandonRufino_index][brandTwo_index] != 0) printf("brand adjacency matrix incorrect.\n");
    if (brand_adjacency_matrix[brandTwo_index][brandZero_index] != 1) printf("brand adjacency matrix incorrect.\n");
    if (brand_adjacency_matrix[brandTwo_index][brandonRufino_index] != 0) printf("brand adjacency matrix incorrect.\n");
    if (brand_adjacency_matrix[brandTwo_index][brandTwo_index] != 0) printf("brand adjacency matrix incorrect.\n");
    printf("Specific test #3 passed.\n");

    // testing edge cases
    User *local = create_user("Local");
    User *walter = create_user("Walter");
    User *baljeet = create_user("Baljeet");
    User *stewie = create_user("Stewie");
    User *yerrrr = create_user("Yerrrr");
    User *anikami = create_user("Anikami");
    User *atlanta = create_user("Atlanta");
    User *ming = create_user("Ming");
    User *giannis = create_user("Giannis");
    add_friend(local, local);
    add_friend(local, walter);
    add_friend(local, baljeet);
    add_friend(local, stewie);
    add_friend(local, yerrrr);
    add_friend(local, anikami);
    add_friend(local, atlanta);
    add_friend(local, ming);
    add_friend(local, giannis);

    if (!in_friend_list(local->friends, walter)) {
        printf("Walter was not added to local's friends properly.\n");
        return 1;
    }

    if (in_friend_list(local->friends, local)) {
        printf("Local is a friend of himself. Cannot be possible.\n");
        return 1;
    }
    printf("Specific test #4 passed.\n");

    printf("Expecting User not in list: \n");
    remove_friend(local, local);
    remove_friend(local, walter);

    if (in_friend_list(local->friends, walter)) {
        printf("Walter is still Local's friend. Not removed properly\n");
        return 1;
    }
    printf("Specific test #5 passed.\n");

    User *nulled_user = create_user(NULL);
    if (nulled_user) {
        printf("Created a user with a NULL username. Cannot have a NULL username.\n");
        return 1;
    }
    printf("Specific test #6 passed.\n");

    User *nulled_user1 = create_user("");
    if (nulled_user1) {
        printf("Created a user for empty string. Not allowed.\n");
        return 1;
    }
    printf("Specific test #7 passed.\n");

    follow_brand(local, "brandZero");
    follow_brand(local, "brandonRufino");
    follow_brand(local, "brandTwo");

    if (!in_brand_list(local->brands, "brandZero") && !in_brand_list(local->brands, "brandonRufino") && !in_brand_list(local->brands, "brandTwo")) {
        printf("Local did not follow the brands properly.\n");
        return 1;
    }
    printf("Specific test #8 passed.\n");

    unfollow_brand(local, "brandZero");
    unfollow_brand(local, "brandonRufino");
    unfollow_brand(local, "brandTwo");

    if (in_brand_list(local->brands, "brandZero") || in_brand_list(local->brands, "brandonRufino") || in_brand_list(local->brands, "brandTwo")) {
        printf("Local did not unfollow the brands properly.\n");
        return 1;
    }
    printf("Specific test #9 passed.\n");

    follow_brand(local, "brandTwos");
    if (in_brand_list(local->brands, "brandTwos")) {
        printf("Local followed an invalid brand.\n");
        return 1;
    }
    printf("Specific test #10 passed.\n");

    // local is friends with everyone
    add_friend(local, local);
    add_friend(local, walter);
    add_friend(local, baljeet);
    add_friend(local, stewie);
    add_friend(local, yerrrr);
    add_friend(local, anikami);
    add_friend(local, atlanta);
    add_friend(local, ming);
    add_friend(local, giannis);

    // stewie is friends with everyone
    add_friend(stewie, local);
    add_friend(stewie, walter);
    add_friend(stewie, baljeet);
    add_friend(stewie, stewie);
    add_friend(stewie, yerrrr);
    add_friend(stewie, anikami);
    add_friend(stewie, atlanta);
    add_friend(stewie, ming);
    add_friend(stewie, giannis);

    // walter is friends with everyone
    add_friend(walter, local);
    add_friend(walter, walter);
    add_friend(walter, baljeet);
    add_friend(walter, stewie);
    add_friend(walter, yerrrr);
    add_friend(walter, anikami);
    add_friend(walter, atlanta);
    add_friend(walter, ming);
    add_friend(walter, giannis);

    // baljeet is friends with everyone
    add_friend(baljeet, local);
    add_friend(baljeet, walter);
    add_friend(baljeet, baljeet);
    add_friend(baljeet, stewie);
    add_friend(baljeet, yerrrr);
    add_friend(baljeet, anikami);
    add_friend(baljeet, atlanta);
    add_friend(baljeet, ming);
    add_friend(baljeet, giannis);

    // yerrrr is friends with everyone
    User *temp_user = yerrrr;
    add_friend(temp_user, local);
    add_friend(temp_user, walter);
    add_friend(temp_user, baljeet);
    add_friend(temp_user, stewie);
    add_friend(temp_user, yerrrr);
    add_friend(temp_user, anikami);
    add_friend(temp_user, atlanta);
    add_friend(temp_user, ming);
    add_friend(temp_user, giannis);

    // anikami is friends with everyone
    temp_user = anikami;
    add_friend(temp_user, local);
    add_friend(temp_user, walter);
    add_friend(temp_user, baljeet);
    add_friend(temp_user, stewie);
    add_friend(temp_user, yerrrr);
    add_friend(temp_user, anikami);
    add_friend(temp_user, atlanta);
    add_friend(temp_user, ming);
    add_friend(temp_user, giannis);

    // atlanta is friends with everyone
    temp_user = atlanta;
    add_friend(temp_user, local);
    add_friend(temp_user, walter);
    add_friend(temp_user, baljeet);
    add_friend(temp_user, stewie);
    add_friend(temp_user, yerrrr);
    add_friend(temp_user, anikami);
    add_friend(temp_user, atlanta);
    add_friend(temp_user, ming);
    add_friend(temp_user, giannis);

    // ming is friends with everyone
    temp_user = ming;
    add_friend(temp_user, local);
    add_friend(temp_user, walter);
    add_friend(temp_user, baljeet);
    add_friend(temp_user, stewie);
    add_friend(temp_user, yerrrr);
    add_friend(temp_user, anikami);
    add_friend(temp_user, atlanta);
    add_friend(temp_user, ming);
    add_friend(temp_user, giannis);

    // giannis is friends with everyone
    temp_user = giannis;
    add_friend(temp_user, local);
    add_friend(temp_user, walter);
    add_friend(temp_user, baljeet);
    add_friend(temp_user, stewie);
    add_friend(temp_user, yerrrr);
    add_friend(temp_user, anikami);
    add_friend(temp_user, atlanta);
    add_friend(temp_user, ming);
    add_friend(temp_user, giannis);

    int num_of_stews_and_local_mutual_friends = get_mutual_friends(stewie, local);
    int num_of_stews_and_walter_mutual_friends = get_mutual_friends(stewie, walter);
    int num_of_stews_and_baljeet_mutual_friends = get_mutual_friends(stewie, baljeet);
    int num_of_stews_and_stewie_mutual_friends = get_mutual_friends(stewie, stewie);
    int num_of_stews_and_yerrrr_mutual_friends = get_mutual_friends(stewie, yerrrr);
    int num_of_stews_and_anikami_mutual_friends = get_mutual_friends(stewie, anikami);
    int num_of_stews_and_atlanta_mutual_friends = get_mutual_friends(stewie, atlanta);
    int num_of_stews_and_ming_mutual_friends = get_mutual_friends(stewie, ming);
    int num_of_stews_and_giannis_mutual_friends = get_mutual_friends(stewie, giannis);


    if (num_of_stews_and_local_mutual_friends != 7) {
        printf("Number of Stewie and Local's mutual friends: %d, Expected: 7.\n", num_of_stews_and_local_mutual_friends);
        return 1;
    }
    printf("Specific test #11 passed.\n");

    if (num_of_stews_and_walter_mutual_friends != 7) {
        printf("Number of Stewie and Walter's mutual friends: %d, Expected: 7.\n", num_of_stews_and_local_mutual_friends);
        return 1;
    }
    printf("Specific test #12 passed.\n");

    if (num_of_stews_and_baljeet_mutual_friends != 7) {
        printf("Number of Stewie and Baljeet's mutual friends: %d, Expected: 7.\n", num_of_stews_and_local_mutual_friends);
        return 1;
    }
    printf("Specific test #13 passed.\n");

    if (num_of_stews_and_stewie_mutual_friends != 8) {
        printf("Number of Stewie and Stewie's mutual friends: %d, Expected: 8.\n", num_of_stews_and_local_mutual_friends);
        return 1;
    }
    printf("Specific test #14 passed.\n");

    if (num_of_stews_and_yerrrr_mutual_friends != 7) {
        printf("Number of Stewie and Yerrrr's mutual friends: %d, Expected: 7.\n", num_of_stews_and_local_mutual_friends);
        return 1;
    }
    printf("Specific test #15 passed.\n");

    if (num_of_stews_and_anikami_mutual_friends != 7) {
        printf("Number of Stewie and Anikami's mutual friends: %d, Expected: 7.\n", num_of_stews_and_local_mutual_friends);
        return 1;
    }
    printf("Specific test #16 passed.\n");

    if (num_of_stews_and_atlanta_mutual_friends != 7) {
        printf("Number of Stewie and Atlanta's mutual friends: %d, Expected: 7.\n", num_of_stews_and_local_mutual_friends);
        return 1;
    }
    printf("Specific test #17 passed.\n");

    if (num_of_stews_and_ming_mutual_friends != 7) {
        printf("Number of Stewie and Ming's mutual friends: %d, Expected: 7.\n", num_of_stews_and_local_mutual_friends);
        return 1;
    }
    printf("Specific test #18 passed.\n");

    if (num_of_stews_and_giannis_mutual_friends != 7) {
        printf("Number of Stewie and Giannis's mutual friends: %d, Expected: 7.\n", num_of_stews_and_local_mutual_friends);
        return 1;
    }
    printf("Specific test #19 passed.\n");

    int num_of_NULL_mutual_friends = get_mutual_friends(NULL, NULL);
    if (num_of_NULL_mutual_friends) {
        printf("Null check failed. Expected: 0 mutual friends, Recieved: %d mutual friends.\n", num_of_NULL_mutual_friends);
        return 1;
    }
    printf("Specific test #20 passed.\n");

    // deleting all users
    delete_user(stewie);
    delete_user(walter);
    delete_user(local);
    delete_user(baljeet);
    delete_user(atlanta);
    delete_user(anikami);
    delete_user(yerrrr);
    delete_user(giannis);
    delete_user(ming);
    delete_user(will);
    delete_user(angela);
    delete_user(mustafa);
    delete_user(brian);

    // checing if any user is in the global users list
    int true1 = in_friend_list(allUsers, stewie);
    int true2 = in_friend_list(allUsers, yerrrr);
    int true3 = in_friend_list(allUsers, atlanta);
    int true4 = in_friend_list(allUsers, walter);
    int true5 = in_friend_list(allUsers, baljeet);
    int true6 = in_friend_list(allUsers, ming);
    int true7 = in_friend_list(allUsers, anikami);
    int true8 = in_friend_list(allUsers, giannis);
    int true9 = in_friend_list(allUsers, angela);
    int true10 = in_friend_list(allUsers, will);
    int true11 = in_friend_list(allUsers, brian);
    int true12 = in_friend_list(allUsers, mustafa);
    int true13 = true1 && true2 && true3 && true4 && true5;
    int true14 = true6 && true7 && true8 && true9 && true10;
    int true15 = true11 && true12;
    int true16 = true13 && true14 && true15;

    if (true16) {
        printf("Did not delete users properly.\n");
        return 1;
    }
    printf("Specific test #21 passed.\n");

    User *x = create_user("x");
    User *y = create_user("y");
    User *z = create_user("z");

    add_friend(x, y);
    add_friend(y, z);

    int degree_of_x_and_z = get_degrees_of_connection(x, z);
    if (degree_of_x_and_z != 2) {
        printf("degree of x and z were not correct. Expected: 2, Recieved: %d\n", degree_of_x_and_z);
        return 1;
    }

    remove_friend(x, y);

    degree_of_x_and_z = get_degrees_of_connection(x, z);
    if (degree_of_x_and_z != -1) {
        printf("expected degree: -1, received degree: %d\n", degree_of_x_and_z);
        return 1;
    }
    printf("------------------------------------\n");
    User* angela1 = create_user("Angela1");
    User* brian1 = create_user("Brian1");
    User* man = create_user("man");
    User* man2 = create_user("man2");
    User* man3 = create_user("man3");
    User* man4 = create_user("man4");
    User* man5 = create_user("man5");
    add_friend(angela1, brian1);
    add_friend(angela1, man);
    add_friend(angela1, man2);
    add_friend(angela1, man3);
    add_friend(angela1, man4);
    add_friend(man, man5);
    // Expect to see Angela with her friend Brian
    print_user_data(angela1); 
    
    // Expect to see Brian with his friend Angela
    print_user_data(brian1);
    int angela_and_brian1 = get_degrees_of_connection(angela1, brian1);
    int angela_and_man5 = get_degrees_of_connection(angela1, man5);
    printf("angela and brian: %d, expected: 1\nangela and man5: %d, expected: 2\n", angela_and_brian1, angela_and_man5);
    printf("------------------------------------\n");
    User* q = create_user("Q");
    User* r = create_user("R");
    User* s = create_user("S");
    User* f = create_user("F");
    User* g = create_user("G");
    User* i = create_user("I");
    User* j = create_user("J");
    User* l = create_user("L");
    User* m = create_user("M");
    User* n = create_user("N");
    User* o = create_user("O");
    User* P = create_user("P");
    User* h = create_user("H");
    User* t = create_user("T");
    User* u = create_user("U");
    User* a = create_user("A");
    User* b = create_user("B");
    User* c = create_user("C");
    User* d = create_user("D");
    User* e = create_user("E");
    User* k = create_user("K");
    User* v = create_user("V");
    add_friend(a, n);
    add_friend(a, m);
    add_friend(d, l);
    add_friend(d, j);
    add_friend(e, h);
    add_friend(l, h);
    add_friend(g, i);
    add_friend(n, k);
    add_friend(f, c);
    add_friend(d, c);
    add_friend(b, k);
    add_friend(g, i);
    add_friend(s, t);
    add_friend(f, P);
    add_friend(v, e);
    add_friend(q, g);
    add_friend(f, r);
    add_friend(u, r);
    add_friend(o, i);
    add_friend(g, t);
    add_friend(c, q);
    add_friend(s, u);
    add_friend(m, b);
    add_friend(j, v);
    add_friend(o, P);
    add_friend(o, s);
    printf("degree: %d, expected: 5\n", get_degrees_of_connection(g, v));
    
    //delete_user(angela);
    User* angela111 = create_user("Angela11");
    //delete_user(brian);
    User* brian111 = create_user("Brian11");

    User* man11 = create_user("Man");
    User* man12 = create_user("Man2");
    User* man13 = create_user("Man3");
    User* man14 = create_user("Man4");
    User* man15 = create_user("Man5");
    add_friend(angela111, brian111);
    add_friend(brian111, man11);
    add_friend(man11, man12);
    add_friend(man12, man13);
    add_friend(man13, man14);
    add_friend(man14, man15);
    // Expect to see Angela with her friend Brian
    print_user_data(angela111); 
    // Expect to see Brian with his friend Angela
    print_user_data(brian111); 
    int angela_and_brian11 = get_degrees_of_connection(angela111, brian111);
    int angela_and_man15 = get_degrees_of_connection(angela111, man15);
    printf("angela and brian: %d, expected: 1\nangela and man5: %d, expected: 6\n", angela_and_brian11, angela_and_man15);

    printf("Completed.\n");
}
