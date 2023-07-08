// PROGRAM INI MENYIMPAN DATA USER SECARA TEMPORARY SEHINGGA JIKA SUDAH REGISTER NAMUN TERMINAL TERTUTUP/EXIT, MAKA HARUS REGISTER ULANG
#include "../header/product.h"
#include "../header/categories.h"
#include "../header/user.h"

const std::string TOKO = "EZMart";

// Input handling function
void getInputInRange(int minValue, int maxValue, int &choice) {
    bool isValidInput = false;

    while (!isValidInput) {
        std::cin >> choice;

        if (choice >= minValue && choice <= maxValue) {
            isValidInput = true;
            while (std::cin.get() != '\n'); // clear buffer input
        } else {
            std::cout << "Invalid input. Coba lagi: " << std::endl;
            std::cin.clear(); // Clear error flags
            while (std::cin.get() != '\n'); // clear buffer input
        }
    }
}
bool regist(User &user, std::map<std::string, User*> &users);


bool login(User &user, std::map<std::string, User*> &users) {
    int choice;
    std::string name;
    std::string password;
    std::cout << "name: ";
    std::cin >> name;
    std::cout << "Password: ";
    std::cin >> password;
    user.setName(name);
    user.setPassword(password);

    if (users.count(user.getName()) == 1) {
        std::cout << "Selamat Anda sudah login!";
        // Inisiasi variable current user
        user.setSaldo(users[user.getName()]->getSaldo()); // Inisiasi saldo user menggunakan data dari database
        user.setIs_pembeli(users[user.getName()]->getIs_pembeli()); // inisiasi pembeli/penjual user menggunakan data dari database
        return true;
    } else {
        // Handle jika user belum terdaftar
        std::cout << "Anda belum terdaftar!\nSIlahkan register(1) atau kembali ke homepage(2): ";
        getInputInRange(1, 2, choice);
        if (choice == 1) {
            regist(user, users);
            return true;
        }
        return false;
    }

}

bool regist(User &user, std::map<std::string, User*> &users) {
    int choice;
    std::string name;
    std::string password;
    while (true) {
        // Prompt data user
        std::cout << "name: ";
        std::cin >> name;
        std::cout << "Password: ";
        std::cin >> password;
        user.setName(name);
        user.setPassword(password);
        if (users.count(user.getName()) == 1){
            // Handle jika terdapat name conflict
            std::cout << "User dengan name tersebut telah terdaftar!\nSilahkan login(1) atau kembali ke homepage(2): ";
            getInputInRange(1, 2, choice);
            if (choice == 1) {
                login(user, users);
                return true;
            }
            return false;
        }
        std::cout << "Pembeli(1)/Penjual(2)?";
        getInputInRange(1, 2, choice);
        if (choice == 1) {
            user.setIs_pembeli(true);
            break;
        } else if (choice == 2) {
            user.setIs_pembeli(false);
            break;
        } 
    }
    
    // Memasukkan data user ke database
    users[user.getName()] = &user;
    std::cout << "Selamat Anda sudah register!";

    return true;
}

void logout(User &user, std::map<std::string, User*> &users) {
    // update saldo user pada database
    users[user.getName()]->setSaldo(user.getSaldo());
    // Reset current user
    user = User("", "", false, 0);
}

void printProduk(std::map<std::string, Product*> &semua_produk) {
    std::cout <<  std::left <<  std::setw(10) << "KODE" << " | "<< std::left << std::setw(20) << "NAMA" << " | "
    << std::left << std::setw(11) << "HARGA" << " | " << "JUNLAH" << std::endl;
    for (auto it = semua_produk.begin(); it != semua_produk.end(); ++it) {
        std::cout << std::left << std::setw(10) << it->first << " | "
                << std::left << std::setw(20) << it->second->getName() << " | "
                << "Rp" << std::left << std::setw(6) << it->second->getPrice() << "000 | "
                << it->second->getQuantity() << std::endl;
    }
}

