#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 64
#define MAX_PERSONS 1024

typedef struct Person {
	int age;
	char first_name[MAX_STR_LEN];
	char last_name[MAX_STR_LEN];
} Person;

// Sort according to age (decreasing)
// When ages equal compare first name and then last name
int cmp_person(const void *p1, const void *p2)
{

    int l = ((struct Person *)p1)->age;
    int r = ((struct Person *)p2)->age;
    char a;
    char b;
    int i = 0;
    if (l > r)
    {
        return -1;
    }
    else if(l == r)
    {
        a = ((struct Person *)p1)->first_name[i];
        b = ((struct Person *)p2)->first_name[i];
        int flag = 0;
        if (a != b)
        {
            flag = 1;
        }
        while (a == b)
        {
            i += 1;
            a = ((struct Person *)p1)->first_name[i];
            b = ((struct Person *)p2)->first_name[i];
            if (a != b)
            {
                flag = 1;
            }
        }
        if (flag == 1)
        {
            if (a > b)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            i = 0;
            a = ((struct Person *)p1)->last_name[i];
            b = ((struct Person *)p2)->last_name[i];
            while (a == b)
            {
                i += 1;
                a = ((struct Person *)p1)->last_name[i];
                b = ((struct Person *)p2)->last_name[i];
            }
            if (a > b)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
    }
    else
    {
        return 1;
    }
}

// Read data to Person array (till EOF)
int read_person_array(Person *persons)
{
    int i = 0;
    char *wiek;
    char *name1, *name2;
    char tab[MAX_STR_LEN];
    while (fgets(tab,MAX_STR_LEN,stdin) != NULL)
    {
        wiek = strtok(tab," ");
        persons[i].age = atoi(wiek);
        name1 = strtok(NULL," ");
        strcpy(persons[i].first_name,name1);
        name2 = strtok(NULL,"\n");
        strcpy(persons[i].last_name,name2);
        i += 1;
    }
    return i;
}

// Print Person array
void print_person_array(Person *persons, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ",persons[i].age);
        printf("%s ",persons[i].first_name);
        printf("%s\n",persons[i].last_name);
    }
}

// Sort women first (woman's first name ends with 'a');
// Then sort women by age and men by last name
// Line consists of: age, first_name, last_name
// (int that order)
int cmp_lines(const void *l1, const void *l2)
{
    int i = 0;
    int k = 0;
    int flag1 = 0;
    int flag2 = 0;
    char **a1 = (char **)l1;
    char **a2 = (char **)l2;
    int age1, age2;
    char name1[MAX_STR_LEN];
    char name2[MAX_STR_LEN];
    char last1[MAX_STR_LEN];
    char last2[MAX_STR_LEN];
    sscanf(a1,"%d " "%s " "%s ",&age1,name1,last1);
    sscanf(a2,"%d" "%s" "%s",&age2,name2,last2);
    if (name1[strlen(name1)-1] == 'a')
    {
        flag1 = 1;
    }
    if (name2[strlen(name2)-1] == 'a')
    {
        flag2 = 1;
    }
    if (flag1 == 1 && flag2 == 0)
    {
        return -1;
    }
    if (flag1 == 0 && flag2 == 1)
    {
        return 1;
    }
    if (flag1 == flag2)
    {
        if (flag1 == 1)
        {
            if (age1 > age2)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            return strcmp(last1,last2);
        }
    }
    return 1;
}

// Read lines with students' data (as text)
int read_lines(char lines[][MAX_STR_LEN])
{
    int i = 0;
    char tab[MAX_STR_LEN];
    int str_len;
    while(fgets(tab,MAX_STR_LEN,stdin) != NULL)
    {
        str_len = strlen(tab);
        if (str_len > 1)
        {
            strcpy(lines[i],tab);
            i += 1;
        }
    }
    return i;
}

// Print sorted lines
void print_lines(char lines[][MAX_STR_LEN], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s",lines[i]);
    }
}

// -------------------------------------------------

int read_int() {
	char buf[MAX_STR_LEN];
	int n;
	fgets(buf, MAX_STR_LEN, stdin);
	sscanf(buf, "%d", &n);
	return n;
}

int main(void) {
	int to_do = read_int();
	int n;
	Person persons[MAX_PERSONS];
	char lines[MAX_PERSONS][MAX_STR_LEN];
	switch (to_do) {
		case 1:
			n = read_person_array(persons);
			qsort(persons, (size_t)n, sizeof(Person), cmp_person);
			print_person_array(persons, n);
			break;

		case 2:
			n = read_lines(lines);
			qsort(lines, (size_t) n, MAX_STR_LEN, cmp_lines);
			print_lines(lines, n);
			break;

		default:
			printf("Nothing to do for %d\n", to_do);
			break;
	}
}
