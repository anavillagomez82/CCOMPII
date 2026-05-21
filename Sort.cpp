#include <iostream>
#include <chrono>
#include <random>

using namespace std;
//////////////////////////////
// VERSION 1: NORMAL
//////////////////////////////

void mergeNormal(int arr[], int inicio, int medio, int fin) {
	int n1 = medio - inicio + 1;
	int n2 = fin - medio;
	
	int* L = new int[n1];
	int* R = new int[n2];
	
	for (int i = 0; i < n1; i++)
		L[i] = arr[inicio + i];
	
	for (int j = 0; j < n2; j++)
		R[j] = arr[medio + 1 + j];
	
	int i = 0, j = 0, k = inicio;
	
	while (i < n1 && j < n2) {
		if (L[i] <= R[j])
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}
	
	while (i < n1)
		arr[k++] = L[i++];
	
	while (j < n2)
		arr[k++] = R[j++];
	
	delete[] L;
	delete[] R;
}

void mergeSortNormal(int arr[], int inicio, int fin) {
	if (inicio < fin) {
		int medio = inicio + (fin - inicio) / 2;
		
		mergeSortNormal(arr, inicio, medio);
		mergeSortNormal(arr, medio + 1, fin);
		
		mergeNormal(arr, inicio, medio, fin);
	}
}

//////////////////////////////
// VERSION 2: POLIMORFISMO
//////////////////////////////

class Comparador {
public:
	virtual bool comparar(int a, int b) = 0;
	virtual ~Comparador() {}
};

class Ascendente : public Comparador {
public:
	bool comparar(int a, int b) override {
		return a <= b;
	}
};

void mergePoli(int arr[], int inicio, int medio, int fin, Comparador* comp) {
	int n1 = medio - inicio + 1;
	int n2 = fin - medio;
	
	int* L = new int[n1];
	int* R = new int[n2];
	
	for (int i = 0; i < n1; i++)
		L[i] = arr[inicio + i];
	
	for (int j = 0; j < n2; j++)
		R[j] = arr[medio + 1 + j];
	
	int i = 0, j = 0, k = inicio;
	
	while (i < n1 && j < n2) {
		if (comp->comparar(L[i], R[j]))
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}
	
	while (i < n1)
		arr[k++] = L[i++];
	
	while (j < n2)
		arr[k++] = R[j++];
	
	delete[] L;
	delete[] R;
}

void mergeSortPoli(int arr[], int inicio, int fin, Comparador* comp) {
	if (inicio < fin) {
		int medio = inicio + (fin - inicio) / 2;
		
		mergeSortPoli(arr, inicio, medio, comp);
		mergeSortPoli(arr, medio + 1, fin, comp);
		
		mergePoli(arr, inicio, medio, fin, comp);
	}
}

//////////////////////////////
// VERSION 3: PUNTERO A FUNCION
//////////////////////////////

bool ascendente(int a, int b) {
	return a <= b;
}

void mergeFunc(int arr[], int inicio, int medio, int fin,
			   bool (*comparar)(int, int)) {
	
	int n1 = medio - inicio + 1;
	int n2 = fin - medio;
	
	int* L = new int[n1];
	int* R = new int[n2];
	
	for (int i = 0; i < n1; i++)
		L[i] = arr[inicio + i];
	
	for (int j = 0; j < n2; j++)
		R[j] = arr[medio + 1 + j];
	
	int i = 0, j = 0, k = inicio;
	
	while (i < n1 && j < n2) {
		if (comparar(L[i], R[j]))
			arr[k++] = L[i++];
		else
			arr[k++] = R[j++];
	}
	
	while (i < n1)
		arr[k++] = L[i++];
	
	while (j < n2)
		arr[k++] = R[j++];
	
	delete[] L;
	delete[] R;
}
			   
void mergeSortFunc(int arr[], int inicio, int fin,
	bool (*comparar)(int, int)) {
				   
		if (inicio < fin) {
		 int medio = inicio + (fin - inicio) / 2;
					   
			mergeSortFunc(arr, inicio, medio, comparar);
			mergeSortFunc(arr, medio + 1, fin, comparar);
					   
			mergeFunc(arr, inicio, medio, fin, comparar);
				   }
			   }
//////////////////////////////
// VERSION 4: TEMPLATES
//////////////////////////////
template <class T>
struct CLess {
 bool operator()(const T& a, const T& b) const {
		return a <= b;
}
};
								  
