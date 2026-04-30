#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;


struct Pixel {
    unsigned char b;
    unsigned char g;
    unsigned char r;
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    srand(time(0));

    ifstream in("1.bmp", ios::binary);
    if (!in) {
        cout << "Не вдалося відкрити 1.bmp\n";
        return 1;
    }

    unsigned char header[54];
    in.read((char*)header, 54);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];

    cout << "Width: " << width << " Height: " << height << endl;

    int size = width * height;

    // Зчитуємо всі пікселі
    vector<Pixel> pixels(size);
    in.read((char*)pixels.data(), size * sizeof(Pixel));

    in.close();

    vector<Pixel> neg = pixels;

    for (int i = 0; i < size; i++) {
        neg[i].r = 255 - pixels[i].r;
        neg[i].g = 255 - pixels[i].g;
        neg[i].b = 255 - pixels[i].b;
    }

    ofstream out2("2.bmp", ios::binary);
    out2.write((char*)header, 54);
    out2.write((char*)neg.data(), size * sizeof(Pixel));
    out2.close();

    vector<Pixel> reduced = pixels;

    for (int i = 0; i < size; i++) {
        reduced[i].r = pixels[i].r / 2;
        reduced[i].b = pixels[i].b / 2;
    }

    ofstream out3("3.bmp", ios::binary);
    out3.write((char*)header, 54);
    out3.write((char*)reduced.data(), size * sizeof(Pixel));
    out3.close();

    vector<Pixel> noise = pixels;

    for (int i = 0; i < size; i++) {
        noise[i].r = min(255, pixels[i].r + rand() % (pixels[i].r / 2 + 1));
        noise[i].g = min(255, pixels[i].g + rand() % (pixels[i].g / 2 + 1));
        noise[i].b = min(255, pixels[i].b + rand() % (pixels[i].b / 2 + 1));
    }

    ofstream out4("4.bmp", ios::binary);
    out4.write((char*)header, 54);
    out4.write((char*)noise.data(), size * sizeof(Pixel));
    out4.close();

    cout << "Готово: створено 2.bmp, 3.bmp, 4.bmp\n";

    return 0;
}
