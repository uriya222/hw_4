#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_LETTERS 26
#define WORD_LEN 15

int flag = 1;

typedef struct Node
{
    char letter;
    long unsigned int count;
    struct Node *children[NUM_LETTERS];
} Node;

Node *initNode(char letter)
{
    Node *pNode = NULL;
    pNode = (Node *)malloc(sizeof(Node));
    if (pNode)
    {
        pNode->count = 0;
        pNode->letter = letter;
        int i;
        for (i = 0; i < NUM_LETTERS; i++)
            pNode->children[i] = NULL;
    }
    else
    {
        printf("not enouph memory");
        exit(1);
    }
    return pNode;
}
int conversion_to_int(char ch)
{
    return (int)(ch) - (int)('a');
}
void insert(Node *root, const char *word)
{
    int i, index;
    int word_len = strlen(word);
    Node *p = root;
    for (i = 0; i < word_len; i++)
    {
        index = conversion_to_int(word[i]);
        if (!p->children[index])
        {
            p->children[index] = initNode(word[i]);
        }
        p = p->children[index];
    }
    p->count++;
}
void freeTree(Node *p)
{
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        if (p->children[i] != NULL)
        {
            freeTree(p->children[i]);
        }
        else
            continue;
    }
    free(p);
}
void printWords1(Node *p, char *hold, int s)
{
    int i = 0;
    if (p == NULL)
    {
        return;
    }
    if (p->count)
    {
        hold[s] = 0;
        printf("%s %ld\n", hold, p->count);
        p->count = 0;
    }
    for (i = 0; i < NUM_LETTERS; i++)
    {
        hold[s] = 'a' + i;
        printWords1(p->children[i], hold, s + 1);
    }
}
void printWords2(Node *p, char *hold, int s)
{
    int i = 0;
    if (p == NULL) return;
    for (i = NUM_LETTERS-1; i >=0; i--)
    {
        hold[s] = i+'a';
        printWords2(p->children[i], hold, s + 1);
    }
    if (p->count)
    {
        hold[s] = 0;
        printf("%s %ld\n", hold, p->count);
        p->count = 0;
    }
}
char *getWord()
{
    int i = 0, size = WORD_LEN, sigh = 1;
    char ch, *tmp2 = (char *)malloc(WORD_LEN);
    ch = getchar();
    while ((ch != '\n') && (ch != ' ')&& (ch != '\t'))
    {
        if ((int)ch == EOF)
        {
            flag = 0;
            break;
        }
        while ((ch < 'A') || (('Z' < ch) && (ch < 'a')) || ('z' < ch))
        {
            if ((ch == '\n') || (ch == ' ') || (ch != '\t') || ((int)ch == EOF))
            {
                sigh = 0;
                break;
            }
            ch = getchar();
        }
        if (!sigh) break;
        tmp2[i] = ch;
        i++;
        if (i >= size)
        {
            tmp2 = (char *)realloc(tmp2, i + WORD_LEN);
            size += WORD_LEN;
        }
        ch = getchar();
    }
    *(tmp2 + i) = '\0';
    return tmp2;
}
void Lower(char* w,size_t len){
   size_t i;
   for(i=0;i<len;i++){
      w[i] = tolower(w[i]);
   }
}
int main(int argc, char *argv[])
{
    if ((argc == 2 && argv[1][0] == 'r' && strlen(argv[1]) == 1)||(argc==1))
    {
        size_t max_len = 0, w_len;
        Node *root = initNode(' ');
        while (flag)
        {
            char *word = getWord();
            w_len = strlen(word);
            if (max_len < w_len)
            {
                max_len = w_len;
            }
            Lower(word,strlen(word));
            if (strcmp(word,"\0"))
            {
                insert(root, word);
            }
            free(word);
        }
        char *tmp = (char *)malloc(max_len + 1);
        if (!tmp)
        {
            printf("not enouph memory");
            exit(1);
        }
        if(argc==1) printWords1(root, tmp, 0);
        else printWords2(root, tmp, 0);
        freeTree(root);
        free(tmp);
    }
    else
    {
        printf("try ./frequency  or  ./frequency r\n");
        return 1;
    }
    return 0;
}