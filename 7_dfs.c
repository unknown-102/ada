#include <stdio.h>
#include <stdlib.h>

int mat[100][100], vis[100];
int isCycle = 0, components = 0, opcount = 0, isTester = 0;

void dfs(int n, int source, int par)
{
    vis[source] = 1;

    if (isTester)
        printf("-->%c ", source + 65);

    for (int i = 0; i < n; i++)
    {
        opcount++;
        if (mat[source][i] && vis[i] && i != par)
            isCycle = 1;
        else if (mat[source][i] && !vis[i])
            dfs(n, i, source);
    }
}

void tester()
{
    int n;
    isTester = 1;
    printf("Enter the number of vertices\n");
    scanf("%d", &n);
    printf("Enter the adjacency matrix :\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    // dfs(n, 0, -1);

    for (int i = 0; i < n; i++)
        if (!vis[i])
        {
            components++;
            dfs(n, i, -1);
        }

    printf("\nThe number of connected components :%d\n", components);

    if (isCycle)
        printf("Cycle exists\n");
    else
        printf("Cycle doesnot exists\n");
}

void plotter()
{
    FILE *f1 = fopen("dfsadjMat.txt", "a");
    isTester = 0;

    for (int k = 1; k <= 10; k++)
    {
        int n = k;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                    mat[i][j] = 1;
                else
                    mat[i][j] = 0;
            }
        }
        opcount = 0;
        for (int i = 0; i < n; i++)
            if (!vis[i])
            {
                components++;
                dfs(n, i, -1);
            }
        fprintf(f1, "%d\t%d\n", n, opcount * 2);
    }
    fclose(f1);
}

void main()
{
    int choice;
    printf("Enter\n1.Tester\n2.Plotter\n");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice");
    }
}