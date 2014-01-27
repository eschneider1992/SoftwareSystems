/*
* Takes in input related to card values, and calculates the goodness of a blackjack bet
* Homework 01, SoftSys 2014, Eric Schneider
*/

#include <stdio.h>
#include <stdlib.h>

/*
* Takes in the identity of a card, with mixed numbers and letters, and applies blackjack scores to the cards

* Only the first character of the input is used

* card: character array containing the identity of the card
*/
int determineVal(char card[]) {
	int val = 0;
	switch(card[0]) {
		case 'K':
		case 'Q':
		case 'J':
			val = 10;
			break;
		case 'A':
			val = 11;
			break;
		default:
			val = atoi(card);
	}
	return val;
}

/*
* Judges whether the given card value increases or decreases the chance of a good hand next round

* val; value of the given card
*/
int updateValuableCards(int val) {
	if ((val > 2) && (val < 7)) {
		return 1;
	} else if (val == 10) {
		return -1;
	}
	return 0;
}

/*
* Prompts the user for input of the played card, calculates
* how that changes blackjack odds, and loops to get next card.

* User input is truncated to the first two characters.

* card_name: buffer where result is stored
* count: Value of the goodness of a blackjack bet
*/
int main() {
	char card_name[3];
	int count = 0;
	int val = 0;
	
	while ( card_name[0] != 'X') {
		puts("Enter the card_name: ");
		scanf("%2s", card_name);
		
		if (card_name[0] == 'X')
			continue;

		val = determineVal(card_name);

		if ((val < 1) || (val > 11)) {
			puts("I do not understand that value!");
			continue;
		}

		count += updateValuableCards(val);

		printf("Current count: %i\n", count);
	}
	return 0;
}