template <class T, class Compare>
void mergeTemplate(T arr[], int inicio, int medio,
	int fin, const Compare& op)
{
									  int n1 = medio - inicio + 1;
									  int n2 = fin - medio;
									  
									  T* L = new T[n1];
									  T* R = new T[n2];
									  
									  for (int i = 0; i < n1; i++)
										  L[i] = arr[inicio + i];
									  
									  for (int j = 0; j < n2; j++)
										  R[j] = arr[medio + 1 + j];
									  
									  int i = 0, j = 0, k = inicio;
									  
									  while (i < n1 && j < n2) {
										  if (op(L[i], R[j]))
											  arr[k++] = L[i++];
										  else
											  arr[k++] = R[j++];
									  }
									  
									  while (i < n1)
										  arr[k++] = L[i++];
									  
									  while (j < n2)
										  arr[k++] = R[j++];
									  
									  delete[] L;
									  delete[] R;
								  }
								  
								  template <class T, class Compare>
									  void mergeSortTemplate(T arr[], int inicio,
															 int fin, const Compare& op)
								  {
									  if (inicio < fin) {
										  
										  int medio = inicio + (fin - inicio) / 2;
										  
										  mergeSortTemplate(arr, inicio, medio, op);
										  mergeSortTemplate(arr, medio + 1, fin, op);
										  
										  mergeTemplate(arr, inicio, medio, fin, op);
									  }
								  }
									  //////////////////////////////
									  // MAIN
									  //////////////////////////////
									  
									  int main() {
										  
										  const int n = 50000;
										  
										  int* arr1 = new int[n];
										  int* arr2 = new int[n];
										  int* arr3 = new int[n];
										  int* arr4 = new int[n];
										  
										  // Generador moderno de números aleatorios
										  random_device rd;
										  mt19937 gen(rd());
										  uniform_int_distribution<> dist(0, 99999);
										  
										  for (int i = 0; i < n; i++) {
											  int num = dist(gen);
											  
											  arr1[i] = num;
											  arr2[i] = num;
											  arr3[i] = num;
											  arr4[i] = num;
										  }
										  
										  chrono::high_resolution_clock::time_point inicio, fin;
										  
										  double t_normal, t_poli, t_func, t_template;
										  
										  // 1. NORMAL
										  inicio = chrono::high_resolution_clock::now();
										  
										  mergeSortNormal(arr1, 0, n - 1);
										  
										  fin = chrono::high_resolution_clock::now();
										  
										  t_normal = chrono::duration<double, milli>(fin - inicio).count();
										  
										  // 2. POLIMORFISMO
										  Comparador* compPoli = new Ascendente();
										  
										  inicio = chrono::high_resolution_clock::now();
										  
										  mergeSortPoli(arr2, 0, n - 1, compPoli);
										  
										  fin = chrono::high_resolution_clock::now();
										  
										  t_poli = chrono::duration<double, milli>(fin - inicio).count();
										  
										  delete compPoli;
										  
										  // 3. FUNCION
										  inicio = chrono::high_resolution_clock::now();
										  
										  mergeSortFunc(arr3, 0, n - 1, ascendente);
										  
										  fin = chrono::high_resolution_clock::now();
										  
										  t_func = chrono::duration<double, milli>(fin - inicio).count();
										  
										  // 4. TEMPLATE
										  CLess<int> compTemplate;
									
										  inicio = chrono::high_resolution_clock::now();
										  
										  mergeSortTemplate(arr4, 0, n - 1, compTemplate);;
										  
										  fin = chrono::high_resolution_clock::now();
										  
										  t_template = chrono::duration<double, milli>(fin - inicio).count();
										  
										  // RESULTADOS
										  cout << "================================================\n";
										  cout << "COMPARATIVA DE TIEMPOS (N = " << n << ")\n";
										  cout << "================================================\n";
										  
										  cout << "1. Normal:             " << t_normal   << " ms\n";
										  cout << "2. Polimorfismo:       " << t_poli     << " ms\n";
										  cout << "3. Puntero funcion:    " << t_func     << " ms\n";
										  cout << "4. Templates:          " << t_template << " ms\n";
										  
										  cout << "================================================\n";
										  
										  delete[] arr1;
										  delete[] arr2;
										  delete[] arr3;
										  delete[] arr4;
										  
										  return 0;
									  }
