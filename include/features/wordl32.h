#ifndef WORDL3_H
#define WORDL3_H

#include "../ADT/boolean.h"
#include "../ADT/mesinkarakter.h"
#include "../ADT/mesinkata.h"

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 5

extern char board[MAX_ATTEMPTS][WORD_LENGTH * 3 + 1];

void evaluateGuess(const char *target, Word guess, char *result);
/* Mengevaluasi tebakan terhadap kata target.
 * I.S :
 * - `target` adalah kata target yang valid dalam bentuk string null-terminated.
 * - `guess` adalah tebakan pengguna dalam bentuk struktur Word.
 * - `result` adalah array karakter kosong dengan ukuran minimal WORD_LENGTH * 3 + 1.
 *
 * F.S.:
 *   - `result` diisi dengan hasil evaluasi tebakan, berupa:
 *   - Huruf yang benar di posisi yang tepat diikuti spasi (' ').
 *   - Huruf yang benar di posisi yang salah ditandai dengan '*'.
 *   - Huruf yang salah ditandai dengan '%'.
 */

boolean isValidGuess(Word guess);
/* Memvalidasi apakah tebakan memiliki panjang kata yang sesuai.
 *
 * I.S.:
 * - `guess` adalah struktur Word yang merepresentasikan tebakan pengguna.
 *
 * F.S.:
 * - Mengembalikan TRUE jika panjang tebakan (`guess.Length`) sama dengan WORD_LENGTH.
 * - Mengembalikan FALSE jika tidak.
 */

boolean compareWords(const char *target, Word guess, int LENGTH);
/* Membandingkan kata target dan tebakan pengguna untuk kesamaan.
 * I.S.:
 * - `target` adalah string null-terminated dengan panjang WORD_LENGTH.
 * - `guess` adalah tebakan pengguna dalam bentuk struktur Word.
 *
 * F.S.:
 * - Mengembalikan TRUE jika `target` dan `guess` identik.
 * - Mengembalikan FALSE jika berbeda.
 */

//void INITIALIZED_WORDL3(char ***wordsList, int *wordCount);

void playWordl3(int *money);
/* Fungsi utama untuk memainkan permainan Wordl3.
 *
 * I.S.:
 * - File "words.txt" tersedia dan berisi daftar kata dengan panjang WORD_LENGTH.
 * - Permainan belum dimulai, papan permainan kosong, dan pemain belum melakukan tebakan.
 *
 * F.S.:
 * - Pemain telah menyelesaikan permainan dalam batasan jumlah tebakan (MAX_ATTEMPTS).
 * - Jika pemain berhasil menebak kata target, permainan berakhir dengan kemenangan.
 * - Jika pemain kehabisan tebakan, permainan berakhir dengan kekalahan, dan jawaban yang benar ditampilkan.
 * - Semua memori yang dialokasikan secara dinamis telah dibebaskan.
 */

#endif 
