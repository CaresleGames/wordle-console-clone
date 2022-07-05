#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define size_word 5

typedef unsigned int bool;

char word[] = "Tests";
/*
 * = -> Correct letter and position
 * * -> Correct letter bad position
 * | -> Bad letter 
 */
char correct_letters[] = "*****";

// All the arrays in this program are 5 of length
void printArray(char* arr) {
	for(int i = 0; i < size_word; i++) {
		printf("%c", arr[i]);
	}
	printf("\n");
}

// returns the number of lines of a file
// each line represents a word
int get_number_lines(FILE* file) {
	if (file == NULL) return 0;
	char sentence[256];
	int n;
	while (fgets(sentence, sizeof(sentence), file) != NULL) {
		n++;
	}
	return n;
}

// the word list is fill with the word to find
void word_to_find(const char* file_to_open, char* words_list) {
	FILE* pFile;
	pFile = fopen(file_to_open, "r");
	fpos_t pos;

	fgetpos(pFile, &pos);
	int number_words = 0;
	number_words = get_number_lines(pFile);
	srand(time(NULL));
	int word_to_get = rand() % number_words; 
	char sentence[256];
	char word_from_file[6];
	int i = 0;

	fsetpos(pFile, &pos);
	while (fgets(sentence, sizeof(sentence), pFile) != NULL) {
		i++;
		if (i == word_to_get) {
			for (int j = 0; j < size_word; j++) {
				word_from_file[j] = sentence[j];
			}
		}
	}
	fclose(pFile);
	for(int i = 0; i < size_word; i++) {
		words_list[i] = word_from_file[i];
	}
}

bool check_word(char* w) {
	bool result = true;
	for(int i = 0; i < size_word; i++) {
		if (w[i] == word[i])
			correct_letters[i] = '=';
		if (w[i] != word[i]) {
			correct_letters[i] = '|';
			for (int j = 0; j < size_word; j++) {
				if (w[i] == word[j]) {
					correct_letters[i] = '*';
					break;
				}
			}
			result = false;
		}
	}
	printf("%s\n", correct_letters);
	return result;
}

int main() {
	word_to_find("words.txt", word);
	int turn = 0;
	char my_word[6];
	printf("Write the word in lowercase:\n");
	while (turn < 6) {
		printf("Select your word:\n");
		scanf("%5s", my_word);
		if (turn < 6) {
			int r = check_word(my_word);
			if (r == true) {
				printf("You win\n");
				break;
			}
		}
		turn++;
	}
	if (turn == 6) {
		printf("The answer is %s\n", word);
	}
}
