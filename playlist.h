#ifndef PLAYLIST
#define PLAYLIST

//helper function
Playlist_Node* Get_Head(Master_Node* master_head,Playlist* P);
// 6 functions 
void show_Playlist(Playlist* playlst); 
void Add_song_Playlist(char song_name[50],Master_Node* master_head,Playlist* P);
void Del_song_Playlist(char song_name[50],Playlist* p);
void Add_album_playlist(char albumName[50],Album* AlbumN,Playlist* P);
void Next_song(Playlist* plylst);
void Prev_song(Playlist* plylst);

#endif