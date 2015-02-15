/**
			Tin Vo
**/

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include "Person.h"
#include "Rating.h"
#include "Matcher.h"

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::map;
using std::pair;

struct PGroup{
    Person& p;
    int group;
    PGroup(Person& p, const int group) : p(p), group(group){}
};

struct matchesName {
    string name;
    matchesName(const string& name) : name(name){}
    bool operator() (const Rating& r) { return r.personPtr->name == name; }
};

void readIn(list<Person>& capulets, list<Person>& montagues){
    
    /// variables used to load in the input
    int personCount; /// how many people there are
    list<Rating> defCapRating; /// a default rating for all capulets
    list<Rating> defMonRating; /// a default rating for all montagues
    map<string, PGroup> personMap; /// mapping a persons name to the person and group
    
    cin >> personCount; /// read in the count
    
    /// add the people to the group
    string name;
    int groupNum;
    for (size_t i = 0; i < personCount; ++i){
        cin >> name >> groupNum; /// read in our name and group
        /// get which list or rating we need based on the group
        list<Person>& group = groupNum == 1 ? capulets : montagues;
        list<Rating>& rating = groupNum == 1 ? defCapRating : defMonRating;
        group.push_back(Person(name));
        Person& ourPerson = group.back();
        PGroup pg(ourPerson, groupNum);
        personMap.insert(pair<string, PGroup>(name, pg));
        rating.push_back(Rating(&ourPerson, 0));
    }
    
    
    string line;
    string preferenceName;
    getline(cin, line); /// get a line to get into correct position
    /// i will use client as the person at the front of the list whose
    /// ratings we are adding
    for (size_t i = 0; i < personCount; ++i){
        /// get our preferences
        getline(cin, line);
        std::istringstream lis(line); /// get an input stream over our line
        lis >> name; /// our client name
        
        PGroup& pg = personMap.find(name)->second; /// find our client with the map
        Person& client = pg.p; /// our client
        list<Rating>& ratings = client.rateList; /// our client prefs
        
        /// make a copy of our default rating into our ratings using copy
        list<Rating>& defRating = pg.group == 1 ? defMonRating : defCapRating;
        std::copy(defRating.begin(), defRating.end(), std::front_inserter(ratings));
        
        /// remove our client from our default list
        client.rateList.remove_if(matchesName(client.name));
        
        int count = 0;
        /// now iterate over the preferences, and replace the default ratings
        int rating = personCount / 2;
        while (lis >> preferenceName){
            ratings.remove_if(matchesName(preferenceName));
            ratings.push_back(Rating(&personMap.find(preferenceName)->second.p, rating));
            rating--;
            count++;
        }
        
        /// remove person with rate 0, and push back to the rate list (to the end)
        vector<Rating> zeroRates;
        for (list<Rating>::iterator iter = ratings.begin(); iter != ratings.end(); ++iter) {
            if (iter->score == 0)
                zeroRates.push_back(*iter);
        }
        
        for (int i = 0; i < (personCount / 2) - count; i++) {
            Rating temp = zeroRates[i];
            ratings.remove_if(matchesName(temp.personPtr->name));
            ratings.push_back(Rating(&personMap.find(temp.personPtr->name)->second.p, 0));
        }
        
        /// could also you this
        /*for (int i = (personCount / 2) - count - 1; i >= 0; i--) {
            Rating temp = zeroRates[i];
            ratings.remove_if(matchesName(temp.personPtr->name));
            ratings.push_back(Rating(&personMap.find(temp.personPtr->name)->second.p, 0));
        } */
        
    }
}

int main(int argc, char const *argv[])
{
    list<Person> capulets; /// capulets
    list<Person> montagues; /// montagues
    readIn(capulets, montagues); /// will fill in the provided lists
    
    // Print out the results
    Matcher match = Matcher(capulets.size());
    map<const Person*, const Person*> m = match.stableMatch(capulets, montagues);
    for (map<const Person*, const Person*>::iterator iter = m.begin(); iter != m.end(); ++iter){
        cout << iter->first->name << " " << iter->second->name << endl;
    }
    return 0;
}