#include "../header/product.h"
#include "../header/categories.h"
#include "../header/user.h"
#include "../header/relationship.h"


const std::string TOKO = "EZMart";
const std::string FILENAME = "user_data.json";
const std::string FILENAMEP = "product_data.json";
const std::string FILENAMER = "relationship_data.json";

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

std::map<std::string, User*> loadUsersFromFile() {
    std::map<std::string, User*> users;

    std::ifstream file(FILENAME);
    if (file.is_open()) {
        nlohmann::json userData;
        file >> userData;
        file.close();

        for (const auto& [username, userJson] : userData.items()) {
            std::string name = userJson["name"];
            std::string password = userJson["password"];
            bool is_pembeli = userJson["is_pembeli"];
            double saldo = userJson["saldo"];

            User *user = new User(name, password, is_pembeli, saldo);
            users.emplace(username, user);
        }
    }

    return users;
}

void saveUsersToFile(std::map<std::string, User*> &users, User &user) {
    nlohmann::json userData;
    for (auto& [key, user] : users) {
        userData[user->getName()] = user->toJson();
    }

    std::ofstream file(FILENAME);
    file << userData.dump(4);  
    file.close();
}

void updateSaldo(const std::string& username, double newSaldo) {
    std::ifstream file(FILENAME);
    if (file.is_open()) {
        nlohmann::json userData;
        file >> userData;
        file.close();

        if (userData.contains(username)) {
            // Update the saldo
            userData[username]["saldo"] = newSaldo;

            // Save the modified user data back to the JSON file
            std::ofstream outFile(FILENAME);
            outFile << userData.dump(4);  
            outFile.close();

        } else {
            std::cout << "User not found." << std::endl;
        }
    } else {
        std::cout << "Failed to open the file." << std::endl;
    }
}


bool regist(User &user, std::map<std::string, User*> &users);

bool isPasswordStrong(const std::string& password) {
    // Cek panjang
    bool isValid = true;
    if (password.length() < 8) {
        std::cout << "Minimal panjang password adalah 8!\n";
        return false;
    }

    // Check huruf kecil
    if (!std::regex_search(password, std::regex("[a-z]"))) {
        isValid = false;
    }

    // Check kapital
    if (!std::regex_search(password, std::regex("[A-Z]"))) {
        isValid = false;
    }

    // Check angka
    if (!std::regex_search(password, std::regex("[0-9]"))) {
        isValid = false;
    }

    // Password passed all checks
    if (isValid) {
        return isValid;
    } else {
        std::cout << "Password harus memiliki setidaknya 1 huruf kecil, 1 huruf kapital, dan 1 angka!\n";
        return isValid;
    }
}

bool isUsernameValid(const std::string& username) {
    bool isValid = true;
    if (username.length() < 4) {
        std::cout << "Panjang minimal username adalah 4!\n";
    }
    // Cek kapital
    if (std::regex_search(username, std::regex("[A-Z]"))) {
        isValid = false;
    }

    // Cek symbol
    if (std::regex_search(username, std::regex("[!@#$%^&*]"))) {
        isValid = false;
    }

    if (isValid) {
        return isValid;
    } else {
        std::cout << "Username tidak boleh mengandung huruf kapital atau simbol!\n";
        return isValid;
    }
}

bool login(User &user, std::map<std::string, User*> &users) {
    int choice;
    std::string name;
    std::string password;

    std::cout << "Username: ";
    std::cin >> name;

    // cek nama
    if (users.count(name) != 1) {
        // Handle jika user belum terdaftar
        std::cout << "Anda belum terdaftar!\nSIlahkan register(1) atau kembali ke homepage(2): ";
        getInputInRange(1, 2, choice);
        if (choice == 1) {
            regist(user, users);
            return true;
        }
        return false;  
    } 
    
    // cek password match
    while (true) {
        std::cout << "Password: ";
        std::cin >> password;
        if (users[name]->getPassword() != password) {
            std::cout << "Password salah!\n";
        } else {
            break;
        }
    }

    user.setName(name);
    user.setPassword(password);

    // Inisiasi variable current user
    user.setSaldo(users[name]->getSaldo()); // Inisiasi saldo user menggunakan data dari database
    user.setIs_pembeli(users[name]->getIs_pembeli()); // inisiasi pembeli/penjual user menggunakan data dari database

    std::cout << "Selamat Anda sudah login!";
    return true;

}

