//Шифрование N5

#include <iostream>
#include<string>
#include<Windows.h>

using namespace std;

void permutation(string code, int cnt, string* block, string* new_block) {
    string vrem;
    for (int i = 0; i < cnt; i++) {             //по блокам массива 
        for (int j = 0; j < size(code); j++) {  //по цифрам в коде
            vrem = *block;    
            *new_block = *new_block + vrem[(code[j] - '0')-1];
        }
        new_block++;
        block++;
    }
}

void moving(string code, int cnt, string* new_block) {

    string* first = new_block;
    string dop[15] = {};    

    for (int j = 0; j < ((cnt + size(code) - 1) / size(code)); j++) {
        for (int i = 0; i < size(code); i++) {
            if  ( ((code[i] - '0') - 1 + (j * (size(code)-1))) < cnt ) {
               dop[(code[i] - '0') - 1] = *new_block;
               new_block++;
               
            } 
        }
    }

    new_block = first;
    for (int i = 0; i < cnt; i++) {
        *new_block = dop[i];
        new_block++;
    }
}

void depermutation(string code, int cnt, string* block, string* new_block) {
    string vrem;
    for (int i = 0; i < cnt; i++) {             //по блокам массива 
        for (int j = 0; j < size(code); j++) {  //по буквам в блоке
            vrem = *block;
            if ((code[j] - '0') == (j + 1)) {
                *new_block = *new_block + vrem[j];
            }
            else {
                int z = 0;
                while ((code[z] - '0') != (j + 1)) {
                    z++;
                }
                *new_block = *new_block + vrem[z];
            }
        }
        new_block++;
        block++;
    }
}

void demoving(string code, int cnt, string* new_block) {
    string* first = new_block;
    string dop[15] = {};
    int z = 0;

    for (int j = 0; j < ((cnt + size(code) - 1) / size(code)); j++) {  //количесвто дублирования кода
        for (int i = 0; i < size(code); i++) {                         //цифры в коде
            if (((code[i] - '0') - 1 + (j * (size(code)-1) )) < cnt) {
                dop[z] = *(new_block + ((code[i] - '0') - 1));
                z++;
            }
        }
    }

    new_block = first;
    for (int i = 0; i < cnt; i++) {
        *new_block = dop[i];
        new_block++;
    }
}

void output(string *blocks, int cnt) {
    cout << endl;
    for (int i = 0; i < cnt; i++) {
        cout << *blocks << endl;
        blocks++;
    }
}

void encryption() {
    string code;
    cout << endl << "Введите ключ для шифрования - ";
    getline(cin, code, '\n');

    //Условия проверки исходных данных 
    int prov = 0;
    while ((prov < size(code))) {
        if ((code[prov] - '0' > size(code)) || (code[prov] - '0' < 1) || (code[prov] < '1') || (code[prov] > '9')) {
            cout << "Ошибка! Неверный ввод." << endl << "Код должен состоять из последовательности натуральных цифр." << endl << "Например: 324156." << endl << "Повторите ввод - ";
            getline(cin, code, '\n');
            prov = -1;
        }
        prov++;
    }

    cout << endl;
    string text;
    cout << "Введите исходный текст, который надо зашифровать, без пробелов - ";
    getline(cin, text, '\n');

    text.erase(remove(text.begin(), text.end(), ' '), text.end()); // для удаления лишних пробелов

    cout << endl << "Исходные данные:" << endl << text << "; " << code << endl; //для проверки корректного ввода

    string blocks[30] = {}; //блоки, на которые делится исходный текст
    string block = ""; //доп переменная хранящая текущий блок

    //добавление "ъ" в конец строки, если число букв в тексте не кратно числу цифр к коде
    if ((size(text) % size(code)) != 0) {
        char c = 'ъ';
        while ((size(text) % size(code)) != 0) {
            text = text + c;
        }
    }

    int cnt = 0; //количесвто блоков

    //деление текста на блоки
    for (int i = 0; i < (size(text) / size(code)); i++) {
        for (int j = i * size(code); j < i * size(code) + size(code); j++) {
            block = block + text[j];
        };
        blocks[i] = block;
        cnt++;
        block = "";
    }

    string new_blocks[30] = {};
    string* point_newbloks = &new_blocks[0];
    string* point_oldblocks = &blocks[0];

    output(point_oldblocks, cnt);

    permutation(code, cnt, point_oldblocks, point_newbloks);

    //для проверки
    output(point_newbloks, cnt);

    moving(code, cnt, point_newbloks);

    output(point_newbloks, cnt+1);

    text = "";
    cout << endl << "Зашифрованный текст: " << endl;
    for (int i = 0; i < cnt; i++) {
        text = text + new_blocks[i];
    }
    cout << text << endl;
}

void decryption() {
    string code;
    cout << endl << "Введите ключ, с помощью которого был зашифрован текст - ";
    getline(cin, code, '\n');

    //Условия проверки исходных данных 
    int prov = 0;
    while ((prov < size(code))) {
        if ((code[prov] - '0' > size(code)) || (code[prov] - '0' < 1) || (code[prov] < '1') || (code[prov] > '9')) {
            cout << "Ошибка! Неверный ввод." << endl << "Ключ должен состоять из последовательности натральных цифр." << endl << "Например: 324156." << endl << "Повторите ввод - ";
            getline(cin, code, '\n');
            prov = -1;
        }
        prov++;
    }

    cout << endl;
    string text;
    cout << "Введите ранне зашифрованный текст, который надо дешифровать, без пробелов - ";
    getline(cin, text, '\n');

    text.erase(remove(text.begin(), text.end(), ' '), text.end()); // для удаления лишних пробелов

    cout << endl << "Исходные данные:" << endl << text << "; " << code << endl; //для проверки корректного ввода

    string blocks[30] = {}; //блоки, на которые делится исходный текст
    string block = ""; //доп переменная хранящая текущий блок

    int cnt = 0; //количесвто блоков

    //деление текста на блоки
    for (int i = 0; i < (size(text) / size(code)); i++) {
        for (int j = i * size(code); j < i * size(code) + size(code); j++) {
            block = block + text[j];
        };
        blocks[i] = block;
        cnt++;
        block = "";
    }

    string new_blocks[30] = {};
    string* point_newbloks = &new_blocks[0];
    string* point_oldblocks = &blocks[0];

    output(point_oldblocks, cnt);

    depermutation(code, cnt, point_oldblocks, point_newbloks);

    //для проверки
    output(point_newbloks, cnt);

    demoving(code, cnt, point_newbloks);

    //для проверки
    output(point_newbloks, cnt);

    block = new_blocks[cnt - 1];
    while (block[size(code) - 1] == 'ъ') {
        block.pop_back();
    }
    new_blocks[cnt - 1] = block;

    text = "";
    cout << endl << "Дешифрованный текст: " << endl;
    for (int i = 0; i < cnt; i++) {
        text = text + new_blocks[i];
    }
    cout << text << endl;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //-------------------------шифрование 

    string f1;
    cout << "Если вы хотите зашифровать текст, то введите 0 - ";
    getline(cin, f1, '\n');

    if (f1[0] - '0' == 0) {
        encryption();
    }    

    //-----------------------дешифрование 

    string f2;
    cout << endl << "Если вы хотите дешифровать текст, то введите 0 - ";
    getline(cin, f2, '\n');

    if (f2[0] - '0' == 0) {
        decryption();
    }

}

