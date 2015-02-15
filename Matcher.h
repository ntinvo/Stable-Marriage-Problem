/**
			Tin Vo
**/

#ifndef MATCHER_H
#define	MATCHER_H
#include "Person.h"
#include "Rating.h"
#include <string>
#include <map>
#include <list>

using namespace std;

class Matcher {
public:
	int numPairs;
	Matcher(int);
	map<const Person*, const Person*> stableMatch(const list<Person>&, const list<Person>&);
};
#endif	/* MATCHER_H */

