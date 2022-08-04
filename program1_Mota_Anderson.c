//Name: Anderson Mota
//Dr. Steinberg
//COP3502C Spring 2022
//Programming Assignment 1

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIMIT 20

char ** doubleIt(char ** arr, int * maxsize);
char ** populate(char ** words, FILE * fptr, int * currentsize, int * maxsize);
char * generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize); //write sentence to console window
void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE * fptr); //write story to txt file
void displaySentence(char * sentence);
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize);

char ** populate(char ** words, FILE * fptr, int * currentsize, int * maxsize) {
  // while there are more lines in the file keep going
  while (!feof(fptr)) {
    //Allocate a word with a limit of characters
    words[ * currentsize] = malloc(LIMIT * sizeof(char));
    //Check if allocated
    if (words[ * currentsize] == NULL) {
      printf("Failed to allocate");
      exit(1);
    }

    //scan the text file	
    //Copy strings into array
    if ((fscanf(fptr, "%s", words[ * currentsize])) != -1);

    // Increment
    ( * currentsize) ++;

    //If the array is full double it
    if ( * currentsize == * maxsize) {
      //returns a doubled maxsize
      words = doubleIt(words, maxsize);
    }

  } //END OF WHILE-LOOP

  //Return with words
  return words;
} //EOF populate
char ** doubleIt(char ** arr, int * maxsize) {

  //double the original size
  int newSize = 0;
  newSize = ( * maxsize) * 2; //double

  //Allocate a new heap, twice the size for the strings (words)

  char ** newHeap = NULL;
  newHeap = malloc(sizeof(char * ) * newSize);
  //check it for failure
  if (newHeap == NULL) {
    printf("Memory was not allocated!");
    exit(1);
  }

  //For-Loop stores the strings from the old heap
  for (int i = 0; i < newSize; i++) {
    newHeap[i] = NULL;
  } //End of for
  for (int i = 0; i < * maxsize; i++) {

    newHeap[i] = malloc(LIMIT * sizeof(char));
    //Check if allocated
    if (newHeap[i] == NULL) {
      printf("Failed to allocate");
      exit(1);
    }
    //Copy strings from old to new
    strcpy(newHeap[i], arr[i]);
    //Print

    //	printf("%s", newHeap[i]);

  }
  ////Free the old heap 
  for (int j = 0; j < * maxsize; j++) {
    //Free the old heap

    free(arr[j]);
  }
  //Free the soul
  free(arr);

  //return size	
  * maxsize = ( * maxsize) * 2;
  //Return with the new heap that has the updated size and old strings
  return newHeap;

} //EOF doubleIt

char * generateSentence(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize) {

  //Allocate a sentence with a limit of 100 characters
  char * sentence = malloc(100 * sizeof(sentence));
  //check it for failure
  if (sentence == NULL) {
    printf("Failed to allocate!");
    exit(1);
  }

  strcpy(sentence, "");

  //concatenate into sentence
  strcat(sentence, article[rand() % articlesize]); // Article
  strcat(sentence, " ");
  strcat(sentence, adjective[rand() % adjsize]); // Adjective
  strcat(sentence, " ");
  strcat(sentence, noun[rand() % nounsize]); // Noun
  strcat(sentence, " ");
  strcat(sentence, verb[rand() % verbsize]); // Verb
  strcat(sentence, " ");
  strcat(sentence, preposition[rand() % prepositionsize]); // Preposition
  strcat(sentence, " ");
  strcat(sentence, article[rand() % articlesize]); // Article
  strcat(sentence, " ");
  strcat(sentence, adjective[rand() % adjsize]); // Adjective
  strcat(sentence, " ");
  strcat(sentence, noun[rand() % nounsize]); // Noun
  strcat(sentence, ".\n");

  return sentence;

} //EOF generateSentence
void displaySentence(char * sentence) {

  printf("%s", sentence);

} //EOF displaySentence
void generateStory(char ** noun, char ** verb, char ** adjective, char ** preposition, char ** article, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize, FILE * fptr) {

  int max = 401;
  int min = 100;
  //Gives me a range of 100-500
  int randomnumber = 0;
  randomnumber = (rand() % max) + min;
  //randomnumber is between 100-150
  for (int i = 0; i < randomnumber; i++) {
    char * sentence = generateSentence(noun, verb, adjective, preposition, article, nounsize, verbsize, adjsize, prepositionsize, articlesize);
    fprintf(fptr, "%s", sentence);
    free(sentence);
  }

} //EOF generateStory
void cleanUp(char ** nouns, char ** verbs, char ** adjectives, char ** prepositions, char ** articles, int nounsize, int verbsize, int adjsize, int prepositionsize, int articlesize) {
  /*
  free the memory of each array
  free the shell
  */
  for (int i = 0; i < nounsize; i++) {
    free(nouns[i]);
  }

  for (int i = 0; i < verbsize; i++) {
    free(verbs[i]);
  }

  for (int i = 0; i < adjsize; i++) {
    free(adjectives[i]);
  }

  for (int i = 0; i < prepositionsize; i++) {
    free(prepositions[i]);
  }

  for (int i = 0; i < articlesize; i++) {
    free(articles[i]);
  }
  free(nouns);
  free(verbs);
  free(adjectives);
  free(prepositions);
  free(articles);

} //EOF cleanUp

