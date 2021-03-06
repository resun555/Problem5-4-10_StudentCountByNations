// Problem5-4-10_StudentCountByNations.c : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

#pragma warning( disable : 4996 )

struct Student
{
	char sname[20];
	char snation[20];
};

typedef struct Student Student;

struct NationCountMap
{
	char *nation;
	size_t count;
};

typedef struct NationCountMap NationCountMap;

struct BinaryNode
{
	NationCountMap countMap;
	struct BinaryNode *leftChild;
	struct BinaryNode *rightChild;
};

typedef struct BinaryNode BinaryNode;

BinaryNode * Insert(
	BinaryNode **root,
	BinaryNode *newNode
);

void InOrder(
	BinaryNode *root,
	void(*Process)(BinaryNode *node)
);

void AccessProcess(
	BinaryNode *node
);

void Release(
	BinaryNode *root
);


int main()
{
	size_t length;
	printf("Enter student count: ");
	scanf("%zu", &length);
	getchar();
	Student *students = (Student *)malloc(sizeof(Student) * length);
	BinaryNode *root = NULL;
	for (size_t i = 0; i < length; i++)
	{
		printf("Enter student name: ");
		gets_s(students[i].sname, 20);
		printf("Enter student nation: ");
		gets_s(students[i].snation, 20);
		BinaryNode *newNode = (BinaryNode *)malloc(sizeof(BinaryNode));
		newNode->countMap.nation = students[i].snation;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		BinaryNode *node = Insert(&root, newNode);
		if (node != newNode)
		{
			free(newNode);
		}
		if (node == newNode)
		{
			node->countMap.count = 0;
		}
		node->countMap.count++;
	}
	InOrder(root, AccessProcess);
	Release(root);
	free(students);
    return 0;
}


BinaryNode * Insert(BinaryNode **root, BinaryNode *newNode)
{
	if (*root == NULL)
	{
		*root = newNode;
		return *root;
	}
	else
	{
		if (strcmp(newNode->countMap.nation, (*root)->countMap.nation) < 0)
		{
			return Insert(&(*root)->leftChild, newNode);
		}
		else if (strcmp(newNode->countMap.nation, (*root)->countMap.nation) > 0)
		{
			return Insert(&(*root)->rightChild, newNode);
		}
		else
		{
			return *root;
		}
	}
}


void InOrder(BinaryNode *root, void(*Process)(BinaryNode *node))
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		InOrder(root->leftChild, Process);
		Process(root);
		InOrder(root->rightChild, Process);
		return;
	}
}


void AccessProcess(BinaryNode *node)
{
	printf("Student nation: %s\n", node->countMap.nation);
	printf("Student count: %zu\n", node->countMap.count);
	return;
}


void Release(BinaryNode *root)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		Release(root->leftChild);
		Release(root->rightChild);
		free(root);
		return;
	}
}

