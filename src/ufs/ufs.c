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

        if (parentINode->content.entryType == DIRECTORY)
        {
            long iNodeId = findINodeIdInDirectory(&parentINode->content.directory,
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

    if (parentINode->content.entryType == ARCHIVE)
    {
        printf(FILE_IS_NOT_DIRECTORY, parentINode->header->name);
        return false;
    }

    long idFound = findINodeIdInDirectory(&parentINode->content.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    // Check if entry already exists.
    if (idFound != -1)
    {
        INode *existingINode = ufs->iNodes[idFound];

        if (entryType == DIRECTORY)
        {
            if (existingINode->content.entryType == ARCHIVE)
            {
                printf(FILE_EXISTS);
                return false;
            }

            printf(DIRECTORY_EXISTS);
            return false;
        }
        else if (existingINode->content.entryType == DIRECTORY)
        {
            printf(FILE_EXISTS);
            return false;
        }

        updateEntryMetadata(&existingINode->metadata);
        return true;
    }

    return addEntry(&parentINode->content.directory,
                    createSingleNode(ufs, entryPath->entryNames[entryPath->size - 1], entryType)->header);
}

bool renameEntry(UFS *ufs, Path *entryPath, char *newEntryName)
{
    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return false;
    }

    long idFound = findINodeIdInDirectory(&parentINode->content.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return false;
    }

    if (findINodeIdInDirectory(&parentINode->content.directory,
                               newEntryName) != -1)
    {
        printf(NAME_EXISTS, newEntryName);
        return false;
    }

    return changeINodeEntryName(ufs->iNodes[idFound], newEntryName);
}

bool moveEntry(UFS *ufs, Path *entryPath, Path *newEntryPath)
{
    INode *parentINode = findParentINode(ufs, entryPath);
    INode *newParentINode = findParentINode(ufs, newEntryPath);

    // caso os paths sejam iguais, retorna erro
    if(findINodeIdInDirectory(&parentINode->content.directory, entryPath->entryNames[entryPath->size - 1]) == findINodeIdInDirectory(&newParentINode->content.directory, newEntryPath->entryNames[newEntryPath->size - 1]))
    {
        // falta escrever a mensagem de erro
        return false;
    }

    // confere se o primeiro path esta dentro do segundo path (transformar em funcao depois)
    if(entryPath->size < newEntryPath->size)
    {
        bool entryPathInNewEntryPath = true;

        for(int i = 0; (i < entryPath->size && i < newEntryPath->size); i++)
        {
            if(strcmp(entryPath->entryNames[i], newEntryPath->entryNames[i]) != 0)
            {
                entryPathInNewEntryPath = false;
                break;
            }
        }

        // caso o primeiro path esteja dentro do segundo path, retorna erro
        if(entryPathInNewEntryPath)
        {
            // falta escrever a mensagem de erro
            return false;
        }
    }

    INode *iNode = ufs->iNodes[findINodeIdInDirectory(&parentINode->content.directory, entryPath->entryNames[entryPath->size - 1])];
    
    // segundo path nao existe(nao tem problema)
    if(findINodeIdInDirectory(&newParentINode->content.directory, newEntryPath->entryNames[newEntryPath->size - 1]) == -1)
    {
        // caso o segundo path nao exista e esteja no mesmo diretorio do primeiro, chama o rename
        if(parentINode->header->id == newParentINode->header->id)
        {
            return renameEntry(ufs, entryPath, newEntryPath->entryNames[newEntryPath->size - 1]);
        }
        // caso o segundo path nao exista e esteja num diretorio diferente do primeiro, ele eh excluido e eh criado um novo no segundo path
        else
        {
            if(addEntry(&newParentINode->content.directory, createSingleNode(ufs, newEntryPath->entryNames[newEntryPath->size - 1], iNode->content.entryType)->header))
            {
                INode *currINode = ufs->iNodes[findINodeIdInDirectory(&newParentINode->content.directory, newEntryPath->entryNames[newEntryPath->size - 1])];

                if(currINode->content.entryType == DIRECTORY)
                {
                    currINode->content = iNode->content;
                    currINode->header = iNode->header;
                    currINode->metadata = iNode->metadata;
                }
                else if(currINode->content.entryType == ARCHIVE)
                {
                    // passar o conteudo do arquivo
                }
                return deleteEntry(ufs, entryPath);
            }
            else return false;
        }
    }
    // segundo path existe
    else
    {
        INode *newINode = ufs->iNodes[findINodeIdInDirectory(&newParentINode->content.directory, newEntryPath->entryNames[newEntryPath->size - 1])];

        // caso o segundo path exista e for um file, retorna erro
        if(newINode->content.entryType == ARCHIVE)
        {
            // ainda falta escrever a mensagem de erro
            return false;
        }
        // caso o segundo path exista e for um diretorio, cria uma nova entry nesse path
        else if(newINode->content.entryType == DIRECTORY)
        {
            if(addEntry(&newINode->content.directory, createSingleNode(ufs, entryPath->entryNames[entryPath->size - 1], iNode->content.entryType)->header))
            {
                INode *currINode = ufs->iNodes[findINodeIdInDirectory(&newINode->content.directory, entryPath->entryNames[entryPath->size - 1])];

                if(currINode->content.entryType == DIRECTORY)
                {
                    currINode->content = iNode->content;
                    currINode->header = iNode->header;
                    currINode->metadata = iNode->metadata;
                }
                else if(currINode->content.entryType == ARCHIVE)
                {
                    // passar o conteudo do arquivo
                }

                return deleteEntry(ufs, entryPath);
            }
            else return false;
        }
    }
}

bool deleteEntry(UFS *ufs, Path *entryPath)
{
    INode *parentINode = findParentINode(ufs, entryPath);
    return removeEntry(&parentINode->content.directory, entryPath->entryNames[entryPath->size - 1]);
}

void displayEntry(UFS *ufs, Path *entryPath)
{
    if (entryPath->size == 1 && entryPath->entryNames[0][0] == '.')
    {
        Node *current = ufs->iNodes[0]->content.directory.entries.head;

        while (current)
        {
            if (ufs->iNodes[current->entryHeader->id]->content.entryType == DIRECTORY)
            {
                printf("%s%s%s\n", CYAN, current->entryHeader->name, RESET);
            }
            else
            {
                printf("%s\n", current->entryHeader->name);
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

    long idFound = findINodeIdInDirectory(&parentINode->content.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    if (ufs->iNodes[idFound]->content.entryType == ARCHIVE)
    {
        printf("\n%s\n", ufs->iNodes[idFound]->header->name);
        return;
    }

    Node *current = ufs->iNodes[idFound]->content.directory.entries.head;

    while (current)
    {
        if (ufs->iNodes[current->entryHeader->id]->content.entryType == DIRECTORY)
        {
            printf("%s%s%s\n", CYAN, current->entryHeader->name, RESET);
        }
        else
        {
            printf("%s\n", current->entryHeader->name);
        }

        current = current->nextNode;
    }
}

void traverseDirectory(UFS *ufs, Directory *directory, long inodeId, int level)
{
    INode *inode = ufs->iNodes[inodeId];

    if (inode->content.entryType != DIRECTORY)
    {
        return;
    }

    Node *current = inode->content.directory.entries.head;

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

        printf("%s\n", current->entryHeader->name);

        traverseDirectory(ufs, directory, current->entryHeader->id, level + 1);
        current = current->nextNode;
    }
}

void displayEntryHierarchy(UFS *ufs, Path *entryPath)
{
    if (entryPath->size == 1 && entryPath->entryNames[0][0] == '.')
    {
        printf("\n.\n"); // Root directory
        traverseDirectory(ufs, &ufs->iNodes[ROOT_INODE]->content.directory, ROOT_INODE, 1);
        return;
    }

    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return;
    }

    long idFound = findINodeIdInDirectory(&parentINode->content.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    if (ufs->iNodes[idFound]->content.entryType == ARCHIVE)
    {
        printf("\n%s\n", entryPath->entryNames[entryPath->size - 1]);
    }
    else
    {
        printf("\n%s\n", entryPath->entryNames[0]);
    }

    traverseDirectory(ufs, &ufs->iNodes[idFound]->content.directory, idFound, 1);
}

void displayFile(UFS *ufs, Path *entryPath)
{
    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return;
    }

    long idFound = findINodeIdInDirectory(&parentINode->content.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    if (ufs->iNodes[idFound]->content.entryType == DIRECTORY)
    {
        printf(FILE_IS_DIRECTORY, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    displayFileContent(&ufs->iNodes[idFound]->content.file);
}

void displayMetadata(UFS *ufs, Path *entryPath)
{
    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return;
    }

    long idFound = findINodeIdInDirectory(&parentINode->content.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return;
    }

    displayEntryMetadata(&ufs->iNodes[idFound]->metadata);
}