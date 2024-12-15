#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Artist {
protected:
    string artistName;

public:
    Artist(const string &name) : artistName(name) {}

    virtual string displayInfo() const {
        return "Artist: " + artistName + "\n";
    }
};

class Album : public Artist {
protected:
    string albumName;
    int releaseYear;

public:
    Album(const string &artistName, const string &albumName, int year)
        : Artist(artistName), albumName(albumName), releaseYear(year) {}

    string displayInfo() const override {
        return Artist::displayInfo() + "Album: " + albumName + "\nYear: " + to_string(releaseYear) + "\n";
    }
};

class Song : public Album {
protected:
    string songTitle;
    string lyricsSnippet;

public:
    Song(const string &artistName, const string &albumName, int year, const string &title, const string &lyrics)
        : Album(artistName, albumName, year), songTitle(title), lyricsSnippet(lyrics) {}

    string displayInfo() const override {
        return Album::displayInfo() + "Song Title: " + songTitle + "\nFull Lyrics: " + lyricsSnippet + "\n";
    }

    const string &getLyricsSnippet() const {
        return lyricsSnippet;
    }

    const string &getAlbumName() const {
        return albumName;
    }

    const string &getArtistName() const {
        return artistName;
    }
};

class SongFinder {
private:
    vector<Song> songDatabase;

public:
    void addSong(const Song &song) {
        songDatabase.push_back(song);
    }

    vector<string> findSongByLyrics(const string &lyrics) const {
        vector<string> searchWords;
        stringstream ss(lyrics);
        string word;
        while (ss >> word) {
            searchWords.push_back(word);
        }

        vector<string> results;
        for (const auto &song : songDatabase) {
            string songLyrics = song.getLyricsSnippet();
            bool match = all_of(searchWords.begin(), searchWords.end(), [&songLyrics](const string &searchWord) {
                return songLyrics.find(searchWord) != string::npos;
            });

            if (match) {
                results.push_back(song.displayInfo());
            }
        }
        return results;
    }

    vector<string> findSongByAlbum(const string &album) const {
        vector<string> results;
        for (const auto &song : songDatabase) {
            if (song.getAlbumName() == album) {
                results.push_back(song.displayInfo());
            }
        }
        return results;
    }

    vector<string> findSongByArtist(const string &artist) const {
        vector<string> results;
        for (const auto &song : songDatabase) {
            if (song.getArtistName() == artist) {
                results.push_back(song.displayInfo());
            }
        }
        return results;
    }
};

int main() {
    SongFinder finder;
    finder.addSong(Song("Kanye West", "The Life of Pablo ", 2016, "Father Stretch My Hands Pt. 1", 
                        R"("You're the only power (power)
                        Youre the only power that can
                        Youre the only power
                        You're the only power that can
                        If young Metro don't trust you I'm gon' shoot you
                        Beautiful morning, you're the sun in my morning, babe
                        Nothing unwanted
                        Beautiful morning, you're the sun in my morning, babe
                        Nothing unwanted
                        I just want to feel liberated, I, I, na-na-na
                        I just want to feel liberated, I, I, na-na-na
                        If I ever instigated, I'm sorry
                        Tell me, who in here can relate? I, I, I
                        Now if I fuck this model
                        And she just bleached her asshole
                        And I get bleach on my T-shirt
                        I'ma feel like an asshole
                        I was high when I met her
                        We was down in Tribeca
                        She'll get under your skin if you let her
                        She'll get under your skin if you-uh
                        I don't even want to talk about it
                        I don't even want to talk about it
                        I don't even want to say nothing
                        Everybody gon' say something
                        I'd be worried if they said nothing
                        Remind me where I know you from?
                        She looking like she owe you some'
                        You know just what we want
                        I want to wake up with you in my
                        Beautiful morning, you're the sun in my morning, babe
                        Nothing unwanted
                        Beautiful morning, you're the sun in my morning, babe
                        Nothing unwanted
                        I just want to feel liberated, I, I, na-na-na
                        I just want to feel liberated, I, I, na-na-na
                        If I ever instigated, I'm sorry
                        Tell me who in here can relate, I, I, I)"));
    finder.addSong(Song("Artist2", "Album2", 2020, "Song2", "Another set of lyrics for song two."));
    finder.addSong(Song("Artist3", "Album3", 2019, "Song3", "Lyrics from song three appear here."));

    int choice;
    do {
        cout << "\nSong Finder Menu:\n";
        cout << "1. Search by Lyrics\n";
        cout << "2. Search by Album\n";
        cout << "3. Search by Artist\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To clear the newline character from the input buffer

        if (choice == 1) {
            string lyrics;
            cout << "Enter lyrics snippet: ";
            getline(cin, lyrics);
            vector<string> results = finder.findSongByLyrics(lyrics);
            if (results.empty()) {
                cout << "No songs found with the given lyrics." << endl;
            } else {
                cout << "Songs found:\n";
                for (const auto &result : results) {
                    cout << result << endl;
                }
            }
        } else if (choice == 2) {
            string album;
            cout << "Enter album name: ";
            getline(cin, album);
            vector<string> results = finder.findSongByAlbum(album);
            if (results.empty()) {
                cout << "No songs found in the given album." << endl;
            } else {
                cout << "Songs found:\n";
                for (const auto &result : results) {
                    cout << result << endl;
                }
            }
        } else if (choice == 3) {
            string artist;
            cout << "Enter artist name: ";
            getline(cin, artist);
            vector<string> results = finder.findSongByArtist(artist);
            if (results.empty()) {
                cout << "No songs found by the given artist." << endl;
            } else {
                cout << "Songs found:\n";
                for (const auto &result : results) {
                    cout << result << endl;
                }
            }
        } else if (choice == 4) {
            cout << "Exiting Song Finder. Goodbye!" << endl;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
