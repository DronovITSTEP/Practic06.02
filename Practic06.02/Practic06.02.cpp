#include <iostream>
#include <io.h>


using namespace std;

int main()
{
    /*struct _finddata_t myFileInfo;

    char path[150];
    char mask[20];

    cout << "Enter full path (for example, D:\\): \n";
    cin >> path;

    cout << "Enter mask (for example, *.* or *.txt): \n";
    cin >> mask;

    strcat_s(path, mask);


    long done = _findfirst(path, &myFileInfo);
    do {
        cout << myFileInfo.name << endl;
    } while (_findnext(done, &myFileInfo) == 0);*/

    //Дан текстовый файл. Необходимо создать новый файл,
    //в кторый необходимо переписать все слова, 
    //длина которых больше 7 букв
    FILE* f;
    char path[25]{ "C:\\Test\\text.txt" };
    char path2[25]{ "C:\\Test\\text2.txt" };

    // узнаем размер исходного файла (размер возвращается в байтах)
    // один символ char = 1 byte
    _finddata_t file;
    _findfirst(path, &file);
    char* arr = new char[file.size+1];

    int length = 0; // вся длина строки 
    if (!fopen_s(&f, path, "r")) {
        while (!feof(f))
        {
            // построковое чтение из файла и занесение его в массив
            fgets(arr, file.size, f);
            length += strlen(arr);
            arr += strlen(arr); 
        }
    }
    fclose(f);
    arr -= length; // возвращаем указатель в начало строки
    puts(arr);

    char* newArr = new char[100];// для хранения информации позиции указателя

    if (!fopen_s(&f, path2, "a")) {
        char* p = nullptr;
        do {
            // ищет в строке str любой из символов во втором аргументе функции
            if (!p) p = strtok_s(arr, " .,!?\n", &newArr);
            //продолжаем поиск
            p = strtok_s(NULL, " .,!?\n", &newArr);
            if (p) {
                if (strlen(p) >= 7) {
                    fprintf_s(f, p);
                    fprintf_s(f, "\n");
                }
            }
        } while (p);
    }
    fclose(f);
}
