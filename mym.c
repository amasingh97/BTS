#include "mym.h"
#include "stdio.h"
#include "stdlib.h"

#define GREEN   "\033[32m"
#define RED "\033[31m"
#define BOLDYELLOW "\033[01;33m"
#define BOLDRED "\033[1;31m"
#define RESET   "\033[0m"

#define getName(var) #var

MEM_MAN * myminit(int size, char strategy){
    MEM_MAN * newManager = create_mem_man(size, strategy);
    return newManager;
} //Größe des Heaps --> max Seiten

void mymterm(MEM_MAN * heap){
    term_mem(heap);
} //free den ganzen Speicher

void error(char * name){
    printf("Not enough memory for: %s returning NULL\n", name);
}

MEM_NODE * FirstFit(MEM_MAN * heap, int offset, char * name){
    int index = 0;
    int freecnt = 0;
    MEM_NODE * temp = heap->First;

    while (index < heap->size){
        if(!temp->occupied){
            ++freecnt;
        }
        else{
            freecnt = 0;
        }

        if(freecnt == offset) {
            //ALLOKIEREN
            MEM_NODE * start = temp;
            start->occupied = true;
            for (int i = 1; i < offset; ++i) {
                start = start->Prev;
                start->occupied = true;
            }
            start->len = offset;
            start->name = name;
            return start;
        }

        temp = temp->Next;
        ++index;
    }
    error(name);
    return NULL;
}

MEM_NODE * NextFit(MEM_MAN * heap, int offset, char * name){

    int index = 0;
    int freecnt = 0;
    MEM_NODE * temp = heap->Last;
    if(temp->Next == NULL) temp = heap->First;

    while (index < heap->size){
        if(!temp->occupied){
            ++freecnt;
        }
        else{
            freecnt = 0;
        }

        if(freecnt == offset) {
            //ALLOKIEREN
            MEM_NODE * start = temp;
            start->occupied = true;
            for (int i = 1; i < offset; ++i) {
                start = start->Prev;
                start->occupied = true;
            }
            start->len = offset;
            heap->Last = start;
            start->name = name;
            return start;
        }
        if(temp->Next == NULL) {
            freecnt = 0;
            temp = heap->First;
        }
        else temp = temp->Next;
        ++index;
    }
    error(name);
    return NULL;
}

MEM_NODE * BestFit(MEM_MAN * heap, int offset, char * name){
    //struct for free_blocks
    struct block{
        int len;
        MEM_NODE* startblock;
    };
    typedef struct block BLOCKS;

    //calloc some memory for the free blocks
    BLOCKS* free_blocks = (BLOCKS *)calloc(((heap->size)/2),sizeof(BLOCKS));

    //the magic starts
    if(free_blocks) {
        int index = 0, freecnt = 0, structcn = 0;
        MEM_NODE *temp = heap->First;
        MEM_NODE *temp_freeblock = temp;
        //search for min free blocks
        while (index < heap->size) {
            if(!temp->occupied) {
                structcn = 0;
                while (temp_freeblock){
                    if (!temp_freeblock->occupied) {
                        ++structcn;
                    }
                    else if(temp_freeblock->occupied || temp_freeblock == heap->Last){
                        break;
                    }
                    temp_freeblock = temp_freeblock->Next;
                }
            }
            if(temp_freeblock){
                if(structcn >= offset) {
                    if(free_blocks->len == 0){
                        free_blocks->len = structcn;
                        free_blocks->startblock = temp;
                    }
                    else if(free_blocks->len > structcn){
                        free_blocks->len = structcn;
                        free_blocks->startblock = temp;
                    }
                }
                else if(temp_freeblock->occupied){
                    while(temp_freeblock->occupied && temp_freeblock->Next) {
                        temp_freeblock = temp_freeblock->Next;
                    }
                    temp = temp_freeblock;
                    ++freecnt;
                    ++index;
                }
                else{
                    break;
                }
            }
            else{
                if(structcn >= offset) {
                    if(free_blocks->len == 0){
                        free_blocks->len = structcn;
                        free_blocks->startblock = temp;
                    }
                    else if(free_blocks->len > structcn){
                        free_blocks->len = structcn;
                        free_blocks->startblock = temp;
                    }
                }
                else {
                    break;
                }
            }
        }

        if (free_blocks->len >= offset) {
            MEM_NODE * start = free_blocks->startblock;
            MEM_NODE * copy_start = start;
            start->occupied = true;
            start->len = offset;
            start->name = name;
            for (int i = 1; i < offset; ++i) {
                start = start->Next;
                start->occupied = true;
            }
            return copy_start;
        }
    }

    error(name);
    return NULL;

}

