/**
			Tin Vo
**/

#ifndef RATING_H
#define	RATING_H
class Person;

class Rating{
public:
	Person* personPtr;
	int score;
	Rating();
	Rating(Person*, int);

	// returns true if the current score < parameter score
	bool operator < (const Rating& person) const {
		return score < person.score;
	}

	// returns true if the current score > parameter score
	bool operator > (const Rating& person) const {
		return score > person.score;
	}

	// returns true if the current score <= parameter score
	bool operator <= (const Rating& person) const {
		return score <= person.score;
	}

	// returns true if the current score >= parameter score
	bool operator >= (const Rating& person) const {
		return score >= person.score;
	}

	// returns true if the current Node score == parameter score
	bool operator == (const Rating& person) const {
		return score == person.score;
	}
};
#endif	/* RATING_H */

