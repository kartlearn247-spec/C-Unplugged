#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "struct.h"
#include "library.h"

void Create_Album(char album[50],Album* head){
    
    char albumfile[strlen(album)+5];
    strcpy(albumfile, album);
    strcat(albumfile, ".txt");
    FILE* fp = fopen(albumfile,"w");
    fclose(fp);
    Album* newnode = malloc(sizeof(Album));
    newnode->nextA=head->nextA;
    head->nextA = newnode;
    strcpy(newnode->nameA, album);
    newnode->album_head = NULL;
    newnode->Write='y';
    printf("Album is created\n");
}

Album* Del_Album(char album[50], Album* head) {
    if (head == NULL) {
        printf("There are no albums to delete.\n");
        return NULL;
    }
    char albfile[55];
    strcpy(albfile,album);
    strcat(albfile,".txt");
    if(strcmp(head->nameA,album)==0){
        Album_Node* song_node = head->album_head;
        while (song_node != NULL) {
            Album_Node* next_song = song_node->next;
            free(song_node);
            song_node = next_song;
        } 
        Album* nexthead = head->nextA;           
        free(head);
        FILE* fp = fopen(albfile,"w");
        fclose(fp);
        printf("The album is deleted.\n");
        return nexthead;
    }

    Album* prev = head;
    Album* curr = head->nextA;

    while (curr != NULL) {
        if (strcmp(curr->nameA, album) == 0) {
            // Found the album. Unlink it from the list.
            prev->nextA = curr->nextA;

            // Free the list of songs within the album
            Album_Node* song_node = curr->album_head;
            while (song_node != NULL) {
                Album_Node* next_song = song_node->next;
                free(song_node);
                song_node = next_song;
            }
            // Free the album struct itself
            free(curr);
            
            FILE* fp = fopen(albfile,"w");
            fclose(fp);
            printf("The album is deleted.\n");
            return head;
        }
        prev = curr;
        curr = curr->nextA;
    }

    printf("The album is not found\n");
    return head;
}

void Add_song_album(char songname[50],char album[50],Master_Node* master,Album* Album_node){
    song* newsong = GetAddress(songname,master);
    if(newsong==NULL){
        printf("The song is not present in the master list.\n");
        return;
    }
    Album* AlbumDet=GetAlbum(album,Album_node);
    if(AlbumDet==NULL){
        printf("The album is not found.\n");
        return;
    }
 
    Album_Node* head = AlbumDet->album_head;
    Album_Node* newnode = malloc(sizeof(Album_Node));
    newnode->song_address=newsong;
    newnode->next=NULL;
    if(head==NULL) {
        AlbumDet->album_head=newnode;
        AlbumDet->Write='y';
        printf("Song is added to the album\n");
        return;
    }
    if(strcmp(head->song_address->name,songname)==0){
        printf("The song already exists.\n");
        free(newnode);
        return ;
    }

    while(head->next!=NULL){
        if(strcmp(head->next->song_address->name,songname)==0){
            printf("The song already exists.\n");
            free(newnode);
            return;
        }
        else{
            head=head->next;
        }
    }
    
    head->next=newnode;
    AlbumDet->Write='y';

    printf("Song is added to the album\n");
    return;
}
      
void Del_song_album(char songname[50],char albumname[50],Album* albumDet){
    Album* Albumdet=GetAlbum(albumname,albumDet);
    if(Albumdet==NULL){
        printf("Could not find the album.\n");
        return;
    }
    
    Album_Node* currnode = Albumdet->album_head;
    if(currnode == NULL){
        printf("The album is empty.\n");
        return;
    }
    if(strcmp(currnode->song_address->name,songname)==0){
        Albumdet->album_head = currnode->next;
        free(currnode);
        Albumdet->Write='y';

        printf("The song is removed from the album.\n");
        return;
    }
    while(currnode->next != NULL){
        if(strcmp(currnode->next->song_address->name,songname)==0){
            Album_Node* delnode = currnode->next;
            currnode->next = delnode->next;
            free(delnode);
            Albumdet->Write='y';
            printf("The song is removed from the album.\n");
            return;
        }
        else{
            currnode = currnode->next;
        }
    }
    printf("Song not found in the album.\n");
    return;
}

void Show_songs_album(char album[50],Album* headAlbumDet){
    Album* Album_det = GetAlbum(album,headAlbumDet);
    if(Album_det==NULL){
        printf("Could not find the album.\n");
        return;
    }
    Album_Node* currnode = Album_det->album_head;
    if(currnode==NULL){
        printf("The album is empty.\n");
        return;
    }

    printf("\n--- Songs in Album: %s ---\n", Album_det->nameA);
    while(currnode!=NULL){
        if (currnode->song_address != NULL) {
            printf("  Title:    %s\n", currnode->song_address->name);
            printf("  Artist:   %s\n", currnode->song_address->artist);
            printf("  Duration: %d seconds\n\n", currnode->song_address->duration);
        }
        currnode = currnode->next;
    }
    printf("---------------------------------\n");
    return;
}