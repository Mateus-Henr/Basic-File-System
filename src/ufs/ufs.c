#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ufs.h"
#include "../miscelaneous/error.h"

#define DELIMITER "/"
#define ROOT_INODE 0

void initializeUFS(UFS *ufs, long maxINodes)
{
    ufs->maxINodes = maxINodes;
    ufs->iNodeCount = 1;
    ufs->freeINodeCount = maxINodes - ufs->iNodeCount;

    ufs->iNodes = (INode **) malloc(maxINodes * sizeof(INode *));

    if (!ufs->iNodes)
    {
        printf(ALLOCATION_ERROR, "UFS INodes");
        exit(EXIT_FAILURE);
    }

    ufs->iNodes[ROOT_INODE] = initializeINode(ROOT_INODE, "/", DIRECTORY);

    for (long i = 1; i < maxINodes; i++)
    {
        ufs->iNodes[i] = NULL;
    }

    ufs->freeINodes = (INode **) malloc(maxINodes * sizeof(INode *));

    if (!ufs->freeINodes)
    {
        printf(ALLOCATION_ERROR, "UFS Free INodes.");
        free(ufs->iNodes);
        exit(EXIT_FAILURE);
    }
}

INode *createSingleNode(UFS *ufs, char *entryName, enum EntryType entryType)
{
    return ufs->iNodes[ufs->iNodeCount++] = initializeINode(ufs->iNodeCount, entryName, entryType);
}

INode *findParentINode(UFS *ufs, Path *entryPath)
{
    INode *parentINode = ufs->iNodes[ROOT_INODE];

    for (long i = 0; i < entryPath->size - 1; i++)
    {
        if (!parentINode)
        {
            printf(INODE_NOT_FOUND, entryPath->entryNames[i]);
            return NULL;
        }

        if (parentINode->entryContent.entryType == DIRECTORY)
        {
            long iNodeId = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                                  entryPath->entryNames[i]);

            if (iNodeId == -1)
            {
                printf(INODE_NOT_FOUND, entryPath->entryNames[i]);
                return NULL;
            }

            parentINode = ufs->iNodes[iNodeId];
        }
        else // FILE
        {
            printf(FILE_IS_NOT_DIRECTORY, entryPath->entryNames[i]);
            return NULL;
        }
    }

    return parentINode;
}

bool createEntry(UFS *ufs, Path *entryPath, enum EntryType entryType)
{
    if (ufs->iNodeCount + 1 == ufs->maxINodes)
    {
        printf(MAX_NUMBER_OF_INODES);
        return false;
    }

    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return false;
    }

    if (parentINode->entryContent.entryType == ARCHIVE)
    {
        printf(FILE_IS_NOT_DIRECTORY, parentINode->entryName);
        return false;
    }

    long idFound = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    // Check if entry already exists.
    if (idFound != -1)
    {
        INode *existingINode = ufs->iNodes[idFound];

        if (entryType == DIRECTORY)
        {
            if (existingINode->entryContent.entryType == ARCHIVE)
            {
                printf(FILE_EXISTS);
                return false;
            }

            printf(DIRECTORY_EXISTS);
            return false;
        }
        else if (existingINode->entryContent.entryType == DIRECTORY)
        {
            printf(FILE_EXISTS);
            return false;
        }

        updateEntryMetadata(&existingINode->entryMetadata);
        return true;
    }

    INode *createdINode = createSingleNode(ufs, entryPath->entryNames[entryPath->size - 1], entryType);
    return addEntry(&parentINode->entryContent.directory, createdINode->id, createdINode->entryName);
}

bool renameEntry(UFS *ufs, Path *entryPath, char *newEntryName)
{
    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return false;
    }

    long idFound = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return false;
    }

    if (findINodeIdInDirectory(&parentINode->entryContent.directory,
                               newEntryName) != -1)
    {
        printf(NAME_EXISTS, newEntryName);
        return false;
    }

    changeEntryNameInDirectory(&parentINode->entryContent.directory,
                               entryPath->entryNames[entryPath->size - 1],
                               newEntryName);

    return changeINodeEntryName(ufs->iNodes[idFound], newEntryName);
}