void tampilan_pembeli(User &user, std::map<std::string, User*> &users, std::map<std::string, Product*> &semua_produk, Categories categories) {
    int choice;
    int topupsaldo;
    int jumlah;
    std::string kode;
    
    // Clear screen with ANSI
    std::cout << "\033[2J\033[1;1H";
    std::cout << "\nSelamat datang di E-commerce Customer " << user.getName();
    // Main loop
    while (true) {
        // Main menu customer
        std::cout << "\nSaldo Anda Sekarang = Rp" << user.getSaldo() << "000";
        std::cout << "\n\nMENU\n 1. Belanja\n 2. Top up saldo\n 3. Log out\n";
        // Kembali ke home page jika == 3
        getInputInRange(1,3, choice);
        
        // Menu belanja
        if (choice == 1) {
            int choiceBelanja;
            
            // All product or by category
            std::cout << "\n1. Tampilkan semua Produk\n2. Cari berdasarkan kategory\n";
            getInputInRange(1,2, choiceBelanja);

            // jika by category
            if (choiceBelanja == 2) {
                categories.printAllcategories();

                std::string kode;
                std::cout << "Silahkan masukan kode dari kategory yang ingin anda cari: ";
                std::cin >> kode;
                std::cout << "Berikut adalah produk yang tersedia saat ini: \n";
                // printing product
                bool check = categories.printProductbyCategory(kode);

                // if there's no product in check
                if (!check) continue;
            } else { // jika all
                std::cout << "Berikut adalah produk yang tersedia saat ini: \n";
                printProduk(semua_produk);
            }

            // Menanyakan barang yang akan dibeli
            std::cout << "\nApakah ada yang ingin ada beli?(Masukan kode barang, jika tidak -> ketik tidak)";
            std::cin >> kode;

            // Jika barang ditemukan
            if (semua_produk.count(kode) == 1){
                std::cout << "\nJumlah yang ingin anda beli: ";
                getInputInRange(1, static_cast<int>(semua_produk[kode]->getQuantity()), jumlah);
                if (user.getSaldo() < semua_produk[kode]->getPrice() * jumlah) {
                    std::cout << "Saldo Anda tidak mencukupi!";
                } else {
                    // Jika saldo mencukupi
                    user.setSaldo(user.getSaldo() - semua_produk[kode]->getPrice() * jumlah) ; // Mengurangi saldo jika saldo mencukupi
                    // Jika barang habis di database
                    if (semua_produk[kode]->getQuantity() - jumlah == 0) {
                        categories.deleteProduct(semua_produk[kode], semua_produk[kode]->getCategory());
                        semua_produk.erase(kode); // menghapus barang dari database
                    } else {
                        // Jika tidak maka stok/quantity dikurangi
                        semua_produk[kode]->setQuantity(semua_produk[kode]->getQuantity() - jumlah);
                        categories.setQuantity(semua_produk[kode], semua_produk[kode]->getCategory(), semua_produk[kode]->getQuantity() - jumlah);
                    }
                   
                    // Menambah saldo seller jika barang yang dibeli dari seller bukan toko
                    if (semua_produk[kode]->getOwner() != TOKO) {
                        users[semua_produk[kode]->getOwner()]->setSaldo(users[semua_produk[kode]->getOwner()]->getSaldo() + semua_produk[kode]->getPrice() * jumlah);
                    }
                }
            } else if (kode == "tidak"){
                continue;
            } else {
                std::cout << "Kode barang tidak ditemukan!\n";
            }

        // Menu topup
        } else if (choice == 2) {
            std::cout << "Masukan nominal saldo yang anda ingin topup(ribu, mis: 15 -> 15 ribu, min 10 ribu max 10 juta): ";
            getInputInRange(10, 10000, topupsaldo);
            user.setSaldo(user.getSaldo() + topupsaldo);
        // Kembali ke menu utama
        } else if (choice == 3) {
            // Logout
            logout(user, users);
            break;
        } 
    }
    
}

