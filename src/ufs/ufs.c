#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "ufs.h"
#include "../miscelaneous/error.h"
#include "../miscelaneous/verbose.h"

#define DELIMITER "/"
#define ROOT_INODE 0

void initializeUFS(UFS *ufs, long maxINodes, bool mode, int blockSize)
{
    ufs->maxINodes = maxINodes;
    ufs->iNodeCount = 1;
    ufs->verbose = mode;
    initializeMemory(&ufs->memory, maxINodes, 100);

    ufs->iNodes = (INode **) malloc(maxINodes * sizeof(INode *));

    if (!ufs->iNodes)
    {
        printf(ALLOCATION_ERROR, "UFS INodes");
        exit(EXIT_FAILURE);
    }

    ufs->iNodes[ROOT_INODE] = initializeINode();
    initializeINodeWithContent(ufs->iNodes[ROOT_INODE], ROOT_INODE, "/", DIRECTORY, &ufs->memory);

    for (long i = 1; i < maxINodes; i++)
    {
        ufs->iNodes[i] = initializeINode();
    }

    initializeLinkedListINode(&ufs->freeINodes);

    for (long i = 1; i < maxINodes; i++)
    {
        if (!insertNodeINode(&ufs->freeINodes, i))
        {
            exit(EXIT_FAILURE);
        }
    }
}

INode *createSingleNode(UFS *ufs, char *entryName, enum EntryType entryType)
{
    long freeINode = ufs->freeINodes.head->id;
    initializeINodeWithContent(ufs->iNodes[freeINode], freeINode, entryName, entryType, &ufs->memory);

    if (removeNodeINode(&ufs->freeINodes, freeINode))
    {
        ufs->iNodeCount++;
        return ufs->iNodes[freeINode];
    }

    return NULL;
}

