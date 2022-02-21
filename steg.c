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
    char format[2]; 
    struct Pixel ** data; 
    int max; 
    int height; 
    int width; 
};

/* Reads an image from an open PPM file.
 * Returns a new struct PPM, or NULL if the image cannot be read. */
struct PPM *getPPM(FILE * f)
{
    //allocating memory for the PPM file
    struct PPM * ppm = malloc(sizeof(struct PPM)); 

    //store the PPM file format
    fscanf(f, "%s\n", ppm -> format); 

    //error case: not in p3 format
    if (strcmp(ppm -> format, "P3") != 0)
    {
        printf("Image cannot be read");
        return NULL;
    }  
    fscanf(f, "%i %i\n", &ppm -> width, &ppm -> height);
    fscanf(f, "%i\n", &ppm -> max); 

    ppm -> data = (struct Pixel **) malloc((ppm -> height)*sizeof(struct Pixel *));

    //scanning the data of the pixels
    for (int i = 0; i < ppm -> height; i++)
    {
        ppm -> data[i] = (struct Pixel *) malloc((ppm -> width)*sizeof(struct Pixel));
        for(int j = 0; j < ppm -> width; j++){ 
            fscanf (f,"%i",&(ppm -> data[i][j]).red); 
            fscanf (f,"%i",&(ppm -> data[i][j]).green); 
            fscanf (f,"%i",&(ppm -> data[i][j]).blue);
        }
    }
    return ppm; 
}

/* Write img to stdout in PPM format. */
void showPPM(const struct PPM *img)
{
    //print the PPM file information: P3, its height, width and max rgb value
    printf("P3\n");
    printf("%i\n", img -> width);
    printf("%i\n", img -> height);
    printf("%i\n", img -> max);

    //printing out the rgb values respectively in matrix format
    for (int i = 0; i < img -> height; i++)
    {
        for (int j = 0; j < img -> width; j++)
        {
            struct Pixel p = img -> data[i][j];
            printf("%i %i %i\n", p.red, p.green, p.blue);
        }  
    }    
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
    //introducing needed variables
    struct PPM * img1 = (struct PPM*) img;
    srand(time(NULL));
    int x_pix;
    int rand_int;
    int len = strlen(text);
    int width1 = img1 -> width;
    int height1 = img1 -> height;

    //error case: message too long
    if (len > 75)
    {
        printf("Message too large for image\n");
        return NULL;
    }

    //encoding the message into the ppm file 
    for (int i = 0; i < len; i++)
    {
        int row;
        int col;

        rand_int = (rand() % 100);
        x_pix = x_pix + rand_int;

        row = x_pix / width1;
        col = x_pix - (row * width1);

        if(text[i] != img1 -> data[row][col].red)
        {
            img1 -> data[row][col].red = text[i];
        }
        //error case: ASCII value same as that of the red pixel
        else{
            printf("Error!\nCould not encode message");
            return NULL;
        }
    }
    return img1;

}

/* Extract the string encoded in the red channel of newimg, by comparing it
 * with oldimg. The two images must have the same size.
 * Returns a new C string, or NULL on error. */
char *decode(const struct PPM *oldimg, const struct PPM *newimg)
{
    //introducing needed variables
    int w1 = oldimg -> width;
    int h1 = oldimg -> height;
    struct Pixel ** p1 = oldimg -> data;

    int w2 = newimg -> width;
    int h2 = newimg -> height;
    struct Pixel ** p2 = newimg -> data;

    int len_counter;
    len_counter = 0;

    //setting memory allocation for the decoded message
    char *message = malloc(sizeof(char) * 75);

    //error case: sizes are different
    if (w1 != w2 || h1 != h2)
    {
        printf("Error!\nDimensions of the PPM files are different");
        return NULL;
    }

    //reading the contents of the file and revealing the decoded message
    for (int i = 0; i < h2; i++)
    {
        for (int j = 0; j < w2; j++)
        {
            if (p1[i][j].red != p2[i][j].red)
            {
                message[len_counter] = p2[i][j].red;
                len_counter ++; 
            }         
        }  
    }
    return message;
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
