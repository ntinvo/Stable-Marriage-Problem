/**
			Tin Vo
**/

#include "Person.h"

// Constructor for Person class
Person::Person(string name): name(name) {}

// Return Rating for people in the Rate List
Rating Person::getRate(string name) {
	Rating temp;
	list<Rating>::const_iterator it;
	for (it = Person::rateList.begin(); it != Person::rateList.end(); it++) {
		temp = *it;
		if (temp.personPtr->name == name) {
			return temp;
		}
	}
	return temp;
}
