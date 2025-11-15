#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "library.h"
#include<stdlib.h>

Playlist_Node* Get_Head(Master_Node* master_head,Playlist* P){
    //This function creates a doubly linked circular linked list
    FILE* fp = fopen("playlist.txt","r");
    char line[50];
    char cur_song[50];
    fscanf(fp,"Current song: \"%[^\"]\"",cur_song);
    fgetc(fp); //consume a new line
    // printf("curr song %s\n",cur_song);
    Playlist_Node* head = NULL;
    Playlist_Node* temp = NULL;
    
    
    int flag = 0;
    while(fscanf(fp,"\"%[^\"]\"\n",line)==1){
        // printf("line :%s\n",line);
        flag = 1;
        Playlist_Node* newnode = malloc(sizeof(Playlist_Node));
        newnode->next = NULL;
        newnode->prev = NULL;
        newnode->song_address = GetAddress(line,master_head);   
        // printf("1\n");
        // printf("newnode sonadd name : %sk\n",newnode->song_address->name);
        if(strcmp(newnode->song_address->name,cur_song)==0){
            P->current_song = newnode;
            // printf("4\n");
        }
        if(head==NULL){
            // printf("2\n");

            head = newnode;
            temp = head;
        }
        else{
            // printf("3\n");
            temp->next = newnode;
            newnode->prev = temp;
            temp = temp->next;
        }
    }
    if(flag==0){
        P->current_song=NULL;
        P->head=NULL;   
    }
    else{
        temp->next=head;
        head->prev=temp;
    }
    fclose(fp);

    return head;
}

void show_Playlist(Playlist* playlst){
    
    if(playlst->head == NULL){
        printf("The playlist is empty.\n");
        return;
    }

    printf("\n--- Playlist ---\n");
    Playlist_Node* temp = playlst->head;
    do {
        if (temp == playlst->current_song) {
            printf("--> Current Song:\n");
        }
        if (temp->song_address) {
            printf("    Title:    %s\n", temp->song_address->name);
            printf("    Artist:   %s\n", temp->song_address->artist);
            printf("    Duration: %d seconds\n\n", temp->song_address->duration);
        }
        temp = temp->next;
    } while (temp != playlst->head);
    printf("----------------\n");
}

void Del_song_Playlist(char songname[50],Playlist* p){
    //remove a song from the playlist
    if(p->head==NULL){
        printf("The playlist is empty\n");
        return;
    }
    // Case 1: Deleting the only node in the playlist
    if(p->head->next == p->head && strcmp(p->head->song_address->name, songname) == 0){
        free(p->head);
        p->head = NULL;
        p->current_song = NULL;
        printf("Song is removed successfully\n");
        return;
    }

    Playlist_Node* nodep = p->head;
    Playlist_Node* headp = p->head;

    do{
        if(strcmp(nodep->next->song_address->name,songname)==0){
            
            Playlist_Node* delnode = nodep->next;
            if(delnode == headp){
                p->head = headp->next;
            }
            else if(delnode == p->current_song){
                p->current_song = delnode->next;
            }
            nodep->next = delnode->next;
            delnode->next->prev = nodep;
            free(delnode);
            printf("Song is removed successfully\n");
            return;
        }
        else{
            nodep = nodep->next;
        }
    
    }while(nodep != headp);

    printf("Could not find the song. Try Again\n");
    return;
}

void Add_song_Playlist(char songname[50],Master_Node* master_head,Playlist* P){
    //Add song to the playlist from master linked list
    song* sgAddress = GetAddress(songname,master_head);
    if(sgAddress==NULL){
        printf("The song you typed did not exist in the library.Try Again\n");
        return;
    }
    else{      
        Playlist_Node* newnodep = malloc(sizeof(Playlist_Node));
        newnodep->song_address = sgAddress;

        // If playlist is empty
        if(P->head == NULL){
            P->head = newnodep;
            P->current_song = newnodep;
            newnodep->next = newnodep;
            newnodep->prev = newnodep;
        }
        else{
            //inserting after the current song
            Playlist_Node* currnext = P->current_song->next;
            
            P->current_song->next = newnodep;
            newnodep->prev = P->current_song;

            currnext->prev = newnodep;
            newnodep->next = currnext;
        }

        printf("The song is added to the playlist\n");
        return;
    }
    
}

void Add_album_playlist(char albumName[50],Album* AlbumN,Playlist* P){

    Album* album = GetAlbum(albumName,AlbumN);
    Playlist_Node* temphead=NULL;
    Playlist_Node* currnode=NULL;
    if(album==NULL){
        printf("The album is not found.Try Again\n");
        return;
    }
    else{
        Album_Node* sgnode = album->album_head;
        
        while(sgnode != NULL){
            Playlist_Node* newnode = malloc(sizeof(Playlist_Node));
            newnode->next = NULL;
            newnode->prev = NULL;
            newnode->song_address = sgnode->song_address;
            sgnode = sgnode->next;
            if(temphead==NULL){
                temphead=newnode;
                currnode=temphead;
            }
            else{
                currnode->next=newnode;
                newnode->prev=currnode;
                currnode = currnode->next;
            }
        }
        if(P->head == NULL){
            P->head = temphead;
            P->current_song = temphead;
            currnode->next = temphead;
            temphead->prev = currnode;
            printf("Album added to the playlist.\n");
            return;
        }
        else{
            Playlist_Node* currnext = P->current_song->next;
            temphead->prev = P->current_song;
            P->current_song->next = temphead;
            currnext->prev = currnode;
            currnode->next = currnext;
            printf("Album added to the playlist.\n");
            return;
        }
    }
    
}

void Next_song(Playlist* plylst){
    if(plylst->current_song==NULL){
        printf("There is no songs in the Playlist.\n");
        return;
    }
    plylst->current_song = plylst->current_song->next;
    printf("Playing next song\n");
}

void Prev_song(Playlist* plylst){
    if(plylst->current_song==NULL){
        printf("There is no songs in the Playlist.\n");
        return;
    }
    plylst->current_song = plylst->current_song->prev;
    printf("Playing the previous song\n");
}