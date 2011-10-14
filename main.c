/* @author: Indra Ginanjar
 * @email: indraginanjar@gmail.com
 * @date: January 27th, 2011
 * @desc:
 *    lower filename case
 *    modified from Peter Parker's code at
 *    http://stackoverflow.com/questions/612097/how-can-i-get-a-list-of-files-in-a-directory-using-c-or-c
*/


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

void lowerstr(char **dest, char *src)
{
    int len = strlen(src);
    int i;
    *dest = calloc(len + 1, sizeof(char));
    for (i = 0; i < len; ++i)
    {
        (*dest)[i] = tolower(src[i]);
    }
}

int main(int argc, char *argv[])
{
    char usrkey;
    DIR *dir;
    struct dirent *ent;
    char *newname;
    if(argc > 1)
    {
        if(strcmp(argv[1], "/?") == 0 || strcmp(argv[1], "/h") == 0 || strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
        {
            printf("\nLower Filename Case v1\nUsage:\ntolower [dirname]\n\ndirname : directory to operate on, \".\" will be used if empty\n\n**USE AT YOUR OWN RISK**\n\n");
            return 0;
        }
    }
    printf("\nLower Filename Case v1\nindraginanjar@gmail.com\n\n**USE AT YOUR OWN RISK**\n\nThis will rename all your files in selected directory (default is \".\")\nAre you sure? (type \"y\" to continue)... ");
    if(scanf("%c", &usrkey) == EOF)
        return 0;
    if (usrkey != 'y' && usrkey != 'Y')
        return 0;
    printf("\n\nRenaming files...\n");
    if(argc > 1)
    {
        dir = opendir (argv[1]);
    }
    else
    {
        dir = opendir (".");
    }

    if (dir != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
            {
                lowerstr(&newname, ent->d_name);
                if (strcmp(newname, ent->d_name) == 0)
                {
                    printf ("\"%s\" is already in lowercase\n", ent->d_name);
                }
                else
                {
                    if (rename(ent->d_name, newname) != 0)
                    {
                        printf ("\"%s\" is cannot be renamed\n", ent->d_name);

                    }
                    else
                    {
                        printf ("\"%s\" is renamed to \"%s\"\n", ent->d_name, newname);
                    }
                }
            }
        }
        free(newname);
        closedir (dir);
    }
    else
    {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
    return 0;
}