bool moveEntry(UFS *ufs, Path *entryPath, Path *newEntryPath)
{
    /* aki eh pra pegar os tipos de cada entry, importante pra ver se no move vai continuar com o msm nome ou se vai trocar

    diretorio e diretorio -> move o primeiro diretorio para dentro do segundo diretorio; caso o segundo diretorio nao exisir, move o primeiro diretorio para o diretorio onde o segundo diretorio inexistente deveria estar, e passa a ter o nome desse diretorio inexistente; caso o diretorio onde o diretorio inexistente deveria estar nao existir, retorna erro
    arquivo e diretorio -> move o arquivo para o diretorio; caso o diretorio nao existir, retorna erro
    arquivo e arquivo -> retorna erro; caso o segundo arquivo nao existir, move o primeiro arquivo para o diretorio onde o segundo arquivo inexistente deveria estar, e passa a ter o nome desse arquivo inexistente; caso o diretorio onde o arquivo inexistente deveria estar nao existir, retorna erro
    diretorio e arquivo -> retorna erro
    qualquer caso onde o primeiro nao existir -> retorna erro
    quando os dois diretorios ou arquivos estiverem no msm diretorio, renomear o arquivo/diretorio

    INode *parentINode = findParentINode(ufs, entryPath);
    INode *newParentINode = findParentINode(ufs, newEntryPath);

    para o tipo do newParentINode, tem q ver o q fazer qnd esse path nao existir, mas ainda for um comando valido, como comentado acima
    */

    // confere se o move eh para o msm diretorio, se for, chama o renameEntry
    if(entryPath->size == newEntryPath->size)// && findINodeIdInDirectory() == newEntryType) essa segunda condicao eh pra ver se os dois paths sao pra arquivos
    {
        for(int i = 0; i < entryPath->size - 1; i++)
        {
            if(strcmp(entryPath->entryNames[i], newEntryPath->entryNames[i]) != 0)
            {
                break;
            }

            if(i == entryPath->size - 2 && strcmp(entryPath->entryNames[i], newEntryPath->entryNames[i]) == 0)
            {
                return renameEntry(ufs, entryPath, newEntryPath->entryNames[newEntryPath->size - 1]);
            }
        }
    }

    /*
    tentavita de move usando delete e create entry, mas provavelmente tem q conferir muito mais coisa ainda
    if(deleteEntry(ufs, entryPath))
    {
        return createEntry(ufs, newEntryPath, newEntryType)
    }
    */
}

bool deleteEntry(UFS *ufs, Path *entryPath)
{

}

void displayEntry(UFS *ufs, Path *entryPath)
{
    if (entryPath->size == 1 && entryPath->entryNames[0][0] == '.')
    {
        Node *current = ufs->iNodes[0]->entryContent.directory.entries.head;

        while (current)
        {
            if (ufs->iNodes[current->iNodeId]->entryContent.entryType == DIRECTORY)
            {
                printf("%s%s%s\n", CYAN, current->entryName, RESET);
            }
            else
            {
                printf("%s\n", current->entryName);
            }

            current = current->nextNode;
        }

        return;
    }

    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return;
    }

    long idFound = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    if (ufs->iNodes[idFound]->entryContent.entryType == ARCHIVE)
    {
        printf("\n%s\n", ufs->iNodes[idFound]->entryName);
        return;
    }

    Node *current = ufs->iNodes[idFound]->entryContent.directory.entries.head;

    while (current)
    {
        if (ufs->iNodes[current->iNodeId]->entryContent.entryType == DIRECTORY)
        {
            printf("%s%s%s\n", CYAN, current->entryName, RESET);
        }
        else
        {
            printf("%s\n", current->entryName);
        }

        current = current->nextNode;
    }
}

void traverseDirectory(UFS *ufs, Directory *directory, long inodeId, int level)
{
    INode *inode = ufs->iNodes[inodeId];

    if (inode->entryContent.entryType != DIRECTORY)
    {
        return;
    }

    Node *current = inode->entryContent.directory.entries.head;

    while (current)
    {
        for (int i = 0; i < level; i++)
        {
            printf("  |");

            if (i == level - 1)
            {
                printf("-- ");
            }
            else
            {
                printf("   ");
            }
        }

        printf("%s\n", current->entryName);

        traverseDirectory(ufs, directory, current->iNodeId, level + 1);
        current = current->nextNode;
    }
}

void displayEntryHierarchy(UFS *ufs, Path *entryPath)
{
    if (entryPath->size == 1 && entryPath->entryNames[0][0] == '.')
    {
        printf("\n.\n"); // Root directory
        traverseDirectory(ufs, &ufs->iNodes[ROOT_INODE]->entryContent.directory, ROOT_INODE, 1);
        return;
    }

    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return;
    }

    long idFound = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    if (ufs->iNodes[idFound]->entryContent.entryType == ARCHIVE)
    {
        printf("\n%s\n", entryPath->entryNames[entryPath->size - 1]);
    }
    else
    {
        printf("\n%s\n", entryPath->entryNames[0]);
    }

    traverseDirectory(ufs, &ufs->iNodes[idFound]->entryContent.directory, idFound, 1);
}

void displayFile(UFS *ufs, Path *entryPath)
{
    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return;
    }

    long idFound = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    if (ufs->iNodes[idFound]->entryContent.entryType == DIRECTORY)
    {
        printf(FILE_IS_DIRECTORY, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    displayFileContent(&ufs->iNodes[idFound]->entryContent.file);
}

void displayMetadata(UFS *ufs, Path *entryPath)
{
    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return;
    }

    long idFound = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    displayEntryMetadata(&ufs->iNodes[idFound]->entryMetadata);
}