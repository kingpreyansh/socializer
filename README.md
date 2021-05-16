<h1>Socializer. Social Media Network Visualized.</h1>

Socializer is an C-based application that is used to visualize how a basic social media network works by keeping meaningful information of users such as followers, followings, brand preferences, and user description. This data is then used to dynamically suggest other users that may have similar interests or mutual friends. The data is represented in the form of an adjacency list where the brands are parsed from a .txt file containing a matrix like the following:

A, D, C, B

0, 0, 0, 1

0, 0, 0, 0

0, 0, 0, 1

1, 0, 1, 0


The following functionalities exist:
  1) Getting the degree of connection (the shortest path between two nodes using Queues)
  2) Suggested friends based on the user's data
  3) Suggested brands based on what brands the user already follows
  4) Getting mutual friends
