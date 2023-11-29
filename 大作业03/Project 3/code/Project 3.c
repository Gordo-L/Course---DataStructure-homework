#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* A data structure that stores everyone's information.
*/
struct people
{
    char name[9];
    int age, networth;
}s[100000];

/*
 *    compare the order of two elements.
 * ------------------------------------------------
 *
 *    a: pointer to the element to compare.
 *    b: pointer to the element to compare.
 *
 *    returns: 
 *    an integer.
 *    If the return value < 0, the element pointed to by `a` will be
 *    placed on the left of the element pointed to by `b` ; if the 
 *    return value > 0, the element pointed to by `a` will be placed
 *    on the right of the element pointed to by `b` ; if the return 
 *    value = 0, the order of the elements pointed by `a` and `b` is
 *    uncertain.
 */
int cmp(const void* a, const void* b)
{
    //type conversion.
    struct people* aa = (void*)a, * bb = (void*)b;

    //firstly, compare the net worth.
    if (aa->networth == bb->networth)
    {
        //secondly, compare the age.
        if (aa->age == bb->age)

            //Thirdly, compare the alphabetical order of the names.
            return strcmp(aa->name, bb->name) > 0 ? 1 : -1;

        return aa->age > bb->age ? 1 : -1;
    }
    return aa->networth > bb->networth ? -1 : 1;
}


int main()
{
    int n, k, m, a, b;

    /*
    * input n (≤10​5​​) - the total number of people, 
    * and k (≤10​3​​) - the number of queries.
    */
    scanf("%d %d", &n, &k);

    /*
    * input the name (string of no more than 8 characters without space),
    * age (integer in (0, 200]), and the net worth (integer in [−10​6​​,10​6​​])
    * of a person.
    */
    for (int i = 0; i < n; i++)
    {
        scanf("%s %d %d", s[i].name, &s[i].age, &s[i].networth);
    }

    /*  
    *    void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)) 
    *    
    *    sort the array.
    * ------------------------------------------------
    * 
    *    base: pointer to the first element of the array to sort.
    *    nitems: the number of elements in the array pointed by base.
    *    size: the size of each element in the array, in bytes.
    *    compar: pointer to the function used to compare two elements.
    * 
    *    returns:
    *    void.
    */
    qsort(s, n, sizeof(s[0]), cmp);

    /*
    * deal with k queries.
    */
    for (int i = 1; i <= k; i++)
    {
        int c = 0;

        /*
        * input M (≤100) - the maximum number of outputs, 
        * and a、b - [Amin, Amax] which are the range of ages. 
        */
        scanf("%d %d %d", &m, &a, &b);

        /* output each query. */
        printf("Case #%d:\n", i);
        for (int j = 0; j < n; j++)
        {
            /* check the age range. */
            if (s[j].age >= a && s[j].age <= b)
            {
                printf("%s %d %d\n", s[j].name, s[j].age, s[j].networth);
                c++;
            }

            /* the number of output reaches m. */
            if (c == m)break;
        }

        /* no one is found. */
        if (c == 0)printf("None\n");
    }
    getchar();
    getchar();
}

