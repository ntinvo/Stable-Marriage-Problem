/**
			Tin Vo
**/

#ifndef PERSON_H
#define	PERSON_H
#include <string>
#include <list>
#include "Rating.h"

using namespace std;

class Person {
public:
	list<Rating> rateList;
	string name;
	Person();
	Person(string);
	Rating getRate(string);
};
#endif	/* PERSON_H */

