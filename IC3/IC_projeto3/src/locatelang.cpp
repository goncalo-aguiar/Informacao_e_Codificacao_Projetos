//that can process a text containing segments written in different languages. This application should return the character position at which each segment
//starts, as well as the language in which the segment is written.


#include "fcm.cpp"
#include "findlang.cpp"
#include "lang.cpp"
#include <stdio.h>
#include <string.h>
#include <iostream>

#define MAX_LENGTH 1000

int main(int argc, char** argv)
{
    //command line arguments processing
    if(argc <2){
        cout << "Error: Usage sintax is: ./lang <textfile> <textfile>" << endl;
        return 0; 
    } 
    //method to separate text in segments
    char input[MAX_LENGTH];
	int i, j, length, segment_start, language_start;
	char language[MAX_LENGTH];
	
	printf("Please enter the text: \n");
	fgets(input, MAX_LENGTH, stdin);
	
	length = strlen(input);
	
	for (i = 0; i < length; i++) {
		if (input[i] == '<') {
			segment_start = i + 1;
			
			for (j = i + 1; j < length; j++) {
				if (input[j] == '>') {
					strncpy(language, input + segment_start, j - segment_start);
					language[j - segment_start] = '\0';
					language_start = j + 1;
					
					printf("Segment starts at %d, language is %s \n", segment_start, language);
					
					i = j; // skip to the end of the segment
					break;
				}
			}
		}
	}
}
