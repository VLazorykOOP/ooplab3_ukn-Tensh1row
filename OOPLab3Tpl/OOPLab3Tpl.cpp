#if !defined(_MSC_VER)
#define CODING_VS_CODE
#endif
#include <iostream>
#include<cassert>
#include <array>
#include <math.h>
#if !defined(CODING_VS_CODE)
#include <clocale>
#endif


using namespace std;

class Square {
private:
	double side;
	unsigned int color;


public:
	void setColor(unsigned int color) {
		assert(color >= 0 && "Color must be greater or equal than 0");
		this->color = color;
	}

	void setSide(double side)
	{
		assert((side > 0) && "side square must be a positive numbers");
		this->side = side;
	}

	unsigned int getColor() {
		return this->color;
	}

	double getSide()
	{
		return side;
	}


	Square() : side(1.0), color(0) {
		cout << endl << "created square with side = 1.0 and color = 0" << endl;
	}

	Square(double side, unsigned int color) {
		assert((side > 0) && "side square must be a positive numbers");
		assert(color >= 0 && "Color must be greater or equal than 0");
		this->side = side;
		this->color = color;
	}

	Square(double side) :Square(side, 0){}

	double area() {
		return side * side;
	}

	double perimeter() {
		return side * 4;
	}


	void showInfoAboutSquare() {
		cout << "--------------------\n\tColor = " << this->color << "\n";
		cout << "\tSide: " << this->side <<
			"\n--------------------\n";
	}


};


int mainExample11() {

	cout << "TASK 1.9 class Rectangle\n";

	cout << endl << "Square square1(3,5);\n";
	Square square1(3,5);

	cout << "square.area()      =  " << square1.area() << "\n";

	cout << "square.perimeter() = " << square1.perimeter() << "\n";

	cout << "Used method : getSide():" << square1.getSide() << endl;

	cout << "Used method : getColor():" << square1.getColor() << endl;

	cout << "Used method : showInfoAboutSquare()\n";
	square1.showInfoAboutSquare();

	cout << endl << "Square squareDefault();\n";
	Square squareDefault;

	cout << "squarDefault.area()      =  " << squareDefault.area() << "\n";

	cout << "squarDefault.perimeter() = " << squareDefault.perimeter() << "\n";

	cout << "Used method : getSide():" << squareDefault.getSide() << endl;

	cout << "Used method : getColor():" << squareDefault.getColor() << endl;

	cout << "Used method : showInfoAboutSquare()\n";
	squareDefault.showInfoAboutSquare();
	return 1;
}

enum STATE {
	OK, ZERO_VECTOR, NEGATIVE_SIZE, BAD_INIT, BAD_DIV, OUT_OF_RANGE
};


class unsignedIntVector {
	unsigned int quantityElements;
	unsigned int* vector;
	int state;
	static int countObject;

public:
	unsignedIntVector() : vector(nullptr), quantityElements(0), state(ZERO_VECTOR) { countObject++; };
	unsignedIntVector(int quantityElements);
	unsignedIntVector(int quantityElements, unsigned int& value);
	unsignedIntVector(int quantityElements, unsigned int* InputVector);
	unsignedIntVector(const unsignedIntVector& copy);
	unsignedIntVector& operator=(const unsignedIntVector& assign);
	~unsignedIntVector() {
		cout << "\n(DESTRUCTOR)delete vector\n";
		if (vector) {
			delete[] vector;
		}
		--countObject;

	}


	void setValueVectorByIndex(int indexVector, const unsigned int& element);
	void output();
	void input();

	long getValueVectorByIndex(int indexVector);
	long countLengthOfTheVector(const unsignedIntVector&);

	bool checkQuantityElements(int quantityElements);
	bool isIndexIncludedVector(int indexVector);
	bool isEmptyVector(const unsignedIntVector* object);


	bool isEqual(const unsignedIntVector&);
	bool isSmaller(const unsignedIntVector&);
	bool isGreater(const unsignedIntVector&);

	unsignedIntVector add(unsignedIntVector& inputVector);
	unsignedIntVector subtract(unsignedIntVector& inputVector);
	unsignedIntVector multiplyVectorOnUnsignedShort(unsigned short number);

	static int getCountObject() {
		return countObject;
	}
};

int unsignedIntVector::countObject = 0;



unsignedIntVector::unsignedIntVector(int quantityElements) {
	if (checkQuantityElements(quantityElements))
	{
		vector = new unsigned int[quantityElements];
		for (int i = 0; i < quantityElements; i++)
		{
			vector[i] = 0;
		}
	}
	countObject++;

	//	fill_n(0, quantityElements, 0);
}

