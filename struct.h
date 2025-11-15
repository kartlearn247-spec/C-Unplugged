#ifndef STRUCT_H
#define STRUCT_H

// Just like any other data type (doesnt contribute to a data structure)
struct song{
    char name[50];
    char artist[50];
    int duration;
};
typedef struct song song;

//Master linked list of all songs
struct Master_Node{
    song* song_address;
    struct Master_Node* next;
};
typedef struct Master_Node Master_Node;

// the linked list of songs in an Album
struct Album_Node{
    song* song_address;
    struct Album_Node* next;
};
typedef struct Album_Node Album_Node;

//linked list of albums
struct Album{
    char nameA[50];
    Album_Node* album_head;
    struct Album* nextA;
    char Write;
};
typedef struct Album Album;

//the linked list of songs in a playlist
struct Playlist_Node{
    song* song_address;
    struct Playlist_Node* next;
    struct Playlist_Node* prev;
};
typedef struct Playlist_Node Playlist_Node;

struct Playlist{
    Playlist_Node* head;
    Playlist_Node* current_song;

};
typedef struct Playlist Playlist;
#endif