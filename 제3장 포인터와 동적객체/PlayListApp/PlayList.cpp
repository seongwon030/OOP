#include <fstream>
#include <sstream>

#include "Song.h"
#include "PlayList.h"
using namespace std;

PlayList::PlayList(string str) : name(str)
{
}

string PlayList::get_name()
{
    return name;
}

void PlayList::add_song(Song *song)
{
    tracks.push_back(song);
    song->register_playlist(this);
}

void PlayList::print(ostream &out)
{
    out << name << ":" << endl;
    for (auto song_ptr : tracks)
    {
        song_ptr->print(out);
        out << endl;
    }
}

vector<Song *> PlayList::find_songs_by_keyword(string keyword)
{
    vector<Song *> result; // 리턴할 벡터 만들기
    for (Song *item : tracks)
    {
        // 플레이리스트에 속한 노래들에 대한 벡터가 tracks
        // tracks 안에 각각의 Song 객체에 대한 포인터들에 대해 title을 받음
        // keyword가 문자열에 존재하먄 index리턴 / 아니면 npos값 리턴
        if (item->get_title().find(keyword) != string::npos || item->get_artist().find(keyword) != string::npos)
            result.push_back(item);
    }
    return result;
}

Song *PlayList::find_song_by_id(int sid)
{
    for (auto item : tracks)
        if (item->get_id() == sid)
            return item;
    return nullptr;
}

void PlayList::delete_song_by_id(int songId)
{
    for (auto it = tracks.begin(); it != tracks.end(); it++)
    {
        if ((*it)->get_id() == songId)
        {
            tracks.erase(it);
            return;
        }
    }
}

void PlayList::clear_songs()
{
    // 플리에 포함된 모든 노래를 찾아야함
    for (auto it = tracks.begin(); it != tracks.end(); it++)
        (*it)->unregister_playlist(name);
    tracks.clear(); // unnecessary
    // 벡터자체를 clear하는게 반드시 필요하진 않음
    // 플리 객체자체를 delete하므로 플리 안의 벡터사이즈를 0으로 만드는 건 반드시 필요하지 않음
}

int PlayList::size()
{
    return tracks.size();
}