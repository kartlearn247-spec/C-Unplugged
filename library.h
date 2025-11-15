#ifndef LIBRARY
#define LIBRARY
#include "struct.h"
// 3 functions

void show_albums(Album* head);
void show_songs(Master_Node* head);
void Log();

//helper functions
Master_Node* Get_head_MasterLL();
Album* Get_head_AlbumLL(Master_Node* head_master);
song* GetAddress(char song[50],Master_Node* head);
Album* GetAlbum(char albumName[50],Album* AlbumN);

//Save the changes
void WriteMaster(Master_Node* head);
void WritePlaylist(Playlist* P);
void WriteAlbum(Album* AlbumDet);

//Free the nodes
void FreePlaylist(Playlist_Node* head);
void FreeMaster(Master_Node* head);
void FreeAlbum(Album* Albumhead);
#endif