bool deleteSingleNode(UFS *ufs, INode *parentINode, long iNodeId, char *entryName)
{
    insertNodeINode(&ufs->freeINodes, iNodeId);

    bool status = removeEntry(&parentINode->content.directory, entryName);

    if (ufs->iNodes[iNodeId]->content.entryType == ARCHIVE)
    {
        freeFile(&ufs->iNodes[iNodeId]->content.file, &ufs->memory);
    }

    freeINode(ufs->iNodes[iNodeId]);
    ufs->iNodes[iNodeId] = NULL;

    return status;
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

void getPath(char *pathString, Path *path, bool last)
{
    pathString[0] = '\0';

    if(path->size == 1)
    {
        if(!last)
        {
            strcat(pathString, ".");
        }
        else
        {
            strcat(pathString, path->entryNames[path->size - 1]);
        }
    }
    else
    {
        for(int i = 0; i < path->size - 1; i++)
        {
            strcat(pathString, path->entryNames[i]);
            if(i < path->size - 2)
            {
                strcat(pathString, "/");
            }
        }
        if(last)
        {
            strcat(pathString, "/");
            strcat(pathString, path->entryNames[path->size - 1]);
        }
    }
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

    if(addEntry(&parentINode->content.directory, createSingleNode(ufs, entryPath->entryNames[entryPath->size - 1], entryType)->header))
    {
        if(ufs->verbose == true)
        {
            char path[UCHAR_MAX];
            getPath(path, entryPath, false);

            if(entryType == ARCHIVE)
            {
                printf(VERBOSE_TOUCH, entryPath->entryNames[entryPath->size - 1], path);
            }
            else
            {
                printf(VERBOSE_MKDIR, entryPath->entryNames[entryPath->size - 1], path);
            }
        }

        return true;
    }

    return false;
}

bool checkPathInAnother(Path *entryPath, Path *newEntryPath)
{
    if (entryPath->size < newEntryPath->size)
    {
        for (int i = 0; (i < entryPath->size && i < newEntryPath->size); i++)
        {
            if (strcmp(entryPath->entryNames[i], newEntryPath->entryNames[i]) != 0)
            {
                return true;
            }
        }
    }
    else
    { return true; }

    return false;
}

bool moveEntry(UFS *ufs, Path *entryPath, Path *newEntryPath)
{
    char pathString[UCHAR_MAX];
    char newPathString[UCHAR_MAX];
    getPath(pathString, entryPath, false);
    
    INode *parentINode = findParentINode(ufs, entryPath);
    INode *newParentINode = findParentINode(ufs, newEntryPath);

    if (!parentINode || !newParentINode)
    {
        return false;
    }

    char *entryName = entryPath->entryNames[entryPath->size - 1];
    char *newEntryName = newEntryPath->entryNames[newEntryPath->size - 1];

    Directory *entryDirectory = &parentINode->content.directory;
    Directory *newEntryDirectory = &newParentINode->content.directory;

    long foundId = findINodeIdInDirectory(entryDirectory, entryName);
    long newFoundId = findINodeIdInDirectory(newEntryDirectory, newEntryName);

    if (foundId == -1)
    {
        printf(FILE_NOT_FOUND, entryName);
        return false;
    }

    // caso os paths sejam iguais, retorna erro
    if (foundId == newFoundId)
    {
        if (ufs->iNodes[foundId]->content.entryType == ARCHIVE)
        { printf(MOVE_TO_ARCHIVE, newEntryName); }
        else
        { printf(MOVE_TO_ITSELF, entryName); }
        return false;
    }

    // confere se o primeiro path esta dentro do segundo path
    if (!checkPathInAnother(entryPath, newEntryPath))
    {
        printf(MOVE_TO_CHILD, entryName);
        return false;
    }

    INode *iNode = ufs->iNodes[foundId];

    // segundo path nao existe(nao tem problema)
    if (newFoundId == -1)
    {
        // caso o segundo path nao exista e esteja no mesmo diretorio do primeiro, chama o rename
        if (parentINode->header->id == newParentINode->header->id)
        {
            if(changeINodeEntryName(iNode, newEntryName))
            {
                if(ufs->verbose == true)
                {
                    if(iNode->content.entryType == ARCHIVE)
                    {
                        printf(VERBOSE_RENAME_FILE, entryName, newEntryName);
                    }
                    else
                    {
                        printf(VERBOSE_RENAME_DIRECTORY, entryName, newEntryName);
                    }
                }

                return true;
            }
            
            return false;
        }

        // caso o segundo path nao exista e esteja num diretorio diferente do primeiro, ele eh movido e chama o rename
        if (removeEntry(entryDirectory, entryName))
        {
            if (addEntry(newEntryDirectory, iNode->header))
            {
                if(changeINodeEntryName(iNode, newEntryName))
                {
                    if(ufs->verbose == true)
                    {
                        getPath(newPathString, newEntryPath, false);

                        if(iNode->content.entryType == ARCHIVE)
                        {
                            printf(VERBOSE_MV_RENAME_FILE, entryName, newEntryName, pathString, newPathString);
                        }
                        else
                        {
                            printf(VERBOSE_MV_RENAME_DIRECTORY, entryName, newEntryName, pathString, newPathString);
                        }
                    }

                    return true;
                }
                
                return false;
            }
        }

        return false;
    }

    // segundo path existe
    INode *newINode = ufs->iNodes[newFoundId];

    // caso o segundo path exista e for um file, retorna erro
    if (newINode->content.entryType == ARCHIVE)
    {
        printf(MOVE_TO_ARCHIVE, newEntryName);
        return false;
    }

    // caso o segundo path exista e for um diretorio, ele eh movido
    if (findINodeIdInDirectory(&newINode->content.directory, entryName) == -1)
    {
        if (removeEntry(entryDirectory, entryName))
        {
            if(addEntry(&newINode->content.directory, iNode->header))
            {
                if(ufs->verbose == true)
                {
                    getPath(newPathString, newEntryPath, true);

                    if(iNode->content.entryType == ARCHIVE)
                    {
                        printf(VERBOSE_MV_FILE, entryName, pathString, newPathString);
                    }
                    else
                    {
                        printf(VERBOSE_MV_DIRECTORY, entryName, pathString, newPathString);
                    }
                }

                return true;
            }
            
            return false;
        }
    }
    else
    {
        printf(NAME_EXISTS_IN_DIRECTORY, entryName, newINode->header->name);
        return false;
    }

    return false;
}

bool deleteEntryTraversal(UFS *ufs, long iNodeId)
{
    INode *iNode = ufs->iNodes[iNodeId];

    if (iNode->content.entryType != DIRECTORY)
    {
        return true;
    }

    Node *current = iNode->content.directory.entries.head;
    bool status = true;

    while (current)
    {
        Node *nodeToDelete = current;

        if (!deleteEntryTraversal(ufs, current->entryHeader->id))
        {
            return false;
        }

        current = current->nextNode;

        if (!(status = deleteSingleNode(ufs, ufs->iNodes[iNodeId], nodeToDelete->entryHeader->id,
                                        nodeToDelete->entryHeader->name)))
        {
            return false;
        }
    }

    return status;
}

bool deleteEntry(UFS *ufs, Path *entryPath, bool isTraversalDeletion)
{
    char nameString[UCHAR_MAX];
    char pathString[UCHAR_MAX];
    strcpy(nameString, entryPath->entryNames[entryPath->size - 1]);
    getPath(pathString, entryPath, false);
    
    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        printf(DIRECTORY_NOT_FOUND);
        return false;
    }

    long idFound = findINodeIdInDirectory(&parentINode->content.directory,
                                          entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return false;
    }

    if (ufs->iNodes[idFound]->content.entryType == ARCHIVE)
    {
        if(deleteSingleNode(ufs, parentINode, idFound, entryPath->entryNames[entryPath->size - 1]))
        {
            if(ufs->verbose == true)
            {
                printf(VERBOSE_RM, nameString, pathString);
            }

            return true;
        }
        
        return false;
    }

    if (!isTraversalDeletion)
    {
        printf(DIRECTORY_IS_NOT_EMPTY);
        return false;
    }

    if (entryPath->size == 1)
    {
        if(deleteEntryTraversal(ufs, idFound) && deleteSingleNode(ufs, ufs->iNodes[ROOT_INODE], idFound, ufs->iNodes[idFound]->header->name))
        {
            if(ufs->verbose == true)
            {
                printf(VERBOSE_RM_R, nameString, pathString);
            }

            return true;
        }

        return false;
    }

    if(deleteEntryTraversal(ufs, idFound) && deleteSingleNode(ufs, parentINode, idFound, ufs->iNodes[idFound]->header->name))
    {
        if(ufs->verbose == true)
        {
            printf(VERBOSE_RM_R, nameString, pathString);
        }
        
        return true;
    }

    return false;
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