MEM_NODE * WorstFit(MEM_MAN * heap, int offset, char * name){
    //struct for free_blocks
    struct block{
        int len;
        MEM_NODE* startblock;
    };
    typedef struct block BLOCKS;

    //calloc some memory for the free blocks
    BLOCKS* free_blocks = (BLOCKS *)calloc(((heap->size)/2),sizeof(BLOCKS));

    //the magic starts
    if(free_blocks) {
        int index = 0, freecnt = 0, structcn = 0;
        MEM_NODE *temp = heap->First;
        MEM_NODE *temp_freeblock = temp;
        //search for min free blocks
        while (index < heap->size) {
            if(!temp->occupied) {
                structcn = 0;
                while (temp_freeblock){
                    if (!temp_freeblock->occupied) {
                        ++structcn;
                    }
                    else if(temp_freeblock->occupied || temp_freeblock == heap->Last){
                        break;
                    }
                    temp_freeblock = temp_freeblock->Next;
                }
            }
            if(temp_freeblock){
                if(structcn >= offset) {
                    if(free_blocks->len == 0){
                        free_blocks->len = structcn;
                        free_blocks->startblock = temp;
                    }
                    else if(free_blocks->len < structcn){
                        free_blocks->len = structcn;
                        free_blocks->startblock = temp;
                    }
                }
                else if(temp_freeblock->occupied){
                    while(temp_freeblock->occupied && temp_freeblock->Next) {
                        temp_freeblock = temp_freeblock->Next;
                    }
                    temp = temp_freeblock;
                    ++freecnt;
                    ++index;
                }
                else{
                    break;
                }
            }
            else{
                if(structcn >= offset) {
                    if(free_blocks->len == 0) {
                        free_blocks->len = structcn;
                        free_blocks->startblock = temp;
                    }
                    else if(free_blocks->len < structcn){
                        free_blocks->len = structcn;
                        free_blocks->startblock = temp;
                    }
                }
                else {
                    break;
                }
            }
        }

        if (free_blocks->len >= offset) {
            MEM_NODE *start = free_blocks->startblock;
            MEM_NODE *copy_start = start;
            start->occupied = true;
            start->len = offset;
            start->name = name;
            for (int i = 1; i < offset; ++i) {
                start = start->Next;
                start->occupied = true;
            }
            return copy_start;
        }
    }

    error(name);
    return NULL;

}

MEM_NODE * mymmalloc(MEM_MAN * heap, int len, char * name){
    switch (heap->strategy){
        case 'f':
            return FirstFit(heap, len, name);
        case 'n':
            return NextFit(heap, len, name);
        case 'b':
            return BestFit(heap, len, name);
        case 'w':
            return WorstFit(heap, len, name);
        default:
            puts("Strategy not available!");
    }
} //Bereich allozieren


void mymfree(MEM_NODE * to_free){
    int block_length = to_free->len;
    to_free->len = 1;
    to_free->name = NULL;
    MEM_NODE * temp = to_free;
    for (int i = 0; i < block_length; ++i) {
        temp->occupied = false;
        temp = temp->Next;
    }
} //free eine Einheit

void mymdump(MEM_MAN * heap, FILE * fp){
    if(fp){
        switch (heap->strategy){
            case 'f':
                fprintf(fp,BOLDYELLOW"First-Fit-Strategie:\n"RESET);
                break;
            case 'n':
                fprintf(fp,BOLDYELLOW"Next-Fit-Strategie:\n"RESET);
                break;
            case 'b':
                fprintf(fp,BOLDYELLOW"Best-Fit-Strategie:\n"RESET);
                break;
            case 'w':
                fprintf(fp,BOLDYELLOW"Worst-Fit-Strategie:\n"RESET);
                break;
        }
        MEM_NODE * node = heap->First;
        for (int i = 0; i < heap->size; ++i) {
            if(node->name) fprintf(fp, BOLDRED"----------%s----------\n"RESET, node->name);
            fprintf(fp, "┌───────────────────┐\n");
            fprintf(fp, "│");
            node->occupied ? fprintf(fp, RED" Block %3d: Besetzt"RESET, i+1): fprintf(fp, GREEN" Block %3d: Frei   "RESET, i+1);
            fprintf(fp, "│\n");
            fprintf(fp, "└───────────────────┘\n");
            node = node->Next;
        }
    }
} // printed den momentanen Heap
