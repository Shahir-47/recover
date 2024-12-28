#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>


int main(int argc, char *argv[])
{
    //validation to check there is only one command line arguement
    if (argc != 2)
    {
        printf("wrong usage\n");
        return 1;
    }
    //validation to check whether the memory can be accessed
    FILE *memory = fopen(argv[1], "r");
    if (!memory)
    {
        printf("forensic image cannot be opened\n");
        return 1;
    }
    FILE *image;
    //array of 512 elements as 1 block has 512 elements
    unsigned char pic[512];
    int jpfound = 0;
    //counter to keep track of file and write the ###.jpg file
    //it takes 8 elements to write the ###.jpg
    char imagename[8];
    //if it is not the end of memory it will read and return a value that is not zero
    //it'll return zero if it is atthe end and has nothing to read
    while (fread(pic, 512, 1, memory) != 0)
    {
        //validation to check if it is a jpeg format
        if (pic[0] == 0xff && pic[1] == 0xd8 && pic[2] == 0xff && (pic[3] & 0xf0) == 0xe0)
        {
            //validation to check if it is the first jpeg format
            if (jpfound == 0)
            {
                //create the first jpeg file and increment the counter so the next filename is larger than 000.jpeg
                sprintf(imagename, "%03i.jpg", jpfound);
                image = fopen(imagename, "w");
                fwrite(pic, 512, 1, image);             
                jpfound = jpfound + 1;
            }
            else if (jpfound != 0)
            {
                //if it is not the first jpeg file it'll name the file according to which jpeg it is on
                fclose(image);
                sprintf(imagename, "%03i.jpg", jpfound);
                image = fopen(imagename, "w");
                fwrite(pic, 512, 1, image);             
                jpfound = jpfound + 1;
            }

        }
        //if no jpeg file is found it'll keep on writing until found
        else if (jpfound != 0)
        {
            fwrite(pic, 512, 1, image);
        }
    }
    //we've reached the end of the memory and there is nothing further to read/write/append so we'll close the original files and the one we created
    fclose(image);
    fclose(memory);
    return 0;
}
