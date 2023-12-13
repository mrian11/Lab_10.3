#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

enum Train { Z_V, P_COMF, SPEED_E };
string trainStr[] = { "����.", "����.", "�������" };

struct Tramvai
{
    string punkt;
    Train tup;
    double chas;
};

void Create(Tramvai* p, const char* filename, const int N);
void Print(Tramvai* p, const int N);
void Add(Tramvai*& p, int& N, const char* filename);
void SaveToFile(Tramvai* p, const int N, const char* filename);
void LoadFromFile(Tramvai*& p, int& N, const char* filename);
void LineSearch(Tramvai* p, const int N);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int N;
    cout << "������ ������� ����� N: ";
    cin >> N;

    Tramvai* p = new Tramvai[N];
    char filename[100];
    int menuItem;

    do {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - ��������� �� ���������� ����������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ���������� ����������" << endl;
        cout << " [4] - ����� �� ������ ���� ��������� ����" << endl;
        cout << " [5] - ���������� ��������" << endl;
        cout << " [0] - �����" << endl;

        cout << "������ ��������: ";
        cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            cin.ignore();
            cout << "������ ��'� �����: ";
            cin.getline(filename, 99);
            Create(p, filename, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            cin.ignore();
            cout << "������ ��'� ����� ��� ����������: ";
            cin.getline(filename, 99);
            LoadFromFile(p, N, filename);
            Print(p, N);
            break;
        case 4:
            LineSearch(p, N);
            break;
        case 5:
            Add(p, N, filename);
            SaveToFile(p, N, filename);
            break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

    delete[] p;
    return 0;
}

void Create(Tramvai* p, const char* filename, const int N)
{
    ofstream fout(filename, ios::binary);

    if (!fout.is_open())
    {
        cout << "������� �������� �����." << endl;
        return;
    }

    fout.write((char*)&N, sizeof(N));

    for (int i = 0; i < N; i++)
    {
        cout << "������� � " << i + 1 << ":" << endl;

        cin.ignore();
        cout << "����� �����������: ";
        getline(cin, p[i].punkt);

        int tup;
        cout << "��� (0 - ����, 1 - ����, 2 - �������): ";
        cin >> tup;
        p[i].tup = static_cast<Train>(tup);

        cout << "���: ";
        cin >> p[i].chas;

        fout.write((char*)&p[i], sizeof(Tramvai));
    }

    fout.close();
}

void Print(Tramvai* p, const int N)
{
    cout << "������� ����������:" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "������� �" << i + 1 << ": ";
        cout << "�����: " << p[i].punkt << ", ";
        cout << "���: " << trainStr[p[i].tup] << ", ";
        cout << "���: " << p[i].chas << endl;
    }

    cout << "===========================" << endl;
}

void Add(Tramvai*& p, int& N, const char* filename)
{
    ofstream fout(filename, ios::binary | ios::app | ios::ate);

    if (!fout.is_open())
    {
        cout << "������� �������� �����." << endl;
        return;
    }

    int addTrs;
    cout << "������ ������� ���������� �����: ";
    cin >> addTrs;

    fout.write((char*)&addTrs, sizeof(addTrs));

    Tramvai* newTrs = new Tramvai[N + addTrs];
    for (int i = 0; i < N; i++)
    {
        newTrs[i] = p[i];
    }

    for (int i = N; i < N + addTrs; i++)
    {
        cout << "������� � " << i + 1 << ":" << endl;

        cin.ignore();
        cout << "����� �����������: ";
        getline(cin, newTrs[i].punkt);
        int tup;
        cout << "��� (0 - ����, 1 - ����, 2 - �������): ";
        cin >> tup;
        newTrs[i].tup = static_cast<Train>(tup);

        cout << "���: ";
        cin >> newTrs[i].chas;

        fout.write((char*)&newTrs[i], sizeof(Tramvai));

    }


    delete[] p;
    p = newTrs;
    N += addTrs;

    fout.close();
}

void SaveToFile(Tramvai* p, const int N, const char* filename)
{
    ofstream fout(filename, ios::binary);
    fout.write((char*)&N, sizeof(N));
    for (int i = 0; i < N; i++)
        fout.write((char*)&p[i], sizeof(Tramvai));
    fout.close();
}

void LoadFromFile(Tramvai*& p, int& N, const char* filename)
{
    delete[] p;

    ifstream fin(filename, ios::binary);

    if (!fin.is_open())
    {
        cout << "������� �������� ����� " << filename << "." << endl;
        return;
    }

    fin.read((char*)&N, sizeof(N));

    p = new Tramvai[N];

    for (int i = 0; i < N; i++)
    {
        fin.read((char*)&p[i], sizeof(Tramvai));
    }

    fin.close();
}


void LineSearch(Tramvai* p, const int N)
{
    double time;
    cout << "������ ���: ";
    cin >> time;

    cout << "�����, �� �������� ���� " << time << " �����:" << endl;

    for (int i = 0; i < N; i++)
    {
        if (p[i].chas > time)
        {
            cout << "������� �" << i + 1 << ": ";
            cout << "�����: " << p[i].punkt << ", ";
            cout << "���: " << trainStr[p[i].tup] << ", ";
            cout << "���: " << p[i].chas << endl;
        }
    }

    cout << "===========================" << endl;
}