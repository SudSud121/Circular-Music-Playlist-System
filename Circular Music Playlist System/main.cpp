int main()
{
    Playlist p;

    p.InsertAt(CreateSong(1, "Song One"), 0);
    p.InsertAt(CreateSong(2, "Song Two"), 1);
    p.InsertAt(CreateSong(3, "Song Three"), 2);

    cout << "My Circular Playlist\n";
    p.Print();

    cout << "\nNext song:\n";
    p.PlayNext();

    cout << "\nPlaylist:\n";
    p.Print();

    return 0;
}