void tampilan_penjual(User &user, std::map<std::string, User*> &users, std::map<std::string, Product*> &semua_produk, Categories categories) {
    int choice;
    int jumlah;
    std::string name_barang;
    double price;
    std::string kode;
    std::string kategori;

    // Clear screen with ANSI
    std::cout << "\033[2J\033[1;1H";
    std::cout << "\nSelamat datang di E-commerce Seller " << user.getName();
    // Main loop
    while (true) {
        // Main menu customer
        std::cout << "\n\nMENU\n 1. List produk\n 2. Jualan\n 3. Lihat saldo\n 4. Kembali ke menu utama\n";
        // Kembali ke home page jika == 3
        getInputInRange(1,4, choice);
        // Menu belanja
        if (choice == 1) {
            int choiceBelanja;
            // All product or by category
            std::cout << "\n1. Tampilkan semua Produk\n2. Cari berdasarkan kategory\ninput: ";
            getInputInRange(1,2, choiceBelanja);

            // jika by category
            if (choiceBelanja == 2) {
                categories.printAllcategories();

                std::string kode;
                std::cout << "Silahkan masukan kode dari kategory yang ingin anda cari: ";
                std::cin >> kode;
                std::cout << "Berikut adalah produk yang tersedia saat ini: \n";
                categories.printProductbyCategory(kode); 
            } else { // jika all
                std::cout << "Berikut adalah produk yang tersedia saat ini: \n";
                printProduk(semua_produk);
            }

        // Menu topup
        } else if (choice == 2) {
            int choicejual;
            std::cout << "1. Jual barang baru\n2. Tambah/kurang jumlah barang Anda\ninput: ";
            getInputInRange(1, 2, choicejual);
            if (choicejual == 1) {
                // Prompt data barang
                std::cout << "Masukkan data barang yang akan Anda jual\n";
                std::cout << "name: ";
                std::cin >> name_barang;
                std::cout << "Harga(ribu): ";
                std::cin >> price;
                std::cout << "Jumlah barang: ";
                std::cin >> jumlah;

                categories.printAllcategories();            
                std::cout << "Kategori(Masukkan kode): ";
                std::cin >> kategori;

                // Memasukan data barang ke database
                Product *barang_baru = new Product(name_barang, price, jumlah, user.getName(), kategori);
                semua_produk[barang_baru->getCode()] = barang_baru;
                categories.addProduct(kategori, barang_baru);
            } else {
                std::cout << "Masukkan data barang Anda\n";
                std::cout << "name: ";
                std::cin >> name_barang;
                std::cout << "Kode:  ";
                std::cin >> kode;

                std::cout << "Masukkan jumlah quantity baru";
                std::cin >> jumlah;

                semua_produk[kode]->setQuantity(jumlah);
                categories.setQuantity(semua_produk[kode], semua_produk[kode]->getCategory(), jumlah);
            }

        } else if (choice == 3) {
            std::cout << "Saldo Anda: Rp" << user.getSaldo() << "000\n";
        } else {
            return;
        }
        
    }
}

int main() {
    std::map<std::string, Product*> semua_produk;
    std::map<std::string, std::vector<Product*>> categorytoProduct;
    std::map<std::string, User*> users; // sebagai temporary database yang menyimpan user
    User *user = new User("", "", true, 0);
    Categories *categories = new Categories();
    // Inisiasi produk 
    Product *susu = new Product("Susu", 50, 10, TOKO, "FB");
    Product *indomie = new Product{"Indomie", 3, 100, TOKO, "FB"};
    Product *laptop = new Product{"laptop", 10000, 5, TOKO, "E"};
    Product *buku = new Product{"Buku", 100, 20, TOKO, "OS"};
    Product *kipas_angin = new Product{"Kipas Angin", 200, 15, TOKO, "E"};
    Product *boneka = new Product{"Boneka", 150, 25, TOKO, "TG"};

    // Save ke database
    semua_produk[susu->getCode()] = susu;
    semua_produk[indomie->getCode()] = indomie;
    semua_produk[laptop->getCode()] = laptop;
    semua_produk[buku->getCode()] = buku;
    semua_produk[kipas_angin->getCode()] = kipas_angin;
    semua_produk[boneka->getCode()] = boneka;

    categories->addProduct(susu->getCategory(), susu);
    categories->addProduct(indomie->getCategory(), indomie);
    categories->addProduct(laptop->getCategory(), laptop);
    categories->addProduct(buku->getCategory(), buku);
    categories->addProduct(kipas_angin->getCategory(), kipas_angin);
    categories->addProduct(boneka->getCategory(), boneka);

    while (true) {
        int choice;
        // Clear screen with ANSI
        std::cout << "\033[2J\033[1;1H";

        // Main menu program
        std::cout << "\nSelamat datang di E-commerce " << TOKO << "!\n";
        std::cout << "Silahkan register(1) atau login(2) untuk menggunakan layanan atau quit(3): ";
        getInputInRange(1, 3, choice);
        // Register
        if (choice == 1){
            // 
            if(!regist(*user, users)){
                continue;
            };
        }
        // Login
        else if (choice == 2){
            // Kembali ke menu utama jika login gagal
            if(!login(*user, users)) {
                continue;
            }
        // Quit note: database akan reset jika quit   
        } else {
            return 0;
        }

        if (user->getIs_pembeli() == true) {
            tampilan_pembeli(*user, users, semua_produk, *categories);
        } else {
            tampilan_penjual(*user, users, semua_produk, *categories);
        }

    }
    return 0;
}