bool regist(User &user, std::map<std::string, User*> &users) {
    int choice;
    std::string name;
    std::string password;
    bool is_pembeli = false;

    // Prompt data user
    while (true) {
        std::cout << "Username: ";
        std::cin >> name;
        if (isUsernameValid(name)) {
            break;
        }
    }
    while (true) {
        std::cout << "Password: ";
        std::cin >> password;
        if (isPasswordStrong(password)) {
            break;
        }
    }
    
    user.setName(name);
    user.setPassword(password);
    if (users.count(user.getName()) > 0){
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
        is_pembeli = true;
    } else if (choice == 2) {
        user.setIs_pembeli(false);
    } 
    user.setSaldo(0);

    // membuat json user
    nlohmann::json jsonData = user.toJson();
    // menambahkan ke file user_data.json
    std::ofstream file(FILENAME);
    file << jsonData.dump(4); 
    file.close();

    std::cout << "Account created successfully! User data saved to user_data.json" << std::endl;
    
    // Memasukkan data user ke database

    users[user.getName()] = &user;
    std::cout << "Selamat Anda sudah register!";

    return true;
}

void logout(User *user, std::map<std::string, User*> &users) {
    // update saldo user pada database
    users[user->getName()]->setSaldo(user->getSaldo());
    // variable
    delete user;
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

std::map<std::string, Product*> loadProductsFromFile() {
    std::map<std::string, Product*> products;

    std::ifstream file(FILENAMEP);
    if (file.is_open()) {
        nlohmann::json productData;
        file >> productData;
        file.close();

        for (const auto& [code, productJson] : productData.items()) {
            std::string name = productJson["name"];
            double price = productJson["price"];
            int quantity = productJson["quantity"];
            std::string owner = productJson["owner"];
            std::string category = productJson["category"];

            Product* product = new Product{name, price, quantity, owner, category};
            products.emplace(product->getCode(), product);
        }
    }

    return products;
}

std::set<std::string> loadProductNamesFromFile() {
    std::set<std::string> productNames;

    std::ifstream file(FILENAMEP);
    if (file.is_open()) {
        nlohmann::json productData;
        file >> productData;
        file.close();

        for (const auto& [code, productJson] : productData.items()) {
            std::string name = productJson["name"];
            productNames.insert(name);
        }
    } else {
        std::cout << "Failed to open the file." << std::endl;
    }

    return productNames;
}

void saveProductsToFile(const std::map<std::string, Product*>& products) {
    nlohmann::json productData;
    for (const auto& [code, product] : products) {
        productData[code] = product->toJson();
    }

    std::ofstream file(FILENAMEP);
    file << productData.dump(4);  
    file.close();
}

bool isAproduct(const std::set<std::string>& namaProducts, std::string nama) {
    return namaProducts.find(nama) != namaProducts.end();
}

void loadRelationshipsFromFile(Relationship& relationships) {
    std::ifstream file(FILENAMER);
    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << FILENAMER << std::endl;
        return;
    }

    try {
        nlohmann::json jsonData;
        file >> jsonData;

        for (const auto& [user, friends] : jsonData.items()) {
            for (const auto& friendName : friends) {
                relationships.addFriend(user, friendName);
            }
        }

    } catch (const nlohmann::json::exception& e) {
        std::cout << "Error occurred while parsing JSON: " << e.what() << std::endl;
    }

    file.close();
}

void saveRelationshipsToFile(const Relationship& relationships) {
    nlohmann::json jsonData;

    for (const auto& [user, friends] : relationships.getAdjacencyList()) {
        jsonData[user] = friends;
    }

    std::ofstream file(FILENAMER);
    if (!file.is_open()) {
        std::cout << "Failed to open the file: " << FILENAMER << std::endl;
        return;
    }

    try {
        file << jsonData.dump(4);  
    } catch (const nlohmann::json::exception& e) {
        std::cout << "Error occurred while generating JSON: " << e.what() << std::endl;
    }

    file.close();
}

