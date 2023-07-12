# Program E-commerce

Program ini merupakan implementasi sederhana dari sistem E-commerce yang memungkinkan pengguna untuk melakukan registrasi, login, membeli produk, menjual produk, top up saldo, dan berinteraksi dengan teman.

## Requirements

- Compiler C++

- **Instalasi Library nlohmann**
1. Buka terminal atau command prompt di sistem Anda.
2. Pastikan Anda memiliki manajer paket C++ yang sesuai diinstal di komputer Anda, seperti Homebrew untuk macOS atau apt-get untuk Linux.
3. Jalankan perintah instalasi paket berikut, sesuaikan dengan manajer paket yang Anda gunakan:
   - Untuk macOS menggunakan Homebrew:
     ```
     brew install nlohmann_json
     ```
   - Untuk Debian atau Ubuntu menggunakan apt-get:
     ```
     sudo apt-get install nlohmann-json3-dev
     ```
   - Untuk distribusi Linux lainnya, Anda dapat menggunakan manajer paket yang sesuai untuk menginstal library nlohmann JSON.
4. Jika Anda menggunakan windows, Anda hanya perlu mendownload repo ini karena sudah terdapat json-develop folder yang berisi library nlohmann. 

- **Instalasi CMake**

1. Kunjungi situs web resmi CMake di https://cmake.org/download/ dan unduh versi terbaru dari CMake (sesuaikan dengan sistem OS Anda).
2. Setelah unduhan selesai, buka file installer CMake (file dengan ekstensi .msi) dan ikuti petunjuk instalasi yang diberikan.
3. Di jendela instalasi, pilih opsi "Add CMake to the system PATH for all users" untuk menambahkan CMake ke PATH sistem.
4. Lanjutkan dengan mengklik tombol "Next" atau "Install" sampai proses instalasi selesai.
5. Setelah proses instalasi selesai, Anda dapat membuka command prompt atau PowerShell dan menjalankan perintah:
   ```
   cmake --version
   ```
   Jika Anda melihat versi CMake yang tercetak di command prompt atau PowerShell, itu berarti CMake telah terinstal dengan sukses.

- Setelah Anda mempunyai ketiga syarat di atas, Anda dapat mendownload repo ini atau clone repo ini. 

- **Kompilasi dan Eksekusi Program dengan CMAKE**
1. Buka terminal atau command prompt di direktori proyek Anda.
2. Jalankan perintah berikut untuk membuat direktori build:
   ```
   cd build
   ```
3. Di dalam direktori `build`, jalankan perintah berikut untuk mengonfigurasi proyek menggunakan CMake:
   ```
   make
   ```
4. Setelah proses kompilasi selesai, Anda dapat menjalankan program dengan menjalankan perintah berikut:
   ```
   ./ecommerce.exe
   ```

## Cara Menggunakan Program

**Opsi 1**
1. Pastikan Anda memiliki semua prasyarat yang disebutkan di atas.
2. Buka file program E-commerce.
3. Compile program menggunakan compiler C++.
4. Jalankan program yang telah dikompilasi.
5. Di menu utama, pilih salah satu opsi berikut:
   - Untuk melakukan registrasi, pilih opsi 1 dan ikuti instruksi yang diberikan.
   - Untuk melakukan login, pilih opsi 2 dan masukkan nama pengguna (username) dan kata sandi (password) yang telah terdaftar sebelumnya.
   - Untuk keluar dari program, pilih opsi 3.
6. Setelah berhasil login, Anda akan diarahkan ke menu utama E-commerce.
7. Di menu utama, Anda dapat memilih opsi berikut:
   - Untuk membeli produk, pilih opsi 1 dan ikuti instruksi yang diberikan. Anda dapat melihat daftar produk, mencari produk berdasarkan kategori, memilih produk untuk dibeli, dan mengatur jumlah pembelian.
   - Untuk melakukan top up saldo, pilih opsi 2 dan masukkan nominal saldo yang ingin Anda tambahkan.
   - Untuk melihat daftar teman, pilih opsi 3 dan ikuti instruksi yang diberikan. Anda dapat melihat daftar teman, menambahkan teman baru, menghapus teman, atau mengirim uang ke teman.
   - Untuk keluar dari akun dan kembali ke menu utama, pilih opsi 4.
