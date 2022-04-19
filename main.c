#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 1000
#define MAX_RANGE 1000

typedef struct {
    int first;
    int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair* fun, int k, pair para)
{
    int flag = 0;
    for (int i = 0; i < k; i++)
    {
        if ((fun[i]).first == para.first && (fun[i]).second == para.second)
        {
            flag = 1;
            return k;
        }
    }
    if (flag == 0)
    {
        fun[k] = para;
        return k + 1;
    }
}

// Case 1:
// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair* fun, int k)
{
    int flag = 1;
    int rem1, fl;
    for (int i = 0; i < k; i++)
    {
        if (flag == 1)
        {
            rem1 = fun[i].first;
            fl = 0;
            for (int j = 0; j < k; j++)
            {
                if (rem1 == fun[j].first && rem1 == fun[j].second)
                {
                    fl = 1;
                }
            }
            if (fl == 0)
            {
                flag = 0;
            }
        }
    }
    return flag;
}
// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair* fun, int k)
{
    int flag = 1;
    int rem1, fl;
    for (int i = 0; i < k; i++)
    {
        if (flag == 1)
        {
            rem1 = fun[i].first;
            fl = 0;
            for (int j = 0; j < k; j++)
            {
                if (rem1 == fun[j].first && rem1 == fun[j].second)
                {
                    fl = 1;
                }
            }
            if (fl == 1)
            {
                flag = 0;
            }
        }
    }
    return flag;
}
// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair* fun, int k)
{
    int flag = 0;
    int fl;
    int rem1, rem2;
    for (int i = 0; i < k; i++)
    {
        if (flag == 0)
        {
            rem1 = fun[i].first;
            rem2 = fun[i].second;
            fl = 0;
            for (int j = 0; j < k; j++)
            {
                if (rem2 == fun[j].first && rem1 == fun[j].second)
                {
                    fl = 1;
                }
            }
            if (fl == 0)
            {
                flag = 1;
            }
        }
    }
    return abs(flag - 1);
}
// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair* fun, int k)
{
    int flag = 0;
    int rem1, rem2;
    for (int i = 0; i < k; i++)
    {
        if (flag == 0)
        {
            rem1 = fun[i].first;
            rem2 = fun[i].second;
            for (int j = 0; j < k; j++)
            {
                if (rem2 == fun[j].first && rem1 == fun[j].second)
                {
                    if (rem1 != rem2)
                    {
                        flag = 1;
                    }
                }
            }
        }
    }
    return abs(flag - 1);
}
// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair* fun, int k)
{
    int rem1, rem2, fl;
    int flag = 1;
    for (int i = 0; i < k; i++)
    {
        rem1 = fun[i].first;
        for (int j = 0; j < 0; j++)
        {
            if (flag == 1)
            {
                rem2 = fun[j].second;
                fl = 0;
                for (int p = 0; p < k; p++)
                {
                    if ((rem1 == fun[p].first && rem2 == fun[p].second) || (rem2 == fun[p].first && rem1 == fun[p].second))
                    {
                        fl += 1;
                    }
                }
                if (fl == 2)
                {
                    flag = 0;
                }
            }
        }
    }
    return flag;
}
// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair* fun, int k)
{
    int fl;
    int flag = 1;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (fun[i].second == fun[j].first && flag == 1)
            {
                fl = 0;
                for (int p = 0; p < k; p++)
                {
                    if (fun[i].first == fun[p].first && fun[p].second == fun[j].second)
                    {
                        fl = 1;
                    }
                }
                if (fl == 0)
                {
                    flag = 0;
                }
            }
        }
    }
    return flag;
}

