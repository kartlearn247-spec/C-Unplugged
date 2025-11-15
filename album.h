#ifndef ALBUM
#define ALBUM

//5 functions

void Create_Album (char* album,Album* head);
Album* Del_Album (char* album,Album* head);
void Add_song_album(char songname[50],char album[50],Master_Node* master,Album* Album_node);
void Del_song_album(char songname[50],char albumname[50],Album* albumDet);
void Show_songs_album(char album[50],Album* headAlbumDet);

#endif
