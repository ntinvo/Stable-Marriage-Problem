/**
			Tin Vo
**/

#include "Rating.h"

// Empty Rating constructor
Rating::Rating() {}

// Constructor for Rating class 
Rating::Rating(Person* personPtr, int score): personPtr(personPtr), score(score) {}
