#include <iostream>
#include <string>
#include <utility>
using namespace std;

struct Song
{
    int id;
    string name;
    Song* next;
};

class Playlist
{
    Song* head;
    int count;

    Song* GetNodeAt(int index)
    {
        Song* p = head->next;
        for (int i = 0; i < index; i++)
            p = p->next;
        return p;
    }

public:
    Playlist()
    {
        head = NULL;
        count = 0;
    }

    bool IsEmpty()
    {
        return count == 0;
    }

    bool IsNotEmpty()
    {
        return count > 0;
    }

    void Insert(Song* s)
    {
        if (head == NULL)
        {
            head = s;
            s->next = s;
        }
        else
        {
            s->next = head->next;
            head->next = s;
        }
        count++;
    }

    Song* Remove()
    {
        if (IsEmpty()) return NULL;

        Song* s = head->next;

        if (s == head)
            head = NULL;
        else
            head->next = s->next;

        s->next = NULL;
        count--;
        return s;
    }

    void InsertAt(Song* s, int index)
    {
        if (count == 0 || index <= 0)
        {
            Insert(s);
            return;
        }

        if (index >= count)
        {
            s->next = head->next;
            head->next = s;
            head = s;
            count++;
            return;
        }

        Song* p = GetNodeAt(index - 1);
        s->next = p->next;
        p->next = s;
        count++;
    }

    Song* RemoveAt(int index)
    {
        if (IsEmpty()) return NULL;

        index = ((index % count) + count) % count;

        if (index == 0) return Remove();

        Song* p = GetNodeAt(index - 1);
        Song* s = p->next;
        p->next = s->next;

        if (s == head) head = p;

        s->next = NULL;
        count--;
        return s;
    }

    void Swap(int a, int b)
    {
        if (IsEmpty()) return;

        a = ((a % count) + count) % count;
        b = ((b % count) + count) % count;

        Song* x = GetNodeAt(a);
        Song* y = GetNodeAt(b);

        swap(x->id, y->id);
        swap(x->name, y->name);
    }

    void Sort()
    {
        for (Song* i = head->next, *p = i; ; )
        {
            Song* j = i->next;

            while (j != head->next)
            {
                if (i->id > j->id)
                {
                    swap(i->id, j->id);
                    swap(i->name, j->name);
                }
                j = j->next;
            }

            i = i->next;
            if (i == head->next) break;
        }
    }

    void Reverse()
    {
        if (count < 2) return;

        Song* oldHead = head;
        Song* first = head->next;
        Song* p = head;
        Song* c = first;

        while (c != oldHead)
        {
            Song* n = c->next;
            c->next = p;
            p = c;
            c = n;
        }

        oldHead->next = p;
        head = first;
    }

    void Print()
    {
        if (IsEmpty())
        {
            cout << "Playlist is empty!\n";
            return;
        }

        Song* p = head->next;

        for (int i = 0; i < count; i++)
        {
            cout << p->id << " - " << p->name << endl;
            p = p->next;
        }
    }

    void PlayNext()
    {
        if (IsEmpty())
        {
            cout << "Playlist is empty!\n";
            return;
        }

        head = head->next;
        cout << "Now playing: " << head->next->name << endl;
    }

    ~Playlist()
    {
        while (!IsEmpty())
            delete Remove();
    }
};

Song* CreateSong(int id, string name)
{
    return new Song{id, name, NULL};
}

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