unsignedIntVector::unsignedIntVector(int quantityElements, unsigned int& value) {
	if (checkQuantityElements(quantityElements))
	{
		vector = new unsigned int[quantityElements];
		for (int i = 0; i < quantityElements; i++)
		{
			vector[i] = value;
		}
	}
	countObject++;

}

unsignedIntVector::unsignedIntVector(int quantityElements, unsigned int* inputVector) {
	if (quantityElements <= 0 || (inputVector == nullptr))
	{
		vector = nullptr;
		quantityElements = 0;
		state = ZERO_VECTOR;
		cout << "Vector was not created: quantity <= 0";
	}
	else
	{
		this->quantityElements = quantityElements;
		state = OK;
	}


	vector = new unsigned int[quantityElements];
	for (int i = 0; i < quantityElements; i++)
	{
		vector[i] = inputVector[i];
	}

	countObject++;
}

unsignedIntVector::unsignedIntVector(const unsignedIntVector& inputCopy) {
	this->quantityElements = inputCopy.quantityElements;
	vector = new unsigned int[quantityElements];

	for (int i = 0; i < quantityElements; i++)
	{
		vector[i] = inputCopy.vector[i];
	}

	state = OK;

	countObject++;
}

unsignedIntVector& unsignedIntVector::operator= (const unsignedIntVector& assign) {
	if (quantityElements != assign.quantityElements)
	{
		if (vector)
		{
			delete[] vector;
		}
		quantityElements = assign.quantityElements;
		vector = new unsigned int[quantityElements];
		state = OK;
	}

	for (int i = 0; i < quantityElements; i++)
	{
		vector[i] = assign.vector[i];
	}

	return *this;
}

bool unsignedIntVector::checkQuantityElements(int quantityElements)
{
	if (quantityElements <= 0)
	{
		vector = nullptr;
		this->quantityElements = 0;
		state = ZERO_VECTOR;
		cout << "Vector was not created(nullptr): quantity <= 0";
		return false;
	}
	else
	{
		this->quantityElements = quantityElements;
		state = OK;
		return true;
	}
}

bool unsignedIntVector::isEmptyVector(const unsignedIntVector* object) {
	if (object->quantityElements <= 0)
	{
		cout << "!ERROR: Array is empty\n";
		return true;
	}
	else
	{
		return false;
	}
}

bool unsignedIntVector::isIndexIncludedVector(int indexVector) {
	if ((indexVector >= 0) && (indexVector <= this->quantityElements - 1))
	{
		return true;
	}
	else
	{
		state = OUT_OF_RANGE;
		cout << "!ERROR: Array index is out of range\n";
		return false;
	}
}


bool unsignedIntVector::isEqual(const unsignedIntVector& vec1) {
	return (countLengthOfTheVector(vec1) == countLengthOfTheVector(*this));
}

bool unsignedIntVector::isSmaller(const unsignedIntVector& vec1) {
	return (countLengthOfTheVector(vec1) < countLengthOfTheVector(*this));
}

bool unsignedIntVector::isGreater(const unsignedIntVector& vec1) {
	return (countLengthOfTheVector(vec1) > countLengthOfTheVector(*this));
}


void unsignedIntVector::setValueVectorByIndex(int indexVector, const unsigned int& element)
{
	if (isIndexIncludedVector(indexVector) && !isEmptyVector(this))
	{
		vector[indexVector] = element;
	}
	else
	{
		cout << "Incorrect index\n";
	}

}


void unsignedIntVector::input() {
	if (vector)
	{
		delete[] vector;
	}
	do
	{
		cout << "Input non-zero size the VECTOR:\n";
		cin >> quantityElements;
	} while (quantityElements <= 0);

	vector = new unsigned int[quantityElements];

	for (int i = 0; i < quantityElements; i++)
	{
		cout << "Input a long element the vector[" << i << "]: ";
		cin >> vector[i];
		cout << "\n";
	}
}

long unsignedIntVector::getValueVectorByIndex(int indexVector)
{
	if (isIndexIncludedVector(indexVector) && !isEmptyVector(this))
	{
		return vector[indexVector];
	}
	else
	{
		cout << "Returned 0\n";
		return 0;
	}
}

void unsignedIntVector::output() {
	cout << "Information about vector:\n";
	if (quantityElements != 0)
	{
		for (int i = 0; i < quantityElements; i++)
		{
			cout << "\tElement vector[" << i << "] = " << vector[i] << "\n";
		}
	}
	else
	{
		cout << "\tEmpty vector\n";
	}
}