int main() {
  //setup randomness
  int x;
  printf("Enter seed: ");
  scanf("%d", & x);
  srand(x); //set seed

  //declare necessary variables
  int nounsize = 0;
  int verbsize = 0;
  int adjsize = 0;
  int prepositionsize = 0;

  int nounmaxsize = 5;
  int verbmaxsize = 5;
  int adjmaxsize = 5;
  int prepositionmaxsize = 5;
  const int articlemaxsize = 3; //there are only 3 articles in the english language a, an, and the. that is why const is applied

  printf("Welcome to the random sentence generator.\n");

  //double pointers
  char ** nouns = NULL;
  char ** verbs = NULL;
  char ** adjectives = NULL;
  char ** preposition = NULL;
  char ** articles = NULL;

  	nouns = (char **) malloc(sizeof(char *) * nounmaxsize); 
	verbs = (char **) malloc(sizeof(char *) * verbmaxsize);
	adjectives = (char **) malloc(sizeof(char *) * adjmaxsize); 
	preposition = (char **) malloc(sizeof(char *) * prepositionmaxsize); 
	articles = (char **) malloc(sizeof(char *) * articlemaxsize); 

  //make sure malloc was able to allocate memory
  if (nouns == NULL || verbs == NULL || adjectives == NULL || preposition == NULL || articles == NULL) {
    printf("malloc was not successful\n");
    printf("Program will now terminate.\n");
    exit(1);
  }

  //populate articles using strcpy. numbers represent how many characters are needed. this includes \0 character
  articles[0] = malloc(sizeof(char) * 2);
  strcpy(articles[0], "A");
  articles[1] = malloc(sizeof(char) * 3);
  strcpy(articles[1], "An");
  articles[2] = malloc(sizeof(char) * 4);
  strcpy(articles[2], "The");

  //open the file of words
  FILE * fptr = fopen("nouns.txt", "r");
  FILE * fptr2 = fopen("verbs.txt", "r");
  FILE * fptr3 = fopen("adjectives.txt", "r");
  FILE * fptr4 = fopen("preposition.txt", "r");

  //make sure the files were opened properly
  if (fptr == NULL || fptr2 == NULL || fptr3 == NULL || fptr4 == NULL) {
    printf("file was not successful in opening.");
    printf("Program will now terminate.\n");
    exit(1);
  }

  //populate the dynamic array
  nouns = populate(nouns, fptr, &nounsize, &nounmaxsize); //populate nouns
  verbs = populate(verbs, fptr2, &verbsize, &verbmaxsize); //populate verbs
  adjectives = populate(adjectives, fptr3, &adjsize, &adjmaxsize); //populate adjectives
  preposition = populate(preposition, fptr4, &prepositionsize, &prepositionmaxsize); //populate prepositions

  //close the files
  fclose(fptr);
  fclose(fptr2);
  fclose(fptr3);
  fclose(fptr4);

  //now lets generate 5 sentences and write them to the console window

  printf("Let's generate some random sentences that don't make sense.\n");

  for (int x = 0; x < 5; ++x) {
    char * sentence = generateSentence(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize);
    displaySentence(sentence);
    free(sentence);
  }

  printf("Now let's create three stories that just don't make sense.\n");
  fptr = fopen("story1.txt", "w");
  generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 1
  fclose(fptr);

  fptr = fopen("story2.txt", "w");
  generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 2
  fclose(fptr);

  fptr = fopen("story3.txt", "w");
  generateStory(nouns, verbs, adjectives, preposition, articles, nounsize, verbsize, adjsize, prepositionsize, articlemaxsize, fptr); //story 3
  fclose(fptr);

  cleanUp(nouns, verbs, adjectives, preposition, articles, nounmaxsize, verbmaxsize, adjmaxsize, prepositionmaxsize, 3);

  printf("The stories were generated successfully and stored in their respective text files.\n");
  printf("Check them out!\n");

  return 0;
}

