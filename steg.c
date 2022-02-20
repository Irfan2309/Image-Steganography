#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* The RGB values of a pixel. */
struct Pixel {
    int red;
    int green;
    int blue;
};

/* An image loaded from a PPM file. */
struct PPM {
    char format[2]; //intitialized with 2 character "format" because PPM is P3
    struct Pixel ** data; //defining "Pixel" as a pointer array
    int max; 
    int height; 
    int width; 
};

/* Reads an image from an open PPM file.
 * Returns a new struct PPM, or NULL if the image cannot be read. */
struct PPM *getPPM(FILE * f)
{
    /* TODO: Question 2a */
    return NULL;
}

/* Write img to stdout in PPM format. */
void showPPM(const struct PPM *img)
{
    /* TODO: Question 2b */
}

/* Opens and reads a PPM file, returning a pointer to a new struct PPM.
 * On error, prints an error message and returns NULL. */
struct PPM *readPPM(const char *filename)
{
    /* Open the file for reading */
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "File %s could not be opened.\n", filename);
        return NULL;
    }

    /* Load the image using getPPM */
    struct PPM *img = getPPM(f);

    /* Close the file */
    fclose(f);

    if (img == NULL) {
        fprintf(stderr, "File %s could not be read.\n", filename);
        return NULL;
    }

    return img;
}

/* Encode the string text into the red channel of image img.
 * Returns a new struct PPM, or NULL on error. */
struct PPM *encode(const char *text, const struct PPM *img)
{
    /* TODO: Question 2c */
    return NULL;
}

/* Extract the string encoded in the red channel of newimg, by comparing it
 * with oldimg. The two images must have the same size.
 * Returns a new C string, or NULL on error. */
char *decode(const struct PPM *oldimg, const struct PPM *newimg)
{
    /* TODO: Question 2d */
    return NULL;
}

/* TODO: Question 3 */
int main(int argc, char *argv[])
{
    /* Initialise the random number generator, using the time as the seed */
    srand(time(NULL));

    /* Parse command-line arguments */
    if (argc == 3 && strcmp(argv[1], "t") == 0) {
        /* Mode "t" - test PPM reading and writing */

        struct PPM *img = readPPM(argv[2]);
        showPPM(img);

    } else if (argc == 3 && strcmp(argv[1], "e") == 0) {
        /* Mode "e" - encode PPM */

        struct PPM *oldimg = readPPM(argv[2]);

        /* TODO: prompt for a message from the user, and read it into a string */

        struct PPM *newimg;
        /* TODO: encode the text into the image with encode, and assign to newimg */

        /* TODO: write the image to stdout with showPPM */

    } else if (argc == 4 && strcmp(argv[1], "d") == 0) {
        /* Mode "d" - decode PPM */

        struct PPM *oldimg;
        /* TODO: get original file filename from argv, load it with
           readPPM, then assign to oldimg */

        struct PPM *newimg;
        /* TODO: get encoded file filename from argv, load it with
           readPPM, then assign to newimg */

        char *message;
        /* TODO: decode the encodedPPM with the comparisonPPM and assign to message */

        /* TODO: print the decoded message to stdout */

    } else {
        fprintf(stderr, "Unrecognised or incomplete command line.\n");
        return 1;
    }

    return 0;
}
