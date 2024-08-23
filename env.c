#include "main.h"
/**
 * 
 */
void env()
{
    size_t ct = 0;

    while (__environ[ct])
    {
        printf("%s\n", __environ[ct]);
        ct++;
    }
}
