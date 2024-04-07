#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

using namespace std;
namespace fs = filesystem;

// Fungsi rekursif untuk mencari file dalam direktori dan subdirektori
void findFile(const fs::path &directory, const string &fileName, vector<fs::path> &foundFiles)
{
    for (const auto &entry : fs::directory_iterator(directory))
    {
        if (fs::is_directory(entry.path()))
        {
            // Jika entry adalah direktori, rekursif mencari di dalamnya
            findFile(entry.path(), fileName, foundFiles);
        }
        else if (entry.path().filename() == fileName)
        {
            // Jika entry adalah file dan namanya sesuai, simpan path-nya
            foundFiles.push_back(entry.path());
        }
    }
}

int main()
{
    string directoryPath;
    string fileName;

    cout << "Masukkan path direktori: ";
    cin >> directoryPath;

    cout << "Masukkan nama file yang dicari: ";
    cin >> fileName;

    fs::path directory(directoryPath);

    if (!fs::exists(directory) || !fs::is_directory(directory))
    {
        cerr << "Direktori tidak valid.\n";
        return 1;
    }

    vector<fs::path> foundFiles;
    findFile(directory, fileName, foundFiles);

    if (foundFiles.empty())
    {
        cout << "File dengan nama '" << fileName << "' tidak ditemukan." << endl;
    }
    else
    {
        cout << "File ditemukan:\n";
        for (const auto &file : foundFiles)
        {
            cout << file << endl;
        }
    }

    return 0;
}
