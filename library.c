#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

Master_Node* Get_head_MasterLL(){ //As well it generates the linked list
    FILE* fp = fopen("Songs.txt","r");
    if (fp == NULL) {
        perror("Error opening Songs.txt");
        return NULL;
    }
    char title[50];
    char artist_name[50];
    int duration;
    Master_Node* head = NULL;
    Master_Node* curr = NULL;
    while(fscanf(fp,"|%49[^|]|%49[^|]|%d|\n",title,artist_name,&duration)==3){
        song* s = malloc(sizeof(song));
        if (s == NULL) {
            perror("Failed to allocate memory for song");
            continue; // Skip this entry
        }
        strcpy(s->name,title);
        strcpy(s->artist,artist_name);
        s->duration = duration;
        Master_Node* newnode = malloc(sizeof(Master_Node));
        if (newnode == NULL) {
            perror("Failed to allocate memory for master node");
            free(s); // Clean up partially allocated memory
            continue;
        }
        newnode->song_address = s;
        newnode->next = NULL;

        if(head == NULL){
            head = newnode;
            curr = head;
            continue;
        }
        curr->next = newnode;
        curr = curr->next;
    }
    fclose(fp);
    return head;
}

Album* GetAlbum(char albumName[50],Album* AlbumN){
    //Getting the node in which the Album details are stored.
    //We need the head of the album.
    while(AlbumN!=NULL){
        if(strcmp(albumName,AlbumN->nameA)==0){ return AlbumN;}
        else{ AlbumN = AlbumN->nextA;}
    }
    return NULL;
}

song* GetAddress(char song[50],Master_Node* head){
    while(head != NULL){
        if(strcmp(head->song_address->name,song)==0){
                return head->song_address;
            }
            head = head->next;
    }
    printf("Song in GetAddress %s\n",song);

    return NULL;
}

static Album_Node* Get_head_SongA(char Album[50],Master_Node* head_master){
    char full_path[100];
    // Use snprintf for safe string formatting
    snprintf(full_path, sizeof(full_path), "%s.txt", Album);

    FILE* fp = fopen(full_path,"r");
    if (fp == NULL) {
        // This is not necessarily an error, the album file might just not exist yet.
        return NULL;
    }
    char song_name[50];
    Album_Node* head = NULL;
    Album_Node* temp = NULL;
    while(fgets(song_name,sizeof(song_name),fp)!=NULL){
        song_name[strcspn(song_name,"\n")]='\0';
        Album_Node* newnode = malloc(sizeof(Album_Node));
        if (newnode == NULL) {
            perror("Failed to allocate memory for album song node");
            continue;
        }
        newnode->next = NULL;
        newnode->song_address = GetAddress(song_name,head_master);
        if (head == NULL){
            head = newnode;
            temp = head;
            continue;
        }
        temp->next = newnode;
        temp = temp->next;
    }
    fclose(fp);
    return head;    
}

Album* Get_head_AlbumLL(Master_Node* head_master){
    FILE* fp = fopen("Albums.txt","r");
    if (fp == NULL) {
        perror("Error opening Albums.txt");
        return NULL;
    }
    char alb_name[50];
    Album* head = NULL;
    Album* temp = NULL;
    while(fgets(alb_name,sizeof(alb_name),fp)!=NULL){
        alb_name[strcspn(alb_name, "\n")] = '\0';
        Album* newnode = malloc(sizeof(Album));
        newnode->nextA = NULL;
        if (newnode == NULL) {
            perror("Failed to allocate memory for album node");
            continue;
        }
        strcpy(newnode->nameA,alb_name);
        newnode->album_head = Get_head_SongA(alb_name,head_master);
        if (head==NULL){
            head = newnode;
            temp = head;
            continue;
        }
        temp->nextA = newnode;
        temp = temp->nextA;
    }
    fclose(fp);
    return head;
}

void show_albums(Album* head){
    printf("Showing the list of albums:\n");
    while(head != NULL){
        printf("\t* %s\n",head->nameA);
        head = head->nextA;
    }
}

void show_songs(Master_Node* head){
    printf("Showing the list of songs:\n");
    while(head != NULL){
        printf("\t* %s\n",head->song_address->name);
        head = head->next;
    }
}

void Log(){

    FILE *fp = fopen("log.txt","r");
    char line[200];
    while(fgets(line,sizeof(line),fp)!=NULL){
        //fgets retains the newline character
        printf("%s",line);   
    }
    fclose(fp);
}

void FreePlaylist(Playlist_Node* head){
    if(head==NULL) return ;

    if(head->next == head){
        free(head);
        return ;
    }

    head->prev->next = NULL;

    Playlist_Node* currnode = head;
    Playlist_Node* tempnode = head;



    while(currnode!=NULL){
        currnode = currnode->next;
        free(tempnode);
        tempnode=currnode;
    }
}

void FreeMaster(Master_Node* head){
    Master_Node* cur = head;
    while(cur != NULL){
        Master_Node* next = cur->next;
        if (cur->song_address != NULL) {
            free(cur->song_address);
            cur->song_address = NULL;
        }
        free(cur);
        cur = next;
    }
}

void FreeAlbum(Album* Albumhead){
    if(Albumhead == NULL) return ;
    Album* tempA = Albumhead;
    while(tempA!=NULL){
        Album_Node* songhead = tempA->album_head;
        while(songhead!=NULL){
            Album_Node* currsong = songhead;
            songhead = songhead->next; // Advance pointer before freeing
            free(currsong);
        }
        // Correctly advance the album pointer before freeing the current one
        tempA=tempA->nextA;
        free(Albumhead);
        Albumhead = tempA;
    }
}

void WriteMaster(Master_Node* head){
    FILE *fp = fopen("Songs.txt","w");
    Master_Node* temp = head;
    while(temp != NULL){
        fprintf(fp,"|%s|%s|%d|\n",temp->song_address->name,temp->song_address->artist,temp->song_address->duration);
        temp = temp->next;
    }
    fclose(fp);
}
void WritePlaylist(Playlist* P){
    Playlist_Node* temp = P->head;
    if(temp==NULL){
        FILE* fp = fopen("playlist.txt","w");
        fprintf(fp,"Current song: \"\"");
        return;
    }
    
    FILE *fp = fopen("playlist.txt","w");
    fprintf(fp,"Current song: \"%s\"\n",P->current_song->song_address->name);
    
    do{
        fprintf(fp, "\"%s\"\n", temp->song_address->name);
        temp = temp->next;
    }while(temp!=P->head);
    fclose(fp);
}
void WriteAlbum(Album* AlbumDet){
    FILE* fpalbum = fopen("Albums.txt","w");
    while (AlbumDet != NULL) {
        fprintf(fpalbum,"%s\n",AlbumDet->nameA);
        if(AlbumDet->Write == 'y'){ 
            char albfile[54];
            strcpy(albfile,AlbumDet->nameA);
            strcat(albfile,".txt");
            FILE* fp = fopen(albfile,"w");
            Album_Node* currnode = AlbumDet->album_head;
            while(currnode != NULL){
                fprintf(fp, "%s\n", currnode->song_address->name);
                currnode = currnode->next;
            }
            fclose(fp);
        }
        AlbumDet = AlbumDet->nextA;
    }
    fclose(fpalbum);
}