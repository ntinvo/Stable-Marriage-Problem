/**
			Tin Vo
**/

#include "Person.h"
#include "Matcher.h"
#include "Rating.h"
#include <set>
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;
class Person;

// Matcher constructor with numPairs
Matcher::Matcher(int numPairs): numPairs(numPairs) {}

// Find the stable matches for the two lists(capulets and montagues)
map< const Person*, const  Person*> Matcher::stableMatch(const list<Person>& capulets, const list<Person>& montagues) {
	map<const Person*, const Person*> matches;
	set<string> notAvaiSet;
	map<string, string> pair;
	int counter = 0;
	while (counter < Matcher::numPairs) {
        const Person* man;
		// iterate and pick any person that's available	
		for (list<Person>::const_iterator it = montagues.begin(); it != montagues.end(); it++) {
            man = &*it;
            if (notAvaiSet.find(man->name) == notAvaiSet.end())
				break;
		}
		// iterate through the refer list
        list<Rating>::const_iterator it;
        for (it = man->rateList.begin(); notAvaiSet.find(man->name) == notAvaiSet.end() && it != man->rateList.end(); it++) {
			Rating tempRate = *it;
        	Person* woman = tempRate.personPtr;

			// woman is available
            if (notAvaiSet.find(woman->name) == notAvaiSet.end()){
                matches[woman] = man;
                pair[woman->name] = man->name;
                notAvaiSet.insert(man->name);
                notAvaiSet.insert(woman->name);
				counter++;
			} else {
				// get the rates of current man and partner
                Rating currManRate = woman->getRate(man->name);
                Rating partnerRate = woman->getRate(pair[woman->name]);
				// check who is referred
				if (currManRate > partnerRate) {
                    matches[woman] = man;
                    pair[woman->name] = man->name;
                    Person* partner = partnerRate.personPtr;
                    notAvaiSet.insert(man->name);
                    notAvaiSet.erase(partner->name);
				}
			}
		}
	}
    return matches;
}

