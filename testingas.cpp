#include <vector>
#include <limits>
#include <algorithm>
#include <string>
#include <sys/time.h>
#include <iostream>

using std::cout;

template <class T>
   class Vector {
    public: // interfeisas
      typedef T* iterator;
      typedef const T* const_iterator;
      typedef size_t size_type;
      typedef T value_type;
      // rule of three
      Vector() { create(); }
      explicit Vector(size_type n, const T& t = T{}) { create(n, t); }
      Vector(const Vector& v) { create(v.begin(), v.end()); }

      Vector& operator=(const Vector&);
      ~Vector() { uncreate(); }

      T& operator[](size_type i) { return data[i]; }
      const T& operator[](size_type i) const { return data[i]; }
      void push_back(const T& t) {
        if (avail == limit)
          grow();
        unchecked_append(t);
      }

      size_type size() const { return avail - data; }
      size_type capacity() const { return limit - data; }
      iterator begin() { return data; }
      const_iterator begin() const { return data; }
      iterator end() { return avail; }
      const_iterator end() const { return avail; }


    // likusi interfeiso realizacija
    private:
      iterator data; // pakeista iš T* į iterator
      iterator avail; // pirmasis po paskutiniojo sukonstruoto Vector elementas
      iterator limit; // pakeista iš T* į iterator

      // atminties išskyrimo valdymui
      std::allocator<T> alloc; // objektas atminties valdymui
      // išskirti atmintį (array) ir ją inicializuoti
      void create();
      void create(size_type, const T&);
      void create(const_iterator, const_iterator);
      // sunaikinti elementus array ir atlaisvinti atmintį
      void uncreate();
      // pagalbinės funkcijos push_back realizacijai
      void grow();
      void unchecked_append(const T&);
};

template <class T>
  void Vector<T>::create() {
    data = avail = limit = nullptr;
  }
template <class T>
  void Vector<T>::create(size_type n, const T& val) {
    data = alloc.allocate(n); // grąžina ptr į array pirmą elementą
    limit = avail = data + n; // sustato rodykles į vietas
    std::uninitialized_fill(data, limit, val); // inicializuoja elementus val reikšme
  }
template <class T>
  void Vector<T>::create(const_iterator i, const_iterator j) {
    data = alloc.allocate(j - i); // išskirti vietos j-i elementams
    limit = avail = std::uninitialized_copy(i, j, data); // nukopijuoja elementus iš intervalo
  }

template <class T>
  void Vector<T>::uncreate() {
    if (data) {
    // sunaikinti (atbuline tvarka) sukonstruotus elementus
      iterator it = avail;
      while (it != data)
        alloc.destroy(--it);
      // atlaisvinti išskirtą atmintį. Turi būti data != nullptr
      alloc.deallocate(data, limit - data);
    }
    // reset'inam pointer'iuss - Vector'ius tuščias
    data = limit = avail = nullptr;
  }

template <class T>
  void Vector<T>::grow() {
    // dvigubai daugiau vietos, nei buvo
    size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));
    // išskirti naują vietą ir perkopijuoti egzistuojančius elementus
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    // atlaisvinti seną vietą
    uncreate();
    // reset'int rodykles į naujai išskirtą vietą
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
  }
// tariame, kad `avail` point'ina į išskirtą, bet neinicializuotą vietą
template <class T>
  void Vector<T>::unchecked_append(const T& val) {
    alloc.construct(avail++, val);
  }

// priskyrimo operatoriaus realizacija
template <class T>
  Vector<T>& Vector<T>::operator=(const Vector& rhs) {
    // patikriname ar ne lygu
    if (&rhs != this) {
    // atlaisviname seną this objekto atmintį
      uncreate();
      // perkopijuojame elementus iš rhs į lhs (this)
      create(rhs.begin(), rhs.end());
    }
    return *this;
  }

template<class T> class allocator {
  public:
    T* allocate(size_t); // išskirti `raw` atmintį
    void deallocate(T*, size_t); // atlaisvinti atmintį
    void construct(T*, const T&); // sukonstruoti 1 objektą
    void destroy(T*); // sunaikinti 1 objektą
};

int main ()
{
    //1 uzduotis: Vector pavyzdines funkcijos
    cout << "Ijungiamos pavyzdines funkcijos..\n";
    std::string a;
    Vector<double> i;
    cout << "Vector i dydis: " << i.size() << "\n";
    cout << "Vector i capacity: " << i.capacity() << "\n";
    cout << "Vector i pradzios adresas: " << i.begin() << "\n";
    cout << "Vector i pabaigos adresas: " << i.end() << "\n";
    cout << "Pridedama reiksmiu i konteineri i: {5,78,21,21.22,6.88}\n";
    i.push_back(5);
    i.push_back(78);
    i.push_back(21);
    i.push_back(21.22);
    i.push_back(6.88);
    cout << "Spausdinamos pridetos reiksmes: ";
    for(auto k : i){
        cout << k << " ";
    }
    cout << "\n";
    cout << "Vector i dydis: " << i.size() << "\n";
    cout << "Vector i capacity: " << i.capacity() << "\n";
    cout << "Vector i pradzios adresas: " << i.begin() << "\n";
    cout << "Vector i pabaigos adresas: " << i.end() << "\n";
    cout << "Kuriamas naujas Vector h, kuris turi 20 ketvertu..\n";
    Vector<double> h(20,4);
    cout << "Sukurta. Tikrinama..\n";
    for(auto k : h){
        cout << k << " ";
    }
    cout << "\n";
    cout << "Vector h prilyginamas Vector'iui i..\n";
    h = i;
    cout << "Tikrinama..\n";
    for(auto k : h){
        cout << k << " ";
    }
    cout << "\n";
    cout << "Vector h dydis: " << h.size() << "\n";
    cout << "Vector h capacity: " << h.capacity() << "\n";
    cout << "Vector h pradzios adresas: " << h.begin() << "\n";
    cout << "Vector h pabaigos adresas: " << h.end() << "\n";
    cout << "Antroji uzduotis: std::vector ir Vector lyginimas..\n";
    // 2 uzduotis: efektyvumo analize - std::vector ir Vector
    unsigned int sz = 100000000;  // 100000, 1000000, 10000000, 100000000
    clock_t start, end;
    cout << "Dydis: " << sz << ".. Pildoma (std::vector)..\n";
    start = clock();
    std::vector<int> v1;
    for (int i = 1; i <= sz; ++i)
        v1.push_back(i);
    end = clock();
    double diff = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Uzpildyta per: " << diff << "\n";

    // Pradėti v2 užpildymo laiko matavimą
    start = clock();
    Vector<int> v2;
    cout << "Dydis: " << sz << ".. Pildoma (Vector)..\n";
    for (int i = 1; i <= sz; ++i)
        v2.push_back(i);
        // Baigti v2 užpildymo laiko matavimą
    end = clock();
    diff = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Uzpildyta per: " << diff << "\n";

    return 0;
}
