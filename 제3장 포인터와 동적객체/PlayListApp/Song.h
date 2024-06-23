#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PlayList;

class Song
{
private:
    // 데이터멤버들은 클래스의 멤버라기보단 각각의 객체에 귀속된 멤버 (object 멤버)
    int id; // each song obj has unique id
    string title;
    string artist;
    string album;
    string mv_url;
    vector<PlayList *> playlists;
    static int id_counter; // class member
    // static 멤버란 클래스 전체에 유일하게 존재하는 멤버
    // static 멤버의 값을 0으로 초기화하고 생성자가 호출될때마다 id_counter를 1증가

public:
    Song();
    Song(string ti, string ar, string al, string mv);
    ~Song();

    int get_id();
    string get_title();
    string get_artist();

    void print(ostream &out);

    void register_playlist(PlayList *ptr_plist);
    void unregister_playlist(string plist_name);
    void play();
};