void Menuteman(User &user, std::map<std::string, User*> &users, Relationship &relationship) {
     while (true) {
        int choiceTeman;
        std::cout << "\n\nMenu friends\n";
        std::cout << " 1. Lihat daftar teman\n 2. Tambah teman\n 3. Hapus teman\n 4. Kirim uang ke teman\n 5. Kembali\ninput: ";
        getInputInRange(1, 5, choiceTeman);
        if (choiceTeman == 1) {
            relationship.printFriends(user.getName());
        } else if (choiceTeman == 2) {
            std::string username;
            std::cout << "Masukkan username orang yang ingin ditambah\ninput: ";
            std::cin >> username;
            if (relationship.areFriends(user.getName(), username)){
                std::cout<< "Username sudah ada di daftar teman!\n";
                continue;
            }
            relationship.addFriend(user.getName(), username);
            saveRelationshipsToFile(relationship);
        } else if (choiceTeman == 3) {
            std::string username;
            std::cout << "Masukkan username teman Anda yang ingin dihapus\ninput: ";
            std::cin >> username;
            relationship.deleteFriend(user.getName(), username);
            saveRelationshipsToFile(relationship);
        } else if (choiceTeman == 4) {
            std::string username;
            double nominal;
            std::cout << "Masukkan username teman Anda\ninput: ";
            std::cin >> username;
            if (!relationship.areFriends(user.getName(), username)){
                std::cout << "Username tidak ada di daftar teman\n";
                continue;
            }
            std::cout << "Masukan nominal(ribu)\ninput: ";
            std::cin >> nominal;
            if (nominal > user.getSaldo()) {// jika saldo kurang
                std::cout << "Saldo Anda tidak mencukupi\n";
                continue;
            }
            users[username]->setSaldo(users[username]->getSaldo() + nominal); // menambah saldo teman
            updateSaldo(username, users[username]->getSaldo());
            user.setSaldo(user.getSaldo() - nominal); // mengurangi saldo user
            users[user.getName()]->setSaldo(user.getSaldo());
            updateSaldo(user.getName(), user.getSaldo());
        } else {
            break;
        }
    }
}

void tampilan_pembeli(User &user, std::map<std::string, User*> &users, std::map<std::string, Product*>&semua_produk, Categories categories, Relationship &relationship) {
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
        std::cout << "\n\nMENU\n 1. Belanja\n 2. Top up saldo\n 3. Friend list\n 4. Log out\ninput: ";
        // Kembali ke home page jika == 3
        getInputInRange(1,4, choice);
        
        // Menu belanja
        if (choice == 1) {
            int choiceBelanja;
            
            // All product or by category
            std::cout << "\n1. Tampilkan semua Produk\n2. Cari berdasarkan kategori\n3. Kembali\ninput: ";
            getInputInRange(1,3, choiceBelanja);

            // jika by category
            if (choiceBelanja == 2) {
                categories.printAllcategories();

                std::string kodeKategory;
                while (true) {
                    std::cout << "Silahkan masukan kode dari kategori yang ingin anda cari: ";
                    std::cin >> kodeKategory;
                    if (categories.isCategory(kodeKategory)) {
                        break;
                    } else {
                        std::cout << "Kode kategori tidak valid!\n";
                    }

                }
    
                std::cout << "Berikut adalah produk yang tersedia saat ini: \n";
                // printing product
                Product *product = new Product(); // dibuat hanya untuk search
                product->printByCategory(semua_produk, kodeKategory);
                delete product;
            // opsi belannja 2
            } else if (choiceBelanja == 1) { // jika all
                std::cout << "Berikut adalah produk yang tersedia saat ini: \n";
                printProduk(semua_produk);
            } else {
                continue;
            }

            // Menanyakan barang yang akan dibeli
            std::cout << "\nApakah ada yang ingin ada beli?(Masukan kode barang, jika tidak -> ketik tidak)\ninput: ";
            std::cin >> kode;

            // Jika barang ditemukan
            if (semua_produk.count(kode) == 1){
                std::cout << "\nJumlah yang ingin anda beli: ";
                getInputInRange(1, static_cast<int>(semua_produk[kode]->getQuantity()), jumlah);
                if (user.getSaldo() < semua_produk[kode]->getPrice() * jumlah) {
                    std::cout << "Saldo Anda tidak mencukupi!";
                } else {
                    // Jika saldo mencukupi
                    // Mengurangi saldo jika saldo mencukupi
                    double newSaldo = user.getSaldo() - semua_produk[kode]->getPrice() * jumlah;
                    user.setSaldo(newSaldo); 
                    updateSaldo(user.getName(), newSaldo);
                    // Jika barang habis di database
                    if (semua_produk[kode]->getQuantity() - jumlah == 0) {
                        semua_produk.erase(kode); // menghapus barang dari database
                    } else {
                        // Jika tidak maka stok/quantity dikurangi
                        int quantity = semua_produk[kode]->getQuantity() - jumlah;
                        semua_produk[kode]->setQuantity(quantity);
                        saveProductsToFile(semua_produk);
                    }
                   
                    // Menambah saldo seller jika barang yang dibeli dari seller bukan toko
                    if (semua_produk[kode]->getOwner() != TOKO) {
                        double newSaldo = users[semua_produk[kode]->getOwner()]->getSaldo() + semua_produk[kode]->getPrice() * jumlah;
                        users[semua_produk[kode]->getOwner()]->setSaldo(newSaldo);
                        updateSaldo(semua_produk[kode]->getOwner(), newSaldo);
                    }
                }
            } else if (kode == "tidak"){
                continue;
            } else {
                std::cout << "Kode barang tidak ditemukan!\n";
            }

        // Menu topup
        } else if (choice == 2) {
            std::cout << "Masukan nominal saldo yang anda ingin topup(ribu, mis: 15 -> 15 ribu, min 10 ribu max 10 juta)\ninput: ";
            getInputInRange(10, 10000, topupsaldo);
            // update saldo
            int newSaldo = user.getSaldo() + topupsaldo;
            user.setSaldo(newSaldo);
            updateSaldo(user.getName(), newSaldo);
        // Kembali ke menu utama
        } else if (choice == 3) {
            Menuteman(user, users, relationship);
        } else {
            // Logout
            logout(&user, users);
            break;
        } 
    }
    
}

