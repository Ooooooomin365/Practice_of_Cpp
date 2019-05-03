#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

class Application {
protected:
	double _value = 0;  //計算結果の初期値は0とする。
public:
	double x, y;
	Application();
	void _Add(double a, double b);
	void _Sub(double a, double b);
	void _Mul(double a, double b);
	void _Div(double a, double b);
};

Application::Application() : _value(0) {}

void Application::_Add(double a, double b) {
	cout << "足したい2つの数字を入力してください。" << endl;
	cin >> a >> b;
	_value = a + b;
	cout << "計算結果:" << _value << endl;
}

void Application::_Sub(double a, double b) {
	cout << "引きたい2つの数字を入力してください。" << endl;
	cin >> a >> b;
	_value = a - b;
	cout << "計算結果:" << _value << endl;
}

void Application::_Mul(double a, double b) {
	cout << "かけたい2つの数字を入力してください。" << endl;
	cin >> a >> b;
	_value = a * b;
	cout << "計算結果:" << _value << endl;
}

void Application::_Div(double a, double b) {
	cout << "割りたい2つの数字を入力してください。" << endl;
	cin >> a >> b;
	_value = a / b;
	cout << "計算結果:" << _value << endl;
}

void _luck() {
	int x;
	try {
		cout << "今日の運勢を占います。1～9の中から好きな数字を入力してください...";
		cin >> x;
		if (x < 1 || x > 9)
			throw 1;

		vector<string> _Komoku = { "大吉です","中吉です","やばいです","外に出ない方がいいです","超大凶です。一日ゆっくり休みましょう。" };
		random_shuffle(_Komoku.begin(), _Komoku.end());  //コンテナをシャッフル
		cout << _Komoku[0] << endl;  //シャッフルしたコンテナの最初の文を取り出す
	}
	catch (int) {
		cout << "入力した数値が不正です。1～9の中から選んでください！" << endl;
	}
}

int menu() {
	int _Select_menu[1];
	cout << "次の中から利用したいものを選んでください。" << endl;
	cout << "***** 1:計算機 2:今日の運勢 3:今月のお小遣いチェック 4:お小遣い新規登録（月初） 0:終了 *****" << endl;
	cin >> _Select_menu[0];
	return(_Select_menu[0]);
}

int _Calcmenu() {
	int _Select_Calc[1];
	cout << "***** 1:足し算 2:引き算 3:かけ算 4:わり算 0:終了 *****" << endl;
	cin >> _Select_Calc[0];
	return(_Select_Calc[0]);
}

//計算結果
void _Calcresult() {
	Application _App;
	int _Select;
	bool _loop = false;

	while (!_loop) {
		_Select = _Calcmenu();
		switch (_Select) {
		case 0:
			_loop = true;
			break;

		case 1:
			_App._Add(_App.x, _App.y);
			break;

		case 2:
			_App._Sub(_App.x, _App.y);
			break;

		case 3:
			_App._Mul(_App.x, _App.y);
			break;

		case 4:
			_App._Div(_App.x, _App.y);
			break;

		default:
			cout << "入力が不正ですお" << endl;
			break;

		}
		if (_loop)
			break;  //0を入力するとswitch文から抜ける
	}
}

class Kodukai {
protected:
	int _Restmoney[1]; //残金を保管する配列を用意
public:
	void income(int x);
	void pay(int x);
	void _Display_Restmoney();
	void _Display();
	void ShinkiKodukai();
};

void Kodukai::_Display() {
	ifstream _open("Text.txt");  //ファイル読み取り
	int _p;
	int _i;

	if (!_open) {
		cerr << "ファイルをオープンできません。" << endl;
		return;
	}

	string _Ko;
	string a = "";  //文字を読み込む際に初期値は空白にする。
	while (getline(_open,_Ko)) {
		a = a + _Ko;  //string型としてセーブした価格を読み取る。
	}
	_Restmoney[0] = atoi(a.c_str());  //string型として読み取った価格をint型へ

	cout << "あなたの今月のお小遣いは" << _Restmoney[0] << "円です。" << endl;
	cout << "昨日はいくら使いましたか？....";
	cin >> _p;
	cout << "昨日の収入はいくらでしたか？....";
	cin >> _i;
	cout << "残金:" << _Restmoney[0] - _p + _i << "円" << endl;

	ofstream _save;  //ファイル書き込み
	_save.open("Text.txt", ios_base::trunc);
	_save << _Restmoney[0] - _p + _i << endl; //残金を上書き保存する。
	_save.close();
}

void Kodukai::ShinkiKodukai() {
	int _newK;

	cout << "今月のお小遣いを設定してください...";
	cin >> _newK;

	ofstream _Shinkisave;
	_Shinkisave.open("Text.txt", ios_base::trunc);
	_Shinkisave << _newK << endl;
	_Shinkisave.close();
}

int main() {
	Application _App;
	Kodukai _k;
	int n;
	bool _loop = false;

	while (!_loop) {
		n = menu();
		switch (n) {
		case 0:
			_loop = true;
			break;

		case 1:
			_Calcresult();
			break;

		case 2:
			_luck();
			break;

		case 3:
			_k._Display();
			break;

		case 4:
			_k.ShinkiKodukai();
			break;

		default:
			cout << "入力が不正ですyo" << endl;
			break;

		}

		if (_loop)
			break;
	}
	return 0;
}