long unsignedIntVector::countLengthOfTheVector(const unsignedIntVector& vector1) {
	long suma = 0;
	for (int i = 0; i < vector1.quantityElements; i++)
	{
		suma += vector1.vector[i];
	}
	return suma;
}


unsignedIntVector unsignedIntVector::add(unsignedIntVector& inputVector) {
	int leastQuantityOfVectors = quantityElements < inputVector.quantityElements ? quantityElements : inputVector.quantityElements;
	if (leastQuantityOfVectors >= 0)
	{
		unsignedIntVector total(leastQuantityOfVectors);
		total.quantityElements = leastQuantityOfVectors;
		for (int i = 0; i < leastQuantityOfVectors; i++)
		{
			total.vector[i] = vector[i] + inputVector.vector[i];
		}
		return total;
	}
	else
	{
		cout << "Returned empty vector\n";
		return unsignedIntVector(0);
	}
}

unsignedIntVector unsignedIntVector::subtract(unsignedIntVector& inputVector) {
	int leastQuantityOfVectors = quantityElements < inputVector.quantityElements ? quantityElements : inputVector.quantityElements;
	if (leastQuantityOfVectors >= 0)
	{
		unsignedIntVector total(leastQuantityOfVectors);
		for (int i = 0; i < leastQuantityOfVectors; i++)
		{
			total.vector[i] = vector[i] - inputVector.vector[i];
		}
		return total;
	}
	else
	{
		cout << "Returned empty vector\n";
		return unsignedIntVector(0);
	}
}

unsignedIntVector unsignedIntVector::multiplyVectorOnUnsignedShort(unsigned short number)
{
	if (!isEmptyVector(this))
	{
		unsignedIntVector temp(quantityElements);
		for (int i = 0; i < quantityElements; i++)
		{
			temp.vector[i] = vector[i] * number;
		}
		return temp;
	}
	else
	{
		cout << "Returned empty vector\n";
		return unsignedIntVector(0);
	}

}


int mainExample22() {
	cout << "\nTASK 2.9:\n";
	unsigned int value1 = 4;
	unsigned int value2 = 7;

	cout << endl << "unsignedIntVector vector1(3, 4);" << endl;
	unsignedIntVector vector1(3, value1);
	vector1.output();

	cout << endl << "unsignedIntVector vector2(7, 7);" << endl;
	unsignedIntVector vector2(7, value2);
	vector2.output();

	cout << endl << "long long_arr[4] = {32,2,10,2};\nunsignedIntVector vector3(4, long_arr);" << endl;
	unsigned int unsigned_int_arr[4] = { 32,2,10,2 };
	unsignedIntVector vector3(4, unsigned_int_arr);
	vector3.output();

	cout << endl << "unsignedIntVector vectorAdd = vector1.add(vector2);" << endl;
	unsignedIntVector vectorAdd = vector1.add(vector2);
	vectorAdd.output();

	cout << endl << "unsignedIntVector multiply = vector2.multiplyVectorOnUnsignedShort(2);" << endl;
	unsignedIntVector multiply = vector2.multiplyVectorOnUnsignedShort(2);
	multiply.output();

	cout << endl << "vector1.setValueVectorByIndex(2, 23)" << endl;
	vector1.setValueVectorByIndex(2, 23);
	vector1.output();

	cout << endl << "vector1.getValueVectorByIndex(2)" << endl;
	cout << vector1.getValueVectorByIndex(2);

	cout << endl << "count objects : " << unsignedIntVector::getCountObject();
	cout << endl << "vector1.isEqual(vector2);" << endl;
	if (vector1.isEqual(vector2))
	{
		cout << "TRUE";
	}
	else
	{
		cout << "FALSE";
	}

	cout << endl << "vector1.isEqual(vector1);" << endl;
	if (vector1.isEqual(vector1))
	{
		cout << "TRUE";
	}
	else
	{
		cout << "FALSE";
	}


	cout << endl << "vector1.isGreater(vector2);" << endl;
	if (vector1.isGreater(vector2))
	{
		cout << "TRUE";
	}
	else
	{
		cout << "FALSE";
	}


	cout << endl << "vector1.isSmaller(vector2);" << endl;
	if (vector1.isSmaller(vector2))
	{
		cout << "TRUE";
	}
	else
	{
		cout << "FALSE";
	}
	return 1;
}


