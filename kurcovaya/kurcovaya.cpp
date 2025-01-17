#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
const string STUD_FILE = "E:\\с++ е#учий\\Курсачевский\\kurcovaya\\kurcovaya\\studfile.csv";
const string USER_FILE = "E:\\с++ е#учий\\Курсачевский\\kurcovaya\\kurcovaya\\userfile.txt";
struct exams {
	string exam_name;
	int e_mark;
};
struct zachet {
	string zach_name;
	bool z_mark;
};
struct student {
	string stud_name;
	int group;
	exams stud_exam[5];
	zachet stud_zach[5];
	int dolg;
	double medium;
	student() {
		medium = -1;
		dolg = 0;
	}
};
struct user {
	string user_name;
	string user_password;
	bool user_root;
};
using student_table = vector<student>;
bool student_table_dolg = false;
bool student_table_medium = false;
void loadData(student_table &data);
int MenuLogin();
int MenuGuest();
void NickInput(user &user);
void ViewStudInfo(student_table data);
void AddStudInfo();
int MenuUser();
int MenuAdmin();
void AddUser();
void DeleteUserInfo(string& del_nick);
void DeleteStudentInfo(student_table data);
string SavePerson(student person);
void SaveData(student_table data);
void Sortirovka(student_table &data);
void Search (student_table &data);
void calcMedumGroup(student_table data);
bool isNumberNumeric();
bool isNumberRangeCorrect(int number, int left_range, int right_range);
int inputNumber(int left_range, int right_range);
int main() {
	setlocale(LC_ALL, "rus");
	user polzovatel;
	student_table data;
	bool exit1 = false;
	while (!exit1) {
		int key_login_menu = MenuLogin();
		switch (key_login_menu) {
		case 1: {
			NickInput(polzovatel);
			if (polzovatel.user_root == true) {
				bool exit2 = false;
				loadData(data);
				while (!exit2) {					
					cout << "Создатель, твори\n";
					int key_admin_menu = MenuAdmin();
					string user_del;
					switch (key_admin_menu) {
					case 1: 
						loadData(data);
						student_table_dolg = false;
						student_table_medium = false;
						break;
					case 2:
						SaveData(data);
					case 3:
						ViewStudInfo(data);
						break;
					case 4:
						AddStudInfo();
						break;
					case 5:
						DeleteStudentInfo(data);
						break;
					case 6:
						Sortirovka(data);
						break;
					case 7:
						Search(data);
						break;
					case 8:
						calcMedumGroup(data);
						break;
					case 10:
						AddUser();
						break;
					case 11:
						cout << "Кого удалить?\n";
						user_del= inputNumber(0,100);
						DeleteUserInfo(user_del);
						break;
					
					case 9:
						exit2 = true;
						break;
					case 0:
						return 0;
						break;
					}
				}
			}
			if (polzovatel.user_root == false) {
				loadData(data);
				bool exit2 = false;
				while (!exit2) {
					cout << "дарова старичок\n";
					int key_user_menu = MenuUser();
					switch (key_user_menu) {
					case 1:
						loadData(data);
						student_table_dolg = false;
						student_table_medium = false;
						break;
					case 2:
						SaveData(data);
					case 3:
						ViewStudInfo(data);
						break;
					case 4:
						AddStudInfo();
						break;
					case 5:
						Sortirovka(data);
						break;
					case 6:
					Search(data);
						break;
					case 7:
						calcMedumGroup(data);
						break;
					case 9:
						exit2 = true;
						break;
					case 0:
						return 0;
					}
				}
			}
			break;
		}
		case 2: {
			bool exit2 = false;
			loadData(data);
			while (!exit2) {				
				int key_guest_menu = MenuGuest();
				switch (key_guest_menu) {
				case 1:
					loadData(data);
					student_table_dolg = false;
					student_table_medium = false;
					break;
				case 3:
					ViewStudInfo(data);
					break;
				case 5:
					Sortirovka(data);
					break;
				case 6:
					Search(data);
					break;
				case 7:
					calcMedumGroup(data);
					break;
				case 9:
					exit2 = true;
					break;
				case 0:
					return 0;
				}
			}
			break;
		}
		case 0:
			exit1 = true;
			break;
	}
	}
	return 0;
}
void loadData(student_table &data)
{
	ifstream stud_file;
	stud_file.open(STUD_FILE);
	data.clear();
	while (!stud_file.eof())
	{
		student line;
		string temp[12];
		char tmpp[1000];
		size_t j = 0;
		stud_file.getline(tmpp, 1000);
		string tmp = string(tmpp);
		while (tmp.find(';') != -1) {
			temp[j] = tmp.substr(0, tmp.find(';'));
			tmp.erase(0, tmp.find(';')+1);
			j++;
		}
		temp[j] = tmp;
		line.group = atoi(temp[0].c_str());
		line.stud_name = temp[1];
		line.stud_zach[0].zach_name = "Бел.яз";
		line.stud_zach[0].z_mark = stoi(temp[2]);
		line.stud_zach[1].zach_name = "Политология";
		line.stud_zach[1].z_mark = stoi(temp[3]);
		line.stud_zach[2].zach_name = "История";
		line.stud_zach[2].z_mark = stoi(temp[4]);
		line.stud_zach[3].zach_name = "Физкультура";
		line.stud_zach[3].z_mark = stoi(temp[5]);
		line.stud_zach[4].zach_name = "Логика";
		line.stud_zach[4].z_mark = stoi(temp[6]);
		line.stud_exam[0].exam_name = "Математика";
		line.stud_exam[0].e_mark = stoi(temp[7]);
		line.stud_exam[1].exam_name = "Физика";
		line.stud_exam[1].e_mark = stoi(temp[8]);
		line.stud_exam[2].exam_name = "ОАИП";
		line.stud_exam[2].e_mark = stoi(temp[9]);
		line.stud_exam[3].exam_name = "ОИАД";
		line.stud_exam[3].e_mark = stoi(temp[10]);
		line.stud_exam[4].exam_name = "Английский язык";
		line.stud_exam[4].e_mark = stoi(temp[11]);
		data.push_back(line);
	}
	stud_file.close();
}
int MenuLogin() {
	int kod_vhod1;
	cout << "Welcome салага\nКак зовут то тебя?\nЕсли ты тут впервые то зайди как гость\n(1-вход с вводом данных, 2-вход как гость,0-слинять)\n";
  kod_vhod1= inputNumber(0, 3);
	return kod_vhod1;
}
int MenuGuest() {	
		int kod_vhod2;
		cout << "как гость ты можешь просматривать информацию\n1 - Загрузка данных о студентах\n3 - Просмотр списка студентов\n5 - Сортировка\n6 - Поиск\n7 - Расчитать средний балл выбранной группы\n9 - Выход к авторизации\n0 - ВЫХОД\n";
		 kod_vhod2= inputNumber(0, 9);
		return kod_vhod2;
}
void NickInput(user &user) {
	string input_nickname, input_pass;
	string nickbuff, passbuff;
	bool nicktrue = false, passtrue = false, root;
	string buffer;
	ifstream nickcheak;
	nickcheak.open(USER_FILE);
	bool autorizations = false;
	while (!autorizations)
	{
		nickcheak.clear();
		nickcheak.seekg(0, ios::beg);
		cout << "введите ваш никнейм\n";
		cin >> input_nickname;
		cout << "введите ваш пароль\n";
		cin >> input_pass;
		while (!nickcheak.eof()) {
			nickcheak >> nickbuff >> passbuff >> root;
			if (nickbuff == input_nickname) {
				nicktrue = true;
			}
			if (passbuff == input_pass) {
				passtrue = true;
			}
			if (nicktrue && passtrue) {
				user.user_name = nickbuff;
				user.user_password = passbuff;
				user.user_root = root;
				cout << "добро пожаловать " << nickbuff << " ,мы скучали\n";
				autorizations = true;
				break;
			}
		}
		if (!nicktrue || !passtrue) {
			cout << "ошибочка ввода\n";
		}
	}
	nickcheak.close();
}
int MenuUser() {
	int kod_vhod2;
	cout << "как пользователь ты можешь смотреть информацию а также добавлять новую, ну и обрабатывать ещё\n1 - Загрузка данных о студентах\n2 - Сохранить данные о студентах\n3 - Просмотр списка студентов\n4 - Добавить студента\n5 - Сортировка\n6 - Поиск\n7 - Расчитать средний балл выбранной группы\n9 - Выход к авторизации\n0 - Выход из приложения\n";
	kod_vhod2= inputNumber(0, 9);
	return kod_vhod2;
}
int MenuAdmin() {
	int kod_vhod3;
	cout<<"разделяй и властвуй\n1 - Загрузка данных о студентах\n2 - Сохранить данные о студентах\n3 - Просмотр списка студентов\n4 - Добавить студента\n5 - Удалить Студента\n6 - Сортировка\n7 - Поиск\n8 - Расчитать средний балл выбранной группы\n10 - Добавить пользователя\n11 - Удалить Пользователя\n9 - Выход к авторизации\n0 - Выход из приложения\n";
	kod_vhod3= inputNumber(0, 11);
	return kod_vhod3;
}
void ViewStudInfo(student_table data) {
	if (data.size() == 0) cout << "Таблица пуста!\n";
	for (int i = 0; i < data.size(); i++) {
		cout << i + 1 << ".  ";
		cout << data[i].group << ' ' << data[i].stud_name << ' ';
		cout << data[i].stud_zach[0].zach_name << '-';
		if (data[i].stud_zach[0].z_mark == 1) {
			cout << "сдан ";
		}
		else cout << "не сдан ";
		cout << data[i].stud_zach[1].zach_name << '-';
		if (data[i].stud_zach[1].z_mark == 1) {
			cout << "сдан ";
		}
		else cout << "не сдан ";
		cout << data[i].stud_zach[2].zach_name << '-';
		if (data[i].stud_zach[2].z_mark == 1) {
			cout << "сдан ";
		}
		else cout << "не сдан ";
		cout << data[i].stud_zach[3].zach_name << '-';
		if (data[i].stud_zach[3].z_mark == 1) {
			cout << "сдан ";
		}
		else cout << "не сдан ";
		cout << data[i].stud_zach[4].zach_name << '-';
		if (data[i].stud_zach[4].z_mark == 1) {
			cout << "сдан ";
		}
		else cout << "не сдан ";
		cout << data[i].stud_exam[0].exam_name << '=';
		if (data[i].stud_exam[0].e_mark == 0) cout << "не сдан ";
		else cout << data[i].stud_exam[0].e_mark << ' ';
		cout << data[i].stud_exam[1].exam_name << '=';
		if (data[i].stud_exam[1].e_mark == 0) cout << "не сдан ";
		else cout << data[i].stud_exam[1].e_mark << ' ';
		cout << data[i].stud_exam[2].exam_name << '=';
		if (data[i].stud_exam[2].e_mark == 0) cout << "не сдан ";
		else cout << data[i].stud_exam[2].e_mark << ' ';
		cout << data[i].stud_exam[3].exam_name << '=';
		if (data[i].stud_exam[3].e_mark == 0) cout << "не сдан ";
		else cout << data[i].stud_exam[3].e_mark << ' ';
		cout << data[i].stud_exam[4].exam_name << '=';
		if (data[i].stud_exam[4].e_mark == 0) cout << "не сдан ";
		else cout << data[i].stud_exam[4].e_mark << ' ';
		if (student_table_medium) cout << "ср.балл:" << data[i].medium;
		if (student_table_dolg) cout << "долги:" << data[i].dolg;
		cout << '\n';		
	}
}
string SavePerson(student person) {
	string res = "";
	res += to_string(person.group) + ';' + person.stud_name + ';';
	res += to_string(person.stud_zach[0].z_mark) + ';';
	res += to_string(person.stud_zach[1].z_mark) + ';';
	res += to_string(person.stud_zach[2].z_mark) + ';';
	res += to_string(person.stud_zach[3].z_mark) + ';';
	res += to_string(person.stud_zach[4].z_mark) + ';';
	res += to_string(person.stud_exam[0].e_mark) + ';';
	res += to_string(person.stud_exam[1].e_mark) + ';';
	res += to_string(person.stud_exam[2].e_mark) + ';';
	res += to_string(person.stud_exam[3].e_mark) + ';';
	res += to_string(person.stud_exam[4].e_mark);
	return res;
}
void SaveData(student_table data) {
	ofstream save_data;
	save_data.open(STUD_FILE);
	for (int i = 0; i < data.size(); i++) {
		save_data << SavePerson(data[i]);
		if (i < data.size() - 1) save_data << '\n';
	}
}
void AddStudInfo() {
	ofstream add_stud_info;
	student person;
	add_stud_info.open(STUD_FILE, ios_base::app);
	string fio, group;
	char buf[1000];
	cout << "введите группу студента\n";
	person.group= inputNumber(100000,999999);
	cout << "введите фио студента\n";
	cin.clear();
	cin.ignore();
	cin.getline(buf, 1000);
	person.stud_name = string(buf);
	cout << "введите 1 если зачет по БЕЛАРУСКОМУ ЯЗЫКУ сдан или 0 если не сдан\n";
	cin >> person.stud_zach[0].z_mark;
	cout << "введите 1 если зачет по ПОЛИТОЛОГИИ сдан или 0 если не сдан\n";
	cin >> person.stud_zach[1].z_mark;
	cout << "введите 1 если зачет по ИСТОРИИ сдан или 0 если не сдан\n";
	cin >> person.stud_zach[2].z_mark;
	cout << "введите 1 если зачет по ФИЗКУЛЬТУРЕ сдан или 0 если не сдан\n";
	cin >> person.stud_zach[3].z_mark;
	cout << "введите 1 если зачет по ЛОГИКЕ сдан или 0 если не сдан\n";
	cin >> person.stud_zach[4].z_mark;
	cout << "введите оценку за экзамен по Математике\n";
	person.stud_exam[0].e_mark= inputNumber(0, 10);
	cout << "введите оценку за экзамен по Физике\n";
	 person.stud_exam[1].e_mark = inputNumber(0, 10);
	cout << "введите оценку за экзамен по ОАИПу\n";
	 person.stud_exam[2].e_mark = inputNumber(0, 10);
	cout << "введите оценку за экзамен по ОИАДу\n";
     person.stud_exam[3].e_mark = inputNumber(0, 10);
	cout << "введите оценку за экзамен по Английскому языку\n";
	 person.stud_exam[4].e_mark = inputNumber(0, 10);
	add_stud_info << '\n' << SavePerson(person);
	add_stud_info.close();
}
void DeleteStudentInfo(student_table data) {
	int stroka;
	char ya;
	cout << "введите строку студента которую хотите удалить\n";
	stroka = inputNumber(0, 100);
	cout << "вы действительно хотите удалить эту строку?(1-да)";
	cin >> ya;
		if (ya == '1') {
			data.erase(data.begin() + stroka - 1);
			SaveData(data);
		}
				cout << "студент успешно удален\n";
}
void DeleteUserInfo(string& del_nick) {
	ifstream user_file_in;
	stringstream ss;
	string buffer;
	user_file_in.open(USER_FILE);
	while (getline(user_file_in, buffer))
	{
		size_t pos = buffer.find(del_nick);
		if (pos == string::npos) {
			ss << buffer << '\n';
		}
	}
	user_file_in.close();
	ofstream user_file_out;
	user_file_out.open(USER_FILE);
	buffer = ss.str();
	if (buffer[0] == '\n') {
		buffer.erase(0, 1);
	}
	user_file_out << buffer;
	user_file_out.close();
}
void AddUser() {
	string nickname, password;
	ofstream add_user_info;
	cout << "вводи ник\n";
	cin >> nickname;
	cout << "вводи пароль\n";
	cin >> password;
	add_user_info.open(USER_FILE, ios_base::app);
	add_user_info << nickname << " " << password << " 0"<<endl;
	add_user_info.close();
}
void findDolg(student_table &data) {
	student_table_dolg = true;
	for (student &stud : data) {
		stud.dolg = 0;
		for (int j = 0; j < 5; j++) {
			if (stud.stud_exam[j].e_mark == 0) stud.dolg++;
			if (stud.stud_zach[j].z_mark == 0) stud.dolg++;
		}
	}
}
void calcMedium(student_table &data) {
	student_table_medium = true;
	for (student &stud: data) {
		stud.medium = 0;
		for (int j = 0; j < 5; j++) {
			stud.medium += stud.stud_exam[j].e_mark;
		}
		stud.medium /= 5;
	}
}
bool sortName(student a, student b) { return a.stud_name < b.stud_name; }
bool sortGroup(student a, student b) { return a.group < b.group; }
bool sortDolg(student a, student b) { return a.dolg < b.dolg; }
bool sortMedium(student a, student b) { return a.medium < b.medium; }
void Sortirovka(student_table &data) {
	int kod;
	cout << "1-Сортировка по имени\n2-Сортировка по группе\n3-Сортировка по задолженностям\n4-Сортировка по среднему баллу\n";
	 kod = inputNumber(1, 4);
	bool(*sortBy)(student, student);
	switch (kod)
	{
		case 1: sortBy = sortName; break;
		case 2: sortBy = sortGroup; break;
		case 3: findDolg(data); sortBy = sortDolg; break;
		case 4: calcMedium(data); sortBy = sortMedium; break;
		default: return;
	}
	sort(data.begin(), data.end(), sortBy);
	char kod2;
	cout << "Хотите отсортировать по убыванию? (1-да)\n";
	cin >> kod2;	
		if (kod2 == '1')
			reverse(data.begin(), data.end());
}
string toFind = "";
bool findName(student a) { return a.stud_name.find(toFind) != string::npos; }
bool findGroup(student a){ return a.group == stoi(toFind); }
bool findDolg(student a) { return a.dolg == stoi(toFind); }
void Search(student_table &data) {
	student_table table;
	int kod;
	cout << "1-Поиск по имени\n2-Поиск по группе\n3-Поиск по задолженностям\n";
	kod = inputNumber(1, 3);
	string find;
	cout << "Введите что хотите найти: ";
	cin >> toFind;
	bool(*findBy)(student);
	switch (kod)
	{
		case 1: findBy = findName; break;
		case 2: findBy = findGroup; break;
		case 3: findDolg(data); findBy = findDolg; break;
		default: return;
	}
	for (student stud : data) {
		if (findBy(stud)) table.push_back(stud);
	}
	data = table;
}
void calcMedumGroup(student_table data) {
	student_table table;
	cout << "Введите группу: ";
	int group;
	group = inputNumber(100000, 999999);
	for (student stud : data) {
		if (stud.group == group) table.push_back(stud);
	}
	calcMedium(table);
	double mark = 0;
	for (student stud : table) {
		mark += stud.medium;
	}
	cout << "Средний балл группы: " << mark / table.size() << '\n';
	student_table_medium = false;
}
bool isNumberNumeric()
{
	if (cin.get() == '\n') return true;
	else
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
}

bool isNumberRangeCorrect(int number, int left_range, int right_range)
{
	if ((number >= left_range) && (number <= right_range)) return true;
	else return false;
}

int inputNumber(int left_range, int right_range)
{
	int number;
	while (true)
	{
		cin >> number;
		if (isNumberNumeric() && isNumberRangeCorrect(number, left_range, right_range)) return number;
		else cout << "Что то не так с вводом" << endl;
	}
}