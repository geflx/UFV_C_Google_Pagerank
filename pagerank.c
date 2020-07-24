#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*
	@authors:	Gabriel Felix, Matheus Lima
*/

struct PageRank { 

    double value;
    int pageId;
    double oldValue;

    // Output pages number, input pages array and input pages number.
    int n_out; 
    int* in; 
    int n_in; 
};

int E(struct PageRank* pages, int N)
{ 
	// Indicates if calculation is finished.
    double sum = 0;
    int i = 0;
    for (i = 0; i < N; i++) {
        sum += (pages[i].value - pages[i].oldValue) * (pages[i].value - pages[i].oldValue);
    }
    if (sqrt(sum) < 0.0000000001)
        return 1; // Yes.
    else
        return 0; // No.
}

double summation(struct PageRank* pages, int id)
{ 
	// Calculates summation of values.

    double sum = 0;
    int i = 0;

    // Using Input pages to calculate summation.
    for (i = 0; i < pages[id].n_in; i++) { 

        int inputId = pages[id].in[i];
        sum += (pages[inputId].oldValue) / ((double) pages[inputId].n_out);

    }
    return sum;
}

int comparePages(const void* a, const void* b)
{ 
    if ((*(struct PageRank*)a).value == (*(struct PageRank*)b).value) { 

    	// Same PageRank values, comparing indices.
        if ((*(struct PageRank*)a).pageId > (*(struct PageRank*)b).pageId) { 
            return -1;
        }
        else
            return 1;
    }

    if ((*(struct PageRank*)a).value < (*(struct PageRank*)b).value)
        return -1;
    else 
        return 1;
}

int main()
{
	// Number of pages, pages array and alocate status check.
    int n_pages = -1;
    struct PageRank* pages;
    int alocated = 0; 


    // Reading input.
    while (1) {

    	// Alocate memory after raeding pages number.
        if ((n_pages != -1) && (alocated == 0)) { 
            pages = calloc(n_pages, sizeof(struct PageRank));
            int k = 0;

            alocated = 1; 
        }

        int readedBytes;
        size_t nbytes = 10;
        char* buffer;
        buffer = (char*)malloc(nbytes + 1);

        // Reading line.
        readedBytes = getline(&buffer, &nbytes, stdin); 
        if (readedBytes == -1) {
            free(buffer);
            break;
        }

        char* delimiter;
        delimiter = strtok(buffer, ":,"); // Capturing IDs.

        int idOrigin = -1; // Origin page id.
        int idNode; // Pages linked to Origin.

        while (delimiter != NULL) {

        	// If n_pages is yet unknown ..
            if (n_pages == -1) { 
                n_pages = atoi(delimiter);
                delimiter = strtok(NULL, ":,");
            }
            // Read origin page id.
            else if (idOrigin == -1) {
                idOrigin = atoi(delimiter);
                delimiter = strtok(NULL, ":,");
            }
            // Reading output pages and writing Origin ID in its input pages array.
            else {
                idNode = atoi(delimiter);
                pages[idNode].n_in++;

                pages[idNode].in = (int*)realloc(pages[idNode].in, (pages[idNode].n_in) * sizeof(int));
                pages[idNode].in[(pages[idNode].n_in) - 1] = idOrigin;

                pages[idOrigin].n_out++;
                delimiter = strtok(NULL, ":,");
            }
        }
        free(buffer);
    }

    // Initializing pages, giving them id "i".
    int i = 0;
    for (i = 0; i < n_pages; i++){ 
        pages[i].pageId = i; 
        pages[i].oldValue = (1 / (double)n_pages);
    }

    // Calculating PageRank.
    int finished = 0;

    // Contants to use in calculation.
    double constOne = (1 - 0.85) / (double)n_pages; 
    double constTwo = 0.85;

    while (finished == 0) { //While E(k) > ε

        for (i = 0; i < n_pages; i++) {

        	// Pages WITHOUT output pages (n_out == 0).
            if (pages[i].n_out == 0) { 

                double temp = pages[i].value;
                pages[i].value = constOne + constTwo * pages[i].oldValue + constTwo * summation(pages, i);
                pages[i].oldValue = temp;

            }
            else {
            	// Pages WITH output pages.

                double temp = pages[i].value;
                pages[i].value = constOne + constTwo * summation(pages, i);
                pages[i].oldValue = temp;

            }
        }

        // Finishes if E(k) < ε.
        if (E(pages, n_pages) == 1)
            finished = 1; 
        
    }

    // Sorting pages and printing order.
    qsort(pages, n_pages, sizeof(struct PageRank), comparePages);   


    printf("Ordered Pages: \n");
    printf("{");
    for (int cont = n_pages - 1; cont >= 0; cont--) {
        printf("%d", pages[cont].pageId);

        if(cont != 0)
        	printf(", ");
        else
        	printf("}\n");
    }

    // Freeing alocated memory.
    for (i = 0; i < n_pages; i++) {
        free(pages[i].in);
    }
    free(pages);

    return 0;
}
