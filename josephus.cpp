#include "stdafx.h"
#include <iostream>
#include <cstdlib>
//#include <string>
using namespace std;

// node class for making our circular linked list
class node
{
public:
	int item; // in this specific case, item holds the original "position" of a node within the circle, essentially it's just a number for which spot the node is in
	node *next; // holds a reference to the next node that this node connects to

	node(int x, node *t) // our constructor which takes in the placement number of our person and another node to represent who hes standing next to
	{
		item = x; // our constructor takes in an int called x and assigns item to it
		next = t; // since t was our first node, each new node connects to the first which gives us a circle
	}
};

typedef node *link; // with this, we can create nodes using our newly made keyword link! 

/* Pay no attention to this, I'm just having fun with typedef for practice :D

typedef string confused;
confused code = "confused";
typedef string i_promise;
i_promise i_am_not = "confused";

*/

// Precondition: the numbers we take in must be > 0
// Postcondition: we return the final survivor after counting N times in a circle and eliminating until one node is left
int Josephus(int N, int M) // we're taking in N for the number of people in our circle and M will represent the Mth person we eliminate. 
{
	int i; // for use by our loops
	link t = new node(1, 0); // our first person, holding the value of 1, linked to noone
	t->next = t; // since noone is next to him, we basically say "you're next to yourself, so you're the only one here". this is done simply as a starting point.
	link x = t; // keeps track of who is elimated. currently, the only player is t so we set x = t

	// this loop builds our circle with players and assigns them placement values
	for (i = 2; i <= N; i++) // we're going to iterate through the number of people we're adding to the circle
	{
		x = (x->next = new node(i, t)); // x->next is now being set to a new node, we pass in i which holds the placement number of our new person and we pass in t for him to stand next to
	}									// finally, x is being assigned to x->next which was JUST assigned our new player. 

	while (x != x->next) // checks to make sure there are more than 1 player, if x is equal to x->next then we have 1 node with nothing connected to it
	{
		for (i = 1; i < M; i++) // we begin at 1 and iterate until M, this way x will always be 1 node behind the node to be eliminated. 
		{
			x = x->next; // through each iteration, we move x around the circle until we hit our limit of M passes. after this loop completes itself, x will be right BEFORE the node to be eliminated
		}

		x->next = x->next->next; // x is currently 1 node behind the node to be eliminated, so we say "hey x, your next node is going to be the one the node next to you is pointing to.". This effectively removes the node from the chain while still keeping everything linked
	}
	return x->item; // finally, we return the data inside the last node
}

int main(int argc, char *argv[])
{
	int people, number; // used to store the amount of people we want in our circle, whereas number represents the amount of times we count around the circle before we eliminate a node
	cout << "How many people are playing?: ";
	cin >> people;
	cout << "Elimate the Nth person: ";
	cin >> number;
	cout << "The last survivor is: " << Josephus(people, number) << endl; // calling our method and outputting the result, which gives us the data in our final survivor
    return 0;
}

