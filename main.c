/* 

NOTICE:
THIS PROGRAM IS WRITTEN AND BASED UPON THE PROVIDED CODE FOR THE LAB-06 ASSIGNMENT. 
FOR EXAMPLE, "listing.c" WAS USED AS A FOUNDATION FOR THIS PROGRAM, AND WAS BUILT UPON WHERE NECESSARY,
AT TIMES USING METHODS PROVIDED IN OTHER FILES SUCH AS "qSortIntegers.c" AND "qSortString.c"

INSTRUCTIONS:
TO COMPILE THE PROGRAM, TYPE "gcc main.c" IN THE TERMINAL
TO RUN, TYPE "./a.out" IN THE TERMINAL
AS A RESULT, A NEW FILE "output.txt" WILL BE CREATED

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024

struct listing {
    int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count,availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
};

// getfields function from listing.c
struct listing getfields(char* line){
    struct listing item;

    item.id = atoi(strtok(line, ","));
    item.host_id = atoi(strtok(NULL, ","));
    item.host_name = strdup(strtok(NULL, ","));
    item.neighbourhood_group = strdup(strtok(NULL, ","));
    item.neighbourhood = strdup(strtok(NULL, ","));
    item.latitude = atof(strtok(NULL, ","));
    item.longitude = atof(strtok(NULL, ","));
    item.room_type = strdup(strtok(NULL, ","));
    item.price = atof(strtok(NULL, ","));
    item.minimum_nights = atoi(strtok(NULL, ","));
    item.number_of_reviews = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365 = atoi(strtok(NULL, ","));
    
    return item;
}

// Function for comparing the price of two items, based on the given code in qSortIntegers.c and qSortStrings.c
int compareByPrice(const void* a, const void* b)
{
    struct listing* listingA = (struct listing*) a;
    struct listing* listingB = (struct listing*) b;
    return listingA->price - listingB->price;
}

// Function for comparing the host name of two items, based on the given code in qSortIntegers.c and qSortStrings.c
int compareByHostName(const void *a, const void *b) {
    const struct listing *listingA = (const struct listing *)a;
    const struct listing *listingB = (const struct listing *)b;
    return strcmp(listingA->host_name, listingB->host_name);
}

int main(int argc, char* args[]) {
    struct listing list_items[22555];
    char line[LINESIZE];
    int i, count = 0;

	// opens "listings.csv" to read from.
    FILE *fptr = fopen("listings.csv", "r");
    if(fptr == NULL){
        printf("Error reading input file listings.csv\n");
        exit (-1);
    }

	count = 0;
    while (fgets(line, LINESIZE, fptr) != NULL){
        list_items[count++] = getfields(line);
    }
    fclose(fptr);

	// creates a new file "output.txt" to print into.
	FILE *fp = fopen("output.txt", "w");
	if (fp == NULL) 
	{
		printf("Error opening file\n");
		return 1;
	}

	// Sorts the items of the array into the desired order, then iterates over the array and prints them to "output.txt".
    qsort(list_items, count, sizeof(struct listing), compareByHostName);
    fprintf(fp, "Array Sorted by Host Name:\n\n");
	for (int i = 0; i < count; i++) 
	{
    	fprintf(fp, "%d, %d, %s, %s, %s, %f, %f, %s, %f, %d, %d, %d, %d\n",
		list_items[i].id,list_items[i].host_id,
		list_items[i].host_name, list_items[i].neighbourhood_group,
		list_items[i].neighbourhood, list_items[i].latitude,
		list_items[i].longitude, list_items[i].room_type,
		list_items[i].price, list_items[i].minimum_nights,
		list_items[i].number_of_reviews, 
		list_items[i].calculated_host_listings_count,
		list_items[i].availability_365);
    }

	// Same as above, but for price this time instead of host name.
    qsort(list_items, count, sizeof(struct listing), compareByPrice);
	fprintf(fp, "\nArray Sorted by Price:\n\n");
	for (int i = 0; i < count; i++) 
	{
    	fprintf(fp, "%d, %d, %s, %s, %s, %f, %f, %s, %f, %d, %d, %d, %d\n",
		list_items[i].id,list_items[i].host_id,
		list_items[i].host_name, list_items[i].neighbourhood_group,
		list_items[i].neighbourhood, list_items[i].latitude,
		list_items[i].longitude, list_items[i].room_type,
		list_items[i].price, list_items[i].minimum_nights,
		list_items[i].number_of_reviews, 
		list_items[i].calculated_host_listings_count,
		list_items[i].availability_365);
    }
	fclose(fp);

    // free memory allocated for string fields.
    for (i=0; i<count; i++) {
        free(list_items[i].host_name);
        free(list_items[i].neighbourhood_group);
        free(list_items[i].neighbourhood);
        free(list_items[i].room_type);
    }

    return 0;
}