// Case 2:
// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair* fun, int k)
{
    if (is_reflexive(fun,k) == 1 && is_transitive(fun,k) == 1 && is_antisymmetric(fun,k) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair* fun, int k)
{
    int rem1, rem2, fl;
    int flag = 1;
    for (int i = 0; i < k; i++)
    {
        rem1 = fun[i].first;
        for (int j = 0; j < k; j++)
        {
            if (flag == 1)
            {
                rem2 = fun[j].second;
                fl = 0;
                for (int p = 0; p < k; p++)
                {
                    if ((rem1 == fun[p].first && rem2 == fun[p].second) || (rem2 == fun[p].first && rem1 == fun[p].second))
                    {
                        fl += 1;
                    }
                }
                if (fl == 0)
                {
                    flag = 0;
                }
            }
        }
    }
    return flag;
}
// A total order relation is a partial order relation that is connected
int is_total_order(pair* fun, int k)
{
    if (is_partial_order(fun,k) == 1 && is_connected(fun,k) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int find_max_elements(pair* fun, int n, int *tab)
{
    int flag = 0;
    int k = 0;
    int fl = 0;
    for (int i = 0; i < n; i++)
    {
        flag = 0;
        fl = 0;
        for (int j = 0; j < n; j++) {
            if (fun[i].first == fun[j].first /*&& i != j*/ && fun[j].first != fun[j].second) {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            for (int j = 0; j < k; j++)
            {
                if (tab[j] == fun[i].first)
                {
                    fl = 1;
                }
            }
        }
        if (flag == 0 && fl == 0)
        {
            tab[k] = fun[i].first;
            k += 1;
        }
    }
    flag = 0;
    int tmp = 0;
    while (flag == 0)
    {
        flag = 1;
        for (int i = 0; i < k - 1; i++)
        {
            if (tab[i+1] < tab[i])
            {
                flag = 0;
                tmp = tab[i+1];
                tab[i+1] = tab[i];
                tab[i] = tmp;
            }

        }
    }
    return k;
}
int find_min_elements(pair* fun, int n, int *tab)
{
    int flag = 0;
    int k = 0;
    int fl = 0;
    for (int i = 0; i < n; i++)
    {
        flag = 0;
        fl = 0;
        for (int j = 0; j < n; j++) {
            if (fun[i].second == fun[j].second /*&& i != j*/ && fun[j].first != fun[j].second) {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            for (int j = 0; j < k; j++)
            {
                if (tab[j] == fun[i].second)
                {
                    fl = 1;
                }
            }
        }
        if (flag == 0 && fl == 0)
        {
            tab[k] = fun[i].second;
            k += 1;
        }
    }
    flag = 0;
    int tmp = 0;
    while (flag == 0)
    {
        flag = 1;
        for (int i = 0; i < k - 1; i++)
        {
            if (tab[i+1] < tab[i])
            {
                flag = 0;
                tmp = tab[i+1];
                tab[i+1] = tab[i];
                tab[i] = tmp;
            }

        }
    }
    return k;
}
int get_domain(pair* fun, int n, int *tab)
{
    int min = fun[0].first;
    int max = fun[0].first;
    int flag = 0;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (fun[i].first > max)
        {
            max = fun[i].first;
        }
        if (fun[i].first < min)
        {
            min = fun[i].first;
        }
    }
    k = max - min + 1;
    for (int i = 0; i < k; i++)
    {
        tab[i] = min + i;
    }
    /*
    for (int i = 0; i < n; i++)
    {
        flag = 0;
        for (int j = 0; j < k; j++)
        {
            if (tab[j] == fun[i].first)
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            tab[k] = fun[i].first;
            k += 1;
        }
    }
    flag = 0;
    int tmp = 0;
    while (flag == 0)
    {
        flag = 1;
        for (int i = 0; i < k - 1; i++)
        {
            if (tab[i+1] < tab[i])
            {
                flag = 0;
                tmp = tab[i+1];
                tab[i+1] = tab[i];
                tab[i] = tmp;
            }

        }
    }
     */
    return k;
}

// Case 3:
int composition (pair* fun, int n, pair* pary, int m, pair* fin)
{
    pair para;
    int p = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (fun[i].second == pary[j].first)
            {
                para.first = fun[i].first;
                para.second = pary[j].second;
                p = add_relation(fin,p,para);
            }
        }
    }
    return p;
}

int cmp (pair p1, pair p2) {
    if (p1.first == p2.first) return p1.second - p2.second;
    return p1.first - p2.first;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair* fun)
{
    int n;
    int k = 0;
    scanf("%d",&n);
    pair para;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&para.first);
        scanf("%d",&para.second);
        k = add_relation(fun,k,para);
    }
    return n;
}

void print_int_array(int *array, int n) {
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(void) {
    int to_do;
    pair relation[MAX_REL_SIZE];
    pair relation_2[MAX_REL_SIZE];
    pair comp_relation[MAX_REL_SIZE];
    int domain[MAX_REL_SIZE];

    scanf("%d",&to_do);
    int size = read_relation(relation);
    int ordered, size_2, n_domain;

    switch (to_do) {
        case 1:
            printf("%d ", is_reflexive(relation, size));
            printf("%d ", is_irreflexive(relation, size));
            printf("%d ", is_symmetric(relation, size));
            printf("%d ", is_antisymmetric(relation, size));
            printf("%d ", is_asymmetric(relation, size));
            printf("%d\n", is_transitive(relation, size));
            break;

        case 2:
            ordered = is_partial_order(relation, size);
            n_domain = get_domain(relation, size, domain);
            printf("%d %d\n", ordered, is_total_order(relation, size));
            print_int_array(domain, n_domain);
            if (!ordered) break;
            int max_elements[MAX_REL_SIZE];
            int min_elements[MAX_REL_SIZE];
            int no_max_elements = find_max_elements(relation, size, max_elements);
            int no_min_elements = find_min_elements(relation, size, min_elements);
            print_int_array(max_elements, no_max_elements);
            print_int_array(min_elements, no_min_elements);
            break;

        case 3:
            size_2 = read_relation(relation_2);
            printf("%d\n", composition(relation, size,
                                       relation_2, size_2, comp_relation));
            break;

        default:
            printf("NOTHING TO DO FOR %d\n", to_do);
            break;
    }

    return 0;
}
