#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
#include "struct.h"
#include "album.h"
#include "playlist.h"

int main()
{
    printf("Welcome to C_unplugged\n");
    printf("Enter help to view valid commands\n");
    FILE *f_log = fopen("log.txt", "a");

    // --- Defining the values of the head of each linked list ---
    Master_Node *head_master = Get_head_MasterLL();
    Album *head_album_det = Get_head_AlbumLL(head_master);
    Playlist *PlaylistVar = malloc(sizeof(Playlist));
    PlaylistVar->head = NULL;
    PlaylistVar->current_song = NULL;
    Playlist_Node *head_playlist = Get_Head(head_master, PlaylistVar);
    PlaylistVar->head = head_playlist;
    // printf("A\n");
    while (1)
    {
        printf(">");
        char s[100];
        // printf("A\n");


        // getting the input
        if (fgets(s, 100, stdin) == NULL)
        {
            fprintf(f_log, "[LOG] EOF reached (user exited) or input error.\n");
            continue;
        }
        else
        {
            fprintf(f_log, "[LOG ]User Command : %s", s);
            // Now remove newline for parsing
            s[strcspn(s, "\n")] = '\0';
        }

        // Now the \n is removed
        // help
        if (strcmp(s, "help") == 0)
        {
            printf("Library commands:\n");
            printf("\t *Show Albums\n");
            printf("\t *Show Songs\n");

            printf("Album commands:\n");
            printf("\t* Create Album \"Album name\"\n");
            printf("\t* Delete Album \"Album Name\"\n");
            printf("\t* Add Song Album \"Song Name\" \"Album Name\"\n");
            printf("\t* Delete Song Album \"Song Name\" \"Album Name\"\n");
            printf("\t* Show Songs Album \"Album Name\"\n");

            printf("Playlist commands:\n");
            printf("\t* Show Playlist\n");
            printf("\t* Add Song Playlist \"Song Name\"\n");
            printf("\t* Delete song Playlist \"Song Name\"\n");
            printf("\t* Add Album Playlist \"Album Name\" \n");
            printf("\t* Next Song \n");
            printf("\t* Previous Song \n");

            printf("View Log\n");
            continue;
        }

        // printf("A\n");

        // Library functions
        if (strcmp(s, "Show Albums") == 0)
        {
            // This should ideally call: show_albums(album_list);
            show_albums(head_album_det);
            continue;
        }

        if (strcmp(s, "Show Songs") == 0)
        {
            // This should ideally call: show_songs(master_list);
            show_songs(head_master);
            continue;
        }

        // Album fucntions
        if (strncmp(s, "Create Album ", 13) == 0)
        {
            char alb_name[50];
            int N_words = sscanf(s, "Create Album \"%[^\"]\"", alb_name);
            if (N_words == 1)
                Create_Album(alb_name, head_album_det);
            else
            {
                printf("ERROR: invalid command format\n");
                fprintf(f_log, "[ERROR] Invalid Command format\n");
            }
            continue;
        }

        if (strncmp(s, "Delete Album ", 13) == 0)
        {
        
            char alb_name[50];
            int N_words = sscanf(s, "Delete Album \"%[^\"]\"", alb_name);
            if (N_words == 1)
                head_album_det = Del_Album(alb_name, head_album_det);
            else
            {
                printf("ERROR: invalid command format\n");
                fprintf(f_log, "[ERROR] Invalid Command format\n");
            }
            continue;
        }

        if (strncmp(s, "Add Song Album ", 15) == 0)
        {
            // Renamed variables for clarity
            char song_name[50], alb_name[50];
            int N_words = sscanf(s, "Add Song Album \"%[^\"]\" \"%[^\"]\"", song_name, alb_name);
            if (N_words == 2)
            {

                Add_song_album(song_name, alb_name, head_master, head_album_det);
            }
            else
            {
                printf("ERROR: invalid command format\n");
                fprintf(f_log, "[ERROR] Invalid Command format\n");
            }
            continue;
        }

        if (strncmp(s, "Delete Song Album ", 18) == 0)
        {
            char alb_name[50], song_name[50];
            int N_words = sscanf(s, "Delete Song Album \"%[^\"]\" \"%[^\"]\"", song_name, alb_name);
            if (N_words == 2)
            {
                Del_song_album(song_name, alb_name, head_album_det);
            }
            else
            {
                printf("ERROR: invalid command format\n");
                fprintf(f_log, "[ERROR] Invalid Command format\n");
            }
            continue;
        }

        if (strncmp(s, "Show Songs Album ", 17) == 0)
        {
            char alb_name[50];
            int N_words = sscanf(s, "Show Songs Album \"%[^\"]\"", alb_name);
            if (N_words == 1)
            {
                Show_songs_album(alb_name, head_album_det);
            }
            else
            {
                printf("ERROR: invalid command format\n");
                fprintf(f_log, "[ERROR] Invalid Command format\n");
            }
            continue;
        }

        // Playlist functions
        if (strcmp(s, "Show Playlist") == 0)
        {
            show_Playlist(PlaylistVar);
            continue;
        }

        if (strncmp(s, "Add Song Playlist ", 18) == 0)
        {
            char song_name[50];
            int N_words = sscanf(s, "Add Song Playlist \"%[^\"]\"", song_name);
            if (N_words == 1)
            {
                Add_song_Playlist(song_name, head_master, PlaylistVar);
            }
            else
            {
                printf("ERROR: invalid command format\n");
                fprintf(f_log, "[ERROR] Invalid Command format\n");
            }
            continue;
        }

        if (strncmp(s, "Delete Song Playlist ", 21) == 0)
        {
            char song_name[50];
            int N_words = sscanf(s, "Delete Song Playlist \"%[^\"]\"", song_name);
            if (N_words == 1)
            {
                Del_song_Playlist(song_name, PlaylistVar);
            }
            else
            {
                printf("ERROR: invalid command format\n");
                fprintf(f_log, "[ERROR] Invalid Command format\n");
            }
            continue;
        }

        if (strncmp(s, "Add Album Playlist ", 19) == 0)
        {
            char alb_name[50];
            int N_words = sscanf(s, "Add Album Playlist \"%[^\"]\"", alb_name);
            if (N_words == 1)
            {
                Add_album_playlist(alb_name, head_album_det, PlaylistVar);
            }
            else
            {
                printf("ERROR: invalid command format\n");
                fprintf(f_log, "[ERROR] Invalid Command format\n");
            }
            continue;
        }

        if (strcmp(s, "Next Song") == 0)
        {
            Next_song(PlaylistVar);
            continue;
        }

        if (strcmp(s, "Previous Song") == 0)
        {
            Prev_song(PlaylistVar);
            continue;
        }

        if (strcmp(s, "View Log") == 0)
        {
            Log();
            continue;
        }
        if(strcmp(s,"end")==0){
            break;
        }

        // If no command matched
        printf("ERROR: Unknown command. Type 'help' for a list of commands.\n");
        fprintf(f_log, "[ERROR] Unknown command: %s\n", s);
    }
    WriteMaster(head_master);
    WriteAlbum(head_album_det);
    WritePlaylist(PlaylistVar);
    
    FreeMaster(head_master);
    FreeAlbum(head_album_det);
    FreePlaylist(PlaylistVar->head);
    free(PlaylistVar);
    fclose(f_log);
}