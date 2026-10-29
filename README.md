# C ile Veri Yapıları ve Algoritmalar (Data Structures & Algorithms in C)

![C](https://img.shields.io/badge/Language-C99%20%2F%20C11-blue.svg)
![Build](https://img.shields.io/badge/Compiler-GCC%20%7C%20Clang%20%7C%20MSVC-informational.svg)
![Status](https://img.shields.io/badge/Status-Completed%20%26%20Tested-brightgreen.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

Bu depo; C programlama dili ile temel **veri yapıları**, **arama & sıralama algoritmaları** ve düşük seviyeli / gömülü sistemler için optimize edilmiş **bellek yönetimi** pratiklerini içermektedir.

Eğitim, pratik ve referans amaçlı hazırlanmış olup; dinamik bellek tahsisinden (`malloc`/`free`) statik havuz tahsisine (`memory pool`), donanım kesmeleri (interrupt) için dairesel kuyruklardan (`ring buffer`) öncelikli kuyruklara (`min-heap`) kadar geniş bir yelpazeyi ele alır.

---

## 📑 İçindekiler

- [Proje Mimarisi ve Dosya Yapısı](#-proje-mimarisi-ve-dosya-yapısı)
- [Modüller ve İçerikleri](#-modüller-ve-i̇çerikleri)
  - [1. Bellek Yönetimi ve Temel Kavramlar](#1-bellek-yönetimi-ve-temel-kavramlar)
  - [2. Doğrusal Veri Yapıları (Linear Data Structures)](#2-doğrusal-veri-yapıları-linear-data-structures)
  - [3. Ağaç ve Öncelikli Veri Yapıları (Trees & Priority Queues)](#3-ağaç-ve-öncelikli-veri-yapıları-trees--priority-queues)
  - [4. Hash ve Tablo Yapıları](#4-hash-ve-tablo-yapıları)
  - [5. Sıralama ve Arama Algoritmaları](#5-sıralama-ve-arama-algoritmaları)
- [Gömülü ve Düşük Seviye Sistem Yaklaşımları](#-gömülü-ve-düşük-seviye-sistem-yaklaşımları)
- [Algoritma Karmaşıklığı (Big-O Complexity)](#-algoritma-karmaşıklığı-big-o-complexity)
- [Derleme ve Çalıştırma Rehberi](#-derleme-ve-çalıştırma-rehberi)
- [Katkıda Bulunma ve Lisans](#-katkıda-bulunma-ve-lisans)

---

## 📂 Proje Mimarisi ve Dosya Yapısı

| Dosya | Açıklama | Başlıca Fonksiyonlar / Özellikler |
|---|---|---|
| [`arrays.c`](arrays.c) | Dizi ve İşaretçi (Pointer) Temelleri | Dizilerin fonksiyona adresle aktarımı, toplam hesabı |
| [`struct.c`](struct.c) | Yapılar (Structs) ve Referansla Erişim | Yapı tanımlama, `.` ve `->` erişimleri, değer güncelleme |
| [`malloc.c`](malloc.c) | Dinamik Bellek Yönetimi | `malloc`, `free`, NULL kontrolü ve dinamik bağlı liste |
| [`memory_pool.c`](memory_pool.c) | Statik Bellek Havuzu (Memory Pool) | Sıfır `malloc` ile sabit boyutlu nesne tahsis mekanizması (`pool allocator`) |
| [`linked_list.c`](linked_list.c) | Temel Bağlı Liste (Stack Memory) | Statik bağlı liste oluşturma ve döngü ile gezinme |
| [`linked_list_and_test.c`](linked_list_and_test.c) | Kapsamlı Dinamik Bağlı Liste & Testler | Ekleme, aradan/baştan/sondan silme ve `assert` test senaryoları |
| [`stack.c`](stack.c) | Yığın (Stack - LIFO) Yapısı | Dizi tabanlı stack; `push`, `pop`, `peek`, doluluk kontrolleri |
| [`ring_buffer.c`](ring_buffer.c) | Dairesel Kuyruk (Circular Queue - FIFO) | Modülo tabanlı ring buffer ve UART interrupt simülasyonu |
| [`trees.c`](trees.c) | İkili Arama Ağacı (Binary Search Tree) | İkili arama, iteratif ekleme, in-order dolaşım, post-order temizleme |
| [`heap.c`](heap.c) | Min-Heap (Öncelikli Kuyruk) | `bubble-up`, `heapify-down`, zamanlayıcı (timer) senaryosu ve testler |
| [`hash_table.c`](hash_table.c) | Hash Tablosu (Açık Adresleme) | Modülo tabanlı hash fonksiyonu ve Doğrusal Yoklama (Linear Probing) |
| [`algorithms.c`](algorithms.c) | Sıralama ve Arama Algoritmaları | Bubble, Insertion, Quick, Heap Sort, Linear ve Binary Search |

---

## 🔍 Modüller ve İçerikleri

### 1. Bellek Yönetimi ve Temel Kavramlar

- **İşaretçiler ve Diziler (`arrays.c`, `struct.c`):**
  - C dilinde dizilerin fonksiyona geçirildiğinde ilk elemanın adresine çözünmesi (decay to pointer).
  - Bellek kopyalaması yapmadan referans üzerinden (`->` operatörü) yapı elemanlarını güncelleme.
- **Dinamik Bellek (`malloc.c`):**
  - Heap belleğinden yer ayırma, NULL işaretçi kontrolleri, `free` sonrası dangling pointer oluşmasını engellemek için işaretçiyi sıfırlama (`p = NULL`).
- **Statik Bellek Havuzu (`memory_pool.c`):**
  - Dinamik tahsisin parçalanma (fragmentation) ve determinizm riskleri taşıdığı gömülü/kritik sistemler için `malloc` yerine statik blok havuz mimarisi.
  - Serbest listesi (`free list`) ile $O(1)$ sürede bellek alma ve iade etme.

### 2. Doğrusal Veri Yapıları (Linear Data Structures)

- **Bağlı Liste (`linked_list.c`, `linked_list_and_test.c`):**
  - Tek yönlü bağlı liste (Singly Linked List).
  - Başa ekleme ($O(1)$), arama ve silme ($O(N)$).
  - Sınır durumları için kapsamlı testler (boş liste, tek eleman, baş/orta/son silme, olmayan değer).
- **Yığın / Stack (`stack.c`):**
  - Son Giren İlk Çıkar (LIFO - Last In First Out).
  - `stack_push`, `stack_pop`, `stack_peek`.
  - Sabit boyutlu dizi üzerinde taşma (overflow) ve yetersizlik (underflow) koruması.
- **Dairesel Kuyruk / Ring Buffer (`ring_buffer.c`):**
  - İlk Giren İlk Çıkar (FIFO - First In First Out).
  - Modülo aritmetiği ile bellek kaydırmaksızın $O(1)$ kuyruğa ekleme ve çıkarma.
  - Mikrodenetleyici UART alma kesmesi (RX Interrupt) kuyruk yönetimi örneği.

### 3. Ağaç ve Öncelikli Veri Yapıları (Trees & Priority Queues)

- **İkili Arama Ağacı (`trees.c`):**
  - Her düğümde küçükler solda, büyükler sağda kuralı.
  - `inorder_yazdir`: Ağacı küçükten büyüğe sıralı dolaşma ($O(N)$).
  - `post_order_agaci_sil`: Çocuk düğümleri kökten önce serbest bırakarak bellek sızıntısını (memory leak) önleme.
- **Min-Heap (`heap.c`):**
  - Kök düğümün her zaman en küçük elemanı barındırdığı tam ikili ağaç mantığı.
  - Dizi üzerinde indis matematiği: Sol çocuk `2*i + 1`, Sağ çocuk `2*i + 2`, Ebeveyn `(i-1)/2`.
  - Zamanlayıcı kuyruğu (Task / Timer Scheduler) kullanım senaryosu ve `assert` doğrulaması.

### 4. Hash ve Tablo Yapıları

- **Hash Tablosu (`hash_table.c`):**
  - Açık Adresleme (Open Addressing) ve Doğrusal Yoklama (Linear Probing).
  - Çakışma durumunda bir sonraki boş göze yerleştirme mantığı.
  - Sabit dizi ile dinamik bellek tahsisine ihtiyaç duymayan hafif mimari.

### 5. Sıralama ve Arama Algoritmaları

- **Algoritmalar Dosyası (`algorithms.c`):**
  - **Bubble Sort:** Erken durdurma (early-exit / `degisti` bayrağı) optimizasyonu ile en iyi durumda $O(N)$.
  - **Insertion Sort:** Küçük veri gruplarında ve neredeyse sıralı dizilerde yüksek verimli araya ekleme.
  - **Quick Sort:** Lomuto bölümleme şeması ile böl-ve-yönet (Divide & Conquer) yaklaşımı ($O(N \log N)$ ortalama).
  - **Heap Sort:** Dizi üzerinde yerinde (in-place) Max-Heap inşa ederek $O(N \log N)$ garantili sıralama.
  - **Linear Search & Binary Search:** Dizi üzerinde $O(N)$ ve sıralı dizide taşma korumalı (`sol + (sag - sol) / 2`) $O(\log N)$ arama.

---

## ⚡ Gömülü ve Düşük Seviye Sistem Yaklaşımları

Bu depodaki kodlar sadece teorik veri yapılarını değil, aynı zamanda pratik sistem programlama prensiplerini de sergiler:
1. **Determinizm ve Fragmantasyon Önleme:** Gömülü sistemlerde `malloc`/`free` çağrılarının getirdiği bellek parçalanması riskini bertaraf eden `memory_pool.c` yaklaşımı.
2. **Interrupt / ISR Uyumluluğu:** Donanım kesmelerinde güvenli veri aktarımı sağlayan kilitlenmesiz `ring_buffer.c` mantığı.
3. **Bellek Güvenliği:** Dinamik ayrılan kaynakların `free` edilip `NULL` ile temizlenmesi ve `assert` tabanlı doğrulama mekanizmaları.
4. **Taşma Koruması:** İkili aramada `(sol + sag) / 2` yerine `sol + (sag - sol) / 2` kullanımı ile aritmetik integer overflow önlemi.

---

## 📊 Algoritma Karmaşıklığı (Big-O Complexity)

| Veri Yapısı / Algoritma | Arama (Ortalama) | Ekleme (Ortalama) | Silme (Ortalama) | Bellek (Alan) |
|---|---|---|---|---|
| **Dizi (Array)** | $O(N)$ | $O(N)$ | $O(N)$ | $O(N)$ |
| **Bağlı Liste (Linked List)** | $O(N)$ | $O(1)$ (Başa) | $O(N)$ | $O(N)$ |
| **Yığın (Stack)** | $O(N)$ | $O(1)$ | $O(1)$ | $O(N)$ |
| **Kuyruk (Ring Buffer)** | $O(N)$ | $O(1)$ | $O(1)$ | $O(N)$ |
| **İkili Arama Ağacı (BST)** | $O(\log N)$ | $O(\log N)$ | $O(\log N)$ | $O(N)$ |
| **Min-Heap** | $O(1)$ (Kök/Peek) | $O(\log N)$ | $O(\log N)$ | $O(N)$ |
| **Hash Tablosu** | $O(1)$ | $O(1)$ | $O(1)$ | $O(N)$ |
| **Binary Search** | $O(\log N)$ | - | - | $O(1)$ |
| **Quick Sort** | - | - | - | $O(\log N)$ |
| **Heap Sort** | - | - | - | $O(1)$ (In-place) |

---

## 🚀 Derleme ve Çalıştırma Rehberi

Dosyalar standart C kütüphaneleri (`stdio.h`, `stdlib.h`, `stdbool.h`, `stdint.h`, `assert.h`) kullanılarak yazılmıştır ve ek bir harici kütüphane gerektirmez.

Herhangi bir GCC, Clang veya MinGW derleyicisi ile çalıştırılabilir:

### Örnek 1: Bağlı Liste Testlerini Çalıştırma
```bash
gcc -Wall -Wextra linked_list_and_test.c -o test_linked_list
./test_linked_list
```

### Örnek 2: Stack Örneğini Çalıştırma
```bash
gcc -Wall -Wextra stack.c -o test_stack
./test_stack
```

### Örnek 3: Dizi ve Struct Örneklerini Çalıştırma
```bash
gcc -Wall -Wextra arrays.c -o test_arrays
./test_arrays

gcc -Wall -Wextra struct.c -o test_struct
./test_struct
```

> **Not:** `algorithms.c`, `hash_table.c` veya `trees.c` gibi kütüphane/fonksiyon şeklinde yazılmış dosyaları kendi `main` fonksiyonunuzu barındıran bir dosyaya dahil ederek (`#include`) veya derleyiciye parametre olarak ekleyerek test edebilirsiniz:
> ```bash
> gcc -Wall -Wextra main.c algorithms.c -o program
> ```

---

## 🛠️ GitHub'a Yükleme (Push) Adımları

Projeyi ilk defa GitHub deponuza göndermek için aşağıdaki adımları terminalde sırasıyla çalıştırabilirsiniz:

```bash
# 1. Git deposunu başlatın (eğer daha önce başlatmadıysanız)
git init

# 2. Tüm dosyaları izlemeye ekleyin
git add .

# 3. İlk commit'i oluşturun
git commit -m "feat: C ile veri yapıları ve algoritmalar uygulamaları"

# 4. Ana dalı 'main' olarak adlandırın
git branch -M main

# 5. GitHub uzaktaki deponuzu ekleyin (kendi repo adresinizi yazın)
git remote add origin https://github.com/KULLANICI_ADINIZ/REPO_ADINIZ.git

# 6. Kodları GitHub'a gönderin
git push -u origin main
```

---

## 📄 Lisans

Bu proje [MIT Lisansı](LICENSE) kapsamında açık kaynak olarak paylaşılmıştır. Dilediğiniz gibi kullanabilir, değiştirebilir ve geliştirebilirsiniz.