8. Setelah keluar dari akun, Anda dapat memilih opsi registrasi atau login kembali untuk menggunakan layanan E-commerce.
9. Untuk keluar dari program, pilih opsi keluar di menu utama.

**Opsi 2**
1. Jika Anda hanya ingin menjalankan program tanpa memperhatikan kode program, ada tidak perlu melaukakan instalasi prasyarat-prasyarat di atas. Akan tetapi, Anda tetap harus mendownload repo ini. Anda dapat masuk ke folder build kemudian cari file bernama `ecommerce.exe`, kemudian run file tersebut.
2. Untuk langkah-langkah saat di dalam program, sama seperti opsi 1.

## Struktur Singkat Program

Program E-commerce terdiri dari beberapa bagian utama:

- File header: `product.h`, `categories.h`, `user.h`, `relationship.h` menyediakan deklarasi kelas, properti, dan method yang digunakan dalam program. Selain itu, terdapat `stdpch.h` yang digunakan untuk me-link library yang dibutuhkan.  
- File src: `product.cpp`, `categories.cpp`, `user.cpp`, `relationship.cpp` menyediakan definisi constructor dan method yang terdapat pada header files. 
- Fungsi `getInputInRange` digunakan untuk memvalidasi input pengguna sesuai dengan rentang yang ditentukan.
- Fungsi-fungsi `loadUsersFromFile`, `saveUsersToFile`, `updateSaldo` digunakan untuk memuat, menyimpan, dan memperbarui data pengguna dari file JSON.
- Fungsi-fungsi `isPasswordStrong`, `isUsernameValid`, `login`, `regist` digunakan untuk validasi kata sandi, validasi username, proses login, dan registrasi pengguna.
- Fungsi-fungsi `printProduk`, `loadProductsFromFile`, `loadProductNamesFromFile`, `saveProductsToFile`, `isAproduct` digunakan untuk mengelola data produk, termasuk tampilan produk, pemrosesan file produk, dan validasi nama produk.
- Fungsi-fungsi `loadRelationshipsFromFile`, `saveRelationshipsToFile`, `Menuteman` digunakan untuk memuat, menyimpan, dan mengelola data relasi teman pengguna.
- Fungsi-fungsi `tampilan_pembeli`, `tampilan_penjual` digunakan untuk menampilkan menu dan tampilan terkait dengan peran pengguna sebagai pembeli atau penjual.
- Fungsi `main` merupakan titik masuk utama program, yang mengatur alur program dan memanggil fungsi-fungsi yang sesuai.

## File Data

Program menggunakan tiga file JSON untuk menyimpan data pengguna, data produk, dan data relasi teman:

- `user_data.json`: File ini berisi informasi pengguna yang telah terdaftar, termasuk nama, kata sandi, peran (pembeli atau penjual), dan saldo. Data pengguna akan dimuat saat program dijalankan dan akan disimpan kembali saat ada perubahan pada data pengguna.
- `product_data.json`: File ini berisi informasi produk yang tersedia, termasuk nama, harga, jumlah, pemilik, dan kategori. Data produk akan dimuat saat program dijalankan dan akan disimpan kembali saat ada perubahan pada data produk.
- `relationship_data.json`: File ini berisi informasi tentang relasi teman antar pengguna. Data relasi teman akan dimuat saat program dijalankan dan akan disimpan kembali saat ada perubahan pada data relasi teman.

Pastikan file-file tersebut ada dan dapat diakses oleh program.

## Kontak

Jika Anda memiliki pertanyaan atau masalah terkait dengan program E-commerce ini, silakan hubungi contact person dibawah.

Email: hajidlutfi@gmail.com
Instagram: @lutfihid_