class VECTOR {
private:
	float x, y, z;
	string state;

public:
	VECTOR() {
		x = 0;
		y = 0;
		z = 0;
	}
	VECTOR(float A) {
		x = A;
		y = A;
		z = A;
	}
	VECTOR(float* Mass) {
		if (Mass == nullptr) {
			state = "ERROR CODE[0001]";
			cout << state << endl;
		}
		else {
			x = Mass[0];
			y = Mass[1];
			z = Mass[2];
		}
	}
	VECTOR(const VECTOR& EX) {
		x = EX.x;
		y = EX.y;
		z = EX.z;
		state = EX.state;
	}


	void showAll() { cout << x << "   " << y << "   " << z << endl; }
	void SSetRand(float a = 10, float b = 3, float c = 7) {
		x = a;
		y = b;
		z = c;
	}
	float GGetRand() {
		int random;
		random = rand() % 100 + 1;

		if (random < 33)return x;
		else if (66 > random > 33) return y;
		else return z;

	}
	void Plus(const VECTOR& other) {
		x = x + other.x;
		y = y + other.y;
		z = z + other.z;
	}
	void Minus(const VECTOR& other) {
		x = x - other.x;
		y = y - other.y;
		z = z - other.z;
	}
	void VProduct(const VECTOR& other) {
		float x1, y1, z1;
		x1 = (y * other.z) - (z * other.y);
		y1 = (x * other.z) - (z * other.x);
		z1 = (x * other.y) - (y * other.x);
		x = x1;
		y = y1;
		z = z1;
	}
	void Deplicate(short int A) {
		float x1, y1, z1;
		if (A != 0) {
			x1 = x / A;
			y1 = y / A;
			z1 = z / A;
			x = x1;
			y = y1;
			z = z1;
		}
		else { state = "ERROR CODE [0002]"; }
		cout << state << endl;
	}
	bool Bilshe(const VECTOR& other) {
		if (x > other.x && y > other.y && z > other.z)return 1;
		else return 0;
	}
	bool Menshe(const VECTOR& other) {
		if (x < other.x && y < other.y && z < other.z)return 1;
		else return 0;
	}
	bool Rivno(const VECTOR& other) {
		if (x == other.x && y == other.y && z == other.z)return 1;
		else return 0;
	}


	VECTOR& operator = (const VECTOR& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		state = other.state;
		return *this;
	}
	~VECTOR() {
		cout << " PbB: " << state << this << endl;
	}
};

class VECT {
private:
	int Namb;
	long* G = nullptr;

public:

	VECT() {

		Namb = 5;
		G = new long[Namb];
		for (int i = 0; i < Namb; i++) { G[i] = 0; }
	}
	VECT(int N) {
		this->Namb = N;
		G = new long[Namb];
		for (int i = 0; i < Namb; i++) { G[i] = 0; }
	}
	int GetNamb() {
		int TEMP1 = this->Namb;
		return TEMP1;
	}

	long* GetPointerG() { return G; }


	void ShowVect() {
		for (int i = 0; i < Namb; i++) { cout << G[i] << " "; }
		cout << endl;
	}
	void InitN(int N) {
		this->Namb = N;
		G = new long[Namb];
		for (int i = 0; i < Namb; i++) { G[i] = 0; }
	}
	void Init1N(int N, double Val) {
		this->Namb = N;
		G = new long[Namb];
		for (int i = 0; i < Namb; i++) { G[i] = Val; }
	}
	void DefaultV(long Element) {
		for (int i = 0; i < Namb; i++) {
			G[i] = Element;
		}
	}
	long ElemByIndV(int i) {
		return G[i];
	}

	~VECT() { delete[] G; }
};