void tampilan_penjual(User &user, std::map<std::string, User*> &users, std::map<std::string, Product*> &semua_produk, Categories categories, std::set<std::string> &namaProduk, Relationship &relationship) {
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
        std::cout << "\n\nMENU\n 1. List produk\n 2. Jualan\n 3. Lihat saldo\n 4. Hapus produk\n 5. Friend list\n 6. logout\ninput: ";
        // Kembali ke home page jika == 3
        getInputInRange(1,6, choice);
        // Menu belanja
        if (choice == 1) {
            int choice1;
            // All product or by category
            std::cout << "\n1. Tampilkan semua Produk\n2. Cari berdasarkan kategori\n3. List produk Anda\n4. Kembali\ninput: ";
            getInputInRange(1,4, choice1);

            // jika by category
            if (choice1 == 2) {
                categories.printAllcategories();
                std::string kodeKategory;

                while (true) {
                    std::cout << "Silahkan masukan kode dari kategori yang ingin anda cari: ";
                    std::cin >> kodeKategory;
                    if (categories.isCategory(kodeKategory)) {
                        break;
                    } else {
                        std::cout << "Kode kategori tidak valid!\n";
                    }

                }
                
                std::cout << "Berikut adalah produk yang tersedia saat ini: \n";
                // printing product
                Product *product = new Product(); // dibuat hanya untuk search
                product->printByCategory(semua_produk, kodeKategory);
                delete product;
            } else if (choice1 == 1){ // jika all
                std::cout << "Berikut adalah produk yang tersedia saat ini: \n";
                printProduk(semua_produk);
            } else if (choice1 == 3) { // list produk yang dijual user
                std::map<std::string, Product*> result;
                for (auto &pair : semua_produk) {
                    if (pair.second->getOwner() == user.getName()) {
                        result.insert(pair);
                    }
                }
                printProduk(result);
            } else { // kembali
                continue;
            }

        // Menu jualan
        } else if (choice == 2) {
            int choicejual;
            std::cout << "1. Jual barang baru\n2. Tambah/kurang jumlah barang Anda\n3. Kembali\ninput: ";
            getInputInRange(1, 3, choicejual);
            // opsi jualan
            if (choicejual == 1) {
                // Prompt data barang
                std::cout << "Masukkan data barang yang akan Anda jual\n";
                while (true) {
                    std::cout << "Nama: ";
                    std::getline(std::cin, name_barang);
                    if (isAproduct(namaProduk, name_barang)) {
                        std::cout << "Barang dengan nama ini sudah ada!\n";
                    } else {
                        break;;
                    }
                }
                
                std::cout << "Harga(ribu): ";
                std::cin >> price;
                std::cout << "Jumlah barang: ";
                std::cin >> jumlah;
                categories.printAllcategories();
                while (true) {
                    std::cout << "Kode Kategori: ";
                    std::cin >> kategori;
                    if (categories.isCategory(kategori)) {
                        break;
                    } else {
                        std::cout << "Kode kategori tidak valid!\n";
                    }
                }        
                
                // Memasukan data barang ke database
                Product *barang_baru = new Product(name_barang, price, jumlah, user.getName(), kategori);
                semua_produk[barang_baru->getCode()] = barang_baru;
                saveProductsToFile(semua_produk);

                std::cout << "Produk berhasil ditambahkan!\n";
            // opsi jualan
            } else if (choicejual == 2) {
                std::cout << "Masukkan data barang Anda\n";
                std::cout << "Nama: ";
                std::cin >> name_barang;
                std::cout << "Kode: ";
                std::cin >> kode;
                if (semua_produk.count(kode) != 0) {
                    std::cout << "Produk Anda:\n";
                    semua_produk[kode]->printProduct();
                    std::cout << "Masukkan jumlah quantity baru: ";
                    std::cin >> jumlah;

                    semua_produk[kode]->setQuantity(jumlah);
                    saveProductsToFile(semua_produk);       
                    std::cout << "Quantity Berhasil diubah\n";             
                } else {
                    std::cout << "Produk tidak ditemukan!\n";
                }
            // opsi jualan
            } else {
                continue;
            }
        // Menu Lihat saldo
        } else if (choice == 3) {
            std::cout << "Saldo Anda: Rp" << user.getSaldo() << "000\n";
        // menu hapus produk
        } else if (choice == 4) {
                std::cout << "Masukkan kode produk-produk yang ingin anda hapus(max 5 per operasi)\n";
                std::vector<std::string> codeProduct(5);
                int i = 0;
                std::cout << "Ketik 'tidak' jika sudah\n";
                while (true) {
                    std::cin >> codeProduct[i];
                    if (codeProduct[i] == "tidak") {
                        break;
                    } else if (semua_produk.count(codeProduct[i]) == 0) {
                        std::cout << "Kode produk tidak valid\n";
                    } else {
                        i++;
                    }

                }
                for (auto &code : codeProduct) {
                    semua_produk.erase(code);
                }
                std::cout << "Berhasil dihapus!\n";
        // Menu relationship 
        } else if (choice == 5) {
            Menuteman(user, users, relationship);
        } else {
            logout(&user, users);
            break;
        }
        
    }
}

int main() {
    std::map<std::string, Product*> semua_produk = loadProductsFromFile(); // database untuk menyimpan data produk
    std::set<std::string> namaProduk = loadProductNamesFromFile(); // database untuk menyimpan nama produk
    std::map<std::string, User*> users = loadUsersFromFile(); // database untuk menyimpan user
    Categories *categories = new Categories(); // menyimpan nama nama kategori
    Relationship *relationship = new Relationship(); // menyimpan relasi / friends user
    loadRelationshipsFromFile(*relationship);


    while (true) {
        User *user = new User("", "", true, 0); // current user
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
            } else {
                saveUsersToFile(users, *user);
            }
        }
        // Login
        else if (choice == 2){
            // Kembali ke menu utama jika login gagal
            if(!login(*user, users)) {
                continue;
            }
        } else {
            delete categories;
            delete user;
            delete relationship;
            return 0;
        }

        if (user->getIs_pembeli()) {
            tampilan_pembeli(*user, users, semua_produk, *categories, *relationship);
        } else {
            tampilan_penjual(*user, users, semua_produk, *categories, namaProduk, *relationship);
        }

    }
    return 0;
}