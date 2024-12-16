# PURRMART

PURRMART adalah aplikasi C yang mensimulasikan permainan pasar di mana pengguna dapat mendaftar, masuk, bekerja untuk mendapatkan uang, membeli barang, dan berpartisipasi dalam berbagai tantangan seperti permainan Wordle dan mini-game coding.

## Struktur Direktori

- **.gitignore**: Menentukan file yang sengaja tidak di-_commit_ oleh git.
- **.vscode**: Berisi file konfigurasi Visual Studio Code.
  - `c_cpp_properties.json`
  - `settings.json`
- **bin**: Berisi file biner yang sudah dikompilasi dan skrip build.
  - `main.exe`
  - `Makefile`
- **build**: Direktori untuk file output build.
- **data**: Berisi file data yang digunakan oleh aplikasi.
  - `config.txt`
  - `savefile.txt`
  - `words.txt`
- **docs**: Dokumentasi terkait proyek.
  - `Form Asistensi Tugas Besar.docx`
  - `IF2111_TB_YY_XX.docx`
  - `Pedoman Tugas Besar.docx`
  - `Pembagian Kelompok Tugas Besar IF2111 Algoritma dan Struktur Data STI 2024_2025.xlsx`
  - `Spesifikasi Tugas Besar 1 IF2111 2024_2025.docx`
- **include**: Berisi file header untuk proyek.
  - `ADT/`: Header Tipe Data Abstrak (misalnya, `array.h`)
  - `features/`: Header untuk implementasi fitur.
- **Makefile**: Alat otomatisasi build untuk mengkompilasi proyek.
- **README.md**: Deskripsi proyek dan instruksi.
- **src**: Berisi file kode sumber.
  - `ADT/`: Implementasi tipe data abstrak.
  - `features/`: Implementasi fitur seperti permainan dan utilitas.
- **tests**: Driver pengujian untuk berbagai modul.
  - `driver_list.c`
  - `driver_mesinkarakter.c`

## Penjelasan File Utama

**File Sumber (`src` direktori):**

- `main.c`: File program utama yang menjalankan aplikasi.
- `misc.c`: Berisi fungsi utilitas yang digunakan di seluruh proyek.
- `mesinkarakter.c`: Implementasi mesin karakter untuk pemrosesan input.
- `mesinkata.c`: Implementasi mesin kata untuk pemrosesan rangkaian karakter.
- `queue.c`: Implementasi struktur data antrean.
- `list.c`: Implementasi struktur data daftar.
- `wordl32.c`: Implementasi fitur permainan Wordle.
- `rng.c`: Implementasi fitur generator angka acak.
- `qwordl3.c`: Implementasi fitur permainan Quantum Wordle.
- `DNA.c`: Implementasi fitur bonus tambahan.

**File Header (`include` direktori):**

- `ADT`: File header untuk tipe data abstrak.
- `features`: File header untuk implementasi fitur.

**File Data (`data` direktori):**

- `config.txt`: Pengaturan konfigurasi untuk aplikasi.
- `savefile.txt`: Data simpan untuk progres pengguna.
- `words.txt`: Daftar kata yang digunakan dalam permainan Wordle.

**Dokumentasi (`docs` direktori):**

- Berbagai file `.docx` dan `.xlsx` yang berisi spesifikasi proyek, panduan, dan pembagian kelompok.

**Makefile:**

- Berisi instruksi build untuk mengkompilasi proyek menggunakan perintah `make`.

**Driver Pengujian (`tests` direktori):**

- `driver_list.c`: Driver pengujian untuk modul daftar.
- `driver_mesinkarakter.c`: Driver pengujian untuk modul mesin karakter.

## Cara Menjalankan Kode

Untuk mengkompilasi dan menjalankan aplikasi, jalankan perintah berikut di terminal:

```bash
gcc -I include src/features/main.c src/features/misc.c src/ADT/mesinkarakter.c src/ADT/mesinkata.c src/ADT/queue.c src/ADT/list.c src/features/wordl32.c src/features/rng.c src/features/qwordl3.c src/features/DNA.c -o main