class MATRIX {
private:
	int m;
	VECT* V;
	string state;

public:
	MATRIX() {
		m = 5;
		state = "good";
		V = new VECT[m];
	}
	MATRIX(int N) {
		m = N;
		state = "good";
		V = new VECT[N];
		for (int i = 0; i < N; i++) { V[i].InitN(N); }
	}
	MATRIX(int N, int M, double value) {
		m = N;
		state = "good";
		V = new VECT[N];
		for (int i = 0; i < N; i++) { V[i].Init1N(M, value); }
	}
	MATRIX(const MATRIX& OTHER) {
		m = OTHER.m;
		state = OTHER.state;
		V = new VECT[m];
		for (int i = 0; i < m; i++) { V[i].InitN(OTHER.V[i].GetNamb()); }
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < OTHER.V[i].GetNamb(); j++) {
				//	cout<< OTHER.V[i].GetPointerG()[j]<<endl;
				//	cout << OTHER.V[j].GetNamb() << endl;
				V[i].GetPointerG()[j] = OTHER.V[i].GetPointerG()[j];
			}
		}

	}

	void ShowMatrix() {
		for (int i = 0; i < m; i++) { V[i].ShowVect(); }

	}
	void Default(long Elem) {
		for (int i = 0; i < m; i++) {
			V[i].DefaultV(Elem);
		}
	}
	long ElemByInd(int i, int j) {
		if (i >= m || j >= V[i].GetNamb()) {
			state = "OUT OF THE RANGE";
			cout << state << endl;
			return 0;
		}
		else
		{
			return V[i].ElemByIndV(j);
		}

	}
	void Plus(const MATRIX& OTHER) {
		if (m == OTHER.m && V[0].GetNamb() == OTHER.V[0].GetNamb()) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < OTHER.V[i].GetNamb(); j++) {
					V[i].GetPointerG()[j] += OTHER.V[i].ElemByIndV(j);
				}
			}
		}
		else { state = "NONE EQUAL MATRIX"; }
	}
	void Minus(const MATRIX& OTHER) {
		if (m == OTHER.m && V[0].GetNamb() == OTHER.V[0].GetNamb()) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < OTHER.V[i].GetNamb(); j++) {
					V[i].GetPointerG()[j] -= OTHER.V[i].ElemByIndV(j);
				}
			}
		}
		else { state = "NONE EQUAL MATRIX"; }
	}
	void Multiplication(const MATRIX& OTHER) {
		if (m == OTHER.m && V[0].GetNamb() == OTHER.V[0].GetNamb()) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < OTHER.V[i].GetNamb(); j++) {
					V[i].GetPointerG()[j] *= OTHER.V[i].ElemByIndV(j);
				}
			}
		}
		else { state = "NONE EQUAL MATRIX"; }
	}
	void Div(long F) {
		if (F != 0) {
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < V[i].GetNamb(); j++) {
					V[i].GetPointerG()[j] /= F;
				}
			}
		}
		else { state = "DIV BY ZERO"; }
	}
	bool Bilshe(int a, int b, int c, int d) {
		if (ElemByInd(a, b) > ElemByInd(c, d))return true;
		else
		{
			return false;
		}
	}
	bool Menishe(int a, int b, int c, int d) {
		if (ElemByInd(a, b) < ElemByInd(c, d))return true;
		else
		{
			return false;
		}
	}
	bool Rivne(int a, int b, int c, int d) {
		if (ElemByInd(a, b) == ElemByInd(c, d))return true;
		else
		{
			return false;
		}
	}
	~MATRIX() {
		delete[] V;
	}

};

void mainExample33() {
	float rvariabl;
	float* arrry = nullptr;
	float arrey[]{ 24.5,513.5,63.2 };
	VECTOR Heppy(arrey);
	Heppy.showAll();
	rvariabl = Heppy.GGetRand();
	cout << rvariabl << endl;
	VECTOR Jojo(Heppy), Killa;
	Jojo.showAll();
	Jojo.GGetRand();
	Killa = Jojo;
	Killa.Plus(Jojo);
	Killa.showAll();
	Jojo.SSetRand();
	Killa.VProduct(Jojo);
	Killa.showAll();
	Killa.Minus(Jojo);
	Killa.showAll();
	short int t = 10;
	Killa.Deplicate(t);
	Killa.showAll();
	if (Jojo.Menshe(Heppy)) cout << "yes" << endl;



	cout << endl;
	cout << endl;
	cout << endl;


	MATRIX F, H(6), M(6), K(3, 9, 241), Z(K);
	F.ShowMatrix();
	cout << endl;
	H.ShowMatrix();
	cout << endl;
	K.ShowMatrix();
	cout << endl;
	Z.ShowMatrix();
	cout << endl;
	H.Default(738);
	H.ShowMatrix();
	cout << endl;
	cout << H.ElemByInd(5, 2);
	cout << endl;
	cout << endl;
	M.Default(53);
	H.Plus(M);
	H.ShowMatrix();
	cout << endl;
	M.Default(1533);
	H.Minus(M);
	H.ShowMatrix();
	cout << endl;
	M.Default(-3);
	H.Multiplication(M);
	H.ShowMatrix();
	cout << endl;
	H.Div(3);
	H.ShowMatrix();
	cout << endl;
}

////////////////////////////////////////////////
int main()
{
	std::cout << " Lab #3  !\n";

	mainExample11();
	std::cout << "end task1" << std::endl;

	mainExample22();
	std::cout << "end task2" << std::endl;

	mainExample33();
	std::cout << "end task3" << std::endl;
}

